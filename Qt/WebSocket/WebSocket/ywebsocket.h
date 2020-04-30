#pragma once
#include <QObject>
#include <QWebSocket>
#include <QTimer>
#include "Public/Log/log.h"
namespace WebSocket
{
	class YWebSocket : public QObject
	{
		Q_OBJECT
	signals:
		void receiveTextMessage(const QString &id, const QString &message);
		void connectFinish();
	public:
		YWebSocket(
			const QString &id,
			QWebSocket *websocket
		);							// websocket 主要接受 websocketserver
		YWebSocket(
			const QString &id,
			const QString &url
		);
		~YWebSocket();
		inline QString getID();
		QAbstractSocket::SocketState state();
		QWebSocket *getWebSocket();
		bool sendTextMessage(const QString &message);
		bool setID(const QString &strID);
		QString getStatus();
	private:
		bool repeatedlyInit();								// 反复的初始化
		bool repeatedlyDeinit();							// 反初始化
	private:
		QString m_strID;
		QWebSocket *p_WebSocket = nullptr;
		QString m_strUrl;
		QAbstractSocket::SocketState m_status = QAbstractSocket::UnconnectedState;
		// 检测时间状态
		QTimer *p_CheckStatusTimer = nullptr;
	};

}
