#include "launcher.h"


// 鼠标点击坐标，对应三个图标的程序,二维码坐标，信息栏坐标

void mouse_click_signal(HWND &hwndDlg,  LPARAM lParam)
{
    // 注册图标焦点POS
    POINT WG_POS = {40, 40};
    POINT SS_POS = {40, 120};
    POINT BK_POS = {40, 200};
    POINT DONATE_POS = {415, 145};
    POINT TIPS_POS = {140, 250};

    POINT mouse_pos;
    mouse_pos.x = LOWORD(lParam);
    mouse_pos.y = HIWORD(lParam);

    char app_cmd[256] = {0};

    // 鼠标点击图标，打开对应程序
    if (abs((int)mouse_pos.x - 40) < 30) {
        if (abs((int)mouse_pos.y - WG_POS.y) < 30) {
            read_app_cmd(app_cmd, "::WG_APP");
            ShellExecuteA(NULL, NULL, app_cmd, NULL, NULL, SW_SHOW);

        } else if (abs((int)mouse_pos.y - SS_POS.y) < 30) {
            read_app_cmd(app_cmd, "::SS_APP");
            ShellExecuteA(NULL, NULL, app_cmd, NULL, NULL, SW_SHOW);

        } else if (abs((int)mouse_pos.y - BK_POS.y) < 30) {
            read_app_cmd(app_cmd, "::MY_APP");
            ShellExecuteA(NULL, NULL, app_cmd, NULL, NULL, SW_SHOW);

        }
    }

    // 点击图片，快速访问Youtube频道
    if (abs((int)mouse_pos.x - DONATE_POS.x) < 80) {
        if (abs((int)mouse_pos.y - DONATE_POS.y) < 80) {

            char url[64] = "https://www.youtube.com/channel/UCupRwki_4n87nrwP0GIBUXA";
            ShellExecuteA(NULL, "open", url, NULL, NULL, SW_SHOW);
            return ;
        }

    }

    // 点击信息栏区域，切换信息
    char buf[512] = {0};
    static int id = 0;
    if (id >= 12)
        id = 0;
    const char* tips[] = {"   信息: 感谢之前打赏和使用本软件的朋友!",
                          "   信息: 点击左边图标，能自动开启对应程序!",
                          "   信息: 编辑START_APP.cmd设置三个图标对应程序",
                          "   信息: IP 管理功能，添加和删除后，请点保存!",
                          "   信息: 中间箭头IP管理，调试:勾选->显示窗口!",
                          " 1. 需要先安装 pcap 网络驱动包 npcap-0.9983.exe",
                          " 2. 修改 Windows_KCP.cmd 脚本服务器IP参数",
                          " 3. 使用软件管理 Windows_KCP.cmd 启动关闭",
                          " 4. 电脑WG客户端设置 修改成 Endpoint = 127.0.0.1",
                          " 5. 手机可以使用 ss+kcp ; KCP插件参数 按脚本提示",
                          "   信息: 点击右边图片，快速访问Youtube频道!",
                          "   信息: 好吧! 点击绿色区域就能关闭程序了!",
                         };
    if (abs((int)mouse_pos.x - TIPS_POS.x) < 150) {
        if (abs((int)mouse_pos.y - TIPS_POS.y) < 30) {
            strcpy(buf, tips[id++]);
            ::SetWindowText(::GetDlgItem(hwndDlg, IDC_INFO_TEXT), buf);
            return ;
        }
    }

    //sprintf(buf, "鼠标点击W坐标:[%d %d]", mouse_pos.x, mouse_pos.y);
    //MessageBox(hwndDlg, buf, buf, MB_OK);
    // WinExec(runapp, SW_SHOW);

    EndDialog(hwndDlg, 0);
}

// 读取 START_APP.cmd 中对应三个图标的程序路径
void read_app_cmd(char* app_cmd, const char* value)
{
    char buf[512] = {0};
    char* pch;
    char* ps;

    FILE*  pFile = fopen("START_APP.cmd", "r");
    if (pFile != NULL) {
        while (fgets(buf, 512, pFile) != NULL) {
            if ((ps = strstr(buf, value)) != NULL)  {
                if ((ps = strstr(buf, "\"")) != NULL)  {
                    pch = strtok(ps, "\"\t\n");
                    strcpy(app_cmd, pch);

                } else if (pch != NULL) {
                    ps = strstr(buf, "=");
                    pch = strtok(ps, " \t\n=");
                    strcpy(app_cmd, pch);
                }
            }
        }
        //  MessageBox(NULL, app_cmd, app_cmd, MB_OK);
        fclose(pFile);
    }
}
