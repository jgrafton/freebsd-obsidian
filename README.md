# freebsd-obsidian
Currently, [Obsidian](obsidian.md) does not run on FreeBSD due to the fact that
the Linux inotify file watching system isn't supported in FreeBSD.  I really
like using Obsidian and I'd like it to run on FreeBSD so this is my attempt at
making it work.

Attempt at Running Obsidian on FreeBSD

## first attempt, stub inotify calls to just return positive
