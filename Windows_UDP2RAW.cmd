@echo.
@set PATH=%~dp0;%PATH%

@set SERVER_IP=188.188.188.188

@route add %SERVER_IP% mask 255.255.255.0 default METRIC default IF default

@start /b udp2raw -c -r%SERVER_IP%:8866 -l0.0.0.0:9009 -k"passwd" --raw-mode faketcp
