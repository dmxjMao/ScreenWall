#pragma once
#include <vector>
#include "Stg.h"

class CSSFile {
public:
	struct StorageNode {
		int idx = 0;
		CString name;
		LPSTORAGE& pParentStorage; //�����ָ�룬�Ǿ���һ��copy��Դ�仯����Ӱ������
		StorageNode(int i, CString nm, LPSTORAGE& p) : idx(i), name(nm), pParentStorage(p) {}
		StorageNode(const StorageNode& rhs) : idx(rhs.idx), name(rhs.name), pParentStorage(rhs.pParentStorage) {}
	};
	struct StreamNode {//stream�ڵ�����
		StgCfgEnum em;//Ψһ�ģ�����������������
		CString name;//������
		StgCfg* cfg;//����
		std::vector<StorageNode> vecPos;//����λ����

		StreamNode(StgCfgEnum e, CString nm, StgCfg* _cfg, std::vector<StorageNode>&& vec/*λ����*/)
			: em(e), name(nm), cfg(_cfg), vecPos(vec) {}
	};
	//
	std::vector<LPSTORAGE> m_vecStorage; //���е����ô洢���󣬴洢������������ա������ĵ��ṹͼ������

										 //���ĵ�
	CSSFile(CString filename);
	~CSSFile();

	//��ȡ��������
	bool GetAllCfg();
	//��ȡָ������ ֻ��LPSTREAMû��
	bool GetCfg(StgCfgEnum em, LPSTREAM* pStream);
	//�ĵ��Ƿ��
	bool IsOpen() const;

protected:
	//�򿪸����ĵ�
	bool OpenSSFile(CString & filename, DWORD mode = STGM_READWRITE | STGM_SHARE_EXCLUSIVE);
	//���������ĵ�
	bool CreateSSFile(const CString & filename, DWORD mode = STGM_READWRITE | STGM_SHARE_EXCLUSIVE);
	//��ȡ��������
	bool ReadAllCfg();
	//�ͷŴ򿪵Ĵ洢����
	void ReleaseStorage();

protected:
	bool m_bOpen = false;
	LPSTORAGE m_pRootStg = nullptr;
	std::vector<StreamNode> m_vecStreamNode;
};