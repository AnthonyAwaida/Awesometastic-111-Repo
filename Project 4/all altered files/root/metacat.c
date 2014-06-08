#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <lib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int metaread(int fd, void *buf, size_t count)
{
	message m;
	m.m1_i1 = fd;
	m.m1_i2 = count;
	m.m1_p1 = (char *) buf;
	return (_syscall(VFS_PROC_NR, 105, &m));
}

int main (int argc, char **argv) {
  int fd;
  char buf[1024];
  if (argc == 1) printf("Usage: metacat [filename]\n");
	else if (argc != 2) { printf("metacat: Too many arguments\n"); exit(1); }
	else {
    fd = open(argv[1], O_RDONLY, 0);
    if (fd < 0) { printf("metacat: %s not found!\n", argv[1]); exit(1); }
    metaread(fd, buf, sizeof(buf));
    printf("metacat: %s: %s\n", argv[1], buf);
    close(fd);
  }
	exit(0);
}
