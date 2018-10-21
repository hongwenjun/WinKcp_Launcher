@echo.
@set PATH=%~dp0;%PATH%
@start /b kcp-client -r "188.188.188.188:4000" -l ":3322" -mode fast2 -mtu 1300
