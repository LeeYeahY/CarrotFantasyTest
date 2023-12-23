#pragma once

#ifndef _CSV_UTIL_
#define _CSV_UTIL_

#include <vector>
#include <map>
#include <string>

typedef std::vector<std::string>String1;//һάstring����
typedef std::vector<String1>String2;//��άstring����
typedef std::map<std::string, String2> CsvMap;//�洢���ݵ�����Csv�ļ�

class FileLoadUtil {//��ȡ�ļ�����
public:
	String1 GetDataLines(const std::string& Src);
};
class StringUtil {
public:
	String1 Split(const std::string& Src, const std::string& Sep);
};
class CsvUtil {

public:
	static CsvUtil* GetInstance();//��ȡʵ��ָ��
	static bool DestructInstance();//����һ��ʵ��

	virtual void AddFilePath(std::string& FilePath);//���·��
	virtual void ReleaseFile(std::string& FilePath);//ɾ��·��

	virtual std::string GetText(const int Row, const int Col, const std::string& Dst);//��ȡ�ַ����ļ���Ϣ
	virtual int GetInt(const int Row, const int Col, const std::string& FilePath);//��ȡ�������ļ�����
	virtual double GetDouble(const int Row, const int Col, const std::string& FilePath);//�����ļ�����

	virtual String1 GetSomeRow(const int Row, const std::string& FileName);//��ȡĳ�����ļ�����Ϣ
	virtual std::tuple<int, int> GetRowAndCol(const std::string& FileName);//��ȡ����������
	virtual int FindValueWithLine(const std::string& Value, const int& ValueCol, const std::string& FilePath);

protected:
	virtual String2& GetFile(const std::string& FilePath);//��ȡ�ļ�����
	~CsvUtil();//��������

private:
	CsvUtil();//���캯��
	CsvUtil(const CsvUtil& FilePath) = delete;//��������csv�����µ�csv
	CsvUtil& operator=(const CsvUtil& FilePath) = delete;//���ظ�ֵ�����

	static CsvUtil* Instance;//ָ��һ��ʵ����ָ��
	CsvMap* MapPtr;//ָ��һ��Csv���ָ��
};
#endif
