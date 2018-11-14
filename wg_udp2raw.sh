#!/bin/bash


# 停止原先服务
systemctl stop rc-local


#安装到启动项 适合debian 9 x64

cat <<EOF >/etc/rc.local
#!/bin/sh -e
#
# rc.local

udp2raw -s -l0.0.0.0:8855 -r 127.0.0.1:9009 -k "passwd" --raw-mode faketcp  >> /var/log/udp2raw.log &

exit 0
EOF

chmod +x /etc/rc.local
systemctl restart rc-local


