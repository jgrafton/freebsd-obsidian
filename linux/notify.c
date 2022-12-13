#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <linux/inotify.h>

#define EVENT_SIZE (sizeof(struct inotify_event))
#define EVENT_BUF_LEN (1024 * (EVENT_SIZE + 16))

int main()
{
    int length;
    int fd;
    int wd;
    char buffer[EVENT_BUF_LEN];
    int i = 0;

    fd = inotify_init();

    if (fd < 0) {
        perror("inotify_event");
    }

    wd = inotify_add_watch(fd, "watchme", IN_CREATE | IN_DELETE);
    
    length = read(fd, buffer, EVENT_BUF_LEN);

    if (length < 0) {
        perror("read");
    }

    while (i < length) {
        struct inotify_event *event = ( struct inotify_event * ) &buffer[i];
        if (event->len ) {
            if ( event->mask & IN_CREATE ) {
                if ( event->mask & IN_ISDIR ) {
                    printf( "New directory %s created.\n", event->name );
                } else {
                    printf( "New file %s created.\n", event->name );
                }
            } else if ( event->mask & IN_DELETE ) {
                if ( event->mask & IN_ISDIR ) {
                    printf( "Directory %s deleted.\n", event->name );
                } else {
                    printf( "File %s deleted.\n", event->name );
                }

            }
        }
        i += EVENT_SIZE + event->len;
    } /* while */

    inotify_rm_watch( fd, wd );
    close( fd );

} /* main */
    
