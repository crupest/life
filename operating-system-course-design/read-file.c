#include <bits/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

int main() {
  int fd = open("/mnt/fat-test/big", O_RDONLY);
  if (fd < 0)
    return 1;

  __off_t size = lseek(fd, 0, SEEK_END);
  if (size < 0)
    return 2;

  for (__off_t i = 512; i <= size; i += 512) {
    if (lseek(fd, size - i, SEEK_SET) < 0)
      return 3;
    char buffer[512];
    if (read(fd, buffer, 512) < 0)
      return 4;
  }

  return 0;
}
