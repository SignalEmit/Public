/*******************************************************************************
* 版权所有 (C) 2019
* 
* 文件名称： log.js
* 文件标识： 
* 其它说明： 负责日志模块
* 当前版本： V1.0
* 作    者： 闫晨博
* 完成日期： 2019-09-05
*******************************************************************************/
class Log {
    // 初始化类
    constructor() {
        // 日志打印开关
        this.m_LogPrintOnoff = false;
        // 日志存储开关
        this.m_LogSaveOnoff = false;
        // 日志存储
        this.m_SaveFilePath = null;
    }
    // 设置打印开关
    setOpenPrint(OnOff) {
        this.m_LogPrintOnoff = OnOff;
    }
    // 设置存储开关
    setOpenSave(OnOff) {
        this.m_LogSaveOnoff = OnOff;
    }
    // 系统日志
    System(string) {
        if (this.m_LogPrintOnoff) {
            console.log(string);
        }
    }
    // 日志提示
    Info(string) {
        if (this.m_LogPrintOnoff) {
            console.log(string);
        }
    }
    // 调试日志
    Debug(string) {

    }
    // 警告
    Warring(string) {

    }
    // 错误
    Error(string) {
        if (this.m_LogPrintOnoff) {
            console.log(string);
        }
    }
}

var log = new Log();
console.log("日志类初始化")
module.exports = {
    log
}