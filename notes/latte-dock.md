---
title: latte-dock 更新到0.9.9 右击dock栏无法打开设置
date: 2020/03/03 17:13
tags: 
    - linux
    - manjaro
    - dock
---
**<font color=#ff0000 size=3>2020年3月7日更新：latte-dock已经修复这个问题,此文留作参考</font>**
## 系统配置如下：
![systeminfo](https://raw.githubusercontent.com/nswy123/MarkDownImages/master/systeminfo.png)
### 关于latte-dock 0.9.9的更新内容如下：
``` update
 Version 0.9.9 
* CRITICAL: initialize properly configuration files during startup [kde#417886]
* IMPORTANT: Do not load a Shared Layout as Central when it is already loaded and as such do not mess the MultipleLayouts appearance when a Shared layout should also be used [kde#417886]
* [wayland] do not crash when right clicking Tasks plasmoid [kde#417546]
* update animations speed to support plasma 5.18 new animation speed values
* do not double release dock visibility after Meta application launcher triggering [kde#417239]
* improve blur region calculations in general and do not send invalid areas to kwin [kde#417254]
* improve blur area calculations during startup when parabolic effect is disabled [kde#416928]
* show Tasks icon size properly during startup when parabolic effect is disabled
```
### 我有试过按住<font color=#ff0000 size=3>ctrl+右击</font>，<font color=#ff0000 size=3>alt+右击</font>，<font color=#ff0000 size=3>shift+右击</font>dock，虽然有响应但是无法选择设置选项。google一通发现这个[帖子](https://store.kde.org/p/1169519/) 贴一下关键评论：
![右击latte-dock无反应](https://raw.githubusercontent.com/nswy123/MarkDownImages/master/latte-dock-update-review.png)
**<font color=#ff0000 size=3>原来直接用快捷键就可以打开了</font>**，**<font color=#ff0000 size=4>win+a </font>**，**<font color=#ff0000 size=3>win一般是alt左边的键，fn右边的键</font>**
### 如果你有多个latte-dock的话，一般是默认打开第一个dock
