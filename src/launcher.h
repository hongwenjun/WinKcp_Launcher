#ifndef LAUNCHER_H_INCLUDED
#define LAUNCHER_H_INCLUDED

#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include <string.h>
#include "resource.h"

// 鼠标点击坐标，对应三个图标的程序,二维码坐标，信息栏坐标
void mouse_click_signal(HWND &hwndDlg, LPARAM lParam);

// 读取 START_APP.cmd 中对应三个图标的程序路径
void read_app_cmd(char* app_cmd, const char* value);

#endif // LAUNCHER_H_INCLUDED
