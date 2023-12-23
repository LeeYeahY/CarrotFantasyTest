#pragma once

#ifndef _CSV_UTIL_
#define _CSV_UTIL_

#include <vector>
#include <map>
#include <string>

typedef std::vector<std::string>String1;//一维string数组
typedef std::vector<String1>String2;//二维string数组
typedef std::map<std::string, String2> CsvMap;//存储数据的整个Csv文件

class FileLoadUtil {//读取文件的类
public:
	String1 GetDataLines(const std::string& Src);
};
class StringUtil {
public:
	String1 Split(const std::string& Src, const std::string& Sep);
};
class CsvUtil {

public:
	static CsvUtil* GetInstance();//获取实例指针
	static bool DestructInstance();//销毁一个实例

	virtual void AddFilePath(std::string& FilePath);//添加路径
	virtual void ReleaseFile(std::string& FilePath);//删除路径

	virtual std::string GetText(const int Row, const int Col, const std::string& Dst);//读取字符型文件信息
	virtual int GetInt(const int Row, const int Col, const std::string& FilePath);//获取数字型文件内容
	virtual double GetDouble(const int Row, const int Col, const std::string& FilePath);//复制文件内容

	virtual String1 GetSomeRow(const int Row, const std::string& FileName);//读取某几行文件的信息
	virtual std::tuple<int, int> GetRowAndCol(const std::string& FileName);//获取行数和列数
	virtual int FindValueWithLine(const std::string& Value, const int& ValueCol, const std::string& FilePath);

protected:
	virtual String2& GetFile(const std::string& FilePath);//获取文件内容
	~CsvUtil();//析构函数

private:
	CsvUtil();//构造函数
	CsvUtil(const CsvUtil& FilePath) = delete;//根据已有csv构造新的csv
	CsvUtil& operator=(const CsvUtil& FilePath) = delete;//重载赋值运算符

	static CsvUtil* Instance;//指向一个实例的指针
	CsvMap* MapPtr;//指向一个Csv表的指针
};
#endif
