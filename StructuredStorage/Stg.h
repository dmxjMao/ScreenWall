#pragma once
#include <bitset>
//#include <string>
//#include <vector>
#include <list>

/*
���ýṹ�嶼�á��ƶ���
operator= �� swap���ڲ���ģ��
*/

//enum StgCfgs {
//	StgCfgs_Normal,
//	StgCfgs_Revision,
//	StgCfgs_Save,
//	StgCfgs_Custom,
//	StgCfgs_Buff
//};

//������
enum StgCfgEnum {
	StgCfgEnumNormal,
	StgCfgEnumRevision_AutoAmend,
	StgCfgEnumRevision_Operator,
	StgCfgEnumRevision,
	StgCfgEnumSave,
	StgCfgEnumCustom,
	StgCfgEnumBuff
};
//extern const CString g_StgStreamNames[];//constҪ��

//�ṹ����
struct StgCfg{
	int nSize;//�ṹ���С
	StgCfg(int sz) : nSize(sz) {}
};

struct StgNormalCfg : StgCfg{
	bool bfloatToolbar = true;
	bool bRealtimePreview = true;
	bool bOpenEmailWhenInReadView = false;
	int nColorScheme = 1;
	int nScreenTipStyle = 0;
	LPTSTR pszUsername;
	int cchUsername = 0;
	LPTSTR pszShortname;
	int cchShortname = 0;	

	//��������
	//������ֵ
	//�ƶ�����
	//�ƶ���ֵ
	//����
	StgNormalCfg(int sz) : StgCfg(sz){}
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
	bool bAutoReplace = false;//��ѡ�˺�����ֶβ���Ч
	LPTSTR pszAutoReplace;//��ʽ��acc-abc;���-���;
	int cchAutoReplace = 0;
	
	StgRevisionCfg_AutoAmend(int sz) : StgCfg(sz) {}
};

struct StgRevisionCfg_Operator : StgCfg {
	bool bAddOpToContextMenu = false;
	//std::bitset<8> bsOpts;
	char szOpts[8] = { 0 };

	StgRevisionCfg_Operator(int sz) : StgCfg(sz) {}
};

struct StgRevisionCfg : StgCfg {
	bool bCheckWhenInput = false;
	bool bUseContextCheck = false;
	char szStyles[10] = { 0 };
	int nStyle = 0;
	//std::bitset<10> bsStyles;

	StgRevisionCfg(int sz) : StgCfg(sz) { /*bsStyles.set();*/ }
};


//����
struct StgSaveCfg : StgCfg {
	int nSaveType = 0;
	int nRecoverTime = 10;
	bool bAutoRecover = true;
	LPTSTR strRecoverFilePath;
	int cchRecoverFilePath = 0;

	StgSaveCfg(int sz) : StgCfg(sz) {}
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
		TYPE type;//�ڵ�����
		//INFO info;
		LPSTORAGE pStorage;//type=Storage
		StgCfg* pCfg;//type=Stream
		StgCfgEnum emCfg;//��������
		Node(CString nm, CString fnm, TYPE t, StgCfg* p = nullptr, StgCfgEnum em = StgCfgEnumBuff) :
			name(nm), parentName(fnm), type(t), pCfg(p), emCfg(em) {}
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
	//�ͷŴ򿪵Ĵ洢����
	void ReleaseStorage();

private:
	//���Ҹ��ڵ�洢����
	Node& FindParentNode(std::list<Node>::iterator it/*��ǰ�ڵ�*/, const CString& name/*���ڵ���*/);

protected:
	bool m_bOpen = false;
	//CString m_strFilename;
	LPSTORAGE m_pRootStg = nullptr;
	//StorageData *m_pCurrentStg = nullptr;
	std::list<Node> m_liNode;
	//const std::vector  ���ÿ���ͬ��
};