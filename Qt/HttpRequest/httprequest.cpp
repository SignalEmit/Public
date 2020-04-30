#include "httprequest.h"

HttpRequest::HttpRequest()
{
	
}

HttpRequest::~HttpRequest()
{

}

QByteArray HttpRequest::post(QString url,QByteArray froms)
{
	QNetworkAccessManager manager;
	QNetworkRequest request;
	QByteArray line;
	QEventLoop eventLoop;
	request.setUrl(QUrl(url));
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
	request.setRawHeader(QByteArray("Accept"), QByteArray("application/json, text/javascript, */*; q=0.01"));
	request.setRawHeader(QByteArray("User-Agent"), QByteArray("Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/65.0.3325.146 Safari/537.36"));

	request.setRawHeader(QByteArray("Connection"), QByteArray("keep-alive"));
	request.setRawHeader(QByteArray("X-Requested-With"), QByteArray("XMLHttpRequest"));
	request.setRawHeader(QByteArray("Referer"), QByteArray("https://live.dszuqiu.com/"));
	QByteArray append(froms);
	QNetworkReply* reply = manager.post(request, append);
	QTimer timer;
	connect(&manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
	connect(&timer, SIGNAL(timeout()), &eventLoop, SLOT(quit()));
	timer.start(5000);
	eventLoop.exec();
	line = reply->readAll();
	return line;
}

HttpRequest *HttpRequest::getHttpRequest()
{
	static HttpRequest httpRequest;
	return &httpRequest;
}
