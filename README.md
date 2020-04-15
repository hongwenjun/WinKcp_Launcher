- 欢迎加入编程语言群 Telegram 电报群：https://t.me/codeblocks
- [![](https://raw.githubusercontent.com/hongwenjun/vps_setup/master/img/youtube.png)频道](https://www.youtube.com/sRGB18/videos) &nbsp;&nbsp;www.youtube.com/sRGB18 &nbsp;&nbsp;[![](https://raw.githubusercontent.com/hongwenjun/vps_setup/master/img/paypal.png)赞赏支持!](https://paypal.me/sRGB18)&nbsp;&nbsp;https://paypal.me/sRGB18
---
### Windows KcpTun Udp2Raw 启动管理器  [下载](https://github.com/hongwenjun/WinKcp_Launcher/archive/master.zip)  [使用视频演示](https://youtu.be/uwpQ6DLB_OU)
![](https://raw.githubusercontent.com/hongwenjun/WinKcp_Launcher/master/gui.gif)

### 严重声明和友情提示：
- 此项目仅限于技术交流和探讨，在您测试完毕后必须在1秒钟内彻底删除项目副本。此项目为bash一键脚本，其中涉及到的任何软件版权和责任归原作者所有。
- 在中国境内使用、传播、售卖、免费分享等任何翻墙服务，都是违法的。如果你在中国境内使用、测试此项目脚本，或者使用此脚本搭建服务器发生以上违法行为，都有违作者意愿！你必须立刻停止此行为！并删除脚本！

### 使用 bash wgmtu 配置好服务器段后的服务示例
![](https://raw.githubusercontent.com/hongwenjun/img/master/ss_wg.png)

### VirSCAN.org 一个非盈利性的免费病毒检测网站，49款杀毒引擎检测安全
  http://r.virscan.org/language/zh-cn/report/9212f801e9cfef20e4ad1bc07aea562e

### 使用说明:
1. 需要先安装 pcap 网络驱动包, 安装 [npcap-0.9983.exe](https://nmap.org/npcap/)
2. 修改 [Windows_KCP.cmd 和 Windows_UDP2RAW.cmd 服务器IP参数](https://github.com/hongwenjun/WinKcp_Launcher/tree/master/template)，双击启动调试
3. 双击 WinKcp_Launcher 分别管理  Windows_KCP.cmd 和 Windows_UDP2RAW.cmd 启动关闭
4. 电脑$$客户端设置  导入下面的模版配置，再修改成实际密码
5. 电脑WG客户端设置  导入 wg_client.conf 修改 Endpoint = 127.0.0.1:端口 另存一个配置
6. 手机可以使用 ss+kcp ; KCP插件参数 按脚本提示

### Shadowsocks + Kcp + Udp2RAW  配置模版，导入后改实际密码

```
ss://YWVzLTI1Ni1nY206d2cyOTk5QDEyNy4wLjAuMToyMDE4#test
```

### 手机SS+KCP加速方案
```
  # 手机SS  KCP插件下载URL; 权限设置: SS和KCP插件能后台运行和管理启动
  https://github.com/shadowsocks/kcptun-android/releases

  KCPTUN端口: 4000 ; KCP插件设置参数 mode=fast2;key=wg2999;mtu=1300
```

### OpenWRT和KoolShar使用 加速udp2raw+kcptun脚本 https://git.io/sskcp.sh
- KcpTun [软件下载](https://github.com/xtaci/kcptun/releases) client_linux 改名成 kcp-client 存放路径 /usr/bin
- KoolShare LEDE X64 可以酷软装udp2raw和kcptun，做软链接，示例命令

    ln -s /koolshare/bin/kcpclient /usr/bin/kcp-client

### 软路由参考 《OpenWRT 安装 WireGuard 配置 Udp2Raw + UdpSpeeder + WireGuard 文档教程》
- 短网址: https://git.io/wrt.wg

### 参数参考  udp2raw+kcptun 加速tcp流量 Step by Step 教程
https://github.com/wangyu-/udp2raw-tunnel/blob/master/doc/kcptun_step_by_step.md

![](https://raw.githubusercontent.com/hongwenjun/vps_setup/master/img/speed_raw.png)


### START_APP.cmd 文件 设置三个图标对应程序

```
@TITLE 运行Brook客户端Kcp+Udp2RAW    #设置自定义按钮的显示文本

::设置三个图标对应程序，点击图标能自动开启; 路径如果有空格需要"双引号"括起来

::WG_APP =  "C:\Program Files\TunSafe\TunSafe.exe"
::SS_APP =  "C:\Program File\Shadowsocks\Shadowsocks.exe"
::MY_APP =  D:\Git\git-bash.exe

```

### 运行Brook客户端Kcp+Udp2RAW 本地批处理示例
![](https://raw.githubusercontent.com/hongwenjun/img/master/brook_kcp.png)
