#include "launcher.h"


void mouse_click_signal(HWND &hwndDlg, LPARAM lParam)
{
    // 注册图标焦点POS
    POINT WG_POS = {40, 40};
    POINT SS_POS = {40, 120};
    POINT BK_POS = {40, 200};
    POINT DONATE_POS = {415, 145};

    POINT mouse_pos;
    mouse_pos.x = LOWORD(lParam);
    mouse_pos.y = HIWORD(lParam);

    char buf[512] = {0};

    if (abs((int)mouse_pos.x - 40) < 30) {
        if (abs((int)mouse_pos.y - WG_POS.y) < 30) {
            sprintf(buf, "鼠标点击WG_POS:[%d %d]", mouse_pos.x, mouse_pos.y);

        } else if (abs((int)mouse_pos.y - SS_POS.y) < 30) {
            sprintf(buf, "鼠标点击SS_POS:[%d %d]", mouse_pos.x, mouse_pos.y);

        } else if (abs((int)mouse_pos.y - BK_POS.y) < 30) {
            sprintf(buf, "鼠标点击BK_POS:[%d %d]", mouse_pos.x, mouse_pos.y);
        }

        MessageBox(hwndDlg, buf, buf, MB_OK);
    }

    if (abs((int)mouse_pos.x - DONATE_POS.x) < 80) {
        if (abs((int)mouse_pos.y - DONATE_POS.y) < 80) {

            sprintf(buf, "鼠标点击W坐标:[%d %d]", mouse_pos.x, mouse_pos.y);
            MessageBox(hwndDlg, buf, buf, MB_OK);
        }
    }
     EndDialog(hwndDlg, 0);
}
