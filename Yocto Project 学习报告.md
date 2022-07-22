### Yocto Project 学习报告

### 一、 相关术语介绍

##### 1. OpenEmbedded (OE)

一个用于为嵌入式设备创建Linux发行版的自动化构建框架和交叉编译环境。OE 是yocto project的构建系统，主要为其提供构建引擎（BitBake）和构建配置文件（Metadata，元数据）。

##### 2. Yocto Project (YP)

Yocto Project 是一个开源的合作项目，用来帮助开发者不考虑硬件架构为嵌入式产品构建定制的基于Linux的系统。该项目提供了发布硬件支持和软件堆栈的标准，允许交换软件配置和构建。

##### 3. Poky

Poky 是yocto project的官方参考Linux发行版。它包含OE构建系统（BitBake 和 oe-core）以及让你开始构建自己的Linux发行版的元数据。

> Poky 不包含二进制文件。是一个如何从源代码构建您自己的自定义 Linux 发行版的工作示例。

OE，Poky, YP三者关系如下：

![Screenshot from 2022-07-17 11-14-47.png](/home/yongy/Pictures/Screenshot%20from%202022-07-17%2011-14-47.png)

Poky 包含以下核心组件

                                                                                所在目录

- BitBake工具                                                    (poky/bitbake)

- Build scripts                                                   (poky/scripts)

- 基础包recipes（oe-core）                           (poky/meta)

- meta-poky （包含发行版policy）               (poky/meta-poky)

- Reference BSP                                              (poky/meta-yocto-bsp)

- yocto project documentation                    (poky/documentation)

#### 4. Metadata (元数据)

包含如何构建镜像信息的文件。主要有以下几种：

- Recipes (.bb)    包含如何下载包源代码，该包的依赖库和其他recipes，以及配置、编译选项和安装包的指令等等。最重要的一类元数据。

- Configuration (.conf)    定义默认值。
  
  - local.conf    配置构建系统。主要包含以下变量：
    
    - MACHINE（我们正在构建的机器，选项有qemuarm、qemumips、qemumips64等等）
    
    - DL_DIR（首次构建系统时下载源代码压缩包的存放目录）
    
    - SSTATE_DIR（BitBake支持增量式构建，基于shared state cache。share state 文件存放目录）
    
    - SDKMACHINE（SDK目标架构，选项有i686、x86_64、aarch64）
    
    - 以及优化选项以减少最大构建时间（BB_NUMBER_THREADS、PARALLEL_MAKE）
    
    - PACKAGE_CLASSES（包管理选项，生成何种类型的包，deb|ipk|rpm，OE-Core默认是ipkg，然而Poky默认是rpm
  
  - bblayer.conf    告诉BitBake构建期间考虑那些层。主要包含
    
    - BBPATH    主搜索路径，类似与shell中的PATH变量
    
    - BBFILES     所有包的recipes名称的变量
    
    - BBLAYERS    包含BitBake所处理层的变量

- BitBake classes (.bbclass)   该文件包含recipes中共有变量定义，可以被不同的recipe文件继承。
  
  - 在recipes文件中，`inherit autotools` 将使BitBake包含`autotools.bbclass`文件（该文件通过BBPATH在classes目录下找到）

- Append files (.bbappend)    定义.bb文件的附加元数据，可以新加或覆盖原来配方文件中的信息。在命名附加文件时，可以使用通配符（%）来匹配 recipes file 名称。如busybox_1.21.%.bbappend

- Include files (.inc)    用于在元数据间共享信息
  
  - 使用.inc文件在recipes之间共享元数据的两种方式
    
    - `include file.inc`    将包含.inc文件，如果未发现file.inc，继续而不报错
    
    - `require file.inc`    与`include`相似，如果未发现file.inc，报错

#### 5. BitBake

一个由Python实现的构建引擎（任务执行器和调度器）。BitBake根据recipes(.bb)和recipes append files(.bbappend)执行相应的任务。标准recipes的构建如下：

- do_fetch: 定位并下载源代码

- do_unpack: 将源代码解压到工作目录

- do_patch: 应用补丁文件

- do_configure: 执行必要的预构建配置

- do_compile: 利用指定编译器编译源代码

- do_install: 在WORKDIR中安装

- do_package_sysroot:    将artifacts复制到sysroot

- do_package:    创建二进制包

BitBake中的重要变量

- BitBake自动设置的变量
  
  - TOPDIR    （build 目录）
  
  - LAYERDIR    （当前层目录）
  
  - FILE     （将被处理的文件的路径和文件名）

- 控制构建的policy变量
  
  - BUILD_ARCH    （构建主机架构）
  
  - TARGET_ARCH    （目标机架构）
  
  - ...

- 构建时元数据
  
  - PN    Package Name (e.g. "myrecipe")
  
  - PV    Package Version
  
  - PR    Package Release
  
  - P      "${PN}-\${PV}"
  
  - PF    "\${PN}-\${PV}-\${PR}"
  
  - FILE_DIRNAME     (FILE 目录)
  
  - FILE_PATH
  
  - TMPDIR    "\${TOPDIR}/tmp"
  
  - WORKDIR     "\${TMPDIR}/work/\${PF}"
  
  - S      "\${WORKDIR}/\${R}"     (source dir)
  
  - B     "{S}"    (build dir)
  
  - D    "\${WORKDIR}/\${image}"    (destination dir)
  
  - DEPLOY_DIR    "\${TMPDIR}/deploy"
  
  - DEPLOY_DIR_IMAGE    "\${DEPLOY_DIR}/images"

- 常见元数据
  
  - SUMMARY   （对包和recipes的简短的描述）
  
  - DESCRIPTION    （对包和recipes详细的描述）
  
  - HOMEPAGE      （上游资源网页）
  
  - LICENSE     （所含源码遵循的协议）
  
  - LIC_FILES_CHECKSUM    （license 文件的校验和）
  
  - SRC_URI（哪里获取上游资源和应用那些补丁，BitBake可从诸如本地文件、源控制系统或对应网站获取源代码）
  
  - DEPENDS（依赖库或其他配置文件）
  
  - RDEPENDS（运行时依赖包）

#### 6. Layer (层)

Yocto 项目由层组成。层是包含一组BitBake元数据的存储库（目录），具有优先级，可以覆盖下层的策略(policy)和配置设置。

Yocto 项目采用层模型，层模型同时支持协作和定制。

*示例Poky的层模型*RT

```bash
                    其他层
            -----------------------
                 meta-yocto-bsp <----- 使用 meta-loongson 替换
            -----------------------
                   meta-poky    
            -----------------------
                     meta  （oe-core） <------  meta

注意：build/conf/bblayers.conf中的BBLAYERS变量的层顺序和优先级很重要。
     如果多个层定义了一个机器配置，构建系统将使用给定相同层优先级的最后一个层。构建
     系统自上而下通过BBLAYERS中列出的层工作。

poky/meta
    recipes-bsp          任何与特定硬件或硬件配置信息有关联的内容
    recipes-connectivity 与其他设备通信相关的库和应用
    recipes-core         需要用来构建一个基本可行的Linux镜像的内容（包含常用依赖）
    recipes-devtools     主要是构建系统使用的工具，也可在目标系统上使用
    recipes-extended     与核心中的应用比，虽不是必须的，但这些工具增添了更完整功能
    recipes-graphics     X和其他图形相关的系统库
    recipes-gnome        所有与GTK+应用框架相关的内容
    recipes-kernel       内核和具有较强内核依赖性的通用应用/库
    recipes-multimedia   支持声音，图片和视频的应用程序和codecs(编码译码器)
    recipes-rt           提供包和镜像recipes以使用和测试（抢占实时）PREEMPT_RT内核
    recipes-sato         sato示例/参考UI/UX，与其相关的APP和配置
    recipes-support      被其他recipes使用，但不直接包含在镜像中  
```

##### BitBake 创建层（使用bitbake-layers工具）

```bash
$bitbake-layers create-layer meta-mylayer # 创建一个名为meta-mylayer的层
$bitbake-layers add-layer meta-mylayer # 将新创建的层加入bblayers.conf中的
                                       # BBLAYERS
-----------------------------------------------------------------------
$bitbake-layers --help
usage: bitbake-layers [-d] [-q] [-F] [--color COLOR] [-h] <subcommand> ...

BitBake layers utility

optional arguments:
 -d, --debug Enable debug output
 -q, --quiet Print only errors
 -F, --force Force add without recipe parse verification
 --color COLOR Colorize output (where COLOR is auto, always, never)
 -h, --help show this help message and exit 


subcommands:
    show-layers         show current configured layers.
    show-overlayed      list overlayed recipes (where the same recipe exists
                        in another layer)
    show-recipes        list available recipes, showing the layer they are
                        provided by
    show-appends        list bbappend files and recipe files they apply to
    show-cross-depends  Show dependencies between recipes that cross layer
                        boundaries.
    layerindex-fetch    Fetches a layer from a layer index along with its
                        dependent layers, and adds them to conf/bblayers.conf.
    layerindex-show-depends
                        Find layer dependencies from layer index.
    add-layer           Add one or more layers to bblayers.conf.
    remove-layer        Remove one or more layers from bblayers.conf.
    flatten             flatten layer configuration into a separate output
                        directory.
    create-layer        Create a basic layer
```

 

#### BSP (Board Support Package)

BSP是为特定硬件平台（special board）启动支持的层，通常由厂商提供并维护，为主板定义机器配置变量。在该层，可添加特定机器的recipes和定制的Boot loader, Kernel config, Graphics drivers (e.g. Xorg), 支持硬件特征的额外的recipes。在loongos-la64中，meta-loongson应该就是定制的BSP。

```bash
poky/meta/recipes-bsp
    acpid
        描述： ACPID 是一个用于传递ACPI事件的完全灵活、完全可扩展的守护进程。它聆听
        网络连接接口（或聆听已弃用文件 /proc/acpi/event），当一个事件发生时执行程序
        处理该事件。执行的程序可通过一系列配置文件配置，这些配置文件可由包或管理员放置
        到位
    alsa-state
        描述：Alsa scenario file,一个初始化脚本和状态文件，用于在系统启动时恢复声音状态并在
        系统关闭时保存声音状态
    apmd
        描述：The Advanced Power Management (APM) 支持访问电池状态信息和一组管理
        电脑电量消耗的工具
    efibootmgr    （EFI Boot Manager）
        描述：修改EFI Boot Manager的Linux用户空间应用
    efivar        （管理UEFI变量的工具）
        描述：efivar提供对UEFI变量设备一个简单的命令行接口
    formfactor     （设备形状参数信息）
        描述：一个形状参数配置文件，提供关于被构建镜像的目标硬件的信息以及构建系统无法
        从其他源（如内核）获取的信息
    gnu-efi        （生成EFI二进制文件的库）
        描述：GNU-efi旨在使用GNU工具链和EFI开发环境为ARM-64，ARM-32，x86_64，
        IA_64(IPF)，IA-32(x86)和MIPS平台开发EFI应用
    grub
        描述：GRUB2是下一代GPLed Unified Bootloader 打算在x86操作系统上统一
        bootloading。除了装载Linux内核，它实现了多装载标准（Multiboot standard）
        允许灵活装载多个Boot images
    keymaps
        描述：键盘映射和初始化脚本，在启动时设置键盘映射
    libacpi        （ACPI数据收集库）
        描述：用于在Linux上收集ACPI数据的程序的通用共享库，实现热区、电池信息、风扇信息、
        交流状态。
    lrzsz        （zmodem/xmodem/ymodem文件传输工具）
        描述：Lrzsz是一个经过修饰的zmodem/ymodem/xmodem包，由Chuck Forsberg的
        rzsz包的公共域版本构建而成。这些程序使用纠错协议（{z，x，y}调制解调器）通过
        拨入串行端口从各种操作系统下运行的各种程序发送（sz，sx，sb）和接收
        （rz，rx，rb）文件。
    opensbi    （RISC-V Open Source Supervisor Binary Interface）
        描述：OpenSBI旨在为平台特定固件（M模式）和通用操作系统、虚拟机监控程序或
        引导程序（S模式或HS模式）提供RISC-V SBI规范的开源和可扩展实现。RISC-V平台
        或片上系统供应商可以轻松扩展OpenSBI实现，以适应特定的硬件配置

    pciutils    （PCI 工具）
        描述：PCI实用程序包包含一个用于便携式访问PCI总线配置空间的库和基于该库的几个
        实用程序
    pm-utils    （电源管理工具和脚本）
        描述：简单的shell命令行工具去挂起和休眠
    setserial   （控制串行端口的配置）
        描述：setserial 是一个程序，用于设置和/或报告与串行端口相关的配置信息
    u-boot      （嵌入式设备通用Boot Loader）
    usbinit     （启用USB小工具以太网的初始化脚本）
        描述：该模块允许通过USB进行以太网仿真，允许以比大多数Wifi连接更高的速度一次性
        完成SSH和NFS等各种东西，并通过同一根电线充电。
    usbutils    （主机端USB控制台实用程序）
        描述：包含用于检查连接到USB总线的设备的lsusb实用程序
    v86d        （uvesafb内核模块的用户支持二进制文件）   
        描述：v86d为需要执行x86 BIOS代码的内核驱动程序提供了后端。代码在受控环境中
        执行，结果通过netlink接口传回内核

poky/meta-yocto-bsp
    可通过该层对recipes-bsp, recipes-graphics, recipes-kernel进行补充
poky/meta-yocto-bsp/recipes-bsp
    formfactor  （使用formfactor_0.0.bbappend补充）
    gma500-gfx-check    （Intel gma500_gfx fix for certain hardware）
        描述：避免为某些硬件设备插入gma500_gfx模块
```

#### SSTATE CACHE (shared state cache，共享状态缓存)

Yocto 项目实现了支持增量构建的共享状态代码。构建系统通过构建任务输入的校验和（或签名）来检测给定任务的“输入”变化。校验和改变，系统假定输入已经改变且需要重新运行任务。共享状态 (sstate) 代码跟踪哪些任务将哪些输出添加到构建过程。这意味着可以删除、升级或以其他方式操纵给定任务的输出。

### Loongos-la64

```bash
loongos-la64/
    sources  <-- 所有的yocto layer
    |—— meta-openembedded 保存其他BSP层的层（容器层）
    |—— meta-clang
    |—— meta-dpdk
    |—— meta-mingw
    |—— meta-openwrt
    |—— meta-phosphor
    |—— meta-python2
    |—— meta-qt5
    |—— meta-tensorflow
    |—— meta-virtualization
    |—— meta-loongson                                  <—— 软链接
    |__ poky    <-- yocto 参考发行版（BitBake工具和oe-core） |
    meta-loongson    <-- BSP                           ——>    
    scripts          <-- 脚本文件
    |—— setup-environment.sh 环境设置脚本，完成bitbake的基本配置
    |__ manifest.xml, manifest-master.xml 项目展示
    qemu     <-- em...暂时没搞清楚其用途
```

构建了meta-loongson层

```bash
meta-loongson/
    classes            <-- 存在公共类文件(*.bbclass)
    conf               <-- 配置文件
    |
    
    recipes-benchmarks
    recipes-bsp
    recipes-connectivity
    recipes-core
    recipes-dbs
    recipes-devtools
    recipes-extended
    recipes-gnome
    recipes-graphics
    recipes-images
    recipes-kernel
    recipes-loongos
    recipes-multimedia
    recipes-navigation
    recipes-qt
    recipes-support
    recipes-xenomai
        描述：给用户空间提供xenomai支持，以及用来实现基于xenomai RTOS实现的实时应用
        程序的库
    recipes-helloworld    # 参考recipe
```

#### 概念区别

**OpenEmbedded Classic (OE-Classic) metadata repository**, OE-经典元数据库更像是一组recipes集合，可以从中找到需要包或库的recipes。[OE-Classic](https://github.com/openembedded/openembedded).

OpenEmbedded-Core (OE-Core) ,是一个包含当前OpenEmbedded版本的核心元数据层。它是无发行版的（可以使用DISTRO = "nodistro"构建起作用的镜像）并且只包含模拟机器支持。

<img src="file:///home/yongy/Pictures/Screenshot%20from%202022-07-19%2015-42-18.png" title="" alt="Screenshot from 2022-07-19 15-42-18.png" width="259">

#### 公共代码库

http://git.yoctoproject.org



#### 
