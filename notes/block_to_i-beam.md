---
title: spacemacs 光标block转换为I-beam
date: 2020/05/18 21：29
tags: 
    - spacemacs
    - manjaro
    - arch
    - emacs
---
# spacemacs 光标block转换为I-beam
## 打开.spacemacs文件:
>sudo nano ~/.spacemacs
### 使用ctrl+w打开搜索，输入user-config进行定位，或者直接定位到最后面。在此配置里面添加:
>(setq evil-emacs-state-cursor '("red" bar))
### 添加后如图:
![ ](/notes/blogImg/5.18.5.png)
### 重启spacemacs即可。


## 参考链接:
[A community-driven Emacs distribution](https://gitter.im/syl20bnr/spacemacs/archives/2017/04/13)
## 附图:
## 1、![ ](/notes/blogImg/5.18.1.png)

## 2、![ ](/notes/blogImg/5.18.2.png)

## 3、![ ](/notes/blogImg/5.18.3.png)

## 4、![ ](/notes/blogImg/5.18.4.png)
