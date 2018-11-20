@echo.
@set PATH=%~dp0;%PATH%

@set SERVER_IP=188.188.188.188

@route add %SERVER_IP% mask 255.255.255.0 default METRIC default IF default

@start /b speederv2 -c -l0.0.0.0:9009 -r%SERVER_IP%:8888 -f20:10 -k "passwd" --mode 0