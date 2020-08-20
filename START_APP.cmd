@TITLE 运行Brook客户端Kcp+Udp2RAW    #设置自定义按钮的显示文本

::设置三个图标对应程序，点击图标能自动开启; 路径如果有空格需要"双引号"括起来

::WG_APP =  "C:\Program Files\TunSafe\TunSafe.exe"
::SS_APP =  .\Shadowsocks.exe
::MY_APP =  D:\Git\git-bash.exe

@echo.
@set PATH=%~dp0;%~dp0/bin;%PATH%
::  两个冒号是注释，删除命令行首开启命令

::  BROOK + KcpTun + Udp2Raw 客户端接口配置 示例如下
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

