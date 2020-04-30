#ifndef FILE_H
#define FILE_H

#include <QFile>
#include "../Log/log.h"
#include <QDebug>
class YFile
{
public:
    YFile( QString filename = " " );
    void setFileName( const QString &filename );
    QString getFileContent( bool *success = false );
	bool exists() const;
	quint64 getFileSize();
private:
    QString strFileName;
};

#endif // FILE_H
