# WireGuard + Speeder + Udp2Raw 和 Shadowsocks + Kcp + Udp2RAW 一键脚本
### 请访问 https://github.com/hongwenjun/WinKcp_Launcher 下载客户端程序和模版

[![ScreenShot](https://raw.githubusercontent.com/hongwenjun/vps_setup/master/Wireguard/ss_wgmtu.jpg)](https://youtu.be/-sJLfPg12oc)

### GCP添加防火墙规则 ss-wg-udp
```
# 入站  来源IP  0.0.0.0/0 ;指定协议和端口
tcp:1999,2999,3999,8000; udp:1999,2999,3999,8000

# 最好提前指定，不然要等很久才能生效

```

###  示例服务端信息
```
按以下实际信息填充    服务器IP: 35.236.155.75
  WG+SPEED+UDP2RAW 原端口: 8000 ;  UDP2RAW伪装TCP后端口: 2999 ; 转发密码: wg2999

  SS+KCP+UDP2RAW加速: UDP2RAW伪装TCP后端口: 1999 ; SS密码: wg2999 加密协议 aes-256-gcm

 手机SS+KCP加速方案: KCPTUN端口: 4000 ; KCP插件设置参数 mode=fast2;key=wg2999;mtu=1300

```
###  root@gcp-tw:~# cat /etc/rc.local
```
#!/bin/sh -e
#
# rc.local

# SS+KCP+UDP2RAW 加速UDP TCP伪装
ss-server -s 127.0.0.1 -p 40000 -k wg2999 -m aes-256-gcm -t 300 >> /var/log/ss-server.log &
kcp-server -t "127.0.0.1:40000" -l ":4000" --key wg2999 -mode fast2 -mtu 1300  >> /var/log/kcp-server.log &
udp2raw -s -l0.0.0.0:1999 -r 127.0.0.1:4000 -k wg2999 --raw-mode faketcp  >> /var/log/udp2raw.log &

# WG + Speeder + Udp2RAW 加速UDP TCP伪装
speederv2 -s -l127.0.0.1:8888  -r127.0.0.1:8000  -f20:10 -k wg2999 --mode 0  >> /var/log/speederv2.log &
udp2raw   -s -l0.0.0.0:2999  -r 127.0.0.1:8888  -k wg2999 --raw-mode faketcp  >> /var/log/wg_udp2raw.log &

exit 0
```
### 下载模版文件，如图修改红框范围内 IP端口和密码
![](https://raw.githubusercontent.com/hongwenjun/WinKcp_Launcher/master/template/wg_ss.png)

###  WG_TW_SPEED_UDP2RAW_TEST.conf      示范WG+Speed+Udp2RAW客户端配置
```
[Interface]
PrivateKey = GGWbHT5xxQjDzdF/MAowtfMmHmhsWR1qdJAab7Aut2U=
Address = 10.0.0.5/24
DNS = 8.8.8.8

[Peer]
PublicKey = +rAd6hO5oox8GfzIHsycaj7h2aITrz12R0C8XRHnrCI=
Endpoint = 127.0.0.1:8000
AllowedIPs = 0.0.0.0/0, ::0/0
PersistentKeepalive = 25

```

###  Windows_UDP2RAW.cmd  示范客户端开启串接模版
```
@echo.
@set PATH=%~dp0;%PATH%

@set SERVER_IP=35.236.155.75
@set PORT=2999
@set PASSWORD=wg2999
@set WG_PORT=8000

@route add %SERVER_IP% mask 255.255.255.0 default METRIC default IF default
@start /b udp2raw -c -r%SERVER_IP%:%PORT% -l0.0.0.0:8888 -k %PASSWORD% --raw-mode faketcp
@start /b speederv2  -c -l0.0.0.0:%WG_PORT% -r127.0.0.1:8888 -f20:10 -k %PASSWORD% --mode 0

```

###  Windows_KCP.cmd   示范客户端开启串接模版
```
@echo.
@set PATH=%~dp0;%PATH%

@set SERVER_IP=35.236.155.75
@set PORT=1999
@set PASSWORD=wg2999
@set SS_PORT=2018

@start /b kcp-client -r "127.0.0.1:4000" -l ":%SS_PORT%" --key %PASSWORD% -mode fast2 -mtu 1300
@start /b udp2raw -c -r%SERVER_IP%:%PORT% -l0.0.0.0:4000 -k %PASSWORD% --raw-mode faketcp

```
### Shadowsocks + Kcp + Udp2RAW  配置模版，导入后改实际密码

```
ss://YWVzLTI1Ni1nY206d2cyOTk5QDEyNy4wLjAuMToyMDE4#test
```

### 手机SS+KCP加速方案
```
  # 手机SS  KCP插件下载URL
  https://github.com/shadowsocks/kcptun-android/releases
  
  KCPTUN端口: 4000 ; KCP插件设置参数 mode=fast2;key=wg2999;mtu=1300
```
