from collections import defaultdict
import requests
import json
import binascii
import os.path
import sys
from time import sleep

user_id        = '56524497'
chat_id        = '21'
ctdyear2011    = '-29253653'
version        = '5.24'
count          = 7
needLikes      = "&need_likes=1"
key            = open('key.vk', 'r').read()[:-1]
api            = 'https://api.vk.com/method/'
get            = 'https://oauth.vk.com/authorize?client_id=4552027&redirect_uri=https://oauth.vk.com/blank.html&scope=wall,offline&response_type=token'
url            = api + 'wall.get?owner_id=' + ctdyear2011 + '&count=' + str(count) + '&v=' + version + '&access_token=' + key
getCommentsUrl = api + 'wall.getComments?owner_id=' + ctdyear2011 + '&v=' + version + '&sort=desc' + needLikes + '&access_token=' + key + '&post_id='
sendMessageUser = api + 'messages.send?user_id=' + user_id + '&v=' + version + '&access_token=' + key + '&message='
sendMessageChat = api + 'messages.send?chat_id=' + chat_id + '&v=' + version + '&access_token=' + key + '&message='
addComment     = api + 'wall.addComment?owner_id=' + ctdyear2011 + '&v=' + version + '&access_token=' + key + '&post_id='
addPost        = api + 'wall.post?owner_id=' + ctdyear2011 + '&v=' + version + '&access_token=' + key + '&message='
urlToGet       = api + 'groups.getMembers?group_id=' + ctdyear2011[1:] + '&v=' + version + '&access_token=' + key
friends        = api + 'users.get?fields=name&name_case=Nom&v=' + version + '&access_token=' + key + '&user_ids='
save           = 'output.json'
names          = 'members.txt'
maxlength      = 2046
send           = True

def printJson(s):
    print(json.dumps(s, indent=4, ensure_ascii=False))

def sendComment(post_id, text):
    f(addComment + post_id + '&text=' + toHtml(text))

def post(text):
    f(addPost + toHtml(text))

def parseListOfUsers():
    getListOfUsers()
    users = defaultdict(str)
    for s in open(names, 'r'):
        l = s[:-1].split(' ', 1)
        users[int(l[0])] = l[1]
    return users

def toHtml(s):
    h = str(binascii.hexlify(s.encode('UTF-8')), 'UTF-8')
    return '%' + '%'.join(h[i : i + 2] for i in range(0, len(h), 2))

def f(s):
    if len(s) > maxlength:
        (url, param) = s.rsplit('&', 1)
        param = param.split('=', 1)
        s = requests.post(url, {param[0] : binascii.unhexlify(param[1].replace('%', '')).decode('utf-8')}).json()
    else:
        s = requests.get(s).json()
    if 'response' in s.keys():
        return s['response']
    return s

def sendMessageFun(s):
    if send:
        s = toHtml(s)
        f(sendMessage + s)

def j(s):
    for y in s:
        if y['type'] == 'poll':
            print('/e polls.addVote?owner_id=' + ctdyear2011 + '&poll_id=' + str(y['poll']['id']) + '&answer_id=')
            for x in y['poll']['answers']:
                print('\t' + x['text'] + ': ' + str(x['id']))
    s = json.dumps(s, indent=4, ensure_ascii=False)
    sendMessageFun(s)
    print(s)

def pr(s):
    if 'attachments' in s.keys():
        x = '\n-----atata-----'
        j(s['attachments'])
    else:
        x = ''
    return x

def getComments(post_id, count):
    x = f(getCommentsUrl + str(post_id) + '&count=' + str(count))
    if "items" in x.keys():
        return x["items"]
    print(x)
    raise NameError('error in getComments')

def getListOfUsers():
    if os.path.isfile(names):
        return
    r = open(names, 'w')
    for s in f(friends + ','.join(map(str, f(urlToGet)['items']))):
        r.write(str(s['id']) + ' ' + s['first_name'] + ' ' + s['last_name'] + '\r')
    r.write('-29253653 ctdyear2011\r')
    r.close()

def getLikes():
    c = {}
    try:
        n = 4
        for i in range(1000):
            url = api + 'wall.get?owner_id=' + ctdyear2011 + '&count=' + str(n) + '&v=' + version + '&access_token=' + key
            x = f(url + '&offset=' + str(i * n))
            if 'items' in x.keys() and len(x['items']) > 0:
                for y in x['items']:
                    print('parsing ' + str(y['id']))
                    likes = int(y['likes']['count'])
                    comm = int(y['comments']['count'])
                    if not y['from_id'] in c:
                        c[y['from_id']] = likes
                    else:
                        c[y['from_id']] += likes
                    for comment in getComments(y['id'], comm):
                        cc = int(comment['likes']['count'])
                        if not comment['from_id'] in c:
                            c[comment['from_id']] = cc
                        else:
                            c[comment['from_id']] += cc
            else:
                break
            sleep(2)
    except:
        print("fail?")
    users = parseListOfUsers()
    for x in c:
        print(users[x] + " " + str(c[x]))

def getStat():
    a = []
    try:
        n = 99
        for i in range(30):
            url = api + 'wall.get?owner_id=' + ctdyear2011 + '&count=' + str(n + 1) + '&v=' + version + '&access_token=' + key
            x = f(url + '&offset=' + str(i * n))
            if 'items' in x.keys() and len(x['items']) > 0:
                for y in x['items']:
                    print(str(y['comments']['count']) + ' ' + str(y['id']))
                    #if (y['id'] == 11746):
                        #print(y)
                        #sys.exit()
            else:
                break
            sleep(2)
    except:
        print('Fail?')
    print(sorted(a)[::-1])

# sendMessageFun('💩' * 20)
#getLikes()
#getStat()

#url = "http://codeforces.ru/api/contest.standings?contestId=512&from=1&count=2"
#printJson(f(url))

#print(json.dumps(getComments(19785, 10), indent=4, ensure_ascii=False))

#for x in range(313):
#    if x > 0 and x != 5 and x != 9:
#        f(api + 'wall.delete?post_id=' + str(x) + '&access_token=' + key)
#        sleep(0.5)
