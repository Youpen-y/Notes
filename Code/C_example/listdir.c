#include <assert.h>
#include <stdio.h>
#include <dirent.h>

int main(int argc, char **argv)
{
    DIR *dp = opendir(".");
    assert(dp != NULL);
    struct dirent *d;
    while((d = readdir(dp))!=NULL){
	printf("inode: %d\t name: %s\n", (int)d->d_ino, d->d_name);
    }
    closedir(dp);
    return 0;
}

