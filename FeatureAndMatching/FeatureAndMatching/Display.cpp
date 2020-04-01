#include "pch.h"
#include "Display.h"

Display Display::display;

Display* Display::GetInstance()
{
	return &Display::display;
}

void Display::OutputLine(const CString& str)
{
	this->OutputArea->SendMessage(WM_VSCROLL, SB_BOTTOM, 0);
	this->OutputArea->SetSel(this->OutputArea->GetWindowTextLength(), this->OutputArea->GetWindowTextLength(), FALSE);
	this->OutputArea->ReplaceSel(str + _T("\r\n"));
}

void Display::ClearOutput()
{
	this->OutputArea->SetWindowTextW(_T(""));
}

void Display::PrintTimeElapsed()
{
	CString str;
	str.Format(_T("×ÜºÄÊ±: %d ms"), GetTickCount64() - this->_StartTime);

	this->OutputLine(str);
}

void Display::StartTick()
{
	this->_StartTime = GetTickCount64();
}