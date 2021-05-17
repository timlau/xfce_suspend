#!/usr/bin/python3

import os
import sys
import subprocess

from PySide6.QtGui import QGuiApplication
from PySide6.QtQml import QQmlApplicationEngine
from PySide6.QtCore import QObject, Signal, Slot
from xfce import XfceLidClose


class Backend(QObject):

    def __init__(self):
        super().__init__()
        self._checked = False
        self._lid_close = XfceLidClose()


    def set_suspend(self):
        state = self._lid_close.get_suspend()

    @Slot(result=bool)
    def isEnabled(self):
        return self._checked

    @Slot(bool)
    def setEnabled(self, state):
        self._checked = state
        print("State changed: ", state)
        self._lid_close.set_suspend(state)


if __name__ == "__main__":

    # directory where this file is located
    workdir =  os.path.dirname(os.path.abspath(__file__))    

    # Define our backend object, which we pass to QML.
    backend = Backend()

    # Qt application setup
    app = QGuiApplication()
    engine = QQmlApplicationEngine()
    engine.quit.connect(app.quit)

    # register backend to QML engine
    engine.rootContext().setContextProperty("backend", backend)

    engine.load(os.path.join(workdir, "../main.qml"))

    if not engine.rootObjects():
        sys.exit(-1)

    # set the current lid close action
    backend.set_suspend()

    # run the application
    sys.exit(app.exec())

