---
title: Manjaro显卡驱动问题开机黑屏，配置源，机场etc
date: 2020/03/23 17:13
tags: 
    - linux
    - manjaro
    - arch
    - 黑屏
    - 机场
---
## 安装
### 刻录软件：[rufus](https://rufus.ie/)，刻录模式建议选择dd
## 遇到的问题1(安装时卡住)
```shell
Started TLP system startup/shutdown
A start job is running for livemedia mhwd scripe(xxxx)
```
### 解决方法
1. 引导开机后进入安装启动界面，选择BOOT栏
2. 按e键进入编辑模式，将driver=free改成driver=intel
3. 在后面加上xdriver=mesa acpi_osi=! acpi_osi="Windows 2009"
4. 按ctrl+x或F10启动
### 此时可以进入安装界面，可参考其他教程按自己所需进行分区，我个人一般不分配/home空间，直接大部分给/，即根目录，swap分区因为笔记本16g的内存，我会给到8g，这个看个人情况，/boot启动分区最为重要，一定要记住盘区/sd×，设置为启动引导分区，切勿选错。
## 分区安装完后重启依然会黑屏，解决方法
### 启动进入grub引导界面，默认即Manjaro选项卡，在此选项卡按e进入编辑页面，在倒数第二行找到quite，在其后添加acpi_osi=! acpi_osi='Windows 2009'，然后按F10进入系统
## 进入系统修改启动文件grub.cfg来彻底解决黑屏
### ctrl+alt+t打开终端，输入
> sudo nano /boot/grub/grub.cfg
### <font color=#ff0000 size=3>如果没有安装nano可以使用vim或者vi打开</font>
### 打开后找到linux   /boot/vmlinuz-5.4-x86_64 root=UUID=a9b1b419-f272-4f3c-90ae-30c57807cb1e rw  quiet这一行，不同linux版本可能有一些差别，在quiet后面添加<font color=#ff0000 size=3>xdriver=mesa acpi_osi=! acpi_osi="Windows 2009"</font>即可,按ctrl+o(字母)提示保存，再按回车即可，按ctrl+x退出。
## 配置pacman源
> sudo pacman-mirrors -i -c China -m rank
### 在弹出的窗口选择合适的一个或者几个
## 配置archlinuxcn源
>sudo nano /etc/pacman.conf
### 在末尾添加以下内容：
```shell
[archlinuxcn]

SigLevel = Optional TrustedOnly

Server = http://repo.archlinuxcn.org/$arch
```
### 之后执行：
```shell
sudo pacman-mirrors -g      #更新
sudo pacman -Syyu           #更新系统
sudo pacman -S archlinuxcn-keyring  #导入keyring
```
## 设置代理
### 根据不同机场提供的不同规则选择软件，目前比较稳的如v2ray和trojan，linux端的gui软件推荐[qv2ray](https://github.com/Qv2ray/Qv2ray),核心用的[v2ray](https://github.com/v2ray/v2ray-core),点击跳转到qv2ray的[下载地址](https://github.com/Qv2ray/Qv2ray/releases)或者直接使用命令安装：
>sudo pacman -S v2ray qv2ray
### [trojan](https://github.com/trojan-gfw/trojan)的安装方法
>sudo pacman -S trojan
### trojan安装完后需要配置一下才能使用，然后再设置自启动就可以了。
## 配置qv2ray
### qv2ray图形界面比较容易操作，根据机场提供的订阅地址输入后即可以代理。如图，点击左上角订阅，然后输入订阅地址既可。具体可以参考[wiki](https://github.com/Qv2ray/Qv2ray/wiki/Getting-Started-step0_zh)
![ ](/notes/blogImg/qv2ray.png)
## 配置trojan
> sudo nano /etc/trojan/config.json
### 打开配置文件后只需要更改以下几个选项
```shell
    "run_type": "client",
    "local_addr": "127.0.0.1",  //此为本地地址
    "local_port": 1080,         //设置端口，可根据自己需要更改
    "remote_addr": "此地址由机场提供",//机场提供的地址
    "remote_port": 443,            // 机场提供的端口
    "password": [
        "机场提供的密码"     //机场提供的密码
```
### 设置完毕后按ctrl+o(字母)提示保存，再按回车，按ctrl+x退出
## 推荐的机场
### 我目前自用的主力，用了很久了，稳定，速度可以，主要是价格也可以，注册可先体验，128g每月年付88,256g每月年付128，我个人建议128g足够，我不看视频的话一个月大概才用10-20g流量，远远足够，不过每个人可以根据自己的需求使用，可以走我[链接](https://pud.life/aff/geOg)注册，祝大家用的愉快。
