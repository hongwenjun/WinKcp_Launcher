udp2raw_install()
{
    wget https://262235.xyz/u/udp2raw_binaries.tar.gz
    tar xf udp2raw_binaries.tar.gz
    mv udp2raw_amd64 /usr/bin/udp2raw

    wget https://262235.xyz/u/kcptun-linux-amd64-20230811.tar.gz
    tar xf kcptun-linux-amd64-20230811.tar.gz
    mv server_linux_amd64 /usr/bin/kcp-server
    mv client_linux_amd64 /usr/bin/kcp-client

	wget https://262235.xyz/u//speederv2_binaries.tar.gz
    tar xf speederv2_binaries.tar.gz
    mv speederv2_amd64 /usr/bin/speederv2
}

def_install(){
    # Download the binary release of Pure Compilation.
    wget -O /tmp/ss.tgz https://git.io/ss.tgz
    tar xvf  /tmp/ss.tgz -C /

    echo "/usr/local/lib" > /etc/ld.so.conf.d/ss-libev.conf
    ldconfig
    export PATH=$PATH:/usr/local/bin
}

cd /tmp/
def_install
udp2raw_install
