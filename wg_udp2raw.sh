#!/bin/bash

# 密码随机
str=$(date | md5sum  | awk '{print $1}')
passwd=${str:0:8}

# 端口参数
wg_port=$(wg | grep 'listening port:' | awk '{print $3}')
raw_port=`expr $wg_port + 1000`
serverip=$(curl -4 icanhazip.com)
==================================================
# 定义文字颜色
Green="\033[32m"  && Red="\033[31m" && GreenBG="\033[42;37m" && RedBG="\033[41;37m" && Font="\033[0m"

# 下载 UDP2RAW
wget https://github.com/wangyu-/udp2raw-tunnel/releases/download/20181113.0/udp2raw_binaries.tar.gz
tar xf udp2raw_binaries.tar.gz
mv udp2raw_amd64 /usr/bin/udp2raw
rm udp2raw* -rf
rm version.txt

#安装到启动项 适合Debian 9  Ubuntu 18

cat <<EOF >/etc/rc.local
#!/bin/sh -e
#
# rc.local

# WireGuard + UDP2RAW 伪装 TCP  原端口 数值加 1000
udp2raw -s -l0.0.0.0:${raw_port} -r 127.0.0.1:${wg_port} -k '${passwd}' --raw-mode faketcp  >> /var/log/wg_udp2raw.log &

#  Windows 端 UDP2RAW 转接命令行
#  start /b udp2raw -c -r${serverip}:${raw_port} -l0.0.0.0:${wg_port} -k '${passwd}' --raw-mode faketcp 

exit 0
EOF

systemctl stop rc-local
chmod +x /etc/rc.local
systemctl restart rc-local
cat /etc/rc.local

echo -e "${GreenBG}   WireGuard 原端口: ${wg_port} ;   UDP2RAW伪装TCP后端口: ${raw_port} ; 转发密码: ${passwd} ${Font}"
echo     "#  Windows 端 UDP2RAW 转接命令行"
echo -e "${Green}  start /b udp2raw -c -r${serverip}:${raw_port} -l0.0.0.0:${wg_port} -k '${passwd}' --raw-mode faketcp  ${Font}"
