/**
 * Part of bargreybars.vim
 * Platform:   Windows x86/x64
 * Maintainer: Dreadnaut <dreadnaut@gmail.com>
 * Version:    0.0.1
 *
 * Code inspired by gvimfullscreen_win32
 * https://github.com/leonid-shevtsov/gvimfullscreen_win32
 *
 * Compiled as x86 or x64 dll with:
 *   cl.exe /LD bargreybars.c Gdi32.lib User32.lib 
 *
 * Call from GVim:
 *   let s:hexColor = "#3f3f3f"
 *   let s:intColor = str2nr(strpart(s:hexColor, 1), 16)
 *   call libcallnr("bargreybars.dll", "SetWindowBackground", s:intColor)
 */
#include <windows.h>

BOOL CALLBACK FindRootWindow(HWND hwnd, LPARAM lParam);
COLORREF LongToColor(long lColor);
COLORREF PickBackgroundColor(HWND hwnd);
VOID ApplyBackground(HWND hwnd, COLORREF crBackground);

/**
 * Finds the GVim window and change its background color.
 * The background color must be supplied as an rgb triplet, represented
 * as a single long integer.
 *
 * If the color supplied is not valid, it will guess the background
 * color based on a pixel in the top left corner
 */
LONG _declspec(dllexport) SetWindowBackground(long lTargetColor) {
  HWND hVim = NULL;
  HWND hTextArea = NULL;

  EnumThreadWindows(GetCurrentThreadId(), FindRootWindow, (LPARAM) &hVim);
  hTextArea = FindWindowEx(hVim, NULL, "VimTextArea", "Vim text area");

  if (hVim != NULL && hTextArea != NULL) {

    BOOLEAN isValidColor = (lTargetColor >= 0);

    /* MessageBox(hVim, isValidColor ? "Valid" : "Auto", "Color", MB_OK); */

    COLORREF crBackground = isValidColor
      ? LongToColor(lTargetColor)
      : PickBackgroundColor(hTextArea);

    ApplyBackground(hVim, crBackground);
  }

  return GetLastError();
}

/**
 * Sets the background color of a window and requests a redraw
 */
VOID ApplyBackground(HWND hwnd, COLORREF crBackground) {
  HBRUSH hbrBackground = CreateSolidBrush(crBackground);

  if (hbrBackground) {
    SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG_PTR) hbrBackground);
    RedrawWindow(hwnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE);
  }
}

/**
 * Accepts the first window which has no parent
 */
BOOL CALLBACK FindRootWindow(HWND hwnd, LPARAM lParam) {
  HWND* hRoot = (HWND*) lParam;

  if (GetParent(hwnd)) {
    *hRoot = NULL;
    return TRUE;
  }

  *hRoot = hwnd;
  return FALSE;
}

/**
 * Converts a long representing a css color to a COLORREF
 */
COLORREF LongToColor(long lColor) {
  long red = (lColor >> 16) & 255;
  long green = (lColor >> 8) & 255;
  long blue = lColor & 255;

  return RGB(red, green, blue);
}

/**
 * Returns the likely background color of the specified window
 */
COLORREF PickBackgroundColor(HWND hwnd) {
  RECT rc;
  COLORREF rgb;

  HDC dc = GetDC(hwnd);
  if (GetClientRect(hwnd, &rc)) {
    rgb = GetPixel(dc, rc.left + 1, rc.top + 1);
  }

  ReleaseDC(hwnd, dc);
  return rgb;
}

