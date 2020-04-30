#ifndef YTIME_H
#define YTIME_H

#include <QDateTime>
namespace Time
{
	class YTime :QDateTime
	{
	public:
		YTime();
		~YTime();
	public:
		//
		static quint64 getMSecsTimeStamp();
	};
}


#endif // YTIME_H
