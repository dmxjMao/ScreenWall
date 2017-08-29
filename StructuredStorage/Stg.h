#pragma once
#include <bitset>
//#include <string>
//#include <vector>
#include <list>

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
extern const CString g_StgStreamNames[];//constҪ��


//����
//enum StgNormalColorScheme {
//	StgNormalColorScheme_Red,
//	StgNormalColorScheme_Green,
//	StgNormalColorScheme_Blue,
//	StgNormalColorScheme_Buff
//};
//const CString StgNormalColorScheme

//enum StgNormalScreenTipStyle {
//	StgNormalScreenTipStyle_1,
//	StgNormalScreenTipStyle_2,
//	StgNormalScreenTipStyle_3,
//	StgNormalScreenTipStyle_Buff
//};

//�ṹ����
struct StgCfg{};

struct StgNormalCfg : StgCfg{
	bool bfloatToolbar = true;
	bool bRealtimePreview = true;
	/*StgNormalColorScheme  emColorScheme = StgNormalColorScheme_Green;
	StgNormalScreenTipStyle emScreenTipStyle = StgNormalScreenTipStyle_1;*/
	int nColorScheme = 1;
	int nScreenTipStyle = 0;
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
	//StgNormalCfg& operator=(StgNormalCfg&& rhs) noexcept;
	//friend void swap(StgNormalCfg& lhs, StgNormalCfg& rhs);
};


//У��

struct StgRevisionCfg_AutoAmend : StgCfg {
	bool bShowAutoAmendBtn = false;
	bool bUpcaseFirst2Char = false;
	bool bAmend3 = false;
	bool bAutoReplace = false;//��ѡ�˺����ֶβ���Ч
	CString strAutoRplace;//��ʽ��acc-abc;���-���;
	
	//StgRevisionAutoAmend_AutoAmend& operator=(StgRevisionAutoAmend_AutoAmend&& rhs) noexcept;
	//friend void swap(StgRevisionAutoAmend_AutoAmend& lhs, StgRevisionAutoAmend_AutoAmend& rhs);
};

struct StgRevisionCfg_Operator : StgCfg {
	bool bAddOpToContextMenu = false;
	std::bitset<8> bsOpts;


	//StgRevisionAutoAmend_Operator& operator=(StgRevisionAutoAmend_Operator&& rhs) noexcept;
	//friend void swap(StgRevisionAutoAmend_Operator& lhs, StgRevisionAutoAmend_Operator& rhs);
};


struct StgRevisionCfg : StgCfg {
	//StgRevisionCfg_AutoAmend stAutoAmend;
	//StgRevisionAutoAmend_Operator stOperator;
	bool bCheckWhenInput = false;
	bool bUseContextCheck = false;
	int nStyle = 0;
	//StgRevisionStyle stStyle;
	std::bitset<10> bsStyles;

	StgRevisionCfg() { bsStyles.set(); }
};


struct StgSaveCfg : StgCfg {
	//StgSaveSaveType emSaveType = StgSaveSaveType_Docx;
	int nSaveType = 0;
	bool bAutoRecover = true;
	int nRecoverTime = 10;
	CString strRecoverFilePath = _T("C:\\Users\\dmxjMao\\Documents\\");

	//StgSave& operator=(StgSave&& rhs) noexcept;
	//friend void swap(StgSave& lhs, StgSave& rhs);
};


//�Զ���



//Stg������
class IStgCfgOperator {
public:
	virtual HRESULT GetStgCfgs() = 0;
	//virtual bool IsDirty() = 0;
	virtual HRESULT SetStgCfgs() = 0;

protected:
	StgCfg* m_cfg = nullptr;
	LPSTREAM m_pStream = nullptr;
	bool m_bDirty = false;
};

//
class CSSFile {
public:
	//�Ӵ洢���֡�����
	enum TYPE { Storage, Stream };
	//union INFO {
	//	LPSTORAGE pStorage;//type=Storage
	//	StgCfg* pCfg;//type=Stream
	//};
	struct Node {
		CString name, parentName;
		TYPE type;
		//INFO info;
		LPSTORAGE pStorage;//type=Storage
		StgCfg* pCfg;//type=Stream
		Node(CString nm, CString fnm, TYPE t, StgCfg* p = nullptr) :
			name(nm), parentName(fnm), type(t), pCfg(p) {}
	};

	CSSFile();
	//struct StorageData
	//{
	//	IStorage *Stg = nullptr;
	//	StorageData *ParentStg = nullptr;
	//};
	//�򿪸����ĵ�
	bool OpenSSFile(const CString & filename, DWORD mode = STGM_READWRITE | STGM_SHARE_EXCLUSIVE);
	//�򿪴洢����
	bool OpenStroage(const CString & name, /*LPSTORAGE pStorage, */DWORD mode = STGM_READWRITE | STGM_SHARE_EXCLUSIVE);
	//����
	bool OpenStream(const CString & name, LPSTREAM* pStream, DWORD mode = STGM_READWRITE | STGM_SHARE_EXCLUSIVE);
	//�رո����ĵ�
	void Close();

protected:
	//���������ĵ�
	bool CreateSSFile(const CString & filename, DWORD mode = STGM_READWRITE | STGM_SHARE_EXCLUSIVE);
	//�����洢����
	bool CreateStroage(const CString & name, LPSTORAGE pStorage, DWORD mode = STGM_READWRITE | STGM_SHARE_EXCLUSIVE);
	//������
	bool CreateStream(const CString & name, LPSTREAM* pStream, DWORD mode = STGM_READWRITE | STGM_SHARE_EXCLUSIVE);
	//�ͷŴ򿪵Ĵ洢����
	bool ExitStorage();
	//��ȡ���洢
	IStorage * GetRootStorage() const;
	//�ĵ��Ƿ��
	bool IsOpen() const;
	//����Ĭ������
	//bool CreateDefaultCfg();

private:
	//���Ҹ��ڵ�洢����
	Node& FindParentNode(std::list<Node>::iterator it/*��ǰ�ڵ�*/, const CString& name/*���ڵ���*/);

protected:
	bool m_bOpen = false;
	//CString m_strFilename;
	LPSTORAGE m_pRootStg = nullptr;
	//StorageData *m_pCurrentStg = nullptr;
	std::list<Node> m_liNode;

};