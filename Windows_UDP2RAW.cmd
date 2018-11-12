@echo.
@set PATH=%~dp0;%PATH%

@set SERVER_IP=144.202.95.95

@start /b udp2raw -c -r%SERVER_IP%:8855 -l0.0.0.0:9009 -k"passwd" --raw-mode faketcp


start /b  C:\soft\TunSafe\TunSafe.exe