var parseString = require('xml2js').parseString;

class XML2js {
  constructor(encoding) {
    this.jsonBuilder = new xml2js.Builder({
      rootName: 'bean',
      xmldec: {
        version: '1.0',
        'encoding': encoding,
        'standalone': false
      }
    });

    this.xmlParser = new xml2js.Parser({ explicitArray: false, ignoreAttrs: true });
  }
  // 加载文件
  load(filepath) {

  }
  // 解析string
  setDoc(strXML, resultcallback) {
    parseString(strXML, function (err, result) {
      resultcallback(err, result);
    });
  }
}

module.exports = {
  XML2js
}
