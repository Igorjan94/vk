#!/usr/bin/env python3
import sys
import requests
import network
from PyQt4 import QtGui, QtCore

class Example(QtGui.QWidget):
    def __init__(self, post_id, text):
        super(Example, self).__init__()
        self.post_id = post_id
        self.text = text
        self.initUI()
    def initUI(self):
        x = 80
        self.setWindowTitle('comment to' + str(self.text))
        self.combo = QtGui.QTextEdit(self)
        self.combo.setFixedWidth(400)
        self.combo.setFixedHeight(x)

        self.button2 = QtGui.QPushButton(self)
        self.button2.setText('Post this comment!!!')
        self.button2.move(200, x)
        self.button2.clicked.connect(self.post)

        self.button = QtGui.QPushButton(self)
        self.button.setText('Send')
        self.button.move(0, x)
        self.button.clicked.connect(self.onClicked)

        self.show()

    def post(self, text):
        s = self.combo.toPlainText()
        if s.replace('\n', '').replace(' ', '') == '':
            self.combo.clear()
            return
        if s != '':
            network.post(s)
            sys.exit()

    def onClicked(self, text):
        s = self.combo.toPlainText()
        if s.replace('\n', '').replace(' ', '') == '':
            self.combo.clear()
            return
        if s != '':
            network.sendComment(self.post_id, s)
            sys.exit()

def main():

    app = QtGui.QApplication(sys.argv)
    ex = Example(sys.argv[1], sys.argv[2])
    sys.exit(app.exec_())


if __name__ == '__main__':
    main()
