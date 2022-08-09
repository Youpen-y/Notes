### File

> A file is any source, with a name, from which data can be read; or any target, with a name, to which data can be written.

- 普通文件
  
  - 文本文件
  
  - 二进制文件

- 目录（directory; folder in Windows directory-like in unix）

- 假文件（提供像访问文件一样可访问的服务，通常为内核使用）
  
  - 特殊文件（设备文件，一个特殊文件是一个物理设备的内部表示，如键盘、显示屏、打印机、磁盘驱动），Unix把所有特殊文件放在`/dev`目录下。
  
  - named pipes (enables you to connect the output of one program to the input of another)
  
  - proc files（允许你访问驻留在内核的信息，在某些特殊示例中，你甚至可以使用proc文件改变内核的数据。起初，这些文件被创建用来提供进程运行时的信息）

----

#### 特殊文件

```
# Hardware
/dev/fd0    floppy disk
/dev/hda    hard disk
/dev/hda1   hard disk: partition 1
/dev/sda    SCSI hard disk
/dev/sda1   SCSI hard disk: partition 1
/dev/sda1   USB flash memory card
/dev/lp0    printer
/dev/usb/lp0    USB printer

# ===================================
# Terminals
/dev/tty    current terminal
/dev/tty1   console / virtual console
/dev/pts/0  pseudo terminal
/dev/ttyp0  pseudo terminal

# ===================================
# Pseudo-devices
/dev/null    discard output, input returns nothing (eof)
/dev/zero    discard output; input returns nulls (0s)
/dev/random  random number generator
/dev/urandom random number generator 
```

软盘：fd0, fd1, fd2...

硬盘：hda, hdb...

硬盘驱动被组织成一个或多个分区，当作单独的设备。第一个硬盘的第一块分区称为/dev/hda1，如果有第2块，称为/dev/hda2。SCSI和SATA硬盘驱动有它们自己的名字。第一个SCSI或SATA驱动是/dev/sda，第二个是/dev/sdb...。同样，分区被编号，/dev/sda1...。

SCSI designations有时也被用作其他类型的设备。一个常见的例子是USB闪存，被当作好像是可移除的SCSI磁盘。由于这个原因，闪存的名称将被命名为/dev/sda1或某些相似的。

> SCSI (Small Computer System Interface)一组计算机和外部设备之间物理连接和数据传输的标准。SCSI标准定义命令、协议、电气、光学和逻辑接口。SCSI标准为特定的外设类型定义命令集；Unknown作为这些类型之一的存在意味着理论上它可以用作几乎任何设备的接口，但该标准非常实用并且针对商业需求。最初Parallel SCSI并行SCSI通常用作硬盘驱动和磁带驱动，但它可以连接非常广泛范围的其他设备。包括扫描仪和CD驱动，尽管并非所有控制器都可以处理所有设备。



#### Special files for terminals: tty

在早前，终端是连接到一个主机电脑上的独立的设备。这样的终端使用特殊文件/dev/tty1, /dev/tty2命名。（tty, 来源于早期Unix终端Teletype machines.）

当在单用户模式下运行Unix时，键盘和显示屏充当内置基于文本的终端。用来表示这个终端的特殊文件是/dev/tty1。

当在一个窗口中使用GUI运行终端仿真时，因为这并不是真正的终端，UNIX创建伪终端PTY去仿真一个终端。

伪终端可能的名字（/dev/ttyp0, /dev/ttyp1）或（/dev/pts/1, /dev/pts/2），可在终端调用tty程序查看终端名。

PTY 充当终端的情况：

- 当你在GUI中打开一个终端窗口

- 连接到一个远程UNIX主机

#### Special files for pseudo-devices

伪设备是充当输入源或输出目标的文件，但和真实设备无关，既不是真实的也不是仿真的。两个最有用的假设备文件是NULL FILE和ZERO FILE。空文件是/dev/null；零文件是/dev/zero。任何写向这些设备的输出被丢弃。因此，有时这些文件被称为bit buckets（垃圾框）

```
$ cat /etc/passwd > /dev/null
$ cat /etc/passwd > /dev/zero
```

两者的区别在于

当一个程序从/dev/null读取时，结果总是eof符号，即nothing。

当一个程序从/dev/zero读取时，结果总是0（数字0），在Unix中，该值被当作NULL CHARACTER 或 NULL。

> The terminology is a bit confusing: the null file returns nothing, while the zero file returns nulls. Such is life.
