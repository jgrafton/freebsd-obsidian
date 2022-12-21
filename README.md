# freebsd-obsidian
This is a simple script to install the [Obsidian](https://obsidian.md)
application on a FreeBSD host.

This project borrows heavily from the
[linux-browser-install](https://github.com/mrclksr/linux-browser-installer.git)
repository and will work in conjunction with the browsers installed by it.

## Requirements:
* AMD64
  * Obsidian only comes as an amd64 binary, thus this is a hard requirement
* src installed that matches your running kernel
  * A kmod must be compiled for your local system to support libinotify
* Tested on FreeBSD 13.1 and 14.0

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

## Google Chrome
Obsidian will install alongside google chome in `/compat/ubuntu` if you already
have chrome installed.
