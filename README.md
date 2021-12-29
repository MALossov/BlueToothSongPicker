<!--
 * @Description: 
 * @Author: MALossov
 * @Date: 2021-12-30 00:02:28
 * @LastEditTime: 2021-12-30 00:16:29
 * @LastEditors: MALossov
 * @Reference: 
-->
# BlueThoothedSongPicker

#### 介绍
电子科技大学2021年信通科协挑战杯A题一等奖代码

#### 软件架构
软件架构说明
本软件的架构分为上位机和下位机两个部分，下面将分别进行描述
- 上位机
  - 上位机通过**VS2017**编写而成，主要功能为：
    - 蓝牙串口通信的主机功能
    - MP3文件播放器的功能
- 下位机
  - 下位机通过**STM32CubeMX**+**Keil5**编程实现，主要功能为：
    - 蓝牙串口从机功能：发送蓝牙串口指令向上位机
    - 通过**STM32F103**开发板控制，**7针SPI协议的0.96‘OLED屏幕**和**4位的独立按键**

#### 安装教程

1.  上位机通过VS编译通过后可用在Windows平台中直接运行
2.  下位机通过**STM32CubeMX**再编译生成对应的**MDK-ARM**工程后通过**Keil5**生成二进制文件，烧写进单片机

#### 使用说明
##### 上位机部分
1.  需要再`main.cpp`文件之中选择对应的蓝牙串口，否则无法通过编译
2.  和下位机联系无提示，但是可用直接使用
3.  音乐文件存放的位置可在`main.cpp`中进行更改，利用列表方式读取，可存多首歌
##### 下位机使用说明
1. 下位机有两种模式：这两种模式使用4位独立按键中的第一颗进行切换
   1. 音量控制模式
   2. 曲目控制模式
2. 下位机的第二个按键为：暂停/播放按键，不受模式影响
3. 下位机的第三，第四个按键分别为：
   1. 声音控制模式下的：加/减声音按键
   2. 曲目控制中的：上一曲/下一曲按键

#### 参与贡献
0. 本项目的基础参与者
   1. **MALossov** ：完成下位机的设计
   2. **Racheal233**：完成上位机的设计
1.  Fork 本仓库：**MALossov**
2.  新建 Feat_xxx 分支
3.  提交代码:**MALossov**
4.  新建 Pull Request


#### 特技

1.  使用 Readme\_XXX.md 来支持不同的语言，例如 Readme\_en.md, Readme\_zh.md
2.  Gitee 官方博客 [blog.gitee.com](https://blog.gitee.com)
3.  你可以 [https://gitee.com/explore](https://gitee.com/explore) 这个地址来了解 Gitee 上的优秀开源项目
4.  [GVP](https://gitee.com/gvp) 全称是 Gitee 最有价值开源项目，是综合评定出的优秀开源项目
5.  Gitee 官方提供的使用手册 [https://gitee.com/help](https://gitee.com/help)
6.  Gitee 封面人物是一档用来展示 Gitee 会员风采的栏目 [https://gitee.com/gitee-stars/](https://gitee.com/gitee-stars/)
