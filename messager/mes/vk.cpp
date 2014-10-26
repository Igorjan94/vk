#include "vk.h"
#include "ui_vk.h"
#include <QTimer>
#include <cstdlib>

using namespace std;

#define AUTO_REFRESH 5

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

string Vk::replace(string t, char c, string to)
{
    string temp = "";
    fori(t.size())
        if (t[i] != c)
            temp.pb(t[i]);
        else
            temp.append(to);
    return temp;
}

Json::Value Vk::parse(string url)
{
    root.clear();
    req.setUrl(QUrl( QString(url.data()) ));
    reply = mgr.get(req);
    eventLoop.exec();
    if (reply->error() != QNetworkReply::NoError)
        qDebug() << reply->errorString();

    if (!reader.parse(reply->readAll().data(), root))
        printf("%s %s\n", "Failed to parse configuration\n", reader.getFormatedErrorMessages().data());
    return root;
}

void Vk::send(string s)
{
    s = sendMessage + replace(replace(s, ' ', "%20"), '\n', "%0A");
    req2.setUrl(QUrl( QString(s.data()) ));
    reply2 = mgr2.get(req2);
    eventLoopSend.exec();
    if (reply2->error() != QNetworkReply::NoError)
        qDebug() << reply2->errorString();
}

void Vk::fromBackup(bool f)
{
    ifstream file("database");
    string s;
    if (file)
        while (getline(file, s))
        {
            int j = 0;
            while (s[j] <= '9' && s[j] >= '0')
                j++;
            if (f)
            {
                if (atoi(s.substr(0, j).data()) == user_id)
                {
                    user = s.substr(j + 1, s.size());
                    return;
                }
            }
            else
            {
                if (s.substr(j + 1, s.size()) == user)
                {
                    user_id = atoi(s.substr(0, j).data());
                    return;
                }
            }
        }
}

void Vk::run()
{
    if (counter++ % 1000 == 0)
        qDebug() << counter;
    items.clear();
    items = parse(getMessages)["response"]["items"];
    fori(items.size())
        temp[i] = items[i]["body"].asString();
    if (temp.size() && pairs.size())
        if (pairs[0] != temp[0])
        {
            int j = 0;
            while (j < temp.size() && pairs[0] != temp[j])
                ++j;
            fori(temp.size())
                pairs[i] = temp[i];
            fori(j)
            {
                ui->textBrowser->append(QString::fromStdString((items[j - i - 1]["out"].asInt() == 0 ? user + ":\n    " : "Я:\n    ") + pairs[j - i - 1]));
                ui->textBrowser->textCursor().movePosition(QTextCursor::End);
                ui->textBrowser->ensureCursorVisible();
            }
        }
}

Vk::Vk(char* s, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Vk)
{
    if (s != 0)
    {
        if (s[0] >= '0' && s[0] <= '9')
        {
            user_id = atoi(s);
            fromBackup(true);
        }
        else
        {
            user = s;
            fromBackup(false);
        }
    }
    else
        fromBackup(true);
    sendMessage = "https://api.vk.com/method/messages.send?user_id=" + itoa(user_id) + "&v=5.24&access_token=" + key + "&message=";
    getMessages = "https://api.vk.com/method/messages.getHistory?count=" + itoa(countMessages) + "&user_id=" + itoa(user_id) + "&v=5.24&access_token=" + key;
    ui->setupUi(this);
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    QObject::connect(&mgr2, SIGNAL(finished(QNetworkReply*)), &eventLoopSend, SLOT(quit()));
    qDebug() << user_id << " " << user.data();
    if (pairs.size() == 0)
        fori(countMessages)
            pairs.pb("qwerty&?ADSF"),
            temp.pb("");

    qDebug() << "all inits done";//------------------------------------------

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(run()));
    timer->start(AUTO_REFRESH * 1000);
//    QThread *thread = new QThread();
  //  connect(thread, SIGNAL(started()), this, SLOT(run()));
    //moveToThread(thread);
    //thread->start();
    //run();
}

void Vk::onReturn()
{
    send(ui->lineEdit->text().toUtf8().data());
    ui->lineEdit->clear();
}

Vk::~Vk()
{
    delete reply;
    if (reply2 != NULL)
        delete reply2;
    delete ui;
}
