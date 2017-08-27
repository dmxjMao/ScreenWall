#pragma once
#include <bitset>
#include <string>
//#include <vector>

/*
���ýṹ�嶼�á��ƶ���
operator= �� swap���ڲ���ģ��
*/

//������
enum StgCfgs {
	StgCfgs_Normal,
	StgCfgs_Revision,
	StgCfgs_Save,
	StgCfgs_Custom,
	StgCfgs_Buff
};

//��ϸ������
enum StgDetailedCfgs {
	StgDetailedCfgs_Normal,
	StgDetailedCfgs_Revision_AutoAmend,
	StgDetailedCfgs_Revision_Operator,
	StgDetailedCfgs_Revision,
	StgDetailedCfgs_Save,
	StgDetailedCfgs_Custom,
	StgDetailedCfgs_Buff
};
extern const TCHAR* g_StgStreamNames[];//constҪ��


//����
enum StgNormalColorScheme {
	StgNormalColorScheme_Red,
	StgNormalColorScheme_Green,
	StgNormalColorScheme_Blue,
	StgNormalColorScheme_Buff
};
//const CString StgNormalColorScheme

enum StgNormalScreenTipStyle {
	StgNormalScreenTipStyle_1,
	StgNormalScreenTipStyle_2,
	StgNormalScreenTipStyle_3,
	StgNormalScreenTipStyle_Buff
};

struct StgNormalCfg {
	bool bfloatToolbar = true;
	bool bRealtimePreview = true;
	StgNormalColorScheme  emColorScheme = StgNormalColorScheme_Green;
	StgNormalScreenTipStyle emScreenTipStyle = StgNormalScreenTipStyle_1;
	CString strUsername;
	CString strShortname;
	bool bOpenEmailWhenInReadView = false;

	//��������
	//������ֵ
	//�ƶ�����
	//�ƶ���ֵ
	//����
	//StgNormalCfg() {}
	//StgNormalCfg::StgNormalCfg(StgNormalCfg&& rhs) noexcept;
	//StgNormalCfg& operator=(const StgNormalCfg& rhs);
	//StgNormalCfg& operator=(StgNormalCfg rhs);
	StgNormalCfg& operator=(StgNormalCfg&& rhs) noexcept;
	friend void swap(StgNormalCfg& lhs, StgNormalCfg& rhs);
};


//У��

struct StgRevisionAutoAmend_AutoAmend {
	bool bShowAutoAmendBtn = false;
	bool bUpcaseFirst2Char = false;
	bool bAmend3 = false;
	bool bAutoReplace = false;//��ѡ�˺����ֶβ���Ч
	std::wstring strAutoRplace;//��ʽ��acc-abc;���-���;
	
	StgRevisionAutoAmend_AutoAmend& operator=(StgRevisionAutoAmend_AutoAmend&& rhs) noexcept;
	friend void swap(StgRevisionAutoAmend_AutoAmend& lhs, StgRevisionAutoAmend_AutoAmend& rhs);
};

struct StgRevisionAutoAmend_Operator {
	bool bAddOpToContextMenu = false;
	std::bitset<8> bsOpts;

	StgRevisionAutoAmend_Operator& operator=(StgRevisionAutoAmend_Operator&& rhs) noexcept;
	friend void swap(StgRevisionAutoAmend_Operator& lhs, StgRevisionAutoAmend_Operator& rhs);
};

enum StgRevisionStyleEnum {
	StgRevisionStyle_Normal,
	StgRevisionStyle_Custom,
	StgRevisionStyle_Buff
};
struct StgRevisionStyle {
	StgRevisionStyleEnum style = StgRevisionStyle_Normal;
	std::bitset<10> bsStyles;

	StgRevisionStyle() { bsStyles.set(); }
	StgRevisionStyle& operator=(StgRevisionStyle&& rhs) noexcept;
	friend void swap(StgRevisionStyle& lhs, StgRevisionStyle& rhs);

};

struct StgRevision {
	StgRevisionAutoAmend_AutoAmend stAutoAmend;
	StgRevisionAutoAmend_Operator stOperator;
	bool bCheckWhenInput = false;
	bool bUseContextCheck = false;
	StgRevisionStyle stStyle;

	//��������
	//������ֵ
	//�ƶ�����
	//�ƶ���ֵ
	//����
	//StgNormalCfg() {}
	//StgNormalCfg::StgNormalCfg(StgNormalCfg&& rhs) noexcept;
	//StgNormalCfg& operator=(const StgNormalCfg& rhs);
	//StgNormalCfg& operator=(StgNormalCfg rhs);
	StgRevision& operator=(StgRevision&& rhs) noexcept;
	friend void swap(StgRevision& lhs, StgRevision& rhs);
};


//����
enum StgSaveSaveType{
	StgSaveSaveType_Docx,
	StgSaveSaveType_Doc,
	StgSaveSaveType_Html,
	StgSaveSaveType_Txt,
	StgSaveSaveType_Xml,
	StgSaveSaveType_Buff
};
struct StgSave {
	StgSaveSaveType emSaveType = StgSaveSaveType_Docx;
	bool bAutoRecover = true;
	unsigned short usRecoverTm = 10;
	std::wstring strRecoverFilePath = L"C:\\Users\\dmxjMao\\Documents\\";

	StgSave& operator=(StgSave&& rhs) noexcept;
	friend void swap(StgSave& lhs, StgSave& rhs);
};


//�Զ���



//Stg������
class IStgOperator {
public:
	virtual HRESULT GetStgCfgs() = 0;
	//virtual bool IsDirty() = 0;
	virtual HRESULT SetStgCfgs() = 0;
};

//
class CSSFile {
public:
	struct StorageData
	{
		IStorage *Stg = nullptr;
		StorageData *ParentStg = nullptr;
	};
	//�����ļ�
	bool CreateSSFile(const CString & filename, DWORD mode = STGM_READWRITE | STGM_SHARE_EXCLUSIVE);
	//���ļ�
	bool OpenSSFile(const CString & filename, DWORD mode = STGM_READWRITE | STGM_SHARE_EXCLUSIVE);
	//������
	bool CreateStream(const CString & name, LPSTREAM* pStream, DWORD mode = STGM_READWRITE | STGM_SHARE_EXCLUSIVE);
	//����
	bool OpenStream(const CString & name, LPSTREAM* pStream, DWORD mode = STGM_READWRITE | STGM_SHARE_EXCLUSIVE);
	//�ر��ļ�
	void Close();
	//�ͷŴ򿪵�storage
	bool ExitStorage();

	IStorage * GetRootStorage() const;
	bool IsOpen() const;

protected:
	bool m_bOpen = false;
	CString m_strFilename;
	IStorage *m_pRootStg = nullptr;
	StorageData *m_pCurrentStg = nullptr;


};