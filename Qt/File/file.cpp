#include "file.h"

YFile::YFile( QString filename )
{
    strFileName = filename;
}
void YFile::setFileName( const QString &filename )
{
    strFileName = filename;
}
QString YFile::getFileContent(  bool *success )
{
    QString fileStr;
    QFile file(strFileName);
    if( file.open(QIODevice::ReadOnly) )
    {
        if( success != nullptr )
        {
            *success = true;
        }
        fileStr = file.readAll();
    }
    else
    {
        if( success != nullptr )
        {
            *success = false;
        }
    }
    file.close();

    return fileStr;
}

bool YFile::exists() const
{
	QFile file(strFileName);
	return file.exists();
}

quint64 YFile::getFileSize()
{
	QFile file(strFileName);
	return file.size();
}