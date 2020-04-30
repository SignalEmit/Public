#include "yocr.h"
namespace Ocr
{
	BaiduOcr::BaiduOcr(
		const QString &url
    ): m_strUrl(url)
	{

	}

	BaiduOcr::BaiduOcr()
	{

	}

	
    bool BaiduOcr::start(const QString &strBase64)
	{
        //Log("URL:"+m_strUrl+" base64"+ strBase64);
        QString strJson = YHttpRequest->post(m_strUrl, QString("image=" + strBase64.toUtf8().toPercentEncoding()).toUtf8());
		Log(tr("收到的识别js[%0]").arg(strJson));
		emit recognitionFinish(strJson);
		return true;
	}

	bool BaiduOcr::base64ToImage(const QByteArray &bytearraye)
	{
		QByteArray Ret_bytearray;
		Ret_bytearray = QByteArray::fromBase64(bytearraye);
		QBuffer buffer(&Ret_bytearray);
		buffer.open(QIODevice::WriteOnly);
		QPixmap imageresult;
		imageresult.loadFromData(Ret_bytearray);
		Log("BaiduOcr::base64ToImage 文件保存！！！");
		if (imageresult.save("123.png"))
		{
			Log("BaiduOcr::base64ToImage 文件保存成功！！！");
		}
		return true;
	}

    bool BaiduOcr::setUrl(const QString &url)
    {
        m_strUrl = url;
        return true;
    }


	BaiduOcr::~BaiduOcr() 
	{

	}
}

