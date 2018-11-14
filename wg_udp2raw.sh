#!/bin/bash

#下载UDP2RAW
wget https://github.com/wangyu-/udp2raw-tunnel/releases/download/20180830.2/udp2raw_binaries.tar.gz
tar xf udp2raw_binaries.tar.gz
mv udp2raw_amd64 /usr/bin/udp2raw
rm udp2raw* -rf
rm version.txt


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


