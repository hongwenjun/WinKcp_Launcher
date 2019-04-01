#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include "resource.h"
#include "ipbox_edit.h"
#include "launcher.h"

bool open_kcp_server(void);
bool open_start_app(void);
bool close_kcp_server(void);
bool open_wireguard_udp2raw(void);
bool kill_advert_process(void);
int  hide_run_cmd(char* cmdline);
void App_Initdialog(HWND & hwnd);
void feedback_info(HWND & hwndDlg, int BTN_ID);

HBITMAP g_hBitmap_DONATE; // 打赏图片的句柄
HICON   g_hIcon;          // 对话框图标句柄
bool debug_flg = false;   // 调试:勾选->显示窗口

HINSTANCE hInst;

BOOL CALLBACK DlgMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

    switch (uMsg) {
    case WM_INITDIALOG: {
            App_Initdialog(hwndDlg); // 设置标题栏图标,// 设置图片

        }
        break;

    case WM_CLOSE: {
            EndDialog(hwndDlg, 0);
        }
        return TRUE;

    case WM_COMMAND: {

            int  wmId    = LOWORD(wParam);
            int  wmEvent = HIWORD(wParam);

            switch (LOWORD(wParam)) {

            case OPEN_START_APP: {
                    open_start_app();
                    EndDialog(hwndDlg, 0);
                }
                break;

            case OPEN_KCP: {
                    close_kcp_server();

                    if (BST_CHECKED == IsDlgButtonChecked(hwndDlg, DEBUG_FLG))
                        debug_flg = true;
                    else
                        debug_flg = false;

                    open_kcp_server();
                    feedback_info(hwndDlg, OPEN_KCP);
                }
                break;

            case OPEN_UDP2RAW: {
                    close_kcp_server();

                    if (BST_CHECKED == IsDlgButtonChecked(hwndDlg, DEBUG_FLG))
                        debug_flg = true;
                    else
                        debug_flg = false;

                    open_wireguard_udp2raw();
                    feedback_info(hwndDlg, OPEN_UDP2RAW);
                }
                break;

            case CLOSE_KCP: {
                    close_kcp_server();
                    kill_advert_process();
                    EndDialog(hwndDlg, 0);
                }
                break;

            case IP_SESELECT: {
                    // ip管理窗口开启
                    ipbox_load(hwndDlg);
                    open_ipbox(hwndDlg);
                }
                break;

            case IP_ADD: {
                    ipbox_add(hwndDlg);
                }
                break;

            case IP_DEL: {
                    ipbox_del(hwndDlg);
                }
                break;

            case IP_SAVE: {
                    ipbox_save(hwndDlg);
                }
                break;

            case IP_LIST: {
                    ipbox_list_signal(hwndDlg, wmEvent);
                }
                break;

                return TRUE;
            }
        }
        return TRUE;

    case WM_LBUTTONDOWN: {
            // 鼠标单击信号传替
            mouse_click_signal(hwndDlg, lParam);
            break;
        }

    }
    return FALSE;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    hInst = hInstance;
//   InitCommonControls();

    // 从资源中加载BMP文件和图标，这些工作也可以在WM_INITDIALOG消息中进行
    g_hBitmap_DONATE = ::LoadBitmap(hInst, (LPCTSTR)IDB_BITMAP1);
    g_hIcon = ::LoadIcon(hInst, (LPCTSTR)IDI_ICON1);

    return DialogBox(hInst, MAKEINTRESOURCE(DLG_MAIN), NULL, (DLGPROC)DlgMain);
}

void feedback_info(HWND & hwndDlg, int BTN_ID)
{
    SetWindowText(::GetDlgItem(hwndDlg, BTN_ID), "【。。加速服务正在运行中。。】");
    SetWindowText(::GetDlgItem(hwndDlg, IDC_INFO_TEXT), "【服务运行中-->三图标启动程序-->点绿色区域关闭】");
}
bool open_start_app(void)
{
    char newip[128] = {0};
    getnewip(newip);
    if (strcmp(newip, "NULL") != 0)
        set_server_ip("START_APP.cmd", newip);

    char cmdline[] = "cmd /c START_APP.cmd";
    hide_run_cmd(cmdline);

    return true;
}

bool open_kcp_server(void)
{
    char newip[128] = {0};
    getnewip(newip);
    if (strcmp(newip, "NULL") != 0)
        set_server_ip("Windows_KCP.cmd", newip);

    char cmdline[] = "cmd /c Windows_KCP.cmd";
    hide_run_cmd(cmdline);

    return true;
}

bool open_wireguard_udp2raw(void)
{
    char newip[128] = {0};
    getnewip(newip);
    if (strcmp(newip, "NULL") != 0)
        set_server_ip("Windows_UDP2RAW.cmd", newip);
//    MessageBox(0, newip, newip, MB_OK);

    char cmdline[] = "cmd /c Windows_UDP2RAW.cmd";
    hide_run_cmd(cmdline);

    return true;
}


bool close_kcp_server(void)
{
    char cmdline[] = "taskkill.exe /im kcp-client.exe  /f /im udp2raw.exe  /im speederv2.exe "
                     "/im brook.exe  /im TunSafe.exe ";
    hide_run_cmd(cmdline);

    return true;
}

bool kill_advert_process(void)
{
    char cmdline[] = "taskkill.exe /im YunDetectService.exe  /im AlibabaprotectUI.exe /im acrotray.exe ";
    hide_run_cmd(cmdline);

    return true;
}

// 后台执行命令行函数
int hide_run_cmd(char* cmdline)
{
    SetConsoleTitle(cmdline);
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);

    // 后台隐藏
    si.dwFlags   =   STARTF_USESHOWWINDOW;
    si.wShowWindow   =   SW_HIDE;

    if (debug_flg) {
        si.wShowWindow = SW_SHOW;
    }

    ZeroMemory(&pi, sizeof(pi));
    // Start the child process.
    CreateProcess(NULL, TEXT(cmdline), NULL, NULL, FALSE, 0,
                  NULL, NULL, &si, &pi);
    // Wait until child process exits.
    WaitForSingleObject(pi.hProcess, INFINITE);
    // Get the return value of the child process
    DWORD ret;
    GetExitCodeProcess(pi.hProcess, &ret);
//    if (!ret) {
//        // .....
//    }
    // Close process and thread handles.
//    CloseHandle(pi.hProcess);
//    CloseHandle(pi.hThread);
    return ret;
}

void App_Initdialog(HWND & hwnd)
{

    // 大图标：按下alt+tab键切换窗口时对应的图标
    // 小图标：就是窗口左上角对应的那个图标
    ::SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)g_hIcon);
    ::SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)g_hIcon);

    // 设置图片
    ::SendDlgItemMessage(hwnd, DONATE_PIC, STM_SETIMAGE, IMAGE_BITMAP, (long)g_hBitmap_DONATE);


    // ipbox : ip管理窗口隐藏
    for (size_t i = 0 ; i != sizeof ipbox / sizeof * ipbox ; i++) {
        HWND hwnd_ipbox = ::GetDlgItem(hwnd, ipbox[i]);
        ::ShowWindow(hwnd_ipbox, SW_HIDE);
    }

    // 读取自定义程序标题名
    read_appname(hwnd);
}
