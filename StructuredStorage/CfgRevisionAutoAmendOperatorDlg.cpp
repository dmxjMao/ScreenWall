// CfgRevisionAutoAmendOperatorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "StructuredStorage.h"
#include "CfgRevisionAutoAmendOperatorDlg.h"
#include "afxdialogex.h"


// CCfgRevisionAutoAmendOperatorDlg dialog

IMPLEMENT_DYNAMIC(CCfgRevisionAutoAmendOperatorDlg, CDialogEx)

CCfgRevisionAutoAmendOperatorDlg::CCfgRevisionAutoAmendOperatorDlg(CSSFile* pSSFile, CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_IDD_CfgRevisionAutoAmend_Operator, pParent)
{
	m_pSSFile = pSSFile;
}

CCfgRevisionAutoAmendOperatorDlg::~CCfgRevisionAutoAmendOperatorDlg()
{
}

void CCfgRevisionAutoAmendOperatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_li1);
	DDX_Control(pDX, IDC_CHECK1, m_ch1);
}


BEGIN_MESSAGE_MAP(CCfgRevisionAutoAmendOperatorDlg, CDialogEx)
END_MESSAGE_MAP()


// CCfgRevisionAutoAmendOperatorDlg message handlers


BOOL CCfgRevisionAutoAmendOperatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//Ҫ��PreSubclassWindow �����޸� LBS_HASSTRINGS | LBS_OWNERDRAWFIXED
	//�е�С���⣺���ʱ������һ���ػ棬����item����ƫ�ƣ�����һ�¾ͺ�
	//m_li1.ModifyStyle(0, LBS_HASSTRINGS | LBS_OWNERDRAWFIXED | LBS_OWNERDRAWVARIABLE);
	//m_li1.SetCheckStyle(BS_CHECKBOX);
	const CString opts[] = { _T("����"),_T("��ʱ��Ϣ��ϵ��"),_T("��ַ"),_T("�ص�"),
		_T("������λת����"),_T("����"),_T("ʱ��"),_T("�绰����") };
	int len = sizeof(opts) / sizeof(opts[0]);
	for (int i = 0; i < len; ++i) {
		m_li1.InsertString(i, opts[i]);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}





//
//HRESULT CCfgRevisionAutoAmendOperatorDlg::SetStgCfgs()
//{
//	HRESULT hr = S_OK;
//
//	hr = m_pStream->Write(&m_cfg, sizeof(m_cfg), 0);
//
//	return hr;
//}