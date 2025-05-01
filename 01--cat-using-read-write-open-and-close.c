#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#define BUF_SIZE 4096

int main(int argc, char *argv[]) {
    int fd;
    ssize_t nread;
    char buf[BUF_SIZE];

    if (argc == 1) {
        while ((nread = read(0, buf, BUF_SIZE)) > 0)
            write(1, buf, nread);  
    } else {
        for (int i = 1; i < argc; i++) {
            fd = open(argv[i], O_RDONLY);
            if (fd < 0) {
                perror(argv[i]);
                return 1;
            }

            while ((nread = read(fd, buf, BUF_SIZE)) > 0)
                write(1, buf, nread);

            close(fd);
        }
    }

    return 0;
}

/*
Using System Calls
$ time ./01--cat-using-read-write-open-and-close.out file1.txt > /dev/null

real    0m0.061s
user    0m0.015s
sys     0m0.030s
*/
/*
#include <stdio.h>
#define getchar() getc(stdin)
#define putchar(c) putc((c), stdout)

// cat: concatenate files, version 1
main(int argc, char *argv[])
{
  FILE *fp;
  void filecopy(FILE *, FILE *);
  
  if (argc == 1) // no args; copy standard input 
    filecopy(stdin, stdout);
  else
    while(--argc > 0)
      if ((fp = fopen(*++argv, "r")) == NULL) {
        printf("cat: can't open %s\n", *argv);
        return 1;
      } else {
          filecopy(fp, stdout);
          fclose(fp);
      }
  return 0;
}
// filecopy: copy file ifp to file ofp
void filecopy(FILE *ifp, FILE *ofp)
{
  int c;
  
  while ((c = getc(ifp)) != EOF)
    putc(c, ofp);
}
*/
/* 
Using Standard Lib Cat from Chapter 7
$ time ./01--cat-using-read-write-open-and-close.out file1.txt > /dev/null

real    0m8.332s
user    0m7.859s
sys     0m0.203s
*/
