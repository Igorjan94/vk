#include <bits/stdc++.h>
#include <curl/curl.h>
#include <unistd.h>
#include <json/json.h>
#include <libnotifymm.h>
#include <cstdlib>
#include <exception>
#include <unistd.h>

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
#define fori1(n) for (int i = 1; i < n; ++i)
#define forj1(n) for (int j = 1; j < n; ++j)
#define vi vector<int>
#define vvi vector<vector<int> >
#define vll vector<long long>
#define pii pair<int, int>
#define whole(a) a.begin(), a.end()

#ifndef ONLINE_JUDGE
#define lld I64d
#endif

#define FILENAME "input"
#define INF 1000000007
#define DOUBLEFORMAT "%f"

using namespace std;

template <class Head, class... Tail> void writeln(Head head, Tail... tail);
template <class Head, class... Tail> void writeln2(Head head, Tail... tail);
template <class Head, class... Tail> void readln(Head& head, Tail&... tail);
void writeln(){printf("\n");}void writeln2(){printf("\n");}void readln(){}

///----------------------------------------------------------------------------------------------------------------------------
string itoa(int i)
{
    string s;
    while (i >= 10)
        s.pb(i % 10 + 48),
        i /= 10;
    s.pb(i + 48);
    reverse(whole(s));
    return s;
}

string buffer;
CURL *curl;
CURLcode res;
Json::Value root, items;   
Json::Reader reader;
string key = "\
";
string url = "https://api.vk.com/method/wall.get?owner_id=-29253653&count=5&v=5.24&access_token=" + key;
string getMessage = "https://api.vk.com/method/wall.getComments?owner_id=-29253653&count=10&v=5.24&sort=desc&access_token=" + key + "&post_id=";
string get = "https://oauth.vk.com/authorize?client_id=4552027&redirect_uri=https://oauth.vk.com/blank.html&scope=wall,offline&response_type=token";
string getName = "https://api.vk.com/method/users.get?v=5.24&user_ids=";
int user_id = 0;
string sendMessage = "https://api.vk.com/method/messages.send?user_id=" + itoa(user_id) + "&v=5.24&access_token=" + key + "&message=";

size_t curl_write( void *ptr, size_t size, size_t nmemb, void *stream)
{           
    buffer.append((char*)ptr, size*nmemb);
    return size*nmemb; 
}       

string ff(string t, char c, string to)
{
    string temp = "";
    fori(t.size())
        if (t[i] != c)
            temp.pb(t[i]);
        else
            temp.append(to);
    return temp;
}

Json::Value parse(string url)
{
    root.clear();
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, url.data()); 
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_write);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    if (res != CURLE_OK)
        writeln("Error in curl");
    if (!reader.parse(buffer, root))
        writeln("Failed to parse configuration\n", reader.getFormatedErrorMessages());
    buffer.clear();
    return root;
}

void notify(string s, string t)
{
    Notify::Notification message(s, t, "dialog-information");
    message.set_timeout(Notify::EXPIRES_NEVER);
    message.show();
    if (s[4] == 'm')
    {
        writeln("send message", t);
        auto x = parse(sendMessage + ff(ff(t, ' ', "%20"), '\n', "%0A"));
    }
}

void toBackup(std::vector<pair<string, int> >& a)
{
    remove("vkparser.temp");
    ofstream out("vkparser.temp");
    fori(a.size())
        out << a[i].second << " " << ff(a[i].first, '\n', "\3") << "\n";
    out.close();
}

void run()
{
    Notify::init("init");
    curl_global_init(CURL_GLOBAL_DEFAULT);
    vector< pair<string, int> > pairs, temp;
    ifstream file("vkparser.data");
    int counter = 0;
    string s;
    if (file)
        while (getline(file, s))
        {
            int i = 0, count = 0;;
            while (i < s.size() && s[i] <= '9' && s[i] >= '0')
                count = count * 10 + s[i++] - '0';
            pairs.pb({ff(s.substr(i + 1, s.size()), '\3', "\n"), count});
            writeln(pairs.back());
            counter = 1;
        }
    if (file)
        toBackup(pairs);

    writeln("all inits done");//------------------------------------------
    while (counter >= 0)
    {
        if (counter++ % 100 == 0)
            writeln(counter);
        items.clear();
        items = parse(url)["response"]["items"];
        fori(items.size())
        {
            Json::Value text = items[i]["text"];
            Json::Value comments = items[i]["comments"]["count"];
            ((counter == 1) ? pairs : temp).pb({text.asString(), comments.asInt()});
        }
        if (counter == 1)
        {
            fori(pairs.size())
                notify("Message", pairs[i].first + " (" + itoa(pairs[i].second) + ")");
            toBackup(pairs);
        }
        else
        if (temp.size() && pairs.size())
        {
            if (pairs[0].first != temp[0].first)
            {    
                int j = 0;
                while (j < temp.size() && pairs[0].first != temp[j].first)
                    ++j;
                fori(temp.size())
                    pairs[i].first = temp[i].first,
                    pairs[i].second = temp[i].second;
                fori(j)
                    notify("New message", pairs[i].first);
                toBackup(pairs);
            }
            else
            {
                bool changed = false;
                fori(pairs.size())
                    if (pairs[i].second < temp[i].second)
                    {
                        changed = true;
                        auto x = parse(getMessage + itoa(items[i]["id"].asInt()))["response"]["items"];
                        ROF(j, temp[i].second - pairs[i].second - 1, 0)
                        {
                            auto y = parse(getName + itoa(x[j]["from_id"].asInt()))["response"][(unsigned int) 0];
                            notify("New comment to " + pairs[i].first, y["first_name"].asString() + " " + y["last_name"].asString() + ": " + x[j]["text"].asString());
                        }
                        pairs[i].second = temp[i].second;
                    }
                if (changed)
                    toBackup(pairs);
            }
        }
        temp.clear();
        sleep(AUTO_REFRESH);
    }
    curl_global_cleanup();
}

int main()
{
//    freopen(FILENAME".in", "r", stdin);
//    freopen(FILENAME".out", "w", stdout);
    run();
    return 0;
}

























void print(double a){printf(" " DOUBLEFORMAT,a);}
void print(int a){printf(" %d",a);}
void print(string a){printf(" %s",a.c_str());}
void print(long long a){printf(" %lld",a);}
void print(unsigned long a){printf(" %ld",a);}
void print(unsigned int a){printf(" %d",a);}
void print(char a){printf(" %c",a);}
void print_no_space(double a){printf(DOUBLEFORMAT, a);}
void print_no_space(int a){printf("%d", a);}
void print_no_space(string a){printf("%s", a.c_str());}
void print_no_space(long long a){printf("%lld", a);}
void print_no_space(unsigned long a){printf("%ld", a);}
void print_no_space(unsigned int a){printf("%d", a);}
void print_no_space(char a){printf("%c", a);}

template<class Type>
void print_no_space(vector<Type>& a);
template<class Type>
void print(vector<Type>& a){for(int i=0;i<a.size();++i)print(a[i]);}
template<class Type>
void print(vector<vector<Type> >& a){if(a.size())(a.size()==1)?print(a[0]):writeln2(a[0]);for(int i=1;i<a.size()-1;++i)writeln2(a[i]);if(a.size()>=2)print_no_space(a.back());}
template<class Type1, class Type2>
void print(pair<Type1, Type2>& a){print(a.first);print(a.second);}

template<class Type>
void print_no_space(vector<Type>& a){if(a.size())print_no_space(a[0]);for(int i=1;i<a.size();++i)print(a[i]);}
template<class Type>
void print_no_space(vector<vector<Type> >&a){for(int i=0;i<a.size()-1;++i)writeln(a[i]);if(a.size())print_no_space(a.back());}
template<class Type1, class Type2>
void print_no_space(pair<Type1, Type2>&a){print_no_space(a.first);print(a.second);}
template <class Head, class... Tail>
void writeln2(Head head, Tail... tail){print(head);writeln2(tail...);}
template <class Head, class... Tail>
void writeln(Head head, Tail... tail){print_no_space(head);writeln2(tail...);}

void read(double &a){scanf("%lf",&a);}
void read(int &a){scanf("%d",&a);}
void read(string &a){cin>>a;}
void read(long long &a){scanf("%lld",&a);}
void read(char &a){scanf("%c",&a);}
template<class Type1, class Type2>
void read(pair<Type1, Type2>&a){readln(a.first, a.second);}
template<class Type>
void read(vector<Type> &a){if(a.size()==0){int n;read(n);a.resize(n);}for(int i=0;i<a.size();++i)readln(a[i]);}
template <class Head,class... Tail>
void readln(Head& head,Tail&... tail){read(head);readln(tail...);}

//:!clang++ vkparser.cpp -o vkparser -std=c++11 -lcurl -I /usr/include/jsoncpp/ -ljsoncpp `pkg-config --cflags --libs libnotifymm-1.0`
