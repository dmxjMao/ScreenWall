#pragma once

/*����*/

enum StgCfgEnum {
	StgCfgEnum_LoginUser, //��¼�û�
	//StgCfgEnum_ServerStation,//����վ
	StgCfgEnum_Buff
};





//���û���
struct StgCfg{
	virtual void Read(LPSTREAM) = 0;
	virtual void Write(LPSTREAM) = 0;
};

//��¼�û�
struct StgCfgLoginUser : StgCfg {
	LPTSTR pszUsername = nullptr;//�û���
	int ccUsername = 0;//�û����ַ�����
	LPTSTR pszPswd = nullptr;//����
	int ccPswd = 0;
	bool bRemPswd = false; //��ס����

	virtual void Read(LPSTREAM);
	virtual void Write(LPSTREAM);

};


