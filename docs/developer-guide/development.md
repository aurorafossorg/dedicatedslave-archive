# Developer Guide

![DedicatedSlave Dev Screen 01](../img/devscreen_01.png)

![Flow Diagram](../img/flowdiagram.png)
a   

***

## Installation

First install development tools:

* Qt Creator ([pacman](https://www.archlinux.org/packages/?name=qtcreator))

Clone the repo via git:

```bash
git clone --depth=1 https://github.com/EnthDev/dedicatedslave.git dedicatedslave
cd dedicatedslave
source env.sh
```

> If you can't use yarn for some reason

***

## Build

Release:

```bash
cmake .
make -j8
```

Debug:

```bash
cmake -DCMAKE_BUILD_TYPE=Debug .
make -j8
```

***

## Run

> The binary files are compile to ***bin/*** and ***bin/dbg/*** (Debug Mode)

CLI

```bash
./dedicatedslave <>
```

GUI

```bash
./dedicatedslave-gui
```

***

## Testing

```bash
...q
```

## Countinous Integration

Sources:

* ubuntu-toolchain-r-test - gcc
* ubuntu-sdk-team - qt

Qt Version: 5.2.1

---

## Versioning

M: Major; N: Minor; P: Patch

* vM.N.P-alpha = Unstable version
* vM.N.P-rc = Pre-release version
* vM.N.P = Release version

***

## References

* https://github.com/stachenov/quazip
* https://wiki.qt.io/Download_Data_from_URL
* https://stackoverflow.com/questions/1874049/explanation-of-the-uml-arrows
* http://www.antonioborondo.com/2014/10/22/zipping-and-unzipping-files-with-qt/
* https://stackoverflow.com/questions/4383864/downloading-file-in-qt-from-url
* https://stackoverflow.com/questions/16250994/how-to-properly-use-qsettings
* https://encrypted.google.com/search?hl=en&q=qprocess%20output%20ui%20qt
* http://zetcode.com/gui/qt5/files/
* https://stackoverflow.com/questions/41848939/reading-and-writing-to-qprocess-in-qt-console-application
* http://www.walletfox.com/course/qxmlstreamreaderexample.php
