
// ScreenWall.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "ScreenWall.h"
#include "MainFrm.h"

#include "ScreenWallDoc.h"
#include "ScreenWallView.h"

#include "SSFile.h"

#include "LoginDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//��ȡ�����߳�
unsigned int __stdcall ReadStgCfgThread(PVOID pv);

// CScreenWallApp

BEGIN_MESSAGE_MAP(CScreenWallApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CScreenWallApp::OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
END_MESSAGE_MAP()


// CScreenWallApp construction

CScreenWallApp::CScreenWallApp()
{
	m_bHiColorIcons = TRUE;

	// TODO: replace application ID string below with unique ID string; recommended
	// format for string is CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("ScreenWall.AppID.NoVersion"));

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CScreenWallApp object

CScreenWallApp theApp;
CGobalVariable g_GobalVariable; //ȫ�ֱ���

// CScreenWallApp initialization

BOOL CScreenWallApp::InitInstance()
{
	int* a = new int;
	//�ڴ�й¶
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(144);
	
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();
	g_GobalVariable.Init(); //ȫ�ֱ�����ʼ��

	//Alt + F4û��
	CLoginDlg login; //��¼
	//DoModal����ֵ�Ǵ���EndDialog�Ĳ�����EndDialog���ڹر�Dialog
	INT_PTR nRet = login.DoModal();
	if (IDCANCEL == nRet) {
		return FALSE; //�رնԻ���
	}	

	EnableTaskbarInteraction(FALSE);

	// AfxInitRichEdit2() is required to use RichEdit control	
	// AfxInitRichEdit2();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)

	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();

	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CScreenWallDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CScreenWallView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	//

	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it
	m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}

// CScreenWallApp message handlers


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnIDLogin();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_COMMAND(IDLogin, &CAboutDlg::OnIDLogin)
END_MESSAGE_MAP()

// App command to run the dialog
void CScreenWallApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CScreenWallApp customization load/save methods

void CScreenWallApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CScreenWallApp::LoadCustomState()
{
}

void CScreenWallApp::SaveCustomState()
{
}

// CScreenWallApp message handlers





int CScreenWallApp::ExitInstance()
{
	_CrtDumpMemoryLeaks();

	return CWinAppEx::ExitInstance();
}





/*ȫ�ֱ���*/
CGobalVariable::CGobalVariable()
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//GDI+��ʼ����ʹ��֮ǰ������GDI+���ú�GdiplusShutdown
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	hEventReadStgCfg = CreateEvent(nullptr, TRUE, FALSE, nullptr);//�ֶ�δ����

}

CGobalVariable::~CGobalVariable()
{
	GdiplusShutdown(gdiplusToken);
	for (auto& p : vecCfg) {
		SAFE_DELETE(p);
	}
	//_CrtDumpMemoryLeaks();
}

bool CGobalVariable::Init()
{
	bool bRet = true;
	hIconApp = ::LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_Grid64px));

	//��������Ŀ¼
	GetModuleFileName(AfxGetInstanceHandle(), szExePath, MAX_PATH);
	TCHAR* pFind = _tcsrchr(szExePath, '\\');
	szExePath[_tcslen(szExePath) - _tcslen(pFind) + 1] = '\0';

	//��ȡ����
	_tcscpy_s(szStgCfgPath, szExePath);
	_tcscat_s(szStgCfgPath, _T("StgCfg.stg"));

	vecCfg.resize(StgCfgEnum_Buff);
	vecCfg[StgCfgEnum_LoginUser] = new StgCfgLoginUser;

	unsigned int nThreadID(0);
	HANDLE hThread = (HANDLE)_beginthreadex(nullptr, 0, ReadStgCfgThread, nullptr, 0, &nThreadID);
	CloseHandle(hThread); hThread = nullptr;

	return bRet;
}



unsigned int __stdcall ReadStgCfgThread(PVOID pv)
{
	unsigned int nRet = 0;

	//�������ĵ�����ȡ����
	CSSFile* pSSFile = new CSSFile(g_GobalVariable.szStgCfgPath);
	nRet = pSSFile->GetAllCfg();
	SAFE_DELETE(pSSFile);
	//delete pSSFile; pSSFile = nullptr;
	//�û�������ò˵��ڵȴ�
	SetEvent(g_GobalVariable.hEventReadStgCfg);

	return nRet;
}