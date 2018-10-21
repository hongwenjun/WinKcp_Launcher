#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include "resource.h"


int hide_run_cmd(char* cmdline);
bool open_kcp_server(void);
bool open_kcp_udp_server(void);
bool close_kcp_server(void);

HINSTANCE hInst;

BOOL CALLBACK DlgMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
    case WM_INITDIALOG: {
        }
        return TRUE;

    case WM_CLOSE: {
            EndDialog(hwndDlg, 0);
        }
        return TRUE;

    case WM_COMMAND: {
            switch (LOWORD(wParam)) {

            case OPEN_KCP: {
                    open_kcp_server();
                    EndDialog(hwndDlg, 0);
                }
                break;

            case OPEN_KCP_UDP: {
                    open_kcp_udp_server();
                    EndDialog(hwndDlg, 0);
                }
                break;

            case CLOSE_KCP: {
                    close_kcp_server();
                    EndDialog(hwndDlg, 0);
                }
                break;

                return TRUE;
            }
        }
        return TRUE;
    }
    return FALSE;
}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    hInst = hInstance;
    InitCommonControls();
    return DialogBox(hInst, MAKEINTRESOURCE(DLG_MAIN), NULL, (DLGPROC)DlgMain);
}


bool open_kcp_server(void)
{
    char cmdline[] = "cmd /c Windows_KCP.cmd";
    hide_run_cmd(cmdline);

    return true;
}

bool open_kcp_udp_server(void)
{
    char cmdline[] = "cmd /c Windows_KCP_UDP.cmd";
    hide_run_cmd(cmdline);

    return true;
}

bool close_kcp_server(void)
{
    char cmdline[] = "taskkill.exe /im kcp-client.exe  /f /im udp2raw.exe";
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
