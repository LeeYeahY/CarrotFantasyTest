#include"CsvUtil.h"

String1 FileLoadUtil::GetDataLines(const std::string&Src)
{
	String1 DataList;
    //�����cocos��ȡ���ļ�������
	if (!cocos2d::FileUtils::getInstance()->isFileExist(Src))
		return DataList;//����һ���յ�vector
	else {
		size_t Size = 0;

		StringUtil MyStringUtil;

		unsigned char* Datas = cocos2d::FileUtils::getInstance()->getFileData(Src, "r", &Size);//��Դ�ļ�����ֻ����ʽ��ȡ����

		if (Datas)//�����ȡ�������ݲ�Ϊ��
			DataList = MyStringUtil.Split((char*)Datas, "\n");//����һ���ַ����Ϊ�Ӵ�

		return DataList;//���ز���Ľ��
	}
}
String1 StringUtil::Split(const std::string& Src, const std::string& Sep)
{
    String1 StringList;//����װ�ز�ֺ���ַ���������

    int Size = Src.size();//ȷ����������

    std::string Str(Src);//��ԭ������ʼ��һ���µ�string����Str���ڽ����޸Ĳ���

    int Start = 0;//��ʼλ��

    int End = 0;//����λ��

    End = Str.find(Sep);//��������Ѱ�ҷָ�����һ�γ��ֵ�λ��

    std::string SplitStr = "";//���ڴ洢��ֳ����Ӵ�

    while (End !=std::string::npos)//��û��Ѱ�ҵ�ĩβʱ
    {
        SplitStr = Str.substr(Start, End);//��SplitStr���մ���������ȡ�����Ӵ�

        StringList.push_back(SplitStr);//�����Ӵ���������б�

        Str = std::string(Str.substr(End + 1, Size));//����StrΪɾ��SplitStr֮��Ĳ���

        End = Str.find(Sep);//Ѱ����һ���ָ�����λ��
    }

    if (Str != "") //�����һ����ȡ�����Ӵ���Ϊ��
        StringList.push_back(Str);//����Ҳ�����ַ���������
    
    return StringList;//����������ȡ�����ַ�������
}
CsvUtil::CsvUtil()//����Csv��map����ռ�
{
	MapPtr = new CsvMap;
}
CsvUtil::~CsvUtil()//��ȫ�ͷſռ�
{
	CC_SAFE_DELETE(MapPtr);
}
CsvUtil* CsvUtil::GetInstance()
{
	if (!Instance)//�����ǰʵ��Ϊ��
		Instance = new CsvUtil;//�򴴽��µĶ���
	return Instance;//���ظ�ʵ����ַ
}
bool CsvUtil::DestructInstance()//����ʵ��
{
	if (Instance) {//ʵ����Ϊ��
		CC_SAFE_DELETE(Instance);//�ͷ���ռ�õĿռ�
		return true;
	}
	return false;
}

void CsvUtil::AddFilePath(std::string& FilePath)
{
	if (FilePath == "")//·��Ϊ��
		return;//ֱ�ӷ���
	else {
        FileLoadUtil MyFileLoadUtil;//����һ����ȡ�ļ��ı���
        auto LinesVec = MyFileLoadUtil.GetDataLines(FilePath);//��ȡ�ļ�������Ӵ�
        String1 StrsVec;
        String2 StrsVecVec;
        StringUtil MyStringUtil;

        for (const auto& CurrentLine : LinesVec)//�����洢�����Ӵ���vector
        {
            StrsVec = MyStringUtil.Split(CurrentLine.c_str(), ",");//��ÿһ�����԰��գ���⿪
            StrsVecVec.push_back(StrsVec);//������ÿһ�е����ݷ����µ�vector
        }
        MapPtr->insert(std::make_pair(std::string(FilePath), StrsVecVec));//�����µļ���
	}
}
void CsvUtil::ReleaseFile(std::string& FilePath)
{
    MapPtr->erase(FilePath);//�ͷŶ�Ӧ�ļ����ڼ���
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
    const auto Dict = GetFile(FilePath);//��ȡ�洢��Ӧ·���ļ���������Ϣ��vector
    const auto LineDatas = Dict.at(Row);//��ȡ��Ӧ���������ݣ�����ȡ��Ӧ��ŵ�ʵ�����Ϣ
    return LineDatas.at(Col);//����Ҫ��ȡ����Ϣ�ı��
}

int CsvUtil::GetInt(const int Row, const int Col, const std::string& FilePath)
{
    return atoi(GetText(Row, Col, FilePath).c_str());//����ȡ������Ϣ���ַ���ת��Ϊ���ݲ�����
}
double CsvUtil::GetDouble(const int Row, const int Col, const std::string& FilePath)
{
    return atof(GetText(Row, Col, FilePath).c_str());//��ȡ�ļ��ж�Ӧλ�õ��ַ���������ת��Ϊdouble�ͱ�������
}

String1 CsvUtil::GetSomeRow(const int Row, const std::string& FileName)
{
    //��ȡ�ļ��������������ӷ��ص�Ԫ���ж�ȡ��һ��Ԫ�أ�������
    auto RowNum = std::get<1>(GetRowAndCol(FileName));

    if (Row > RowNum) 
        return String1();//���Ҫ��ȡ�����������ļ������������򷵻�һ����������������ʲ����ڵ�����

    return  MapPtr->at(FileName).at(Row);//����Ӵ洢����Csv�ļ���vector�л�ȡ��Ӧ·�������ݣ����������ж�ȡ��Row�е��ַ���
}
String2& CsvUtil::GetFile(const std::string& FilePath)
{
    return MapPtr->at(FilePath);//��ȡ��Ӧ�ļ�·�������ݣ�������һ���洢�ַ�����vector
}
int CsvUtil::FindValueWithLine(const std::string& Value, const int& ValueCol, const std::string& FilePath)
{
    auto RowNum = std::get<1>(GetRowAndCol(FilePath));
    //���Ȼ�ȡ��Ӧ�ļ���������

    auto Ret = -1;//Ret�洢���ҽ����-1��ʾ��ǰ��δ�ҵ�
    std::string FindValue(Value);//��Value��ʼ��һ��Ŀ����ұ���

    for (int i = 0; i < RowNum; ++i)//�ӵ�һ�п�ʼ����
    {
        std::string TmpValue = GetText(i, ValueCol, FilePath);//��ȡ��Ӧ������Ӧλ�õ�ֵ
        if (FindValue == TmpValue)//������
        {
            Ret = i;//�����ں�����ֵ��Ret
            break;
        }
    }
    return Ret;//������������
}
