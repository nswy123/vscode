---
title: KDE开机baloo_file_extractor占用cpu过高导致卡顿问题
date: 2020/03/08 10:45
tags: 
    - linux
    - KDE
    - manjaro
---
### <font size=3> 使用htop命令或top命令查看进程，发现 baloo_file_extractor 这个程序占用cpu很高，笔记本风扇持续不断运行，google一下发现这个问题在KDE在4.13版本的时候就有了，具体可以查看这个[帖子](https://forums.gentoo.org/viewtopic-p-7537940.html)</font>

### 这个程序的作用:
**<font size=3>framework for searching and managing metadata，在文件搜索时建立文件索引</font>**
### 解决办法:
**<font size=3>把 baloo_file 和 baloo_file_extractor 这两个文件备份，然后建立一个到 /bin/true 的链接</font>**
#### 依次执行以下命令:
```shell
sudo mv /usr/bin/baloo_file_extractor /usr/bin/baloo_file_extractor.bak
sudo ln -s /bin/true /usr/bin/baloo_file_extractor
sudo mv /usr/bin/baloo_file /usr/bin/baloo_file.bak
sudo ln -s /bin/true /usr/bin/baloo_file
```
#### 然后重启电脑即可
## 相关链接：
https://blog.csdn.net/kongxx/article/details/78809716
https://www.whatled.com/post-1594.html


