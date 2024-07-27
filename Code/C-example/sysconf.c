#include <stdio.h>
#include <unistd.h>

/* sysconf: Used to retrieve system configuration values at runtime.
 * _SC_ARG_MAX, 命令行参数的最大长度
 * _SC_CHILD_MAX, 每个用户ID下可同时运行的最大进程数
 * _SC_CLK_TCK, 每秒时钟滴答数
 * _SC_OPEN_MAX, 一个进程可打开的最大文件数
 * _SC_PAGESIZE, 系统页大小
 * _SC_PHYS_PAGES, 系统内存中物理页总数
 * _SC_NPROCESSORS_CONF, 配置的处理器数目
 * _SC_NPROCESSORS_ONLN, 当前在线的（可用的）处理器数
 */


int main(){
    long int max_command_arg = sysconf(_SC_ARG_MAX);
    long int max_childs = sysconf(_SC_CHILD_MAX);
    long int num_clk_tck = sysconf(_SC_CLK_TCK);
    long int num_files = sysconf(_SC_OPEN_MAX);
    long int page_size = sysconf(_SC_PAGESIZE);
    long int phys_pages = sysconf(_SC_PHYS_PAGES);
    long int nprocessors_conf = sysconf(_SC_NPROCESSORS_CONF);
    long int nprocessors_onln = sysconf(_SC_NPROCESSORS_ONLN);

    printf("Maximum length of command-line arguments: %ld\n", max_command_arg);
    printf("Maximum number of simultaneous processes per user ID: %ld\n", max_childs);
    printf("Number of clock ticks per second: %ld\n", num_clk_tck);
    printf("Maximum number of files that a process can have open at any time: %ld\n", num_files);
    printf("Page size of the system: %ld\n", page_size);
    printf("Total number of physical pages in the system's main memory: %ld\n", phys_pages);
    printf("Number of processors configured: %ld\n", nprocessors_conf);
    printf("Number of processors currently online (available): %ld\n", nprocessors_onln);
    return 0;
}
