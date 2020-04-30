#pragma once
#include <QObject>
#include <QImage>
#include <QByteArray>
#include <QBuffer>
#include <QPixmap>
#include "Public/HttpRequest/httprequest.h"
#include "Public/Log/log.h"
namespace Ocr
{
	class BaiduOcr : public QObject
	{
		Q_OBJECT
	signals:
		void recognitionFinish(const QString &json);
	public:
		BaiduOcr();

		BaiduOcr(
			const QString &url
		);

        bool setUrl(const QString &url);

       
		~BaiduOcr();
		// 开始识别
        bool start(const QString &strBase64);
	private:
		bool base64ToImage(
			const QByteArray &bytearraye
		);
	private:
		// 保存的文件路径
		QString m_strDir;
		// 文件名
		QString m_strFileName;
		// 识别的Base64
		QString m_strBase64;
		// 识别的Thkon
		QString m_strThkon;
		// url
		QString m_strUrl;
	};
}

