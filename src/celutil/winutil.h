// winutil.h
//
// Copyright (C) 2002, Chris Laurel <claurel@shatters.net>
//
// Miscellaneous useful Windows-related functions.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.

#ifndef _WINUTIL_H_
#define _WINUTIL_H_

#include <windows.h>
#include <commctrl.h>
#include <string>

using namespace std;

#if !defined(WINAPI_FAMILY) || (WINAPI_FAMILY == WINAPI_FAMILY_DESKTOP_APP)
void SetMouseCursor(LPCTSTR lpCursor);
void CenterWindow(HWND hParent, HWND hWnd);
void RemoveButtonDefaultStyle(HWND hWnd);
void AddButtonDefaultStyle(HWND hWnd);
#endif
const char* CurrentCP();
std::string UTF8ToCurrentCP(const std::string& str);
std::string CurrentCPToUTF8(const std::string& str);
std::string WideToCurrentCP(const std::wstring& ws);
std::wstring CurrentCPToWide(const std::string& str);
std::string WideToUTF8(const std::wstring& ws);
std::wstring UTF8ToWide(const std::string& str);

#endif
