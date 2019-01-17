#ifndef IPBOX_EDIT_H_INCLUDED
#define IPBOX_EDIT_H_INCLUDED

#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include <string.h>
#include "resource.h"


// ip管理窗口
const long ipbox[] = { IP_TEXT, IP_LIST, IP_ADD, IP_DEL, IP_INFO, IP_SAVE, IP_BOX, IP_LT1, IP_LT2};

void getnewip(char* newip);
void open_ipbox(HWND &hwndDlg);
void ipbox_add(HWND &hwndDlg);
void ipbox_del(HWND &hwndDlg);
void ipbox_save(HWND &hwndDlg);
void ipbox_load(HWND &hwndDlg);
void read_appname(HWND &hwndDlg);
void ipbox_list_signal(HWND &hwndDlg, int wmEvent);

bool CopyTextToClipboard(const char* text);
bool set_server_ip(const char* filename,  const char* newip);
#endif // IPBOX_EDIT_H_INCLUDED
