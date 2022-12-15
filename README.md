# freebsd-obsidian
**NOTE** this is an experimental repo and none of the software should work yet,
this is just me working through getting Obsidian working in FreeBSD

Currently, [Obsidian](obsidian.md) does not run on FreeBSD due to the fact that
the Linux inotify file watching system isn't supported in FreeBSD.  I really
like using Obsidian and I'd like it to run on FreeBSD so this is my attempt at
making it work.

This project borrows heavily from the [linux-browser-install](https://github.com/mrclksr/linux-browser-installer.git) repository

## install Obsidian
```
# ./ob-installer install
```

## deinstall Obsidian
```
# ./ob-installer deinstall
```

Run Obisidian
```
/usr/local/bin/linux-obsidian
```

## NOTES
Running a linux binary that makes calls to inotify on FreeBSD returns:
```text
linux: jid 0 pid 33527 (notify): syscall inotify_init not implemented
linux: jid 0 pid 33527 (notify): syscall inotify_add_watch not implemented
linux: jid 0 pid 33527 (notify): syscall inotify_rm_watch not implemented
```

Obsidian binary returns and spins forever on waiting for inotify to return:
```text
[    0.000000] linux: jid 0 pid 31258 (DedicatedWorker): syscall inotify_init1 not implemented
[    0.000000] linux: jid 0 pid 31195 (ThreadPoolForeg): syscall inotify_init1 not implemented
[    0.000000] linux: jid 0 pid 31195 (ThreadPoolForeg): syscall inotify_init not implemented
```
