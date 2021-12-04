import sqlite3, sys, os.path
# define Color 
Green = '\033[32m'; Red = '\033[31m'; GreenBG = '\033[42;37m'; RedBG = '\033[41;37m'
Yellow = '\033[0;33m'; SkyBlue = '\033[0;36m'; Font = '\033[0m'

db_flag = os.path.exists('vps2021.db')
conn = sqlite3.connect('vps2021.db')
c = conn.cursor()

if db_flag == False :
  c.execute('''CREATE TABLE vps
             (ip text, port text, password text, ss_port text, info text)''')
  c.execute('''INSERT INTO vps VALUES 
            ('188.188.188.188', '22', 'passwd@SSL', '443', '0号示例')''')
  conn.commit()

# sql 获取 vps 数据 , 显示 vps 数据
def display_data(c):
  print(GreenBG, ":: 显示 SQLite3 数据库 vps2021.db 中获节点表  ")
  sql = 'SELECT * FROM vps ORDER BY ip'
  c.execute(sql)
  vps = c.fetchall()

  cnt=0  ; sk = list()
  for row in vps:
    print(SkyBlue, cnt,'节点:', Yellow, row)
    sk.append(list(row))
    cnt+=1
  print(Font)
  return sk

vps = display_data(c)
print(SkyBlue, ":: 使用节点直接输入节点号数字 ")
print(GreenBG, ":: 输入命令:", RedBG, "del <1> 删除节点 \n :: 添加节点:", SkyBlue, 'add <ip port passwd ss_port info>', Font)
print(' $ ', end='')
cmd = input().strip()
cmd = cmd.replace(',', '').replace('\'', '')
arg = cmd.split()
# print(arg)

if (len(arg)==0):
  sys.exit(1)

# 命令 del <1> 删除节点
if arg[0] == 'del' :
  id = int(arg[1])
  row = vps[id]
  c.execute("DELETE FROM vps WHERE ip=? AND port=? ", (row[0], row[1]) )
  conn.commit()
  print('\n'); display_data(c)
  sys.exit(0)

# 命令 add <ip port passwd ss_port info> 添加节点
if arg[0] == 'add' and len(arg)==6:
  row =(arg[1], arg[2], arg[3], arg[4], arg[5])
  c.execute('INSERT INTO vps VALUES (?,?,?,?,?)', row)
  conn.commit()
  print('\n'); display_data(c)
  sys.exit(0)

text = '''
start(){
  # SS + KcpTun + Udp2RAW
    udp2raw -c -r$SERVER_IP:$PORT -l0.0.0.0:4000 -k $PASSWORD --raw-mode  faketcp -a >> /var/log/udp2raw.log &
    kcp-client -r 127.0.0.1:4000 -l :$SS_PORT --key $PASSWORD -mode fast2 -mtu 1300  >> /var/log/kcp-client.log  2>&1 &

  # ss-local -s 服务器IP地址  -p 服务器端口  -b 绑定本地IP  -l 本地端口  -k 密码  -m 加密方式 [-c 配置文件]
    ss-local -s 127.0.0.1 -p $SS_PORT -b 0.0.0.0 -l $SOCKS5_PORT -k $PASSWORD -m aes-256-gcm  -t 300 >> /var/log/ss-local.log &

  # status
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
    echo -e "${SkyBlue}:: Usage: ${GreenBG} bash sskcp.sh ${Yellow} [start|stop|restart|service|set] ${Font}"
    echo
}

status(){
    # log 和 命令行参数
    cat /var/log/udp2raw.log | tail
    cat /var/log/kcp-client.log | tail
    cat /var/log/ss-local.log | tail
    echo

    if [[ -e /etc/openwrt_release ]]; then
       ps | grep  -e udp2raw -e kcp-client -e ss-local
    else
       ps ax | grep --color=auto -e udp2raw -e kcp-client -e ss-local
    fi
    echo
}

setconf()
{
    echo -e "${SkyBlue}:: 修改脚本sskcp.sh记录参数，按${RedBG}<Enter>${SkyBlue}不修改! ${Yellow}"
    head -n 6 sskcp.sh | tail -n 4  &&  echo -e "${SkyBlue}"

    read -p ":: 1.请输入远程服务器IP: "  sv_ip
    read -p ":: 2.请输入udp2raw 端口: "  port
    read -p ":: 3.请输入套接转发密码: "  passwd
    read -p ":: 4.请输入 SS 服务端口: "  ss_port

    if [[ ! -z "${sv_ip}" ]]; then
        sed -i "s/^SERVER_IP=.*/SERVER_IP=${sv_ip}/g"  "sskcp.sh"
    fi
    if [[ ! -z "${port}" ]]; then
        sed -i "s/^PORT=.*/PORT=${port}/g"  "sskcp.sh"
    fi
    if [[ ! -z "${passwd}" ]]; then
        sed -i "s/^PASSWORD=.*/PASSWORD=${passwd}/g"  "sskcp.sh"
    fi
    if [[ ! -z "${ss_port}" ]]; then
        sed -i "s/^SS_PORT=.*/SS_PORT=${ss_port}/g"  "sskcp.sh"
    fi

    echo -e "${Yellow}" && head -n 7 sskcp.sh | tail -n 5 &&  echo -e "${Font}"
}

system_def(){
	Green="\033[32m"  && Red="\033[31m" && GreenBG="\033[42;37m" && RedBG="\033[41;37m"
	Font="\033[0m"  && Yellow="\033[0;33m" && SkyBlue="\033[0;36m"
}

systemd_service(){
    # 安装启动服务
    cat <<EOF >/usr/lib/systemd/system/sskcp.service
[Unit]
Description=sskcp.sh Service
After=network.target

[Service]
Type=forking
User=root
ExecStart=nohup /root/sskcp.sh start &
ExecReload=sh /root/sskcp.sh stop

[Install]
WantedBy=multi-user.target

EOF
	chmod +x  /root/sskcp.sh
	systemctl enable sskcp.service
	systemctl start sskcp.service
	systemctl status sskcp.service
}

# 脚本命令参数
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
	service)
          systemd_service
        ;;
        set)
          setconf
        ;;
    esac
else
    status
fi
help
''' 
def make_sskcp(sk, id):
  cfg = sk[id]
  str = '#!/bin/bash\n\n'
  str += 'SERVER_IP=' + cfg[0] + '\nPORT=' + cfg[1] + '\nPASSWORD=' + cfg[2] + '\nSS_PORT=40000\nSOCKS5_PORT=1080\n'
  print(str)
  str += text
  return str

if int(arg[0]) < len(vps) and len(arg)==1:
  str = make_sskcp(vps, int(arg[0]))
  f = open('sskcp.sh', 'w')
  f.write(str); f.close()
  os.system('bash sskcp.sh stop')
  os.system('bash sskcp.sh start')
  sys.exit(0)

conn.close()
