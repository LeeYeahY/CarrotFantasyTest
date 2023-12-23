#include"CsvUtil.h"

String1 FileLoadUtil::GetDataLines(const std::string&Src)
{
	String1 DataList;
    //如果用cocos读取的文件不存在
	if (!cocos2d::FileUtils::getInstance()->isFileExist(Src))
		return DataList;//返回一个空的vector
	else {
		size_t Size = 0;

		StringUtil MyStringUtil;

		unsigned char* Datas = cocos2d::FileUtils::getInstance()->getFileData(Src, "r", &Size);//从源文件中以只读方式读取数据

		if (Datas)//如果读取到的数据不为空
			DataList = MyStringUtil.Split((char*)Datas, "\n");//将这一串字符拆解为子串

		return DataList;//返回拆解后的结果
	}
}
String1 StringUtil::Split(const std::string& Src, const std::string& Sep)
{
    String1 StringList;//定义装载拆分后的字符串的向量

    int Size = Src.size();//确定主串长度

    std::string Str(Src);//用原主串初始化一个新的string，该Str用于进行修改操作

    int Start = 0;//起始位置

    int End = 0;//结束位置

    End = Str.find(Sep);//从主串中寻找分隔符第一次出现的位置

    std::string SplitStr = "";//用于存储拆分出的子串

    while (End !=std::string::npos)//当没有寻找到末尾时
    {
        SplitStr = Str.substr(Start, End);//用SplitStr接收从主串中提取到的子串

        StringList.push_back(SplitStr);//将该子串放入输出列表

        Str = std::string(Str.substr(End + 1, Size));//更新Str为删除SplitStr之后的部分

        End = Str.find(Sep);//寻找下一个分隔符的位置
    }

    if (Str != "") //若最后一个提取到的子串不为空
        StringList.push_back(Str);//则将其也放入字符串向量中
    
    return StringList;//返回最终提取到的字符串向量
}
CsvUtil::CsvUtil()//给该Csv的map分配空间
{
	MapPtr = new CsvMap;
}
CsvUtil::~CsvUtil()//安全释放空间
{
	CC_SAFE_DELETE(MapPtr);
}
CsvUtil* CsvUtil::GetInstance()
{
	if (!Instance)//如果当前实例为空
		Instance = new CsvUtil;//则创建新的对象
	return Instance;//返回该实例地址
}
bool CsvUtil::DestructInstance()//销毁实例
{
	if (Instance) {//实例不为空
		CC_SAFE_DELETE(Instance);//释放其占用的空间
		return true;
	}
	return false;
}

void CsvUtil::AddFilePath(std::string& FilePath)
{
	if (FilePath == "")//路径为空
		return;//直接返回
	else {
        FileLoadUtil MyFileLoadUtil;//创建一个读取文件的变量
        auto LinesVec = MyFileLoadUtil.GetDataLines(FilePath);//获取文件拆解后的子串
        String1 StrsVec;
        String2 StrsVecVec;
        StringUtil MyStringUtil;

        for (const auto& CurrentLine : LinesVec)//遍历存储各行子串的vector
        {
            StrsVec = MyStringUtil.Split(CurrentLine.c_str(), ",");//将每一个属性按照，拆解开
            StrsVecVec.push_back(StrsVec);//将拆解后每一行的数据放入新的vector
        }
        MapPtr->insert(std::make_pair(std::string(FilePath), StrsVecVec));//创建新的键对
	}
}
void CsvUtil::ReleaseFile(std::string& FilePath)
{
    MapPtr->erase(FilePath);//释放对应文件所在键对
}

std::tuple<int, int> CsvUtil::GetRowAndCol(const std::string& FileName)
{
    auto Dict = GetFile(FileName);
    int Row = Dict.size();
    int Col = (*(Dict.begin())).size();
    return std::make_tuple(Col, Row - 1);
}
std::string CsvUtil::GetText(const int Row, const int Col, const std::string& FilePath)
{
    const auto Dict = GetFile(FilePath);//获取存储相应路径文件中所有信息的vector
    const auto LineDatas = Dict.at(Row);//读取对应行数的数据，即读取对应编号的实体的信息
    return LineDatas.at(Col);//返回要读取的信息的编号
}

int CsvUtil::GetInt(const int Row, const int Col, const std::string& FilePath)
{
    return atoi(GetText(Row, Col, FilePath).c_str());//将获取到的信息由字符串转换为数据并返回
}
double CsvUtil::GetDouble(const int Row, const int Col, const std::string& FilePath)
{
    return atof(GetText(Row, Col, FilePath).c_str());//获取文件中对应位置的字符串并将其转换为double型变量返回
}

String1 CsvUtil::GetSomeRow(const int Row, const std::string& FileName)
{
    //获取文件的总行列数并从返回的元组中读取第一个元素，即行数
    auto RowNum = std::get<1>(GetRowAndCol(FileName));

    if (Row > RowNum) 
        return String1();//如果要读取的行数大于文件的总行数，则返回一个空向量，避免访问不存在的行数

    return  MapPtr->at(FileName).at(Row);//否则从存储整个Csv文件的vector中获取对应路径的数据，并从数据中读取第Row行的字符串
}
String2& CsvUtil::GetFile(const std::string& FilePath)
{
    return MapPtr->at(FilePath);//读取相应文件路径的数据，并返回一个存储字符串的vector
}
int CsvUtil::FindValueWithLine(const std::string& Value, const int& ValueCol, const std::string& FilePath)
{
    auto RowNum = std::get<1>(GetRowAndCol(FilePath));
    //首先获取对应文件的总行数

    auto Ret = -1;//Ret存储查找结果，-1表示当前还未找到
    std::string FindValue(Value);//用Value初始化一个目标查找变量

    for (int i = 0; i < RowNum; ++i)//从第一行开始查找
    {
        std::string TmpValue = GetText(i, ValueCol, FilePath);//获取对应行数对应位置的值
        if (FindValue == TmpValue)//如果相等
        {
            Ret = i;//则将所在函数赋值给Ret
            break;
        }
    }
    return Ret;//返回所在行数
}
