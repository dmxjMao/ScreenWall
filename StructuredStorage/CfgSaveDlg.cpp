// CfgSaveDlg.cpp : implementation file
//

#include "stdafx.h"
#include "StructuredStorage.h"
#include "CfgSaveDlg.h"
#include "afxdialogex.h"

#include "Stg.h"

// CCfgSaveDlg dialog

IMPLEMENT_DYNAMIC(CCfgSaveDlg, CDialogEx)

CCfgSaveDlg::CCfgSaveDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_Cfg_Save, pParent)
{

}

CCfgSaveDlg::~CCfgSaveDlg()
{
}

void CCfgSaveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_cbo1);
}


BEGIN_MESSAGE_MAP(CCfgSaveDlg, CDialogEx)
END_MESSAGE_MAP()


// CCfgSaveDlg message handlers


BOOL CCfgSaveDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	const CString strSaveTypes[] = { _T("Word�ĵ�(*.docx)"),
		_T("Word 97-2003�ĵ�(*.doc)") ,_T("��ҳ(*.html,*.htm)") ,
		_T("���ı�(*.txt)") ,_T("Word XML�ĵ�(*.xml)") };
	int len = sizeof(strSaveTypes) / sizeof(strSaveTypes[0]);
	for (int i = 0; i < len; ++i) {
		m_cbo1.InsertString(i, strSaveTypes[i]);
	}
	m_cbo1.SetCurSel(StgSaveSaveType_Docx);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
