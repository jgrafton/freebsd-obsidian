# freebsd-obsidian
**NOTE** This is an experimental repo that installs a version of Obsidian that
technically works but is hampered by several annoying issues outlined in the
**current status** section below.

This project borrows heavily from the [linux-browser-install](https://github.com/mrclksr/linux-browser-installer.git) repository

## Requirements:
* AMD64
  * Obsidian only comes as an amd64 binary, thus this is a hard requirement
* src installed that matches your running kernel
  * a prereq for running libinotify for a linux binary is the libbsd kmod
* I've only tested this on FreeBSD 13.1.

## install Obsidian
```
# ./ob-installer install
```

## deinstall Obsidian
```
# ./ob-installer deinstall
```

## Run Obisidian
```
/usr/local/bin/linux-obsidian
```

## Current Status
Obsidian actually functions (kind of).
* the linux_libbsd freebsd kernel module needs to be active for libinotify to function properly in the ubuntu chroot
	* [libbsd](https://github.com/wulf7/linux-libbsd)
* fonts are messed up a bit in the obsidian app
* the file browsing dialog does not work properly and appears to be a linux
    permissions issue I do not understand yet.  If you already have an Obsidian
    configuration from $HOME/.config/obsidian, you shouldn't require the
    dialog.

