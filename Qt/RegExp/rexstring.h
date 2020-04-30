#ifndef REXSTRING_H
#define REXSTRING_H

#include <QString>
#include <QRegExp>
#include <QList>
#include <QRegularExpression>
class RexString
{
public:
    static QString GetData(int number,const QString &str,const QString &rex,int location = 0);
    static QList<QString> GetDataList(int number,const QString &str,const QString &rex);
    /*解析比赛和比赛名专用*/
    static void GetDataMap(const QString &str,const QString &rex,QMap<QString,QString> &map);
	// 一个字符串在
    static int CountStr(const QString &str,const QString &rex);
	static  QString GetString(const QString &str,const QString &rex,int location);
	// 一个字符串里是否包含另一个字符串
	static bool existString(QString const &str, const QString &rex);
};

#endif // REXSTRING_H
