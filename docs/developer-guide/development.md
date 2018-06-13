# Developer Guide

## Installation

First install development tools:

* Qt Creator ([pacman](https://www.archlinux.org/packages/?name=qtcreator))

Clone the repo via git:

```bash
git clone --depth=1 https://github.com/EnthDev/dedicatedslave.git dedicatedslave
cd dedicatedslave
```

> If you can't use yarn for some reason

***

## Build

### Release

Windows:

* Open "env.cmd" and call

```
call buildrelease_win.cmd
```

Linux:

```bash
./buildrelease_linux.sh
```

### Debug

***

## Run

Start the app in the dev environment.

```bash
...
```

***

## Testing

```bash
...
```

## Countinous Integration

Sources:
* ubuntu-toolchain-r-test - gcc
* ubuntu-sdk-team - qt

Qt Version: 5.2.1

---

## Versioning

* vM.N.P-alpha = Unstable version
* vM.N.P-rc = Pre-release version
* vM.N.P = Release version

## References

* https://github.com/stachenov/quazip
* https://wiki.qt.io/Download_Data_from_URL
* https://stackoverflow.com/questions/1874049/explanation-of-the-uml-arrows
