from collections import defaultdict
from time import sleep
import requests
import sys
import pickle
import json
from gi.repository import Notify

Notify.init("Hello world")

fil         = open('/home/igorjan/key.vk', 'r')
key         = fil.read()[:-1]
url         = "https://api.vk.com/method/wall.get?owner_id=-29253653&count=5&v=5.24&access_token=" + key
get         = "https://oauth.vk.com/authorize?client_id=4552027&redirect_uri=https://oauth.vk.com/blank.html&scope=wall,offline&response_type=token"
getComments = "https://api.vk.com/method/wall.getComments?owner_id=-29253653&v=5.24&sort=desc&access_token=" + key + "&post_id="
sendMessage = "https://api.vk.com/method/messages.send?user_id=56524497&v=5.24&access_token=" + key + "&message="

users = defaultdict(str)
for s in open('fullDatabase', 'r'):
    l = s[:-1].split(' ', 1)
    users[int(l[0])] = l[1]

def notify(s):
    f(sendMessage + s)
    Hello=Notify.Notification.new("Hello world", s, "dialog-information")
    Hello.set_timeout(Notify.EXPIRES_NEVER)
    Hello.show()

def f(s):
    return requests.get(s).json()['response']

def j(s):
    f(sendMessage + s)
    print(json.dumps(s, indent=4, ensure_ascii=False))

def comments(text, post_id, count):
    if count == 0:
        return
    if count < 0:
        print("o_O count < 0")
        return
    for s in f(getComments + str(post_id) + "&count=" + str(count))["items"]:
        if "attachments" in s.keys():
            x = "\n-----atata-----"
            j(s["attachments"])
        else:
            x = ""
        notify("new comment to " + text + ":\n" + users[s["from_id"]] + ": " +  s["text"] + " " + x)

try:
    a = pickle.load(open('output.obj', 'rb'))
except:
    a = []

counter = 1

while (True):
    if counter % 100 == 0:
        print("counter = " + str(counter))
    counter += 1
    b = []
    try:
        for s in f(url)["items"]:
            b.append((s["id"], users[s["from_id"]], s["comments"]["count"], s["text"], s["attachments"] if "attachments" in s.keys() else ""))
    except:
        print("No internet or WTF?")
        sleep(5)
        continue
    flag = False
    i = 0
    while i < len(b) and (len(a) <= i or a[i][0] != b[i][0]):
        s = b[i]
        a.insert(i, s)
        i += 1
        flag = True
        if s[4] == "":
            x = ""
        else:
            j(s[4])
            x = "\n-----atata-----"
        notify("new message from " + s[1] + ":\n" + s[3] + x)
        comments(s[3], s[0], s[2])
    for i in range(len(a)):
        if a[i][2] != b[i][2]:
            comments(a[i][3], a[i][0], b[i][2] - a[i][2])
    if flag:
        pickle.dump(b, open('output.obj', 'wb'))
        a = b
    sleep(5)
