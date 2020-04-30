#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include "../../Log/log.h"
#include "../tcpSocket/tcpsocket.h"
#include <map>
#include <QMutex>
#include <QThread>
#include <QSemaphore>
#include <QObject>
#include "Public/Tool/tool.h"
#include "Public/String/string.h"

namespace Tcp
{
	class TcpServer : public QObject
	{
		Q_OBJECT
	signals :
		void receiveTextMessage(
			const QString &name,
			const QString &message
		);
	public:
		TcpServer(
			const QString &modelname,
			const QString &ip,
			const quint16 &port
		);

		~TcpServer();

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
		bool changeTcpSocketName(
			const QString &waitchangeid,
			const QString &changname
		);
		// 获取websocket
		Tcp::TcpSocket *getTcpSocket(const QString &strID);
	protected:
		void run();
	private:
		QMutex m_tcpSocketMapMutex;
		// 时间检测定时器
		QTimer *p_checkSocketState = nullptr;
	private:
		// 监听的套接字
		QTcpServer *p_tcpSocketServer;
		/* QString为websocket的编号 */
		std::map<QString, Tcp::TcpSocket*> m_tcpSocketMap;
		// 设置个监听名称
		QString m_strModelName;
	};
}


#endif // TCPSERVER_H
