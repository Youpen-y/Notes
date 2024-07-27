#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

int main() {
    int master, slave;
    char buf[1024];

    // 创建伪终端对
    if (openpty(&master, &slave, NULL, NULL, NULL) == -1) {
	perror("Failed to openpty");
	exit(1);
    }

    printf("Master device: %s\n", ttyname(master));
    printf("Slave device: %s\n", ttyname(slave));

    // 在从设备上启动终端仿真器
    pid_t pid = fork();
    if (pid == -1) {
	perror("Fork failed");
	exit(1);
    } else if (pid == 0) {
	// 子进程执行终端仿真器，例如启动shell
	close(master);	// 关闭主设备
	dup2(slave, STDIN_FILENO);
	dup2(slave, STDOUT_FILENO);
	dup2(slave, STDERR_FILENO);
	close(slave);	// 关闭从设备
	
	// 替换为终端仿真器，例如/bin/bash
	execl("/bin/bash", "/bin/bash", NULL);
	perror("Exec failed");
	exit(1);
    }

    // 父进程从主设备上读取终端输出
    close(slave); // 关闭主设备
    
    while (1) {
	ssize_t bytesRead = read(master , buf, sizeof(buf));
	if (bytesRead <= 0)
	    break;

	// 处理终端输出，这里简单地将其打印到标准输出
	write(STDOUT_FILENO, buf, bytesRead);
    }

    // 等待子进程结束
    int status;
    waitpid(pid, &status, 0);

    return 0;
}

