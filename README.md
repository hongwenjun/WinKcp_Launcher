蘭雅sRGB 龙芯小本服务器 | [sRGB.vicp.net](http://sRGB.vicp.net)
### Windows KcpTun Udp2Raw 启动管理器
![](https://raw.githubusercontent.com/hongwenjun/WinKcp_Launcher/master/gui.gif)

### 严重声明和友情提示：
- 此项目仅限于技术交流和探讨，在您测试完毕后必须在1秒钟内彻底删除项目副本。此项目为bash一键脚本，其中涉及到的任何软件版权和责任归原作者所有。
- 在中国境内使用、传播、售卖、免费分享等任何翻墙服务，都是违法的。如果你在中国境内使用、测试此项目脚本，或者使用此脚本搭建服务器发生以上违法行为，都有违作者意愿！你必须立刻停止此行为！并删除脚本！

### 使用 bash wgmtu 配置好服务器段后的服务示例
![](https://raw.githubusercontent.com/hongwenjun/img/master/ss_wg.png)

### 使用说明:
1. 需要先安装 pcap 网络驱动包(Wpcap-0.99-r8.exe 或者 WinPcap_4_1_3.exe 两者选一个)
2. 修改 [Windows_KCP.cmd 和 Windows_UDP2RAW.cmd 服务器IP参数](https://github.com/hongwenjun/WinKcp_Launcher/tree/master/template)，双击启动调试
3. 双击 WinKcp_Launcher 分别管理  Windows_KCP.cmd 和 Windows_UDP2RAW.cm 启动关闭
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


### 个人浙江电信重启电脑后，Npcap网络驱动有问题
-可以 重启网卡（Npcap Loopback Adapter）或 再装npcap-0.99-r8.exe 解决
```
:: 重启网卡（Npcap Loopback Adapter）
netsh interface set interface "Npcap Loopback Adapter" disabled
@ping 127.0.0.1 -n 3 >nul
netsh interface set interface "Npcap Loopback Adapter" enabled
```
### 运行Brook客户端Kcp+Udp2RAW 本地批处理示例
![](https://raw.githubusercontent.com/hongwenjun/img/master/brook_kcp.png)
