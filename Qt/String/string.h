#ifndef STRING_H
#define STRING_H
#include <string>
#include <vector>
#include <QString>
#include <queue>
namespace YString 
{
	class String
	{
	public:
		String();
		static std::vector<std::string> splite(const std::string &Str, const std::string &delimiter);
		static QString numberToString(const double &lfNumber);
		// 将字符串分割成小块
		static std::queue<QString> cutting(const QString &str,qint64 size);
	};
}

#define NUMBERTOSTRING(x) YString::String::numberToString(x)
#endif // STRING_H

