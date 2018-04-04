#include <iostream>
#include <fcntl.h>    //open
#include <unistd.h>   //write,lseek
#include <sys/stat.h> //st_mode

int main()
{
    char buf1[] = "abcdefghij";
    char buf2[] = "ABCDEFGHIJ";

    int fd;
    if ((fd = open("file.txt", O_WRONLY | O_CREAT | O_TRUNC, 0660)) < 0)
        std::cerr << "open error" << std::endl;
    if (write(fd, buf1, 10) != 10)
        std::cerr << "write error 1" << std::endl;
    if (lseek(fd, 1000, SEEK_SET) == -1)
        std::cerr << "lseek error" << std::endl;
    if (write(fd, buf2, 10) != 10)
        std::cerr << "write error 2" << std::endl;
    return 0;
}