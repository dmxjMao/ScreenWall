#pragma once
#include <bitset>
#include <string>
#include <vector>
//#include <list>
#include <map>




//������
enum StgCfgEnum {
	StgCfgEnumNormal,
	StgCfgEnumRevision,
	StgCfgEnumRevision_AutoAmend,
	StgCfgEnumRevision_Operator,
	StgCfgEnumSave,
	StgCfgEnumCustom,
	StgCfgEnumBuff
};
//extern const CString g_StgStreamNames[];//constҪ��

const unsigned short STGCFG_UsernameLen = 16;
const unsigned int STGCFG_AutoReplaceLen = 1024;


//�ṹ����
struct StgCfg{
	//int nSize;//�ṹ���С
	//StgCfg(int sz) : nSize(sz) {}
	//����д�󶨵�ÿ��������ȥ
	virtual void Read(LPSTREAM/*,StgCfg*&*/) = 0;
	virtual void Write(LPSTREAM/*,const StgCfg*&*/) = 0;
};

struct StgNormalCfg : StgCfg{
	int bfloatToolbar = 1;
	int bRealtimePreview = 1;
	int bOpenEmailWhenInReadView = 0;
	int nColorScheme = 1;
	int nScreenTipStyle = 0;
	/*
	pStream��д������FILE��ֱ�ӽ�TCHAR*��д��
	����û�취����ʱ��TCHAR[]����Ȼ�����ã��������С���ɣ�
	*/
	LPTSTR pszUsername /*= _T("hello")*/ = nullptr; //���������Ͳ���д���ˣ�
	int cchUsername = 0; //������д��֮ǰһ��Ҫ��ֵ
	//std::hash_map<
	virtual void Read(LPSTREAM/*, StgCfg*&*/);
	virtual void Write(LPSTREAM/*, const StgCfg*&*/);
	//TCHAR szUsername[STGCFG_UsernameLen] = { 0 };
	//CString szUsername;  û��
	//int cchUsername = 0;
	//TCHAR szShortname[STGCFG_UsernameLen] = { 0 };
	//int cchShortname = 0;	

	//��������
	//������ֵ
	//�ƶ�����
	//�ƶ���ֵ
	//����
	//StgNormalCfg(/*int sz*/) /*: StgCfg(sz)*/{}
	//StgNormalCfg::StgNormalCfg(StgNormalCfg&& rhs) noexcept;
	//StgNormalCfg& operator=(const StgNormalCfg& rhs);
	//StgNormalCfg& operator=(StgNormalCfg rhs);
	//StgNormalCfg& operator=(StgNormalCfg&& rhs) noexcept;
	//friend void swap(StgNormalCfg& lhs, StgNormalCfg& rhs);
};

//
//У��

struct StgRevisionCfg : StgCfg {
	int nCheckWhenInput = 0;
	int nUseContextCheck = 0;
	int nStyle = 0;
	UINT8 szStyles[10] = { 0 };
	//std::bitset<10> bsStyles;

	//StgRevisionCfg(/*int sz*/)/* : StgCfg(sz)*/ { /*bsStyles.set();*/ }
};

struct StgRevisionCfg_AutoAmend : StgCfg {
	int nShowAutoAmendBtn = 0;
	int nUpcaseFirst2Char = 0;
	int nAmend3 = 0;
	int nAutoReplace = 0;//��ѡ�˺�����ֶβ���Ч
	TCHAR szAutoReplace[STGCFG_AutoReplaceLen] = { 0 };//��ʽ��acc-abc;���-���;
	//int cchAutoReplace = 0;
	
	//StgRevisionCfg_AutoAmend(/*int sz*/) /*: StgCfg(sz)*/ {}
};

struct StgRevisionCfg_Operator : StgCfg {
	int nAddOpToContextMenu = 0;
	//std::bitset<8> bsOpts;
	UINT8 szOpts[8] = { 0 };

	//StgRevisionCfg_Operator(/*int sz*/)/* : StgCfg(sz)*/ {}
};


//
//
////����
//struct StgSaveCfg : StgCfg {
//	int nSaveType = 0;
//	int nRecoverTime = 10;
//	bool bAutoRecover = true;
//	LPTSTR strRecoverFilePath;
//	int cchRecoverFilePath = 0;
//
//	StgSaveCfg(/*int sz*/) /*: StgCfg(sz)*/ {}
//};
//
//
////�Զ���



//Stg������
class CSSFile;
class IStgCfgOperator {
public:
	//virtual HRESULT GetStgCfgs() = 0;
	//virtual HRESULT SetStgCfgs() = 0;

protected:
	//StgCfg* m_cfg = nullptr;
	CSSFile* m_pSSFile = nullptr;
	LPSTREAM m_pStream = nullptr;
	//bool m_bDirty = false;
};

//
class CSSFile {
public:
	//�Ӵ洢���֡�����
	//enum TYPE { Storage, Stream };
	//union INFO {
	//	LPSTORAGE pStorage;//type=Storage
	//	StgCfg* pCfg;//type=Stream
	//};
	//struct Node {
	//	CString name, parentName;
	//	TYPE type;//�ڵ�����
	//	//INFO info;
	//	LPSTORAGE pStorage;//type=Storage
	//	StgCfg* pCfg;//type=Stream
	//	StgCfgEnum emCfg;//��������
	//	Node(CString nm, CString fnm, TYPE t, StgCfg* p = nullptr, StgCfgEnum em = StgCfgEnumBuff) :
	//		name(nm), parentName(fnm), type(t), pCfg(p), emCfg(em) {}
	//};

	struct StorageNode {
		int idx = 0;
		CString name;
		LPSTORAGE& pParentStorage; //�����ָ�룬�Ǿ���һ��copy��Դ�仯����Ӱ������
		//LPSTORAGE pParentStorage = nullptr;
		//StorageNode() {}
		StorageNode(int i,CString nm, LPSTORAGE& p) : idx(i),name(nm), pParentStorage(p){}
		StorageNode(const StorageNode& rhs) : idx(rhs.idx), name(rhs.name), pParentStorage(rhs.pParentStorage) {}
		//StorageNode(StorageNode&& rhs) : idx(rhs.idx), name(rhs.name), pParentStorage(rhs.pParentStorage) {}
		//StorageNode& operator=(StorageNode&& rhs) noexcept {
		//	idx = rhs.idx; name = rhs.name; pParentStorage = rhs.pParentStorage; }
	};
	struct StreamNode {//stream�ڵ�����
		StgCfgEnum em;//Ψһ�ģ�����������������
		CString name;//������
		StgCfg* cfg;//����
		std::vector<StorageNode> vecPos;//����λ����

		StreamNode(StgCfgEnum e, CString nm, StgCfg* _cfg, std::vector<StorageNode>&& vec/*λ����*/)
			: em(e),name(nm),cfg(_cfg), vecPos(vec){}
	};
	//
	std::vector<LPSTORAGE> m_vecStorage; //���е����ô洢���󣬴洢������������ա������ĵ��ṹͼ������

	//���ĵ�
	CSSFile(CString& filename);
	~CSSFile();
	//struct StorageData
	//{
	//	IStorage *Stg = nullptr;
	//	StorageData *ParentStg = nullptr;
	//};

	//��ȡ��������
	bool GetAllCfg();
	//��ȡָ������ ֻ��LPSTREAMû��
	bool GetCfg(StgCfgEnum em, LPSTREAM* pStream);
	//�ĵ��Ƿ��
	bool IsOpen() const;

protected:
	//�򿪸����ĵ�
	bool OpenSSFile(CString & filename, DWORD mode = STGM_READWRITE | STGM_SHARE_EXCLUSIVE);
	//�رո����ĵ�
	//void Close();
	//���������ĵ�
	bool CreateSSFile(const CString & filename, DWORD mode = STGM_READWRITE | STGM_SHARE_EXCLUSIVE);
	//��ȡ��������
	bool ReadAllCfg();
	//�򿪴洢����
	//bool OpenStroage(const CString & name, /*LPSTORAGE pStorage, */DWORD mode = STGM_READWRITE | STGM_SHARE_EXCLUSIVE);
	//����
	//bool OpenStream(const CString & name, LPSTREAM* pStream, DWORD mode = STGM_READWRITE | STGM_SHARE_EXCLUSIVE);
	//�����洢����
	//bool CreateStroage(const CString & name, LPSTORAGE pStorage, DWORD mode = STGM_READWRITE | STGM_SHARE_EXCLUSIVE);
	//������
	//bool CreateStream(const CString & name, LPSTREAM* pStream, DWORD mode = STGM_READWRITE | STGM_SHARE_EXCLUSIVE);

	//��ȡ���洢
	//IStorage * GetRootStorage() const;
	//����Ĭ������
	//bool CreateDefaultCfg();
	//�ͷŴ򿪵Ĵ洢����
	void ReleaseStorage();

private:
	//���Ҹ��ڵ�洢����
	//Node& FindParentNode(std::list<Node>::iterator it/*��ǰ�ڵ�*/, const CString& name/*���ڵ���*/);
	//����̳й�ϵ
	void TransformBase2Derived(StreamNode& node, void*& pv, ULONG& len);


protected:
	bool m_bOpen = false;
	//CString m_strFilename;
	LPSTORAGE m_pRootStg = nullptr;
	//StorageData *m_pCurrentStg = nullptr;
	//std::list<Node> m_liNode;
	std::vector<StreamNode> m_vecStreamNode;
};