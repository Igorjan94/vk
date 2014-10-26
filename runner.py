#!/usr/bin/env py
import sys
import subprocess
from PyQt4 import QtGui, QtCore

class Example(QtGui.QWidget):
    def __init__(self):
        super(Example, self).__init__()
        self.initUI()
    def initUI(self):
        combo = QtGui.QComboBox(self)
        f = open("database", "r")
        for s in f:
            r = s.split(' ')
            t = r[1] + ' ' + r[2]
            combo.addItem(t)
        combo.move(50, 50)
        combo.setFixedHeight(40)
        combo.activated[str].connect(self.onActivated)

        self.setGeometry(300, 300, 300, 200)
        self.setWindowTitle('vk launcher')
        self.show()

    def onActivated(self, text):
        subprocess.call(["./messenger", text[:-1]])

def main():

    app = QtGui.QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())


if __name__ == '__main__':
    main()
