#!/bin/bash

# 密码随机，脚本提供修改
passwd=$(date | md5sum  | head -c 6)

# 默认端口参数, 为了简单好用，请下载脚本自编辑修改
wg_port=$(wg | grep 'listening port:' | awk '{print $3}')
raw_port=2999
speed_port=8888

ss_raw_port=1999
kcp_port=4000

if [ ! -e '/var/ip_addr' ]; then
    echo -n $(curl -4 ip.sb) > /var/ip_addr
fi
serverip=$(cat /var/ip_addr)

########################################################
clear
# 定义文字颜色
Green="\033[32m"  && Red="\033[31m" && GreenBG="\033[42;37m" && RedBG="\033[41;37m"
Font="\033[0m"  && Yellow="\033[0;33m" && SkyBlue="\033[0;36m"

default_display()
{
    echo -e "${GreenBG}   WireGuard + Speeder + Udp2Raw 和 Shadowsocks + Kcp + Udp2RAW 一键脚本   ${Font}"
    echo -e "${SkyBlue}             开源项目: https://github.com/hongwenjun/vps_setup             ${Font}"

    echo -e "随机生成密码: ${RedBG} ${passwd} ${Font} 现在可修改; "
    read -p "请输入你要的密码(按回车不修改): " -t 30 new

    if [[ ! -z "${new}" ]]; then
        passwd="${new}"
        echo -e "${SkyBlue}:: 修改后新密码: ${GreenBG} ${passwd} ${Font}"
        echo -e "${SkyBlue}:: WG+SPEED+UDP2RAW  默认伪装TCP端口: ${RedBG} ${raw_port} "
        echo -e "${SkyBlue}:: SS+KCP+UDP2RAW    默认伪装TCP端口: ${RedBG} ${ss_raw_port} ${Font}"

        read -p ":: 1.请输入WG+SPEED+UDP2RAW 伪装端口: "  raw_port
            if [[ -z "${raw_port}" ]]; then
                raw_port=2999
            fi

        read -p ":: 2.请输入 SS+KCP+UDP2RAW  伪装端口: "  ss_raw_port
            if [[ -z "${ss_raw_port}" ]]; then
                ss_raw_port=1999
            fi
    fi

}

english_display()
{
    echo -e "${GreenBG}   WireGuard+Speeder+Udp2Raw and SS+Kcp+Udp2RAW Automated Configuration   ${Font}"
    echo -e "${SkyBlue}       Open Source Project: https://github.com/hongwenjun/vps_setup       ${Font}"

    echo -e "Random Password: ${RedBG} ${passwd} ${Font} Now, You can change the Password, Press Enter to not Modify:"

    read -p "Please Enter the New Password: " -t 30 new

    if [[ ! -z "${new}" ]]; then
        passwd="${new}"
        echo -e "${SkyBlue}:: Now, the New Password: ${GreenBG} ${passwd} ${Font}"
        echo -e "${SkyBlue}:: WG+SPEED+UDP2RAW  Default Camouflage TCP Port: ${RedBG} ${raw_port} "
        echo -e "${SkyBlue}:: SS+KCP+UDP2RAW    Default Camouflage TCP Port: ${RedBG} ${ss_raw_port} ${Font}"

        read -p ":: 1.Please Modify WG+SPEED+UDP2RAW Camouflage TCP Port: "  raw_port
            if [[ -z "${raw_port}" ]]; then
                raw_port=2999
            fi

        read -p ":: 2.Please Modify SS+KCP+UDP2RAW  Camouflage TCP Port: "  ss_raw_port
            if [[ -z "${ss_raw_port}" ]]; then
                ss_raw_port=1999
            fi
    fi
}

# 中英文显示支持
if [[ "$1" == "english" ]]; then
    english_display
else
    default_display
fi

udp2raw_install()
{
    # 下载 UDP2RAW
    udp2raw_ver=$(wget --no-check-certificate -qO- https://api.github.com/repos/wangyu-/udp2raw-tunnel/releases/latest | grep 'tag_name' | cut -d\" -f4)
    wget https://github.com/wangyu-/udp2raw-tunnel/releases/download/${udp2raw_ver}/udp2raw_binaries.tar.gz
    tar xf udp2raw_binaries.tar.gz
    mv udp2raw_amd64 /usr/bin/udp2raw
    rm udp2raw* -rf
    rm version.txt

    # 下载 KCPTUN
    kcp_ver=$(wget --no-check-certificate -qO- https://api.github.com/repos/xtaci/kcptun/releases/latest | grep 'tag_name' | cut -d\" -f4)
    kcp_gz_ver=${kcp_ver:1:8}

    kcptun_tar_gz=kcptun-linux-amd64-${kcp_gz_ver}.tar.gz
    wget https://github.com/xtaci/kcptun/releases/download/${kcp_ver}/$kcptun_tar_gz
    tar xf $kcptun_tar_gz
    mv server_linux_amd64 /usr/bin/kcp-server
    mv client_linux_amd64 /usr/bin/kcp-client
    rm $kcptun_tar_gz

    # 下载 UDPspeeder
    udpspeeder_ver=$(wget --no-check-certificate -qO- https://api.github.com/repos/wangyu-/UDPspeeder/releases/latest | grep 'tag_name' | cut -d\" -f4)
    wget https://github.com/wangyu-/UDPspeeder/releases/download/${udpspeeder_ver}/speederv2_binaries.tar.gz
    tar xf speederv2_binaries.tar.gz
    mv speederv2_amd64 /usr/bin/speederv2
    rm speederv2* -rf
    rm version.txt
}

# 首次运行脚本需要安装
if [ ! -e '/usr/bin/speederv2' ]; then
    apt install iptables -y   # Debian 11默认没装 iptables
    update-alternatives --set iptables /usr/sbin/iptables-legacy
    udp2raw_install
fi

# 安装到启动项
cat <<EOF >/etc/rc.local
#!/bin/sh -e
#
# rc.local

# SS + KcpTun + Udp2RAW  or (SSR BROOK)            # IPv6 支持参数 -s ::0
ss-server  -s 0.0.0.0 -p 40000 -k ${passwd} -m aes-256-gcm -t 300  -s ::0  >> /var/log/ss-server.log &
kcp-server -t "127.0.0.1:40000" -l ":${kcp_port}" --key ${passwd} -mode fast2 -mtu 1300  >> /var/log/kcp-server.log &
udp2raw -s -l0.0.0.0:${ss_raw_port} -r 127.0.0.1:${kcp_port} -k ${passwd} --raw-mode faketcp -a >> /var/log/udp2raw.log &

# WG + Speeder + Udp2RAW  or (V2ray udp)
# speederv2 -s -l127.0.0.1:${speed_port}  -r127.0.0.1:${wg_port}  -f20:10 -k ${passwd} --mode 0  >> /var/log/speederv2.log &
# udp2raw   -s -l0.0.0.0:${raw_port}  -r 127.0.0.1:${speed_port}  -k ${passwd} --raw-mode faketcp -a >> /var/log/wg_udp2raw.log &

exit 0

EOF

# 重启启动项服务
systemctl stop rc-local

# 简化判断系统 debian/centos 族群
if [ -e '/etc/redhat-release' ]; then
    mv /etc/rc.local /etc/rc.d/rc.local
    ln -s /etc/rc.d/rc.local /etc/rc.local
    chmod +x /etc/rc.d/rc.local
    systemctl enable rc-local
else
    chmod +x /etc/rc.local
fi

systemctl restart rc-local

put_config(){
    echo -e "${SkyBlue}:: WG+Speeder+Udp2Raw 和 SS+Kcp+Udp2RAW 配置信息, 再查${GreenBG} cat vps_setup.log ${Font}"
    cat /etc/rc.local

    echo -e "请访问${GreenBG} https://git.io/winkcp ${Font}下载 Windows KcpTun 和 Udp2RAW 套接桥接工具"
    echo -e "按以下实际信息填充   ${RedBG} 服务器IP: ${serverip} ${Font} "
    echo -e "${Yellow}  WG+SPEED+UDP2RAW 原端口: ${wg_port} ;  UDP2RAW伪装TCP后端口: ${raw_port} ; 转发密码: ${passwd} ${Font}"
    echo -e "${Red}  SS+KCP+UDP2RAW加速: UDP2RAW伪装TCP后端口: ${ss_raw_port} ; SS密码: ${passwd} 加密协议 aes-256-gcm ${Font}"
    echo -e "${Green}  手机SS+KCP加速方案: KCPTUN端口: ${kcp_port} ; KCP插件设置参数 mode=fast2;key=${passwd};mtu=1300  ${Font}"
    echo
    echo -e "${SkyBlue}             开源项目：https://github.com/hongwenjun/vps_setup              ${Font}"
}

put_english_config(){
    echo -e "${SkyBlue}:: WG+Speeder+Udp2Raw and SS+Kcp+Udp2RAW Configuration information. ${Font}"
    cat /etc/rc.local

    echo -e "Please visit ${GreenBG} https://git.io/winkcp ${Font} to download the Windows KcpTun and Udp2RAW Socket Bridge tools."
    echo -e "Display Information ${RedBG} Server IP: ${serverip} ${Font} "
    echo -e "${Yellow}  WG+SPEED+UDP2RAW Original Port: ${wg_port} ;  UDP2RAW Camouflage TCP Port: ${raw_port} ; Forward Password: ${passwd} ${Font}"
    echo -e "${Red}  SS+KCP+UDP2RAW Speeded-Up: UDP2RAW Camouflage TCP Port: ${ss_raw_port} ; SS_Password: ${passwd} Encrypt_Method: aes-256-gcm ${Font}"
    echo -e "${Green}  Mobile Phone SS+KCP Speeded-Up: KCPTUN Port: ${kcp_port} ; KCP Plugin Parameters: mode=fast2;key=${passwd};mtu=1300  ${Font}"
    echo
    echo -e "${SkyBlue}       Open Source Project: https://github.com/hongwenjun/vps_setup       ${Font}"
}

cur_dir=$(pwd) && clear

if [[ "$1" == "english" ]]; then
    put_english_config 2>&1 | tee ${cur_dir}/vps_setup.log
else
    put_config 2>&1 | tee ${cur_dir}/vps_setup.log
fi

