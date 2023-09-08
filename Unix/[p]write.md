#### The difference between read/write and pread/pwrite

```c
#include <unistd.h>

ssize_t read(int fd, void *buf, size_t count);
ssize_t write(int fd, const void *buf, size_t count);

ssize_t pread(int fd, void *buf, size_t count, off_t offset);
ssize_t pwrite(int fd, const void *buf, size_t count, off_t offset);
```

```c
#include <sys/types.h>
#include <unistd.h>

off_t lseek(int fd, off_t offset, int whence);
/* whence
* SEEK_SET: The offset is set to offset bytes
* SEEK_CUR: The offset is set to its current location plus offset bytes
* SEEK_END: The offset is set to the size of the filed plus offset bytes
* since version 3.1, Linux supports additional whence
* SEEK_DATA: Adjust the file offset to the next location in the file
*greater than or equal to offset containing data. If offset points to
*data, then the file offset is set to offset.
* SEEK_HOLE: Adjust the file offset to next hole in the file greater than
*or equal to offset. If offsets points into the middle of a hole, then the
*file offset is set to offset. If there is no hole past offset, then the 
*file offset is adjusted to the end of the file(i.e., there is an implicit
*hole at the end of any file).
*/
```

**A hole is a gap within the file for which there are no allocated data blocks.**  



E.g. a 3KB file contains a 1KB data block followed by a 1KB hole followed by another 1KB data block. **When reading over a hole, zeroes will be returned.**



进程打开的每个文件都有一个当前文件指针(current file pointer/file offset)指示下次读取和写入的位置。

> ***Pread()* works just like *read()* but reads from  the specified position in the file without modifying the file pointer.** 
> 
> This atomicity of pread  enables processes or threads that share file descriptors to read from a shared file at a particular offset without using a locking mechanism that would be necessary to achieve the same result in separate lseek and read system calls. 
> 
> Atomicity is required as the file pointer is shared and  one thread might move the pointer using lseek after another process completes an lseek but prior to the read.
> 
> --- Stackoverflow-[what is the difference between read and pread in unix](https://unix.stackexchange.com/questions/166569/is-partition-table-type-loop-a-good-or-bad-idea-on-btrfs)

lseek + write, pwrite 类似
