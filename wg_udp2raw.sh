#!/bin/bash

# 密码随机
str=$(date | md5sum  | awk '{print $1}')
passwd=${str:0:8}

# 端口参数
wg_port=$(wg | grep 'listening port:' | awk '{print $3}')
raw_port=`expr $wg_port + 1000`
serverip=$(curl -4 icanhazip.com)

##############################################################

# 定义文字颜色
Green="\033[32m"  && Red="\033[31m" && GreenBG="\033[42;37m" && RedBG="\033[41;37m" && Font="\033[0m"

install_udp2raw()
{
    # 下载 UDP2RAW
    wget https://github.com/wangyu-/udp2raw-tunnel/releases/download/20181113.0/udp2raw_binaries.tar.gz
    tar xf udp2raw_binaries.tar.gz
    mv udp2raw_amd64 /usr/bin/udp2raw
    rm udp2raw* -rf
    rm version.txt
}

# 首次运行脚本需要安装
if [ ! -f '/usr/bin/udp2raw' ]; then
    install_udp2raw
fi


#安装到启动项

cat <<EOF >/etc/rc.local
#!/bin/sh -e
#
# rc.local

# WireGuard + UDP2RAW 伪装 TCP  原端口 数值加 1000
udp2raw -s -l0.0.0.0:${raw_port} -r 127.0.0.1:${wg_port} -k '${passwd}' --raw-mode faketcp  >> /var/log/wg_udp2raw.log &

exit 0
EOF

systemctl stop rc-local
chmod +x /etc/rc.local
systemctl restart rc-local
cat /etc/rc.local

echo -e "${GreenBG}:: WireGuard 原端口: ${wg_port} ;   UDP2RAW伪装TCP后端口: ${raw_port} ; 转发密码: ${passwd} ${Font}"
echo -e   "${RedBG}:: Windows_UDP2RAW.cmd  本地客户端脚本, 需要把 MTU 设置成1200-1300  ${Font}"

cat <<EOF >~/Windows_UDP2RAW.cmd
@echo.
@set PATH=%~dp0;%PATH%

@set SERVER_IP=${serverip}
@set RAW_PORT=${raw_port}
@set PASSWORD=${passwd}
@set WG_PORT=${wg_port}

@route add %SERVER_IP% mask 255.255.255.0 default METRIC default IF default
@start /b udp2raw -c -r%SERVER_IP%:%RAW_PORT% -l0.0.0.0:%WG_PORT% -k %PASSWORD% --raw-mode faketcp

EOF

content=$(cat ~/Windows_UDP2RAW.cmd)
echo -e "${Green}${content}${Font}"
