#!/bin/bash

SERVER_IP=188.188.188.188
PORT=1999
PASSWORD=wg2999
SS_PORT=40000

start(){
  # SS + KcpTun + Udp2RAW
    udp2raw -c -r$SERVER_IP:$PORT -l0.0.0.0:4000 -k $PASSWORD --raw-mode  faketcp -a >> /var/log/udp2raw.log &
    kcp-client -r 127.0.0.1:4000 -l :$SS_PORT --key $PASSWORD -mode fast2 -mtu 1300  >> /var/log/kcp-client.log &

  # ss-local -s 服务器IP地址  -p 服务器端口  -b 绑定本地IP  -l 本地端口  -k 密码  -m 加密方式 [-c 配置文件]
    ss-local -s 127.0.0.1 -p $SS_PORT -b 0.0.0.0 -l 1080 -k $PASSWORD -m aes-256-gcm  -t 300 >> /var/log/ss-local.log &

    status
}

stop(){
    killall -9 kcp-client
    killall -9 udp2raw
    killall -9 ss-local
}

restart(){
    stop
    start
}

help(){
    echo -e "${SkyBlue}:: Source: ${Green}https://git.io/sskcp.sh  ${Font}By 蘭雅sRGB"
    echo -e "${SkyBlue}:: Usage: ${GreenBG} bash sskcp.sh ${Yellow} [start | stop | restart | set] ${Font}"
}

status(){
    $PS | grep --color=auto  -e udp2raw -e kcp-client -e ss-local
    echo
}

setconf()
{
    echo -e "${SkyBlue}:: 脚本 sskcp.sh 记录参数，如不修改请按(Ctrl+C)退出! ${Yellow}"
    head -n 6 sskcp.sh | tail -n 4  &&  echo -e "${SkyBlue}"

    read -p ":: 1.请输入远程服务器IP: "  sv_ip
    read -p ":: 2.请输入udp2raw 端口: "  port
    read -p ":: 3.请输入套接转发密码: "  passwd
    read -p ":: 4.请输入 SS 服务端口: "  ss_port

    sed -i "s/^SERVER_IP=.*/SERVER_IP=${sv_ip}/g"  "sskcp.sh"
    sed -i "s/^PORT=.*/PORT=${port}/g"  "sskcp.sh"
    sed -i "s/^PASSWORD=.*/PASSWORD=${passwd}/g"  "sskcp.sh"
    sed -i "s/^SS_PORT=.*/SS_PORT=${ss_port}/g"  "sskcp.sh"
    echo -e "${Yellow}" && head -n 6 sskcp.sh | tail -n 4 &&  echo -e "${Font}" 
}

system_def(){
    PS='ps ax'
    if [[ -e /etc/openwrt_release ]]; then
       PS='ps'
    fi
    # 定义文字颜色
	Green="\033[32m"  && Red="\033[31m" && GreenBG="\033[42;37m" && RedBG="\033[41;37m"
	Font="\033[0m"  && Yellow="\033[0;33m" && SkyBlue="\033[0;36m"
}

# 系统定义和命令参数
system_def
if [[ $# > 0 ]]; then
    key="$1"
    case $key in
        start)
          start
        ;;
        stop)
          stop
        ;;
        restart)
          restart
        ;;
        set)
          setconf
          restart
    esac
else
    status
    help
fi
