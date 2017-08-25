// CfgNormalDlg.cpp : implementation file
//

#include "stdafx.h"
#include "StructuredStorage.h"
#include "CfgNormalDlg.h"
#include "afxdialogex.h"

//#include "Stg.h"

// CCfgNormalDlg dialog

IMPLEMENT_DYNAMIC(CCfgNormalDlg, CDialogEx)

CCfgNormalDlg::CCfgNormalDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_Cfg_Normal, pParent)
{
	//m_spCfg = std::make_shared<StgNormalCfg>();
	//m_pCfg = new StgNormalCfg();
}

CCfgNormalDlg::~CCfgNormalDlg()
{
	//SAFE_DELETE(m_pCfg);
}

void CCfgNormalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK1, m_ck_1);
	DDX_Control(pDX, IDC_CHECK2, m_ck_2);
	DDX_Control(pDX, IDC_CHECK3, m_ck_3);
	DDX_Control(pDX, IDC_COMBO1, m_cbo_1);
	DDX_Control(pDX, IDC_COMBO2, m_cbo_2);
	DDX_Control(pDX, IDC_EDIT2, m_edt_2);
	DDX_Control(pDX, IDC_EDIT3, m_edt_3);
}


BEGIN_MESSAGE_MAP(CCfgNormalDlg, CDialogEx)
END_MESSAGE_MAP()


// CCfgNormalDlg message handlers


BOOL CCfgNormalDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	const auto& cfg = m_cfg;
	m_ck_1.SetCheck(cfg.bfloatToolbar);
	m_ck_2.SetCheck(cfg.bRealtimePreview);
	const CString strColorSchemes[] = { _T("��ɫ"), _T("��ɫ"), _T("��ɫ") };
	int nSchemeCnts = sizeof(strColorSchemes) / sizeof(strColorSchemes[0]);
	for (int i = 0; i < nSchemeCnts; ++i) {
		m_cbo_1.InsertString(i, strColorSchemes[i]);
	}
	m_cbo_1.SetCurSel(cfg.emColorScheme);

	const CString strTips[] = { _T("�򵫼��﷢����"), _T("��ż��"), _T("��ɫ") };
	int nTipCnts = sizeof(strTips) / sizeof(strTips[0]);
	for (int i = 0; i < nTipCnts; ++i) {
		m_cbo_2.InsertString(i, strTips[i]);
	}
	m_cbo_2.SetCurSel(cfg.emScreenTipStyle);

	m_edt_2.SetWindowText(cfg.strUsername);
	m_edt_3.SetWindowText(cfg.strShortname);

	m_ck_3.SetCheck(cfg.bOpenEmailWhenInReadView);

	return TRUE; 
}
