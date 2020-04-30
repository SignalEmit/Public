#ifndef LOG_H
#define LOG_H

#include <stdarg.h>
#include <stdio.h>
#include <iostream>
#include <QString>
#include <QFile>
#include <QDateTime>
# pragma execution_character_set("utf-8")
class MyLog
{
public:
    MyLog(void);
	static bool setSaveLogOpen(const bool &state);
    static void print(const QString &str);
    static void setPrint( bool open );
private:
	static bool bSaveLog;
    static bool bPrintLog;
    static bool bInit;
	static QFile m_File;
};

#define Log(x) MyLog::print(x);

#endif // LOG_H
