#include "ipbox_edit.h"

const char* ipbox_file = "ipbox.dat";
static char getip[256] = "NULL";

void getnewip(char* newip)
{
    strcpy(newip, getip);
}

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
            if (len_ip < 16) {
                strcat(ipbuf, "                ");
                ipbuf[16] = '\0';
            }
            strcat(ipbuf, " # ");
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
            if (pch != NULL)
                *pch = '\0';

            if (strlen(buf) > 0)
                ::SendDlgItemMessage(hwndDlg, IP_LIST, LB_ADDSTRING, NULL, (long)buf);
        }
        fclose(pFile);
    }
}

// 读取 START_APP.cmd 中的标题
void read_appname(HWND &hwndDlg)
{
    char buf[512] = {0};
    char* pch;
    char* ps;
    char* value = "@TITLE";

    FILE*  pFile = fopen("START_APP.cmd", "r");
    if (pFile != NULL) {
        while (fgets(buf, 512, pFile) != NULL) {
            if (ps = strstr(buf, value)) {
                pch = strtok(buf, " \t");
                if (pch != NULL) {
                    pch = strtok(NULL, " \t");
                    ::SetWindowText(::GetDlgItem(hwndDlg, OPEN_START_APP), pch);
                }
            }
        }
        fclose(pFile);
    }
}

void ipbox_list_signal(HWND &hwndDlg, int wmEvent)
{

    HWND hwnd_edit_ip = ::GetDlgItem(hwndDlg, IP_TEXT);
    HWND hwnd_edit_info = ::GetDlgItem(hwndDlg, IP_INFO);
    char buf[512] = {0};
    char* pch = NULL;

    int index = ::SendDlgItemMessage(hwndDlg, IP_LIST, LB_GETCURSEL, 0, 0);
    ::SendDlgItemMessage(hwndDlg, IP_LIST, LB_GETTEXT, index, (long)buf);

    // IP列表选择
    if (wmEvent == LBN_SELCHANGE) {
        pch = strtok(buf, " #");
        if (pch != NULL) {
            ::SetWindowText(hwnd_edit_ip, buf);
            pch = strtok(NULL, " #");
            if (pch != NULL)
                ::SetWindowText(hwnd_edit_info, pch);
            else
                ::SetWindowText(hwnd_edit_info, "");
        }

        strcpy(buf, "   信息: IP 管理功能，添加和删除后，请点保存！");
        ::SetWindowText(::GetDlgItem(hwndDlg, IDC_INFO_TEXT), buf);

    }
    // 鼠标双击选择IP，复制到剪贴板
    if (wmEvent == LBN_DBLCLK) {
        pch = strtok(buf, " #");
        if (pch != NULL) {
            CopyTextToClipboard(buf);
        }

        // 更细提示信息
        strcpy(getip, buf);
        strcpy(buf, "   信息: IP已复制到剪贴板，方便其他程序使用！");
        ::SetWindowText(::GetDlgItem(hwndDlg, IDC_INFO_TEXT), buf);

        //   MessageBox(hwndDlg, buf, getip, MB_OK);

        //  更新命令按钮文本
        strcpy(buf, "开启Speeder + Udp2Raw加速TCP伪装      选择IP: ");
        strcat(buf, getip);
        ::SetWindowText(::GetDlgItem(hwndDlg, OPEN_UDP2RAW), buf);

        strcpy(buf, "开启KcpTun + Udp2Raw加速TCP伪装       选择IP: ");
        strcat(buf, getip);
        ::SetWindowText(::GetDlgItem(hwndDlg, OPEN_KCP), buf);

    }
}

// 复制文本到剪贴板
bool CopyTextToClipboard(const char* text)
{
    int i = 0, j = 0;
    for (; i < 6; i++) {
        //打开剪切板
        j = OpenClipboard(NULL);

        //判断是否打开成功，如果打开失败则重新尝试5次
        if (j == 0 && i < 5)
            Sleep(60);
        if (j == 0 && i == 5)
            return false;
        if (j != 0) {
            i = 0;
            j = 0;
            break;
        }
    }
    //分配字节数，HGLOBAL表示一个内存块
    HGLOBAL hmem = GlobalAlloc(GHND, strlen(text) + 1);

    //锁定内存中指定的内存块，并返回一个地址值令其指向内存块的起始处
    char* pmem = (char*)GlobalLock(hmem);

    //清空剪切板并释放剪切板内数据的句柄
    EmptyClipboard();
    memcpy(pmem, text, strlen(text) + 1);
    SetClipboardData(CF_TEXT, hmem);        //写入数据
    CloseClipboard();                       //关闭剪切板
    GlobalFree(hmem);                       //释放内存块

    return true;     //返回成功
}

// 设置批处理文件中的服务器IP
bool set_server_ip(const char* filename,  const char* newip)
{
    FILE* input = fopen(filename, "r");
    if (input == NULL) {
        return false;
    }
    FILE* output = tmpfile();

#define LINE_SIZE 1024
    char line[LINE_SIZE];
    char* ps;
    char* Value = "@set SERVER_IP=";

    while (fgets(line, LINE_SIZE, input)) {   // 读取每一行
        if (ps = strstr(line, Value)) {
            fprintf(output, "%s%s\n", Value, newip);
        } else {
            fputs(line, output);
        }
    }

    fclose(input);
    rewind(output);

    input = fopen(filename, "w");
    // 回写文件
    while (fgets(line, LINE_SIZE, output)) {

        fputs(line, input);

    }
    fclose(output);
    fclose(input);
    return true;
}
