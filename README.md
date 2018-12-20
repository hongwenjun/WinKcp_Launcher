蘭雅sRGB 龙芯小本服务器 | [sRGB.vicp.net](http://sRGB.vicp.net)

![](https://raw.githubusercontent.com/hongwenjun/WinKcp_Launcher/master/gui.png)

# Shadowsocks + Kcp+Udp2Raw加速 和 Udp2Raw服务TCP伪装 WireGuard Windows Kcp+Udp2Raw 启动器 

# 使用 bash wgmtu 配置好服务器段后的服务示例
![](https://raw.githubusercontent.com/hongwenjun/img/master/ss_wg.png)
### 使用说明:
1. 需要先安装 pcap 网络驱动包(WinPcap_4_1_3.exe 或者 npcap-0.99-r8.exe 两者选一个)
2. 修改 Windows_KCP.cmd 和 Windows_UDP2RAW.cmd 服务器IP参数，双击启动调试
3. 双击 WinKcp_Launcher 分别管理  Windows_KCP.cmd 和 Windows_UDP2RAW.cm 启动关闭 
4. 电脑$$客户端设置  导入下面的模版配置，再修改成实际密码
5. 电脑WG客户端设置  导入 wg_client.conf 修改 Endpoint = 127.0.0.1:端口 另存一个配置 
6. 手机可以使用 ss+kcp ; KCP插件参数 按脚本提示

###  本地电脑端 SS 导入配置，再修改成脚本的实际密码
```
ss://YWVzLTI1Ni1nY206c3NrY3AxOTk5QDEyNy4wLjAuMToyMDE4#SS%2bKCP%2budp2raw
```

### 参数参考  udp2raw+kcptun 加速tcp流量 Step by Step 教程
https://github.com/wangyu-/udp2raw-tunnel/blob/master/doc/kcptun_step_by_step.md


### Shadowsocks+Kcp+Udp2Raw加速 服务端  debian 9  Ubuntu
```
# 一键安装 SS+Kcp+Udp2Raw 脚本 快速安装 for debian 9
wget -qO- git.io/fpZIW | bash

# 一键安装 SS+Kcp+Udp2Raw 脚本 for debian 9  Ubuntu (编译安装)
wget -qO- git.io/fx6UQ | bash
```

### 一键安装wireguard 脚本 For Debian_9  Ubuntu  Centos_7
```
# 一键安装wireguard 脚本 Debian 9 (源:逗比网安装笔记)
wget -qO- git.io/fptwc | bash

# 一键安装wireguard 脚本 Ubuntu 18(源:逗比网安装笔记)
wget -qO- git.io/fpcnL | bash

# CentOS7一键脚本安装WireGuard   (https://atrandys.com/2018/886.html)
yum install -y wget && \
wget https://raw.githubusercontent.com/atrandys/wireguard/master/wireguard_install.sh \
&& chmod +x wireguard_install.sh && ./wireguard_install.sh

```
[![ScreenShot](https://raw.githubusercontent.com/hongwenjun/vps_setup/master/Wireguard/ss_wg.jpg)](https://youtu.be/-cfuQSaJb5w)

###  一键 WireGuard 多用户配置共享脚本
```
# 一键 WireGuard 多用户配置共享脚本 
wget -qO- https://git.io/fpnQt | bash
```
[![ScreenShot](https://raw.githubusercontent.com/hongwenjun/vps_setup/master/Wireguard/wg5clients.jpg)](https://youtu.be/TOaihmhrYQY)

![](https://raw.githubusercontent.com/hongwenjun/vps_setup/master/Wireguard/bash_wg5.gif)


