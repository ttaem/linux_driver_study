#include <stdio.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

#define SAMPLE_IOCTL_MAGIC      'G'
#define SAMPLE_IOCTL_WRITE      _IOW(SAMPLE_IOCTL_MAGIC, 0, int)

/* First you need run "mknod /dev/my_char_device c 202 0" to create /dev/my_char_device */

int main(void)
{
        int ret;
        int my_dev = open("/dev/my_char_device", 0);

        if (my_dev < 0) {
                perror("Fail to open device file: /dev/my_char_device");
        } else {
                ret = ioctl(my_dev, 100, 200);
                if (ret < 0) {
                        perror("Fail to ioctl");
                }
                close(my_dev);
        }
}
