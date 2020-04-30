#ifndef WEBVIEW_H
#define WEBVIEW_H

#include <QObject>
#include <QtWebEngineWidgets/QWebEngineView>
#include <QtWebEngineWidgets/QWebEngineSettings>
#include <QtWebEngineWidgets/QWebEngineProfile>
#include <QtWebEngineWidgets/QWebEngineScriptCollection>
#include <QRegExp>
#include <queue>
#include <QMutex>
#include <QTimer>
# pragma execution_character_set("utf-8")

class WebView : public QWebEngineView
{
	Q_OBJECT
signals:
	void loadFinished_ID(const QString &strID,bool ok);
public:
    WebView();
    ~WebView();
public:
	bool setID(const QString &id);
	/* 延时注入*/
	bool setJsTimer(const QString &strJS);
	// 设置标题
	bool setTittle(const QString &strTittle);
	
private:
    QWebEngineView *createWindow(QWebEnginePage::WebWindowType type)
   {
        return this;
    }

public slots:

private:
	QString strID;
	std::queue<QString> m_WaitJsQueue;
	QMutex mutex;
	QTimer *timer = nullptr;
};

#endif // WEBVIEW_H
