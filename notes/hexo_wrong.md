---
title: 今日配置hexo博客出错的问题及解决办法
date: 2020/05/19 19：10
tags: 
    - hexo
    - manjaro
    - arch
    - nodejs
    - blog
    - pacman
---

### 执行:
>hexo deploy
### 报错:
```bash
FATAL Something's wrong. Maybe you can find the solution here: https://hexo.io/docs/troubleshooting.html
TypeError [ERR_INVALID_ARG_TYPE]: The "mode" argument must be integer. Received an instance of Object                                           
    at copyFile (fs.js:1890:10)
    at tryCatcher (/home/du/nswy123/node_modules/bluebird/js/release/util.js:16:23)                                                             
    at ret (eval at makeNodePromisifiedEval (/usr/lib/node_modules/hexo/node_modules/bluebird/js/release/promisify.js:184:12), <anonymous>:13:39)                                                                       
    at /home/du/nswy123/node_modules/hexo-fs/lib/fs.js:144:39
    at tryCatcher (/home/du/nswy123/node_modules/bluebird/js/release/util.js:16:23)                                                             
    at Promise._settlePromiseFromHandler (/home/du/nswy123/node_modules/bluebird/js/release/promise.js:547:31)                                  
    at Promise._settlePromise (/home/du/nswy123/node_modules/bluebird/js/release/promise.js:604:18)                                             
    ...
```
### 解决方法:
### 此次问题是因为升级nodejs后导致的，查找[相关资料](https://zhuanlan.zhihu.com/p/136552969),发现同样的问题，解决方法就是降级nodejs，本系统使用的是基于arch的manjaro系统，nodejs已经升级为14.2.0,也就是使用pacman作为包管理器，因此降级的方法有以下几种。
---
1、
```bash
sudo pacman -S nvm  # nvm: node version manage
nvm use --delete-prefix v12.16.3
```
2、(个人不建议使用此法) 在[这里](https://mirrors.tuna.tsinghua.edu.cn/)找到nodejs的12.16.3版本，或者目前lst的lastest，下载后使用pacman安装，such as:
>sudo pacman -U "files"

此方法我没有成功，显示缺少medata，可能还是因为依赖的关系吧。

3、
(不建议) 使用downgrade包进行管理:
```bash
sudo pacman -S downgrade
downgrade nodejs
```
此方法我又失败了，以降级firefox为例，具体为:
>downgrade firefox

报错:

```bash
Downgrading from A.L.A. is disabled on the stable branch. To override this behavior, set DOWNGRADE_FROM_ALA to 1 .
See https://wiki.manjaro.org/index.php?title=Using_Downgrade  for more details.

Unable to downgrade firefox
```

按照提示输入:
>DOWNGRADE_FROM_ALA = 1

依然无用.

---
### 再次执行:
>hexo d
### 又一次报错:
```bash
ERROR Plugin load failed: hexo-directory-category
TypeError: rule must be a function, a string or a regular expression.
at new Pattern (/Users/me/wiki-site/node_modules/hexo/node_modules/hexo-util/lib/pattern.js:17:11)
```
### 查阅[相关资料](http://www.hfkstackoverflow.top/2017/12/10/HEXO%E6%90%AD%E5%BB%BA%E4%B8%AA%E4%BA%BA%E5%8D%9A%E5%AE%A2/),使用yarn管理包极为方便:
```bash
# 移除包
yarn remove hexo-directory-category
# 添加包
yarn add hexo-directory-category -S
```
### 再次输入:
>hexo d
### 第三次报错:
```bash
INFO  Deploying: git
INFO  Clearing .deploy_git folder...
FATAL Something's wrong. Maybe you can find the solution here: https://hexo.io/docs/troubleshooting.html
Error: EACCES: permission denied, unlink '/home/du/nswy123/.deploy_git/archives/index.html'         
```
### 显然是因为权限不够的原因，查看报错文件夹的权限:
>ls ~/nswy123/.deploy_git -al
### 输出:
```bash
total 36
drwxr-xr-x  9 du   du   4096  5月 19 18:23 .
drwxr-xr-x  8 du   du   4096  5月 19 18:22 ..
drwxr-xr-x  5 root root 4096  5月 19 18:21 2020
drwxr-xr-x  3 root root 4096  5月 19 18:21 archives
drwxr-xr-x  4 root root 4096  5月 19 18:21 assets
drwxr-xr-x  2 root root 4096  5月 19 18:21 fonts
drwxr-xr-x  8 du   du   4096  5月 19 18:21 .git
drwxr-xr-x  2 root root 4096  5月 19 18:21 img
drwxr-xr-x 13 root root 4096  5月 19 18:21 tags
```
### 为了确保权限足够，我直接加满了权限:
>sudo chmod -R 777 ~/nswy123/.deploy_git
### 大家可以根据自己的情况添加相关权限，或者直接像我这样大力出奇迹,不过我承认这不是一个好习惯。。
### 再次执行:
>hexo d
### 提示输入github帐号和密码，成功。
### By the way,祝贺小笨同学科三满分通过~