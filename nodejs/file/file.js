var fs = require("fs");
const { log } = require("../log/log.js");

class File {
    constructor(filepath) {
        this.filepath = filepath;
    }
    // 获取文件全部内容
    getFileData(encoded = "utf-8") {
        return fs.readFileSync(this.filepath, encoded);
    }
}

module.exports = {
    File
}