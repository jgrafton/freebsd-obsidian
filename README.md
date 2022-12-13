# freebsd-obsidian
**NOTE** this is an experimental repo and none of the software should work yet,
this is just me working through getting Obsidian working in FreeBSD

Currently, [Obsidian](obsidian.md) does not run on FreeBSD due to the fact that
the Linux inotify file watching system isn't supported in FreeBSD.  I really
like using Obsidian and I'd like it to run on FreeBSD so this is my attempt at
making it work.

## first attempt, stub inotify calls to just return positive

## second attempt, overload syscalls to inotify similar to fakeroot

## install Obsidian on FreeBSD procedure
Use the linux-browser-installer to install an Ubuntu file system that supports
chrome
https://github.com/mrclksr/linux-browser-installer.git

install obsidian into ubuntu chroot env by downloading deb package from [Obsidian](obsidian.md)
```
# cp obsidian.deb /compat/ubuntu/root
# chroot /compat/ubuntu /bin/bash
# dpkg -i /root/obsidian.deb
```

from home directory on FreeBSD box
```
/compat/ubuntu/opt/Obsidian/obsidian --no-sandbox --disable-gpu
```
