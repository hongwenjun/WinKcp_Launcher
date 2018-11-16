#  Windows udp2raw+kcptun 加速tcp流量 简易工具  by 蘭雅sRGB
蘭雅sRGB 龙芯小本服务器 | [sRGB.vicp.net](http://sRGB.vicp.net)

### ♦ 最新资讯 ♦Vultr 限时优惠，充值10美元送10美元，3.5美元/月，IP被墙免费换，支持微信、支付宝。
- 点击这个链接注册，也算是对本项目作者的支持鼓励

https://www.vultr.com/?ref=7591742

![](https://raw.githubusercontent.com/hongwenjun/WinKcp_Launcher/master/gui.png)

## Shadowsocks + Kcp+Udp2Raw加速 和 Udp2Raw服务TCP伪装 WireGuard Windows Kcp+Udp2Raw 启动器 

使用视频链接.1   https://youtu.be/A4edsGXQdIc

使用视频链接.2   https://youtu.be/BvF6jQo_ZAo

### 使用说明:
1. 需要先安装 WinPcap_4_1_3.exe (已经包含和其他windows客户端)
2. 修改 Windows_KCP.cmd 里的服务器IP参数，双击启动调试
3. 双击 WinKcp_Launcher 管理 Windows_KCP.cmd 启动关闭 
4. 电脑$$客户端设置  127.0.0.1:3322     密码:xxx   加密 aes-256-gcm
5. 手机$$填PC电脑IP  192.168.1.188:3322 密码:xxx   加密 aes-256-gcm

![](https://raw.githubusercontent.com/hongwenjun/WinKcp_Launcher/master/windows_kcp.gif)

### 参数参考  udp2raw+kcptun 加速tcp流量 Step by Step 教程
https://github.com/wangyu-/udp2raw-tunnel/blob/master/doc/kcptun_step_by_step.md


### 详细见
[Windows_KCP加速使用说明.txt](https://raw.githubusercontent.com/hongwenjun/WinKcp_Launcher/master/Windows_KCP加速使用说明.txt)

### Shadowsocks+Kcp+Udp2Raw加速 服务端  debian 9
```
# 一键安装 Shadowsocks+Kcp+Udp2Raw加速脚本 for debian 9
wget -qO- git.io/fx6UQ | bash
```

###  本地电脑端 SS 导入配置 
```
ss://YWVzLTI1Ni1nY206c3JnYi54eXpAMTI3LjAuMC4xOjMzMjI=
```

### 一键安装wireguard 脚本 debian 9
```
# 一键安装wireguard 脚本 debian 9
wget -qO- git.io/fptwc | bash
```
### 导出到客户端配置，修改实际的IP，不要修改默认9009端口
```
# 查询WireGuard状态
wg

# 显示配置文件，修改实际的IP，不要修改默认9009端口
cat /etc/wireguard/client.conf
```
```
#  vultr 服务商的主机默认网卡是 ens3，使用下面命令修改配置
sed -i "s/eth0/ens3/g"  /etc/wireguard/wg0.conf
reboot
```
### Udp2Raw服务TCP伪装 WireGuard 服务端设置脚本
```
wget https://raw.githubusercontent.com/hongwenjun/WinKcp_Launcher/master/wg_udp2raw.sh \
chmod +x wg_udp2raw.sh && ./wg_udp2raw.sh
```
