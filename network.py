from collections import defaultdict
import requests
import json
import binascii
import os.path

user_id        = '56524497'
ctdyear2011    = '-29253653'
version        = '5.24'
count          = 7
key            = open('/home/igorjan/key.vk', 'r').read()[:-1]
api            = 'https://api.vk.com/method/'
get            = 'https://oauth.vk.com/authorize?client_id=4552027&redirect_uri=https://oauth.vk.com/blank.html&scope=wall,offline&response_type=token'
url            = api + 'wall.get?owner_id=' + ctdyear2011 + '&count=' + str(count) + '&v=' + version + '&access_token=' + key
getCommentsUrl = api + 'wall.getComments?owner_id=' + ctdyear2011 + '&v=' + version + '&sort=desc&access_token=' + key + '&post_id='
sendMessage    = api + 'messages.send?user_id=' + user_id + '&v=' + version + '&access_token=' + key + '&message='
addComment     = api + 'wall.addComment?owner_id=' + ctdyear2011 + '&v=' + version + '&access_token=' + key + '&post_id='
addPost        = api + 'wall.post?owner_id=' + ctdyear2011 + '&v=' + version + '&access_token=' + key + '&message='
urlToGet       = api + 'groups.getMembers?group_id=' + ctdyear2011[1:] + '&v=' + version + '&access_token=' + key
friends        = api + 'users.get?fields=name&name_case=Nom&v=' + version + '&access_token=' + key + '&user_ids='
save           = 'output.json'
names          = 'members.txt'
maxlength      = 2046
send           = True

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
    s = requests.get(s).json()
    if 'response' in s.keys():
        return s['response']
    return s


def sendMessageFun(s):
    if send:
        s = toHtml(s)
        for i in range(len(s) // maxlength + (len(s) % maxlength != 0)):
            f(sendMessage + s[i * maxlength:(i + 1) * maxlength])


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
    return f(getCommentsUrl + str(post_id) + '&count=' + str(count))['items']

def getListOfUsers():
    if os.path.isfile(names):
        return
    r = open(names, 'w')
    for s in f(friends + ','.join(map(str, f(urlToGet)['items']))):
        r.write(str(s['id']) + ' ' + s['first_name'] + ' ' + s['last_name'] + '\r')
    r.write('-29253653 ctdyear2011\r')
    r.close()
