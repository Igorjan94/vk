#!/usr/bin/env python3
import sys
import requests
import network
from PyQt4 import QtGui, QtCore

class Example(QtGui.QWidget):
    def __init__(self, post_id, reply_id, text):
        super(Example, self).__init__()
        self.post_id = post_id
        self.text = text
        self.reply_id = "" if reply_id == 0 else "&reply_to_comment=" + str(reply_id)
        self.initUI()
    def initUI(self):
        x = 80
        self.setWindowTitle('comment to ' + str(self.text))
        self.combo = QtGui.QTextEdit(self)
        self.combo.setFixedWidth(400)
        self.combo.setFixedHeight(x)

        self.button2 = QtGui.QPushButton(self)
        self.button2.setText('Post')
        self.button2.move(200, x)
        self.button2.clicked.connect(self.post)

        self.button = QtGui.QPushButton(self)
        self.button.setText('Reply')
        self.button.move(0, x)
        self.button.clicked.connect(self.onClicked)

        self.show()

    def post(self, text):
        if self.reply_id != 0:
            self.reply_id = 0
            onClicked(self, text)
            return
        s = self.combo.toPlainText()
        if s.replace('\n', '').replace(' ', '') == '':
            print('nothing to post :(')
            self.combo.clear()
            return
        network.post(s)
        sys.exit()

    def onClicked(self, text):
        s = self.combo.toPlainText()
        if self.post_id == 0:
            print('nothing to comment :(')
            return
        if s.replace('\n', '').replace(' ', '') == '':
            self.combo.clear()
            return
        print("sending comment " + s + " to " + self.post_id + " reply on " + self.reply_id)
        network.sendComment(self.post_id + self.reply_id, s)
        sys.exit()

def main():

    app = QtGui.QApplication(sys.argv)
    if len(sys.argv) < 2:
        ex = Example(0, 0, 'nothing, it is new comment :)')
    else:
        ex = Example(sys.argv[1], sys.argv[2], sys.argv[3])
    sys.exit(app.exec_())


if __name__ == '__main__':
    main()
