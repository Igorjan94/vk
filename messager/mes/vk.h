#ifndef VK_H
#define VK_H

#include <bits/stdc++.h>
#include <unistd.h>
#include <json/json.h>
#include <json/writer.h>
#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QDateTime>
#include <QNetworkReply>
#include <QTextEdit>
#include <QUrl>
#include <QKeyEvent>
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
    explicit Vk(QWidget *parent = 0);
    ~Vk();
public slots:
    void onReturn();
    void run(int c);
    void unread();
    void onItemDoubleClicked(QListWidgetItem* item);
    void keyPressEvent(QKeyEvent* event);
    void changeEvent(QEvent* e);

private:
    std::string itoa(int i, int base);
    Json::Value jsonByUrl(std::string url);
    void fromBackup(std::string filename, int id);
    std::string convert(std::string s);
    void setUrls();

    std::vector<std::string> temp;
    std::vector<std::vector<std::string> > pairs;
    std::vector<QString> archive;
    QMap<QString, int> mp;
    std::map<int, int> indexes;
    std::string user = "me2";
    int counter = 0;
    int currentUser = 0;
    int countOfUsers = 0;
    Ui::Vk *ui;
    QTimer* watchUnreadMessages;
    std::string ret;
    int AUTO_REFRESH_UNREAD = 10;
    static const int pool = 5;

    QEventLoop eventLoop[pool];
    QNetworkAccessManager mgr[pool];
    std::vector<QNetworkRequest>         req;
    std::vector<QNetworkReply*>          reply;
    std::vector<Json::Reader>            reader;
    std::vector<int> focused;
    Json::Value root, items;
    QDateTime date;
    QFont bold, unbold;
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
