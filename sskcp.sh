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
    echo -e "\033[0;36m:: Usage \033[42;37m bash sskcp.sh \033[0;33m [start | stop | restart | set] \033[0m"
}

status(){
    clear
    ps ax | grep --color=auto  -e udp2raw -e kcp-client -e ss-local
    echo
}

setconf()
{
	echo "功能等待添加中..."
}

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
    esac
else
    status
    help
fi
