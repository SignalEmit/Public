#pragma once
#include <QWebSocketServer>
#include <QWebSocket>
#include <map>
#include <QMutex>
#include <QThread>
#include <QSemaphore>
#include <QObject>
#include "Public/Tool/tool.h"
#include "Public/WebSocket/WebSocket/ywebsocket.h"
#include "Public/String/string.h"

namespace WebSocketServer
{

	class YWebSocketServer : public QThread
	{
		Q_OBJECT


	signals :
		void receiveTextMessage(
			const QString &name, 
			const QString &message
		);
	public:
		YWebSocketServer(
			const QString &modelname, 
			const QString &ip, 
			const quint16 &port
		);
		~YWebSocketServer();
		// 发送数据
		bool sendTextMessage(
			const QString &name,
			const QString &message
		);
		// 向所有的websocket发送消息
		bool sendTextToAll(
			const QString &message
		);
		// 改变socket的名字 ,waitchangeid待改变的id   changname改变后的id
		bool changeWebSocketName(
			const QString &waitchangeid, 
			const QString &changname
		);
		// 获取websocket
		WebSocket::YWebSocket *getWebSocket(const QString &strID);
	protected:
		void run();
	private:
		QMutex m_WebSocketMapMutex;
		// 线程同步信号量
		QSemaphore p_threadsemaphore;
	private:
		QWebSocketServer *p_WebSocketServer;
		/* QString为websocket的编号 */
		std::map<QString, WebSocket::YWebSocket*> m_WebSocketMap;
		QString m_strModelName;
	};

}
