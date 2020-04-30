#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <QNetworkAccessManager>
#include <QEventLoop>
#include <QNetworkReply>
#include <QTimer>
#include "Public/Log/log.h"

class HttpRequest:public QObject
{
    Q_OBJECT
public:
    HttpRequest();
    ~HttpRequest();
    static QByteArray post(
		QString url,
		QByteArray froms
	);

	static HttpRequest *getHttpRequest();
};

#define YHttpRequest HttpRequest::getHttpRequest()
#endif // HTTPREQUEST_H
