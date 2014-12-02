#include "vk.h"
#include "ui_vk.h"
#include <cstdlib>

using namespace std;

#define AUTO_REFRESH 5
#define AUTO_REFRESH_UNREAD 20

#define pb push_back
#define ll long long
#define forit(it, r) for (auto it = r.begin(); it != r.end(); it++)
#define forn(i, n) for (int i = 0; i < n; ++i)
#define forn1(i, n) for (int i = 1; i < n; ++i)
#define FOR(i, m, n) for (int i = m; i < n; ++i)
#define ROF(i, m, n) for (int i = m; i >= n; --i)
#define fori(n) for (int i = 0; i < n; ++i)
#define forj(n) for (int j = 0; j < n; ++j)

string Vk::itoa(int i)
{
    string s;
    while (i >= 10)
        s.pb(i % 10 + 48),
        i /= 10;
    s.pb(i + 48);
    reverse(s.begin(), s.end());
    return s;
}

QString Vk::convert(string s)
{
    ret.clear();
    fori(s.size())
        ret.append("%" + QString::number((s[i] + 256) % 256, 16));
    return ret;
}

Json::Value Vk::parse(string url)
{
    root.clear();
    req.setUrl(QUrl( QString(url.data()) ));
    reply = mgr.get(req);
    if (!eventLoop.isRunning())
        eventLoop.exec();
    if (reply->error() != QNetworkReply::NoError)
        qDebug() << reply->errorString();

    if (!reader.parse(reply->readAll().data(), root))
        printf("%s %s\n", "Failed to parse configuration\n", reader.getFormatedErrorMessages().data());
    return root;
}

Json::Value Vk::getUnread(string url3)
{
    root3.clear();
    req3.setUrl(QUrl( QString(url3.data()) ));
    reply3 = mgr3.get(req3);
    eventLoop3.exec();
    if (reply3->error() != QNetworkReply::NoError)
        qDebug() << reply3->errorString();
    if (!reader3.parse(reply3->readAll().data(), root3))
        printf("%s %s\n", "Failed to parse configuration\n", reader3.getFormatedErrorMessages().data());
    return root3;
}

void Vk::send(QString s)
{
    s = QString::fromStdString(sendMessage) + convert(s.toUtf8().data());
    req2.setUrl(QUrl(s));
    reply2 = mgr2.get(req2);
    eventLoopSend.exec();
    if (reply2->error() != QNetworkReply::NoError)
        qDebug() << reply2->errorString();
}

void Vk::unread()
{
    auto x = getUnread(getUnreadMessages)["response"];
    if (x["count"].asInt() == 0)
        return;
    for (auto y : x["items"])
    {
        int t = y["message"]["user_id"].asInt();
        if (!(y["message"]["chat_id"].isObject() && y["message"].isMember("chat_id")))
            t = y["message"]["chat_id"].asInt();
        qDebug() << "unread from " << t;
        if (indexes.find(t) == indexes.end())
            ui->textBrowser->append("-------O_O-----------------------------------new message from " + t);
        else
            if (indexes[t] != currentUser)
                ui->listWidget->item(indexes[t])->setFont(bold);
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
    timer->stop();
    item->setFont(unbold);
    archive[currentUser] = ui->textBrowser->toPlainText();
    ui->textBrowser->clear();
    QString s = item->text();
    qDebug() << "Current user: " << s;
    user_id = mp[s];
    user = s.toUtf8().data();
    currentUser = indexes[user_id];
    sendMessage = "https://api.vk.com/method/messages.send?v=5.24&access_token=" + key +  (user_id < 100 ? "&chat_id=" : "&user_id=") + itoa(user_id) + "&message=";
    getMessages = "https://api.vk.com/method/messages.getHistory?count=" + itoa(countMessages) + (user_id < 100 ? "&chat_id=" : "&user_id=") + itoa(user_id) + "&v=5.24&access_token=" + key;
    ui->textBrowser->append(archive[currentUser]);
    ui->textBrowser->textCursor().movePosition(QTextCursor::End);
    ui->textBrowser->ensureCursorVisible();
    run();
    timer->start(AUTO_REFRESH * 1000);
}

void Vk::run()
{
    if (counter++ % 1000 == 0)
        qDebug() << counter;
    items.clear();
    items = parse(getMessages)["response"]["items"];
    fori(items.size())
        temp[i] = items[i]["body"].asString();
    if (temp.size() && pairs[currentUser].size())
        if (pairs[currentUser][0] != temp[0])
        {
            int j = 0;
            while (j < temp.size() && pairs[currentUser][0] != temp[j])
                ++j;
            fori(temp.size())
                pairs[currentUser][i] = temp[i];
            fori(j)
            {
                ui->textBrowser->append(QString::fromStdString((items[j - i - 1]["out"].asInt() == 0 ? user + ":\n    " : "Я:\n    ") + pairs[currentUser][j - i - 1]));
                cout << items[j - i - 1]["date"];
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
}

Vk::Vk(char* s, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Vk)
{
    sendMessage = "https://api.vk.com/method/messages.send?user_id=" + itoa(user_id) + "&v=5.24&access_token=" + key + "&message=";
    getMessages = "https://api.vk.com/method/messages.getHistory?count=" + itoa(countMessages) + "&user_id=" + itoa(user_id) + "&v=5.24&access_token=" + key;
    getUnreadMessages = "https://api.vk.com/method/messages.getDialogs?v=5.27&unread=1&access_token=" + key;
    ui->setupUi(this);
    ui->textBrowser->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::LinksAccessibleByMouse);
    bold.setBold(true);
    unbold.setBold(false);
    fromBackup();
    pairs.resize(mp.size());
    archive.resize(mp.size(), QString::fromStdString(""));
    currentUser = indexes[user_id];
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    QObject::connect(&mgr2, SIGNAL(finished(QNetworkReply*)), &eventLoopSend, SLOT(quit()));
    QObject::connect(&mgr3, SIGNAL(finished(QNetworkReply*)), &eventLoop3, SLOT(quit()));
    qDebug() << user_id << " " << user.data();
    fori(countMessages)
    {
        forj(pairs.size())
            pairs[j].pb("qwerty&?ADSF");
        temp.pb("");
    }

    qDebug() << "all inits done";//------------------------------------------
    run();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(run()));
    timer->start(AUTO_REFRESH * 1000);

    QTimer* watchUnreadMessages = new QTimer(this);
    connect(watchUnreadMessages, SIGNAL(timeout()), this, SLOT(unread()));
    watchUnreadMessages->start(AUTO_REFRESH_UNREAD * 1000);
}

void Vk::onReturn()
{
    send(ui->lineEdit->text());
    ui->lineEdit->clear();
}

Vk::~Vk()
{
    if (reply != NULL)
        delete reply;
    if (reply2 != NULL)
        delete reply2;
    delete ui;
}
