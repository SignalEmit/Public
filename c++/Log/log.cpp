#include "log.h"
#include <QDebug>
bool MyLog::bPrintLog = false;
bool MyLog::bSaveLog = false;					//日志开关关闭
QFile MyLog::m_File("Login/log.txt");
quint64 qFileSize = 30 * 1024 * 1024;			// 30M为一个文件夹
MyLog::MyLog( void )
{

}

void MyLog::setPrint( bool open )
{
	bPrintLog = open;
	QDateTime current_time = QDateTime::currentDateTime();
	QString StrCurrentTime = current_time.toString("yyyy年MM月dd日hh时mm分ss秒");
	QString strFileName = QObject::tr("Login/Log/%0.txt").arg(StrCurrentTime);
	m_File.setFileName(strFileName);
	m_File.open(QIODevice::WriteOnly | QIODevice::Text);
	m_File.close();
}

void MyLog::print(const QString &str)
{
    if ( !bPrintLog )
    {
        return;
    }

	/*
    va_list ptr;
    va_start(ptr, pszFmt);
    int size = vsnprintf(NULL, 0, pszFmt, ptr);
    char *pszMsg = new char[ size+20 ];
    vsprintf(pszMsg, pszFmt, ptr);
    va_end(ptr);
	*/

	//qDebug()<<"打";
	if (str == "")
	{
		int i = 10;
		return;
	}
	qDebug()<<"日志："+ QObject::tr("Time [%0]  Data: %1 \n").arg(QDateTime::currentDateTime().toString()).arg(str);
	//std::cout<<pszMsg<<std::endl;
    //printf("%s\n", pszMsg);

	if (m_File.size() >= qFileSize)
	{
		QDateTime current_time = QDateTime::currentDateTime();
		QString StrCurrentTime = current_time.toString("yyyy年MM月dd日hh时mm分ss秒");
		QString strFileName = QObject::tr("Login/Log/%0.txt").arg(StrCurrentTime);
		m_File.setFileName(strFileName);
		m_File.open(QIODevice::WriteOnly | QIODevice::Text);
		m_File.close();
	}

   if (bSaveLog && m_File.open(QIODevice::QIODevice::Append))
   {
	   m_File.write(QString(QObject::tr("Time [%0]  Data: %1 \n").arg(QDateTime::currentDateTime().toString()).arg(str)).toUtf8());
	   m_File.close();
   }
}

bool MyLog::setSaveLogOpen(const bool &state)
{
	bSaveLog = state;
	return true;
}
