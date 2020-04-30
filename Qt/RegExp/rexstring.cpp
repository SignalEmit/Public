#include "rexstring.h"
QString RexString::GetData(int number,const QString &str,const QString &rex,int location)
{
    QString data;
    QRegExp rx_first(rex);
    rx_first.setMinimal(true);
    int pos_first(0);
    int i =0;
    while ((pos_first = rx_first.indexIn(str, pos_first)) != -1 && i<number)
    {
        data = rx_first.capturedTexts().at(location);
        pos_first += rx_first.matchedLength();
        i++;
    }
    return data;
}

int RexString::CountStr(const QString &str,const QString &rex)
{
    int i = 0;
    QRegExp rx_first(rex);
    rx_first.setMinimal(true);
    int pos_first(0);
    while ((pos_first = rx_first.indexIn(str, pos_first)) != -1)
    {
        i++;
        pos_first += rx_first.matchedLength();
    }
    return i;
}

void RexString::GetDataMap(const QString &str,const QString &rex,QMap<QString,QString> &map)
{
    QRegExp rx_first(rex);
    rx_first.setMinimal(true);
    int pos_first(0);
    while ((pos_first = rx_first.indexIn(str, pos_first)) != -1)
    {
        //map[rx_first.capturedTexts().at(1)] = QString(rx_first.capturedTexts().at(2)).remove(QRegExp("\\s"));
       //pos_first += rx_first.matchedLength();
    }
}
QList<QString> RexString::GetDataList(int number,const QString &str,const QString &rex)
{
    QList<QString> data;
    QRegExp rx_first(rex);
    rx_first.setMinimal(true);
    int pos_first(0);
    while ((pos_first = rx_first.indexIn(str, pos_first)) != -1)
    {
        data.push_back(rx_first.capturedTexts().at(number));
        pos_first += rx_first.matchedLength();
    }
    return data;
}


QString RexString::GetString(const QString &str,const QString &rex,int location)
{
    QString data;
    QRegExp rx_first(rex);
    rx_first.setMinimal(true);
    int pos_first(0);

    while ((pos_first = rx_first.indexIn(str, pos_first)) != -1 )
    {
        data = rx_first.capturedTexts().at(location);
        pos_first += rx_first.matchedLength();

    }
    return data;
}


bool RexString::existString(QString const &str, const QString &rex)
{
	QRegularExpression regularExpression(rex);
	int index = 0;
	QRegularExpressionMatch match;
	do {
		match = regularExpression.match(str, index);
		if (match.hasMatch())
		{
			index = match.capturedEnd();
			return true;
		}
		else
		{
			break;
		}
	} while (index < str.length());
	return false;
}
