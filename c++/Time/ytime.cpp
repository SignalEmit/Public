#include "ytime.h"
namespace Time
{
	YTime::YTime()
	{

	}
	quint64 YTime::getMSecsTimeStamp()
	{
		return currentSecsSinceEpoch();
	}
	YTime::~YTime()
	{

	}
}

