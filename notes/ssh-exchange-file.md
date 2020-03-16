1、简述

通常，利用SSH管理远程Linux服务器时，经常需要与本地交互文件。当然，我们可以利用FTP方式，比如通过Filezilla客户端软件。不过直接使用SSH软件（SecureCRT、Xshell）自带的上传和下载功能无疑使最方便快捷的。通常SSH软件支持的文件传输协议主要有ASCII、Xmodem、Zmodem等。

rz，sz是便是Linux/Unix同Windows进行ZModem文件传输的命令行工具。

使用前提：

首先，你的Linux端（CentOS, Ubuntu）需要安装rz/sz命令，也就是 lszrz 包。

其次，windows端需要支持ZModem的telnet/ssh客户端(Xshell，SecureCRT支持,好像putty不支持)，SecureCRT就可以用SecureCRT登陆到Unix/Linux主机（telnet或ssh均可）

运行命令rz，即是接收文件，xshell就会弹出文件选择对话框，选好文件之后关闭对话框，文件就会上传到linux里的当前目录。如果要上传文件，直接用鼠标点住文件往X-shell里面一拖即是

运行命令 sz file 就是发文件到windows上（保存的目录是可以配置） 比ftp命令方便多了，而且服务器不用再开FTP服务了

2、文件传输协议

文件传输是数据交换的主要形式。在进行文件传输时，为使文件能被正确识别和传送，我们需要在两台计算机之间建立统一的传输协议。这个协议包括了文件的识别、传送的起止时间、错误的判断与纠正等内容。常见的传输协议有以下几种：

ASCII：这是最快的传输协议，但只能传送文本文件。

Xmodem：这种古老的传输协议速度较慢，但由于使用了CRC错误侦测方法，传输的准确率可高达99.6%。

Ymodem：这是Xmodem的改良版，使用了1024位区段传送，速度比Xmodem要快

Zmodem：Zmodem采用了串流式（streaming）传输方式，传输速度较快，而且还具有自动改变区段大小和断点续传、快速错误侦测等功能。这是目前最流行的文件传输协议。

3、在Linux上安装lrzsz

单单是SSH客户端软件支持以上文件传输协议（ASCII,Xmodem，Ymodem,Zmodem）还不行，我们的Linux服务器上也得安装相应的软件，以支持这些文件传输协议才行。在Linux上，lrzsz就是完成此任务的,lrzsz就是一个支持Zmodem 传输协议的工具。我们通过sz/rz两个命令，分别发送/接收文件。如果我们的系统中没有安装lrzsz这个包，就会报错，安装即可解决。

[root@localhost ~]# rz

-bash: rz: command not found

## For CentOS/RHEL

[root@localhost ~]# yum -y install lrzsz

## For Ubuntu

# sudo apt-get install lrzsz

4、理解记忆

其中，对于sz和rz的理解与记忆我用了如下的方法（很多时候容易搞混）：

sz中的s意为send（发送），告诉客户端，我（服务器）要发送文件 send to cilent，就等同于客户端在下载。

rz中的r意为received（接收），告诉客户端，我（服务器）要接收文件 received by cilent，就等同于客户端在上传。

记住一点，不论是send还是received，动作都是在服务器上发起的。我们习惯了说上传或是下载，其实大可不必。使用这两个命令，只要思考一点，是要把文件从服务器上发送出去，还是从客户端接收回来，就可以了。

好吧，最后总结为一句话：

我（客户端）上传，你（服务器）接收（RZ），我下载（客户端），你（服务器）发送（SZ）。

5、简单用法

sz用法：发送出去

### 下载一个文件：

# sz filename

### 下载多个文件：

# sz filename1 filename2

### 下载dir目录下的所有文件，不包含dir下的文件夹：

# sz dir/*

rz用法：接收回来

### 直接键入rz命令即可

# rz

### 直接拖动文件到 xshell， 或者 SecureCRT 窗口即可

输入rz回车后，会出现文件选择对话框，选择需要上传文件，一次可以指定多个文件，上传到服务器的路径为当前执行rz命令的目录。

6、设置默认路径

SecureCRT:

设置上传和下载的默认目录：

英文版： options — session options — X/Y/Zmodem。

中文版： 选项— 会话选项— X/Y/Zmodem。

Xshell:

设置上传和下载的默认目录：

File -> Properties -> ZMODEM

7、操作演示（仅演示Xshell,其他类似）

rz命令(下载)

当我们键入rz命令之后，会弹出文件选择对话框，选择需要传输的文件，点击 Add 即可。

接收的目录就是我们当前执行rz命令的目录。



今天又发现一个更简单直接的方法，直接选中文件，用鼠标点住文件往Xshell里面一拖就可以了。

sz命令（上传）

假设我要发送文件，直接使用sz命令， 其后接上文件名即可。同理，敲下回车后，也会弹出对话框，让我们选择接收的文件夹。

[root@localhost ~]# sz nagios-4.0.7.tar.gz nagios-plugins-2.0.3.tar.gz
8、问题

xshell或者SecureCRT 启动 tmux或screen之后，sz, rz 命令都无法弹出正常的文件选择窗口，该如何解决？

看起来 下不支持 ，所以这两个命令也用不了。

链接： http://sourceforge.net/p/tmux/tickets/6/

如果换用 的话应该是可以使用 sz/rz 的，很早之前我曾在 Windows 的 SecureCRT 上面成功使用过。

需要在 里面设置 ，也许还需要 。细节记得不是很清楚了。

9、缺点

使用lszrz非常方便，但是有一点不足之处： 无法传输大于 4G 的文件。
那肿么办呢？ 可以使用Filezilla， SecureFX 这些FTP工具来替代了。
