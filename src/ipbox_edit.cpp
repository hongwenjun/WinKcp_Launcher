#include "ipbox_edit.h"

const char* ipbox_file = "ipbox.dat";

// ip管理窗口开启  ipbox[] 数组
void open_ipbox(HWND &hwndDlg)
{

    // 隐藏图片
    HWND hwnd_bmp = ::GetDlgItem(hwndDlg, DONATE_PIC);
    ::ShowWindow(hwnd_bmp, SW_HIDE);
    // 隐藏自身按钮
    HWND hwnd_ip_seselect = ::GetDlgItem(hwndDlg, IP_SESELECT);
    ::ShowWindow(hwnd_ip_seselect, SW_HIDE);


    for (size_t i = 0 ; i != sizeof ipbox / sizeof * ipbox ; i++) {
        HWND hwnd_ipbox = ::GetDlgItem(hwndDlg, ipbox[i]);
        ::ShowWindow(hwnd_ipbox, SW_SHOW);
    }

}

// 添加IP地址
void ipbox_add(HWND &hwndDlg)
{

    // 获得文本框的文本
    HWND hwnd_edit_ip = ::GetDlgItem(hwndDlg, IP_TEXT);
    HWND hwnd_edit_info = ::GetDlgItem(hwndDlg, IP_INFO);

    char ipbuf[256];
    char info_buf[256];
    int len_ip = ::GetWindowText(hwnd_edit_ip, ipbuf, 256);
    int len_info = ::GetWindowText(hwnd_edit_info, info_buf, 256);

    if (len_ip > 0) {
        // 向列表框添加文本
        if (len_info > 0) {
            strcat(ipbuf, "  ###  ");
            strcat(ipbuf, info_buf);

            // 清空文本框文本
            ::SetWindowText(hwnd_edit_info, "");
        }

        ::SendDlgItemMessage(hwndDlg, IP_LIST, LB_ADDSTRING, NULL, (long)ipbuf);

    }
}


// 删除IP地址
void ipbox_del(HWND &hwndDlg)
{
    // 获取列表框选择字符串索引
    int index = ::SendDlgItemMessage(hwndDlg, IP_LIST, LB_GETCURSEL, 0, 0);

    // 删除当前索引字符
    ::SendDlgItemMessage(hwndDlg, IP_LIST, LB_DELETESTRING, index, 0);

}

// 保存IP列表
void ipbox_save(HWND &hwndDlg)
{
    char buf[512];
    FILE*  pFile = fopen(ipbox_file, "w");

    // 获取 IP列表 IP总数
    int size = ::SendDlgItemMessage(hwndDlg, IP_LIST, LB_GETCOUNT, 0, 0);

    // IP列表 写文件
    for (size_t index = 0; index != size ; index++) {
        ::SendDlgItemMessage(hwndDlg, IP_LIST, LB_GETTEXT, index, (long)buf);
        fprintf(pFile, "%s\n", buf);
    }

    fclose(pFile);
}

// 加载IP列表
void ipbox_load(HWND &hwndDlg)
{
    char buf[512] = {0};
    char* pch;
    FILE*  pFile = fopen(ipbox_file, "r");
    if (pFile != NULL) {
        while (fgets(buf, 512, pFile) != NULL) {
            pch = strrchr(buf, '\n');
            *pch = '\0';
            if (strlen(buf) > 0)
                ::SendDlgItemMessage(hwndDlg, IP_LIST, LB_ADDSTRING, NULL, (long)buf);
        }
        fclose(pFile);
    }
}
