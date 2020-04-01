#pragma once
#include "pch.h"

class Display
{
private:
	ULONGLONG _StartTime;
	static Display display;
	Display() {};

public:
	~Display() {};
	static Display* GetInstance();

	CEdit* OutputArea;

	void OutputLine(const CString& str);
	void ClearOutput();
	void PrintTimeElapsed();
	void StartTick();
};
#define Dp (Display::GetInstance())