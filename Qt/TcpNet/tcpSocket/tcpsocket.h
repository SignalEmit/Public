#ifndef TCPSOCKET_H
#define TCPSOCKET_H
#include <QTcpSocket>
#include <QDataStream>
#include <QByteArray>
#include <QObject>
#include <QDebug>
#include <QHostAddress>
#include <QTimer>
#include "Public/Log/log.h"
# pragma execution_character_set("utf-8")
namespace Tcp
{
	class TcpSocket : public QObject
	{
		Q_OBJECT
	signals :
		// 发送数据
		void receiveTextMessage(
			const QString &name,
			const QString &message
		);
		// 关闭tcp连接
		void deleteTcpSocket(QString id);
		// 套接字连接信号
		void connectFinish();
	public:
		// 本tcpsocket主要接收socketserver过来的数据
		TcpSocket(
			const QString &id,
			QTcpSocket *tcpSocket
		);	
		// 本tcpsocket主要是自己启动
		TcpSocket(
			const QString &id,
			const QString &ip,
			const quint16 &port
		);

		~TcpSocket() {}
		// 发送数据
		qint64 sendTcpMessage(
			const QString &message
		);
		// 设置id
		bool setID(const QString &id);
		// 获取id
		QString getID();
		// 套接字断开连接
		void tcpDisconnect() { p_tcpSocket->disconnectFromHost(); }
		// 获取套接字
		QTcpSocket *getTcpSocket() { return p_tcpSocket; }
		// 获得tcosocket状态
		QString getStatus();
		// 获得状态码
		QAbstractSocket::SocketState state();
		// 获取缓冲区大小
		quint64 getReadBufferSize();
	public slots:
	   // 收到数据
		void receiveTcpMessage();
	private:
		// 反复的初始化
		bool repeatedlyInit();
		// 反初始化
		bool repeatedlyDeinit();
	private:
		// 唯一标识
		QString m_strID;
		// 现在接收的数据大小，接收一次后重置
		quint16 m_blockSize = 0;
		// 套接字
		QTcpSocket *p_tcpSocket = nullptr;
		// ip
		QString m_strIP;
		// 端口
		quint16 m_nPort;
		// 检测时间状态
		QTimer *p_CheckStatusTimer = nullptr;
		// 待接收的message
		QByteArray strMessage;
	};
}
#endif // TCPSOCKET_H
