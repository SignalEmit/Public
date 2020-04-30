/*******************************************************************************
* 版权所有 (C) 2019
* 
* 文件名称： windowsView.js
* 文件标识： 
* 其它说明： 内嵌页面
* 当前版本： V1.0
* 作    者： 闫晨博
* 完成日期： 2019-08-28
*******************************************************************************/
'use strict'
const electron = window.require('electron');
const BrowserView = electron.remote.BrowserView;
class BrowserViewBase{
    // 构造函数
    constructor(object){
        this.m_electronView = null;
        this.initApp(object);
    }
    // 初始化
    init(object){
        this.initApp(object);
        this.initIPC();
    }
    // 初始化app页面
    initApp(object){
    // 初始化主页面
        this.m_electronView = new BrowserView(object);
    }
    //初始化与外部通信(基类中不实现)
    initIPC(){
        
    }
    // 打开本地文件
    loadFile(filepath){
        this.m_electronView.webContents.loadFile(filepath);
    }
    // 打开URL
    loadURL(url){
        this.m_electronView.webContents.loadURL(url)
    }
    // 返回页面空间
    getView(){
        return this.m_electronView;
    }
}

module.exports = {
    BrowserViewBase
}
// let view = new BrowserView()
// m_mainWidget.m_electronView.setBrowserView(view)
// view.setBounds({ x: 0, y: 0, width: 300, height: 300 })
// view.webContents.loadURL('https://www.baidu.com')