#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <lib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int metawrite(int fd, const void *buf, size_t nbytes)
{
	message m;
	m.m1_i1 = fd;
	m.m1_p1 = (char *) __UNCONST(buf);
	m.m1_i2 = nbytes;
	return (_syscall(VFS_PROC_NR, 106, &m));
}

int main (int argc, char **argv) {
  int fd;
  if (argc <= 2) printf("Usage: metatag [filename] [metadata]\n");
  else if (argc > 3) { printf("metatag: Too many arguments!\n");
exit(1); }
  else {
    fd = open(argv[1], O_RDWR);
    if (fd < 0) { printf("metatag: %s not found!\n", argv[1]); exit(1); }
    metawrite(fd, argv[2], strlen(argv[2]));
    close(fd);
  }
  exit(0);
}

