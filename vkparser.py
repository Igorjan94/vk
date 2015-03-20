#!/usr/bin/env python3
import network
import json
import sys
import subprocess
from time import sleep
from gi.repository import Notify
from gi.repository import Gtk

users = network.parseListOfUsers()

def ssss(notif_object, action_name, post_id, reply_id, text):
    subprocess.Popen(["./runner.py", str(post_id), str(reply_id), text])
    notif_object.close()
    Gtk.main_quit()

def notify(s, e, post_id):
    t = users[e["from_id"]] + ": " + e["text"] + " " + network.pr(e)
    network.sendMessageFun(s + ":\n" + t)
    Hello=Notify.Notification.new(s, t, "dialog-information")
    Hello.set_timeout(Notify.EXPIRES_NEVER)
    Hello.add_action('vkParser', 'Answer', ssss, post_id, e["id"], t)
    Hello.connect('closed', Gtk.main_quit)
    Hello.show()
    Gtk.main()

def main():
    Notify.init("VkParser")

    try:
        a = json.loads(open(network.save, 'r').read())
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
            b = network.f(network.url)["items"]
        except Exception as e:
            print(e)
            print("No internet or WTF?")
            continue
        flag = False
        i = 0
        while i < len(b) and (len(a) <= i or a[i]["id"] != b[i]["id"]):
            a.insert(i, b[i])
            a[i]["comments"]["count"] = 0
            notify("New message", b[i], b[i]["id"])
            flag = True
            i += 1
        for i in range(min(len(a), len(b))):
            if a[i]["comments"]["count"] < b[i]["comments"]["count"]:
                d = b[i]["comments"]["count"] - a[i]["comments"]["count"]
                if (d > 0):
                    try:
                        for s in reversed(network.getComments(a[i]["id"], d)):
                            notify("New comment to " + users[a[i]["from_id"]] + ": " + a[i]["text"], s, a[i]["id"])
                    except NameError:
                        print("O_o")
                a[i]["comments"]["count"] = b[i]["comments"]["count"]
                open(network.save, 'w').write(json.dumps(b, ensure_ascii=False))
                flag = True
            elif a[i]["comments"]["count"] > b[i]["comments"]["count"]:
                a[i]["comments"]["count"] = b[i]["comments"]["count"]

        if flag:
            open(network.save, 'w').write(json.dumps(b, ensure_ascii=False))
            a = b

if __name__ == '__main__':
    main()
