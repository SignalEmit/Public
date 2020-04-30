#ifndef JSON_H
#define JSON_H

#include "radisjson/document.h"
#include <QString>
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

#define GETSTRING(x)	QString::fromStdString(x.GetString())
#define GETINT(x)		x.GetInt()
#define GETBOOL(x)		x.GetBool()
#define GETDOUBLE(x)	x.GetDouble()
#define GETFLOAT(x)		x.GetFloat()
#define GetLONG(x)		x.GetLONG()

#define RADIS_START_PARSER_JSON(x,y)\
rapidjson::Document x;\
x.Parse(y);\
if (!x.HasParseError())\
{\

#define RADIS_END_PARSER_JSON(x)\
}\
else\
{\
	Log(tr("Json 解析错误 位置[%0]").arg(x));\
}\

// json对象转
#define JSONTOQSTRING(x)\
	QString(QJsonDocument(x).toJson())

#endif // JSON_H
