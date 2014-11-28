#ifndef VK_H
#define VK_H

#include <bits/stdc++.h>
#include <unistd.h>
#include <json/json.h>
#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QDebug>
#include <QEventLoop>
#include <QListWidget>
#include <QTimer>
#include <QFont>

namespace Ui {
class Vk;
}

class Vk : public QDialog
{
    Q_OBJECT

public:
    explicit Vk(char *, QWidget *parent = 0);
    ~Vk();
public slots:
    void onReturn();
    void run();
    void unread();
    void onItemDoubleClicked(QListWidgetItem* item);

private:
    std::string itoa(int i);
    void send(std::string s);
    Json::Value parse(std::string url);
    Json::Value getUnread(std::string url);
    void fromBackup();
    std::string replace(std::string t, char c, std::string to);

    std::vector<std::string> temp;
    std::vector<std::vector<std::string> > pairs;
    std::vector<QString> archive;
    QMap<QString, int> mp;
    std::map<int, int> indexes;
    std::string user = "me2";
    int counter = 0;
    int currentUser = 0;
    Ui::Vk *ui;
    QTimer *timer;
    QEventLoop eventLoop, eventLoopSend, eventLoop3;
    QNetworkAccessManager mgr, mgr2, mgr3;
    QNetworkRequest req, req2, req3;
    QNetworkReply *reply, *reply2, *reply3;
    Json::Value root, items, root3;
    Json::Reader reader, reader3;
    QFont bold, unbold;
    int countMessages = 10;
    std::string key = "\
5fd6eba49abd5a1f94127f33803605a4660221181c8f36cdf84864e21d868982635d40ed62e95ff3407cf\
";
    std::string get = "https://oauth.vk.com/authorize?client_id=4552027&redirect_uri=https://oauth.vk.com/blank.html&scope=wall,offline&response_type=token";
    int user_id = 56524497;
    std::string sendMessage;
    std::string getMessages;
    std::string getUnreadMessages;
};

#endif // VK_H
