// CfgRevisionStyle.cpp : implementation file
//

#include "stdafx.h"
#include "StructuredStorage.h"
#include "CfgRevisionStyle.h"
#include "afxdialogex.h"

#include <vector>
using std::vector;

// CCfgRevisionStyle dialog

IMPLEMENT_DYNAMIC(CCfgRevisionStyle, CDialogEx)

CCfgRevisionStyle::CCfgRevisionStyle(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CfgRevision_Style, pParent)
{

}

CCfgRevisionStyle::~CCfgRevisionStyle()
{
}

void CCfgRevisionStyle::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_cbo1);
	DDX_Control(pDX, IDC_LIST1, m_li1);
}


BEGIN_MESSAGE_MAP(CCfgRevisionStyle, CDialogEx)
END_MESSAGE_MAP()


// CCfgRevisionStyle message handlers


BOOL CCfgRevisionStyle::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//CRect rcClient;
	//GetClientRect(&rcClient);

	const CString strItems[] = { _T("��׼"),_T("�Զ���") };
	int len = sizeof(strItems) / sizeof(strItems[0]);
	for (int i = 0; i < len; ++i) {
		m_cbo1.AddString(strItems[i]);
	}
	m_cbo1.SetCurSel(0);

	m_li1.ModifyStyle(0, LVS_NOCOLUMNHEADER);
	m_li1.SetExtendedStyle(m_li1.GetExtendedStyle() | LVS_EX_CHECKBOXES);
	EnableWindowTheme(m_li1.m_hWnd, L"ListView", L"Explorer", NULL);
	//m_li1.SetExtendedStyle(m_li1.GetExtendedStyle() | LVS_NOCOLUMNHEADER);


	m_li1.SetRedraw(FALSE);
	CString strGroup[] = { _T("�﷨"),_T("����ʵ�")};
	vector<CString> vec = { _T("�Ǳ�׼������λ"),_T("�Ǳ�׼���ָ�ʽ"),_T("������������") ,
			 _T("ҽѧ��"),_T("������"),_T("���ӡ��������"),_T("����������"),
			_T("��ѧ��������"), _T("��ѧ��"), _T("ũ�֡�������") };
	len = vec.size();
	//LVITEM lvItem;
	//lvItem.mask = LVIF_TEXT;
	
	CRect rc;
	m_li1.GetClientRect(&rc);
	m_li1.InsertColumn(0, _T(""), LVCFMT_LEFT, rc.Width() - 30);//���һ�У���Ȼ������ʾitem;

	for (int k = 0; k < len; ++k) {
		m_li1.InsertItem(k, vec[k]);
	}

	len = sizeof(strGroup) / sizeof(strGroup[0]);
	m_li1.EnableGroupView(TRUE);
	const CPoint nItemsPerGroup[] = { CPoint(0,3),CPoint(3,vec.size()) }; //�鷶Χ
	for (int i = 0; i < len; ++i) {
		LVGROUP lg = { 0 };
		lg.cbSize = sizeof(lg);
		lg.mask = LVGF_GROUPID | LVGF_HEADER | LVGF_STATE;
		lg.iGroupId = i;
		lg.pszHeader = strGroup[i].GetBuffer();
		lg.cchHeader = strGroup[i].GetLength();
		lg.state = LVGS_COLLAPSIBLE;

		int nGroupId = m_li1.InsertGroup(i, &lg);
		if (-1 == nGroupId) {
			return FALSE;
		}
		//��Ԫ��
		LVITEM lvItem = { 0 };
		lvItem.mask = LVIF_GROUPID;
		//memset(&lvItem, 0, sizeof(LVITEM));
		//lvItem.mask = LVIF_GROUPID;
		const CPoint& range = nItemsPerGroup[i];
		for (int k = range.x; k < range.y; ++k) {
			lvItem.iItem = k;
			//lvItem.iSubItem = 0;
			lvItem.iGroupId = nGroupId;
			m_li1.SetItem(&lvItem);
		}
	}
	m_li1.SetRedraw(TRUE);
	//����ƥ��item�����ȼ�¼
	//len = vec.size();
	////const int nItemsPerGroup[] = { 3,len - 3 };
	//for (int nRow = 0; nRow < len; ++nRow)
	//{
	//	LVITEM lvItem = { 0 };
	//	lvItem.mask = LVIF_GROUPID;
	//	lvItem.iItem = nRow;
	//	if (nRow < 3)
	//		lvItem.iGroupId = 0;
	//	else
	//		lvItem.iGroupId = 1;
	//	m_li1.SetItem(&lvItem);
	//}


	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
