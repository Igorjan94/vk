#!/usr/bin/env python3
from collections import defaultdict
from time import sleep
import requests
import sys
import json
import binascii
import os.path
from gi.repository import Notify

Notify.init("Hello world")

key         = open('/home/igorjan/key.vk', 'r').read()[:-1]
url         = "https://api.vk.com/method/wall.get?owner_id=-29253653&count=5&v=5.24&access_token=" + key
get         = "https://oauth.vk.com/authorize?client_id=4552027&redirect_uri=https://oauth.vk.com/blank.html&scope=wall,offline&response_type=token"
getComments = "https://api.vk.com/method/wall.getComments?owner_id=-29253653&v=5.24&sort=desc&access_token=" + key + "&post_id="
sendMessage = "https://api.vk.com/method/messages.send?user_id=56524497&v=5.24&access_token=" + key + "&message="
send        = False
save        = 'output.json'
names       = 'members.txt'

def toHtml(s):
    h = str(binascii.hexlify(s.encode('UTF-8')), 'UTF-8')
    return '%' + '%'.join(h[i : i + 2] for i in range(0, len(h), 2))

def notify(s, t):
    if send:
        f(sendMessage + toHtml(s + ":\n" + t))
    Hello=Notify.Notification.new(s, t, "dialog-information")
    Hello.set_timeout(Notify.EXPIRES_NEVER)
    Hello.show()

def f(s):
    s = requests.get(s).json()
    if "response" in s.keys():
        return s["response"]
    return s

def j(s):
    s = json.dumps(s, indent=4, ensure_ascii=False)
    if send:
        f(sendMessage + toHtml(s))
    print(s)

def pr(s, what):
    if "attachments" in s.keys():
        x = "\n-----atata-----"
        j(s["attachments"])
    else:
        x = ""
    notify(what, users[s["from_id"]] + ": " +  s["text"] + " " + x)

def comments(text, post_id, count):
    if count <= 0:
        print("o_O count <= 0")
        return
    for s in f(getComments + str(post_id) + "&count=" + str(count))["items"]:
        pr(s, "New comment to " + text)

def getListOfUsers():
    if os.path.isfile(names):
        return
    r = open(names, 'w')
    urlToGet = "https://api.vk.com/method/groups.getMembers?group_id=29253653&v=5.27&access_token=" + key
    for s in f("https://api.vk.com/method/users.get?user_ids=" + ','.join(map(str, f(urlToGet)["items"])) + "&fields=name&name_case=Nom&v=5.24&access_token=" + key):
        r.write(str(s["id"]) + " " + s["first_name"] + " " + s["last_name"] + "\r")
    r.write("-29253653 ctdyear2011\r")

getListOfUsers()
users = defaultdict(str)
for s in open(names, 'r'):
    l = s[:-1].split(' ', 1)
    users[int(l[0])] = l[1]

try:
    a = json.loads(open(save, 'r').read())
except:
    a = []
counter = 0
print("Successfully started")

while (True):
    counter += 1
    if counter > 1:
        sleep(5)
    if counter % 100 == 0:
        print("counter = " + str(counter))

    try:
        b = f(url)["items"]
    except:
        print("No internet or WTF?")
        continue
    flag = False
    i = 0
    while i < len(b) and (len(a) <= i or a[i]["id"] != b[i]["id"]):
        a.insert(i, b[i])
        a[i]["comments"]["count"] = 0
        pr(b[i], "New message ")
        flag = True
        i += 1
    for i in range(len(a)):
        if a[i]["comments"]["count"] != b[i]["comments"]["count"]:
            d = b[i]["comments"]["count"] - a[i]["comments"]["count"]
            comments(a[i]["text"], a[i]["id"], d)
            a[i]["comments"]["count"] += d
            flag = True

    if flag:
        open(save, 'w').write(json.dumps(b, ensure_ascii=False))
        a = b
