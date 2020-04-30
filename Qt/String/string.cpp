#include "string.h"
namespace YString {
String::String()
{

}
// 字符串分隔转换成vector数组类似js中splite
std::vector<std::string> String::splite(const std::string &Str, const std::string &delimiter)
{
    std::string str = Str;
    std::vector<std::string> r;
    while (!str.empty())
    {
        size_t ind = str.find_first_of(delimiter);
        if (ind == -1)
        {
            r.push_back(str);
            str.clear();
        }
        else
        {
            if (0 != ind)
            {
                r.push_back(str.substr(0, ind));

            }
            str = str.substr(ind + delimiter.size(), str.size());
        }
    }
    return r;
}
QString String::numberToString(const double &lfNumber)
{
	return QString::number(lfNumber);
}

std::queue<QString> String::cutting(const QString &str, qint64 size)
{
	QString strMessage = str;
	std::queue<QString> refuer;
	while (strMessage.size() >= size)
	{
		refuer.push(strMessage.mid(0,size));
		strMessage = strMessage.mid(size);
	}
	if (!strMessage.isEmpty())
	{
		refuer.push(strMessage);
	}
	return refuer;
}
}
