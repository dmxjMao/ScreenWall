// LoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ScreenWall.h"
#include "LoginDlg.h"
#include "afxdialogex.h"


// CLoginDlg dialog

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_Login, pParent)
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Login_ModifyPswd, m_btnModifyPswd);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_Login_ModifyPswd, &CLoginDlg::OnBnClickedLoginModifypswd)
END_MESSAGE_MAP()


// CLoginDlg message handlers


BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//����ͼ��
	SetIcon(g_GobalVariable.hIconApp, FALSE);
	//�ͻ�������
	GetClientRect(&m_rcClient);
	//��¼ͼƬ
	CStatic* pWndLoginPic = (CStatic*)GetDlgItem(IDC_Login_Pic);
	pWndLoginPic->ModifyStyle(0, SS_ICON);//�Զ���ӦͼƬ��С
	pWndLoginPic->SetIcon(g_GobalVariable.hIconApp);

	//�޸����밴ť 
	m_btnModifyPswd.LoadBitmaps(IDB_Pen2_24px, IDB_Pen2_24px_Focus, IDB_Pen2_24px_Focus);
	m_btnModifyPswd.SizeToContent();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CLoginDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CDialogEx::OnPaint() for painting messages
	
	Graphics gh(dc.GetSafeHdc());
	//�������ꡢ���
	int x(m_rcClient.left), y(m_rcClient.top);
	int	w(m_rcClient.Width()), h(m_rcClient.Height());

	//����ɫ
	//Rect rc(m_rcClient.left, m_rcClient.top, m_rcClient.Width(), m_rcClient.Height());
	//SolidBrush bgBrush(Color(0, 255, 255, 255));
	//gh.FillRectangle(&bgBrush, rc);

	//������
	Rect rcWelcome(x, y, w, h/4);
	LinearGradientBrush bgBrush(rcWelcome,
		Color(216, 254, 233), Color(255, 255, 255),
		LinearGradientModeVertical);
	gh.FillRectangle(&bgBrush, rcWelcome);

	//��48*48ͼ��
	x += 20; y += 10;
	Bitmap bmpApp(g_GobalVariable.hIconApp);
	//UINT width = bmpApp.GetWidth();  32*32
	gh.DrawImage(&bmpApp, x, y, 48, 48);

	//д�֡���Ļǽ��¼��
	x += 48 + 5; y += 5;
	FontFamily fontFamily(_T("����"));//����
	Gdiplus::Font font(&fontFamily, 16, FontStyleRegular, UnitPixel);//�ֺ�
	PointF pt(x*1.0f, y*1.0f);
	SolidBrush txtBrush(Color(0, 51, 153));
	gh.DrawString(_T("��Ļǽ"), -1, &font, pt, &txtBrush);
	
	pt.Y += font.GetHeight(0.0f); //�ۼ�����߶�
	Gdiplus::Font font2(&fontFamily, 20, FontStyleBold, UnitPixel);
	gh.DrawString(_T("��¼"), -1, &font2, pt, &txtBrush);

	//����
	Pen p(Color(216, 254, 233), 2);
	gh.DrawLine(&p, 0, rcWelcome.GetBottom(), m_rcClient.right, rcWelcome.GetBottom());

	//���ֹ�����
	y = rcWelcome.GetBottom() + 2;
	CRect rcLoginGroup; //"��¼����"�ؼ�λ��
	GetDlgItem(IDC_sts_LoginGroup)->GetWindowRect(&rcLoginGroup); //��Ļ����
	ScreenToClient(&rcLoginGroup);
	CRect rcNotice(rcLoginGroup.left, y, rcLoginGroup.right, rcLoginGroup.top);
	GetDlgItem(IDC_sts_Notice)->MoveWindow(&rcNotice);

}


void CLoginDlg::OnBnClickedLoginModifypswd()
{
	//
	AfxMessageBox(_T("�޸�����"));
}
