# xfce_suspend
Tool to change the lid-close suspend on / off in XFCE 

This is a test project to test Qt 6.1

There is 3 versions of the same tool using the same QML file.

main.cpp is the C++ version

python/main_PySide.py is a python version using PySide6 toolkit

python/main_PyQT.py is a python version using the PyQt6 toolkit.

## Requirement.

### C++
QT 6.1 must be installed using the installer for QT upstream

### Python

**PySide6**

```bash
pip install PySide6==6.1
```

**PyQt6**

```bash
pip install PyQt6
```

A helper lib to read Xfconf using dbus is also needed

https://github.com/timlau/py_rasmil


