#ifndef VK_H
#define VK_H

#include <bits/stdc++.h>
#include <unistd.h>
#include <json/json.h>
#include <json/writer.h>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QDateTime>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QDebug>
#include <QEventLoop>
#include <QTimer>
#include <QThread>

class Vk : QObject
{
    Q_OBJECT

public:
    explicit Vk();
    ~Vk();
public slots:
    void onReturn(std::string s);
    void run(int c, bool f);
    void unread();

private:
    std::string itoa(int i, int base);
    Json::Value jsonByUrl(std::string url, bool f);
    void fromBackup();
    std::string convert(std::string s);
    void setUrls();
    void init();

    std::vector<std::string> temp;
    std::vector<std::vector<std::string> > pairs;
    std::vector<QString> archive;
    QMap<QString, int> mp;
    std::map<int, int> indexes;
    std::vector<QString> names;
    std::string user = "me2";
    int counter = 0;
    int currentUser = 0;
    QTimer* watchUnreadMessages;
    std::string ret;
    int AUTO_REFRESH_UNREAD = 10;
    static const int pool = 8;

    QEventLoop eventLoop[pool];
    QNetworkAccessManager mgr[pool];
    std::vector<QNetworkRequest>         req;
    std::vector<QNetworkReply*>          reply;
    std::vector<Json::Reader>            reader;
    std::vector<int> focused;
    Json::Value root, items;
    QDateTime date;
    int countMessages;
    std::string key;
    std::string get = "https://oauth.vk.com/authorize?client_id=4552027&redirect_uri=https://oauth.vk.com/blank.html&scope=wall,offline&response_type=token";
    int user_id = 56524497;
    std::string sendMessage;
    std::string getMessages;
    std::string markAsRead;
    std::string getUnreadMessages;
};

#endif // VK_H
