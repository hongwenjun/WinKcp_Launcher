?@TITLE 运行Brook客户端
@echo.
@set PATH=%~dp0;%PATH%

::  两个冒号是注释，删除命令行首开启命令

::  运行 WireGuard 客户端 TunSafe
::  CD /D  C:\soft\TunSafe\
::  start TunSafe.exe

::  运行 Shadowsocks 客户端
::  CD /D  C:\soft\Shadowsocks
::  start Shadowsocks.exe

::  BROOK + KcpTun + Udp2Raw 客户端接口配置
@set SERVER_IP=1.2.3.4
@set PORT=2999
@set PASSWORD=wg2999
@set BK_PORT=3999

@start /b kcp-client -r "127.0.0.1:4000" -l ":%BK_PORT%" --key %PASSWORD% -mode fast2 -mtu 1300
@start /b udp2raw -c -r%SERVER_IP%:%PORT% -l0.0.0.0:4000 -k %PASSWORD% --raw-mode faketcp


::  打开 Brook 客户端服务
set IP_URL=127.0.0.1
set PASSWORD=wg2999
set PORT=3999

CD /D  C:\soft\Brook
start /b  brook client -l 127.0.0.1:2080 -i 127.0.0.1 -s %IP_URL%:%PORT% -p %PASSWORD%

