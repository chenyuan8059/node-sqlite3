#ifndef  _DBSQLITE_H_H
#define  _DBSQLITE_H_H

#include "platform_config.h"
class CSqliteRecordset;
typedef auto_ptr<CSqliteRecordset> CSqliteRecordsetPtr;
class CSqliteConn
{
public:
	CSqliteConn(void);
	~CSqliteConn(void);
	friend class CSqliteRecordset;
public:
	//������Կ
	BOOL EnterKey(const char* lpstrKey);
	//��û�м��ܵ����ݿ�������Կ
	BOOL AddKey(const char* lpstrKey);
	//�����Կ
	BOOL DelKey();
	//�����Կ
	BOOL ChangeKey(const char* lpstrKey);

public:
	BOOL OpenSqlite(LPCTSTR lpszConnectString);	//�������ݿ�
	BOOL CloseSqlite();							//�ر�����
	BOOL Excute(LPCTSTR lpszSql);				//ִ��ɾ�������룬����
	CSqliteRecordsetPtr Query(LPCTSTR lpszSql,BOOL& bRet);	//��ѯ
	BOOL BeginTrans();							//����ʼ
	BOOL RollbackTrans();						//����ع�
	BOOL CommitTrans();							//�����ύ
	TSTRING GetLastError();						//��ȡ������Ϣ
	BOOL IsOpen() const;						//�ж����ݿ��Ƿ�������
	//BOOL IsEncrypt()const;
private:
	sqlite3* m_db;								//���Ӿ��
	TSTRING m_szText;							//������Ϣ
	BOOL m_bConnect;
	//BOOL m_bEncrypt;

private:
	//BOOL DirectStatement(TSTRING statement);		//��������
	//CSqliteRecordset*Statement(TSTRING statement); //��������

};

class CSqliteRecordset
{
public:
	friend class CSqliteConn;
public:
	CSqliteRecordset();
	~CSqliteRecordset();
	CSqliteRecordset(TSTRING statement, sqlite3* db);
public:
	//BOOL Open(CSqliteConn *pSqliteConn,LPCTSTR lpszSql);//��ѯ
	BOOL MoveNext();									//����һ��
	BOOL MoveFirst();									//�Ƶ�����
	BOOL MoveLast();									//�Ƶ�ĩ��
public:
	long GetFieldCount();								//�ֶ���
	long GetRecordCount();								//��¼��

	TSTRING GetFieldName(int nCol);						//�ֶ���
	Sqlite3_XX::VARIANT GetFieldValue(LPCTSTR lpszFieldName);		//�ֶ�ֵ
	Sqlite3_XX::VARIANT GetFieldValue(int nCol);					//�ֶ�ֵ
private:
	sqlite3_stmt* m_stmt;								//��¼�����
	TSTRING m_szText;
	//BOOL Execute();					//��������
};


#endif