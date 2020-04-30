#ifndef TOOL_H
#define TOOL_H
#include <QDateTime>
#include <QtGlobal>
const quint64 CMaxRand = 60000;
namespace Tool
{
    class Tools
    {
    public:
        static QString getID()
        {
            qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
            return QString::number( QDateTime::currentSecsSinceEpoch() ) + QString::number( qrand()%CMaxRand );
        }
    };
}
#endif // TOOL_H
