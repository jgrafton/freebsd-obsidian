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

## current status
Obsidian actually functions (kind of).
* linprocfs needs a max_user_watches which requires a modification to the kernel code (patch below)
    * this might not actually be required, i need to test
* the linux_libbsd freebsd kernel module needs to be active for libinotify to function properly in the ubuntu chroot
	* [libbsd](https://github.com/wulf7/linux-libbsd)
* fonts are messed up a bit in the obsidian app, i'm working to figure out why

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

linprocfs.c patch:
```
diff --git a/sys/compat/linprocfs/linprocfs.c b/sys/compat/linprocfs/linprocfs.c
index 27acd7d651a7..09940cd3055d 100644
--- a/sys/compat/linprocfs/linprocfs.c
+++ b/sys/compat/linprocfs/linprocfs.c
@@ -1660,6 +1660,20 @@ linprocfs_dominfree(PFS_FILL_ARGS)
 	return (0);
 }
 
+/*
+ * Filler function for proc/fs/inotify/max_user_watches
+ */
+static int
+linprocfs_domaxuserwatches(PFS_FILL_ARGS)
+{
+
+    uint16_t zero = 0;
+	sbuf_printf(sb, "%u\n", --zero);
+	return (0);
+}
+
+
+
 /*
  * Filler function for proc/scsi/device_info
  */
@@ -2075,6 +2089,14 @@ linprocfs_init(PFS_INIT_ARGS)
 	pfs_create_file(dir, "min_free_kbytes", &linprocfs_dominfree,
 	    NULL, NULL, NULL, PFS_RD);
 
+	/* /proc/sys/fs/.... */
+	dir = pfs_create_dir(sys, "fs", NULL, NULL, NULL, 0);
+
+	/* /proc/sys/fs/inotify/.... */
+	dir = pfs_create_dir(dir, "inotify", NULL, NULL, NULL, 0);
+    pfs_create_file(dir, "max_user_watches", &linprocfs_domaxuserwatches,
+	    NULL, NULL, NULL, PFS_RD);
+
 	return (0);
 }
```
