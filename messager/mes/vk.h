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

private:
    std::string itoa(int i);
    void send(std::string s);
    Json::Value parse(std::string url);
    void fromBackup(bool f);
    std::string replace(std::string t, char c, std::string to);

    std::vector<std::string> pairs, temp;
    std::string user;
    int counter = 0;
    Ui::Vk *ui;
    QEventLoop eventLoop, eventLoopSend;
    QNetworkAccessManager mgr, mgr2;
    QNetworkRequest req, req2;
    QNetworkReply *reply, *reply2;
    Json::Value root, items;
    Json::Reader reader;
    int countMessages = 10;
    std::string key = "\
";
    std::string get = "https://oauth.vk.com/authorize?client_id=4552027&redirect_uri=https://oauth.vk.com/blank.html&scope=wall,offline&response_type=token";
    int user_id = 0;
    std::string sendMessage;
    std::string getMessages;
};

#endif // VK_H
