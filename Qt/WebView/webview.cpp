#include "webview.h"
WebView::WebView()
{
	this->page()->settings()->setAttribute(QWebEngineSettings::LocalStorageEnabled, true);
	//this->page()->settings()->setAttribute( QWebEngineSettings::AllowWindowActivationFromJavaScript,true);
	this->page()->settings()->setAttribute(QWebEngineSettings::AllowGeolocationOnInsecureOrigins, true);

	this->page()->settings()->setAttribute(QWebEngineSettings::JavascriptEnabled, true);
	//this->page()->settings()->setAttribute(QWebEngineSettings::JavaEnabled,true);
	this->page()->settings()->setAttribute(QWebEngineSettings::JavascriptCanOpenWindows, true);
	this->page()->settings()->setAttribute(QWebEngineSettings::JavascriptCanAccessClipboard, true);
	//this->page()->settings()->setAttribute(QWebEngineSettings::DeveloperExtrasEnabled,true);
	this->page()->settings()->setAttribute(QWebEngineSettings::LocalContentCanAccessRemoteUrls, true);
	this->page()->settings()->setAttribute(QWebEngineSettings::LocalContentCanAccessFileUrls, true);
	this->page()->settings()->setAttribute(QWebEngineSettings::WebGLEnabled, true);
	this->page()->settings()->setAttribute(QWebEngineSettings::AutoLoadImages, true);
	this->page()->settings()->setAttribute(QWebEngineSettings::PluginsEnabled, false);

	this->page()->profile()->setHttpCacheType(QWebEngineProfile::DiskHttpCache);
	this->page()->profile()->setPersistentCookiesPolicy(QWebEngineProfile::ForcePersistentCookies);

	connect(this, &QWebEngineView::loadFinished, [&](bool ok)
	{
		emit loadFinished_ID(strID, ok);
	});

	timer = new QTimer;
	connect(timer, &QTimer::timeout, [&]()
	{
		mutex.lock();
		while (!m_WaitJsQueue.empty())
		{
			this->page()->runJavaScript(m_WaitJsQueue.front());
			m_WaitJsQueue.pop();
		}
		mutex.unlock();
	});

}

bool  WebView::setID(const QString &id)
{
	strID = id;
	return true;
}

bool  WebView::setJsTimer(const QString &strJS)
{
	mutex.lock();
	m_WaitJsQueue.push(strJS);
	timer->start(20 * 1000);
	mutex.unlock();
	return true;
}
bool  WebView :: setTittle(const QString &strTittle)
{
	this->setWindowTitle(strTittle);
	return true;
}
 WebView::~WebView()
{
	 timer->stop();
	 delete timer;
}
