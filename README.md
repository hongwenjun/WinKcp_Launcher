#  Windows udp2raw+kcptun 加速tcp流量 简易工具  by 蘭雅sRGB
蘭雅sRGB 龙芯小本服务器 | [sRGB.vicp.net](http://sRGB.vicp.net)

### ♦ 最新资讯 ♦Vultr 限时优惠，充值10美元送10美元，3.5美元/月，IP被墙免费换，支持微信、支付宝。
- 点击这个链接注册，也算是对本项目作者的支持鼓励

https://www.vultr.com/?ref=7591742

![](https://raw.githubusercontent.com/hongwenjun/WinKcp_Launcher/master/gui.png)

## Wireguard 手机和PC客户端设置技巧
[![ScreenShot](https://raw.githubusercontent.com/hongwenjun/vps_setup/master/Wireguard/tel_pc.jpg)](https://youtu.be/O__RsZewA60)

## Shadowsocks + Kcp+Udp2Raw加速 和 Udp2Raw服务TCP伪装 WireGuard Windows Kcp+Udp2Raw 启动器 

使用视频链接.1   https://youtu.be/A4edsGXQdIc

使用视频链接.2   https://youtu.be/BvF6jQo_ZAo
![](https://raw.githubusercontent.com/hongwenjun/WinKcp_Launcher/master/WinKcp_Launcher.webp)

### 使用说明:
1. 需要先安装 WinPcap_4_1_3.exe (已经包含和其他windows客户端)
2. 修改 Windows_KCP.cmd 和 Windows_UDP2RAW.cmd 服务器IP参数，双击启动调试
3. 双击 WinKcp_Launcher 分别管理  Windows_KCP.cmd 和 Windows_UDP2RAW.cm 启动关闭 
4. 电脑$$客户端设置  导入  *ss://YWVzLTI1Ni1nY206c3JnYi54eXpAMTI3LjAuMC4xOjMzMjI=*
5. 电脑WG客户端设置  导入 wg_client.conf 修改 Endpoint = 127.0.0.1:9009 另存一个配置 
6. 手机不能装kcp和udp2raw，需要使用PC或者路由器转接

###  本地电脑端 SS 导入配置，有默认的 SS密码
```
ss://YWVzLTI1Ni1nY206c3JnYi54eXpAMTI3LjAuMC4xOjMzMjI=
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
wget https://raw.githubusercontent.com/yobabyshark/wireguard/master/wireguard_install.sh \
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

#### 导出到客户端配置，修改实际的IP，不要修改默认9009端口
```
# 查询WireGuard状态
wg

# 显示配置文件，修改实际的IP，不要修改默认9009端口
cat /etc/wireguard/client.conf
```
### 遇到wg连接主机而没有流量，使用 Ip addr 命令检查vps网卡是否是ensx，参考下面修改配置重启
```
#  一键脚本已经检查出vultr主机，自动修改配置，不用再手工运行
#  vultr 服务商的主机默认网卡是 ens3，使用下面命令修改配置
sed -i "s/eth0/ens3/g"  /etc/wireguard/wg0.conf
reboot

#  GCP 香港 Ubuntu系统 默认网卡是 ens4，使用下面命令修改配置
#  GCP 香港 Ubuntu系统 没带python，不能开启临时web下载，可以 apt install -y python 安装
sed -i "s/eth0/ens4/g"  /etc/wireguard/wg0.conf
reboot
```

### Udp2Raw服务TCP伪装 WireGuard 服务端设置脚本
```
wget https://raw.githubusercontent.com/hongwenjun/WinKcp_Launcher/master/wg_udp2raw.sh 
chmod +x wg_udp2raw.sh  && ./wg_udp2raw.sh

```
