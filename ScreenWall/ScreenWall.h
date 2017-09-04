
// ScreenWall.h : main header file for the ScreenWall application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CScreenWallApp:
// See ScreenWall.cpp for the implementation of this class
//

class CScreenWallApp : public CWinAppEx
{
public:
	CScreenWallApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CScreenWallApp theApp;


struct StgCfg;
class CGobalVariable {
public:
	HICON hIconApp;//������ͼ��
	//GDI+��ʼ��
	ULONG_PTR gdiplusToken;
	GdiplusStartupInput gdiplusStartupInput;
	TCHAR szExePath[MAX_PATH];//exe·��
	TCHAR szStgCfgPath[MAX_PATH];//�����ĵ�·��
	std::vector<StgCfg*> vecCfg;//����
	HANDLE hEventReadStgCfg;//��ȡ�����߳�����¼�


public:
	CGobalVariable();
	~CGobalVariable();
	bool Init();
};
extern CGobalVariable g_GobalVariable; //ȫ�ֱ���