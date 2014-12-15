#include "vk.h"
#include "ui_vk.h"
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
    markAsRead  = "https://api.vk.com/method/messages.markAsRead?v=5.24&access_token=" + key +
            (user_id < 100 ? "&chat_id=" : "&user_id=") + itoa(user_id);
}

Json::Value Vk::jsonByUrl(string url)
{
    int i = 0;
    while (eventLoop[i].isRunning())
        i = (i + 1) % pool;
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
    auto x = jsonByUrl(getUnreadMessages)["response"];
    if (x["count"].asInt() == 0)
        return;
    for (auto y : x["items"])
    {
        int t = y["message"]["user_id"].asInt();
        if (!(y["message"]["chat_id"].isObject() && y["message"].isMember("chat_id")))
            t = y["message"]["chat_id"].asInt();
        qDebug() << "unread from " << t;
        if (indexes.count(t) == 0)
            ui->textBrowser->append(QString::fromStdString("-----------------------------------O_O-----------------------------------new message from ")
                                    + QString::fromStdString(itoa(t)));
        else
        {
            ui->listWidget->item(indexes[t])->setFont(bold);
            int f = y["unread"].asInt();// - focused[currentUser];
            if (indexes[t] == currentUser)
                run(f - focused[currentUser]),
                focused[currentUser] = f;
        }
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
            ui->listWidget->addItem(temp);
            j = atoi(s.substr(0, j).data());
            mp[temp] = j;
            indexes[j] = i;
            ++i;
        }
}

void Vk::onItemDoubleClicked(QListWidgetItem* item)
{
    QString s = item->text();
    this->setWindowTitle(s);
    int temp = mp[s];
    if (temp == currentUser)
        return;
    item->setFont(unbold);
    archive[currentUser] = ui->textBrowser->toPlainText();
    ui->textBrowser->clear();

    user_id = temp;
    user = s.toUtf8().data();
    qDebug() << "Current user:" << s << QString::number(user_id);
    currentUser = indexes[user_id];
    setUrls();
    ui->textBrowser->append(archive[currentUser]);
    ui->textBrowser->textCursor().movePosition(QTextCursor::End);
    ui->textBrowser->ensureCursorVisible();
    run(ui->textBrowser->toPlainText().size() <= 10 ? countMessages : 0);
}

void Vk::run(int c)
{
    if (counter++ % 1000 == 0)
        qDebug() << counter;
    items.clear();
    items = jsonByUrl(getMessages + itoa(c))["response"]["items"];
    int j = items.size();
    fori(j)
        pairs[currentUser][i] = items[i]["body"].asString();
    fori(j)
    {
        date.setTime_t(items[j - i - 1]["date"].asInt());
        qDebug() << QString::fromStdString("got message: " + pairs[currentUser][j - i - 1]);
        ui->textBrowser->append(date.toString(Qt::SystemLocaleShortDate) +
            QString::fromStdString(":  " + (items[j - i - 1]["out"].asInt() == 0 ?
                //user_name, such difficult because of chats, looks more pretty
                ui->listWidget->item(indexes[items[j - i - 1]["user_id"].asInt()])->text().toStdString() : "Я")
            + "\n     " + pairs[currentUser][j - i - 1]));
        if (!(items[j - i - 1]["attachments"].isObject() && items[j - i - 1].isMember("attachments")))
            cout << "attachment: " << items[j - i - 1]["attachments"],
            ui->textBrowser->append("--------------------------------------!!!attachments!!!--------------------------------------");
        if (!(items[j - i - 1]["fwd_messages"].isObject() && items[j - i - 1].isMember("fwd_messages")))
            cout << "fwdmsg: " << items[j - i - 1]["fwd_messages"],
            ui->textBrowser->append("--------------------------------------!!!fwdMessages!!!--------------------------------------");
        cout.flush();
        ui->textBrowser->textCursor().movePosition(QTextCursor::End);
        ui->textBrowser->ensureCursorVisible();
    }
}

Vk::Vk(char* s, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Vk)
{
    countMessages = 10;
    getUnreadMessages = "https://api.vk.com/method/messages.getDialogs?v=5.27&unread=1&access_token=" + key;
    setUrls();
    ui->setupUi(this);
    ui->textBrowser->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::LinksAccessibleByMouse);
    bold.setBold(true);
    unbold.setBold(false);
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
    watchUnreadMessages = new QTimer(this);
    connect(watchUnreadMessages, SIGNAL(timeout()), this, SLOT(unread()));
    watchUnreadMessages->start(AUTO_REFRESH_UNREAD * 1000);
}

void Vk::onReturn()
{
    string s = ui->lineEdit->text().toUtf8().data();
    if (s == "")
        return;
    if (s[0] == '/' || s[0] == '\\')
    {
        ui->lineEdit->clear();
        char c = s[1];
        int cc = 0;
        if (s.size() > 2)
            cc = atoi(s.substr(3).data());
        switch (c)
        {
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
                ui->textBrowser->clear();
                run(countMessages);
                break;
            case 'm' :
                focused[currentUser] = 0;
                jsonByUrl(markAsRead);
                ui->listWidget->item(currentUser)->setFont(unbold);
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
    qDebug() << QString::fromStdString("sent message: " + s);
    date.setTime_t(QDateTime::currentMSecsSinceEpoch() / 1000);
    ui->textBrowser->append(date.toString(Qt::SystemLocaleShortDate) + QString::fromStdString(":  Я\n   " + s));
    jsonByUrl(sendMessage + convert(s));
    ui->lineEdit->clear();
}

Vk::~Vk()
{
    delete ui;
}
