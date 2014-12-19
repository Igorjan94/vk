#include "vk.h"
#include <cstdlib>

using namespace std;

#define pb push_back
#define ll long long
#define forit(it, r) for (auto it = r.begin(); it != r.end(); it++)
#define forn(i, n) for (int i = 0; i < n; ++i)
#define forn1(i, n) for (int i = 1; i < n; ++i)
#define FOR(i, m, n) for (int i = m; i < n; ++i)
#define ROF(i, m, n) for (int i = m; i >= n; --i)
#define fori(n) for (int i = 0; i < n; ++i)
#define forj(n) for (int j = 0; j < n; ++j)

string Vk::itoa(int i, int base = 10)
{
    string s;
    int k;
    while (i >= base)
        k = i % base,
        s.pb(k > 9 ? k + 'A' - 10 : k + 48),
        i /= base;
    k = i % base;
    s.pb(k > 9 ? k + 'A' - 10 : k + 48);
    reverse(s.begin(), s.end());
    return s;
}

string Vk::convert(string s)
{
    ret.clear();
    fori(s.size())
        if (i < s.size() - 1 && s[i] == '\\' && (s[i + 1] == 'n' || s[i + 1] == -47))
        {
            ret.append("%0A");
            i += 1 + (s[i + 1] == -47);//-47 -- russian t, because has the same place with n (\n == \t_russian)
        }
        else
            ret.append("%" + itoa((s[i] + 256) % 256, 16));
    return ret;
}

void Vk::setUrls()
{
    sendMessage = "https://api.vk.com/method/messages.send?v=5.24&access_token=" + key +  (user_id < 100 ? "&chat_id=" : "&user_id=") + itoa(user_id) + "&message=";
    getMessages = "https://api.vk.com/method/messages.getHistory?v=5.24&access_token=" + key +
            (user_id < 100 ? "&chat_id=" : "&user_id=") + itoa(user_id) + "&count=";
    markAsRead  = "https://api.vk.com/method/messages.markAsRead?peer_id=" + itoa(user_id) + "&access_token=" + key;
}

Json::Value Vk::jsonByUrl(string url, bool f = false)
{
    int i = 0;
    if (f)
    {
        while (eventLoop[i + 4].isRunning())
            i = (i + 1) % (pool / 2);
        i += 4;
    }
    else
        while (eventLoop[i].isRunning())
            i = (i + 1) % (pool / 2);
    root[i].clear();
    req[i].setUrl(QUrl( QString(url.data()) ));
    reply[i] = mgr[i].get(req[i]);
    eventLoop[i].exec();
    if (reply[i]->error() != QNetworkReply::NoError)
        qDebug() << reply[i]->errorString();

    if (!reader[i].parse(reply[i]->readAll().data(), root[i]))
        printf("%s %s\n", "Failed to parse configuration\n", reader[i].getFormatedErrorMessages().data());
    return root[i];
}

void Vk::unread()
{
//    cout << "in unread\n";
    auto x = jsonByUrl(getUnreadMessages, true)["response"];
    if (x["count"].asInt() == 0)
        return;
    for (auto y : x["items"])
    {
        int t = y["message"]["user_id"].asInt();
        if (!(y["message"]["chat_id"].isObject() && y["message"].isMember("chat_id")))
            t = y["message"]["chat_id"].asInt();
        if (indexes.count(t) != 0)
        {
            int f = y["unread"].asInt();
            if (indexes[t] == currentUser)
            {
                run(f - focused[currentUser], true);
                focused[currentUser] = f;
                continue;
            }
        }
        cout << "unread from " << t << "\n";
        cout.flush();
    }
}

void Vk::fromBackup()
{
    ifstream file("database");
    int i = 0;
    string s;
    if (file)
        while (getline(file, s))
        {
            int j = 0;
            while (s[j] <= '9' && s[j] >= '0')
                j++;
            QString temp(s.substr(j + 1).data());
            names.pb(temp);
            j = atoi(s.substr(0, j).data());
            mp[temp] = j;
            indexes[j] = i;
            ++i;
        }
}

void Vk::run(int c, bool f = false)
{
    if (counter++ % 1000 == 0)
        qDebug() << counter;
    items.clear();
    items = jsonByUrl(getMessages + itoa(c), f)["response"]["items"];
    int j = items.size();
    fori(j)
        pairs[currentUser][i] = items[i]["body"].asString();
    fori(j)
    {
        date.setTime_t(items[j - i - 1]["date"].asInt());
        cout << date.toString(Qt::SystemLocaleShortDate).toStdString() +
            ":  " + (items[j - i - 1]["out"].asInt() == 0 ?
                //user_name, such difficult because of chats, looks more pretty
                names[indexes[items[j - i - 1]["user_id"].asInt()]].toStdString() : "Я")
            + "\n     " + pairs[currentUser][j - i - 1] + "\n";
        if (!(items[j - i - 1]["attachments"].isObject() && items[j - i - 1].isMember("attachments")))
            cout << "attachment: " << items[j - i - 1]["attachments"];
        if (!(items[j - i - 1]["fwd_messages"].isObject() && items[j - i - 1].isMember("fwd_messages")))
            cout << "fwdmsg: " << items[j - i - 1]["fwd_messages"];
        cout.flush();
    }
}

void Vk::init()
{
    ifstream in("/home/igorjan/key.vk");
    in >> key;
    in.close();
    countMessages = 10;
    getUnreadMessages = "https://api.vk.com/method/messages.getDialogs?v=5.24&unread=1&access_token=" + key;
    setUrls();
    fromBackup();
    pairs.resize(mp.size());
    archive.resize(mp.size(), QString::fromStdString(""));
    focused.resize(mp.size(), false);
    currentUser = indexes[user_id];
    req.resize(pool);
    reply.resize(pool);
    reader.resize(pool);
    fori(pool)
        QObject::connect(&(mgr[i]), SIGNAL(finished(QNetworkReply*)), &(eventLoop[i]), SLOT(quit()));
    qDebug() << user_id << " " << user.data();
    temp.resize(countMessages);
    fori(pairs.size())
        pairs[i].resize(countMessages);
    qDebug() << "all inits done";//------------------------------------------
    run(countMessages);
}

Vk::Vk()
{
    init();
    watchUnreadMessages = new QTimer(0);
    QThread* somethread = new QThread(this);
    watchUnreadMessages->setInterval(AUTO_REFRESH_UNREAD * 1000);
    watchUnreadMessages->moveToThread(somethread);
    FOR(i, pool / 2, pool)
    {
        eventLoop[i].moveToThread(somethread);
        mgr[i].moveToThread(somethread);
    }
    QObject::connect(watchUnreadMessages, SIGNAL(timeout()), SLOT(unread()), Qt::DirectConnection);
    QObject::connect(somethread, SIGNAL(started()), watchUnreadMessages, SLOT(start()));
    somethread->start();
    string s;
    while (true)
    {
        getline(cin, s);
        onReturn(s);
    }
}

void Vk::onReturn(string s)
{
    if (s == "")
        return;
    if (s[0] == '/' || s[0] == '\\')
    {
        char c = s[1];
        int cc = 0;
        if (s.size() > 2)
            cc = atoi(s.substr(3).data());
        switch (c)
        {
            case 'u' :
                user_id = cc;
                if (user_id == 0)
                    user_id = mp[QString::fromStdString(s.substr(3))];
                user = names[currentUser = indexes[user_id]].toStdString();
                qDebug() << "Current user:" << QString::fromStdString(user) << QString::number(user_id);
                setUrls();
                run(countMessages);
                break;
            case 'r' :
                AUTO_REFRESH_UNREAD = cc;
                watchUnreadMessages->stop();
                watchUnreadMessages->setInterval(AUTO_REFRESH_UNREAD * 1000);
                watchUnreadMessages->start();
                qDebug() << "AUTO_REFRESH_UNREAD set to" << cc;
                break;
            case 'c' :
                countMessages = cc;
                qDebug() << "countMessages set to" << cc;
                setUrls();
                temp.clear();
                temp.resize(cc, "asfd@#");
                fori(pairs.size())
                    pairs[i].clear(),
                    pairs[i].resize(cc);
                run(countMessages);
                break;
            case 'm' :
                focused[currentUser] = 0;
                jsonByUrl(markAsRead);
                qDebug() << "marked as read";
                break;
            case 'e' :
                qDebug() << "executed" << QString::fromStdString(s.substr(3));
                cout << jsonByUrl("https://api.vk.com/method/" + s.substr(3) + "&v=5.24&access_token=" + key);
                break;
            default:
                qDebug() << "r == unread, c == count, m = markAsRead, e = execute";
        }
        return;
    }
    unread();
    focused[currentUser] = 0;
    cout << "sent message: " + s << "\n";
    jsonByUrl(sendMessage + convert(s));
}

Vk::~Vk() {}
