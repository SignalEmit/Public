const electron = window.require('electron');
const BrowserWindow = electron.remote.BrowserWindow;
const {log} = require("../log/log.js");
let openDebug = true;
/*
// 本类用于创建页面的ui
*/
class ElectronWindowBase{
    // 构造函数(objetc主要是传入页面参数,js传入的数页面的等待注入的js的参数)
    constructor(object,jsArray = [],close_callback = null){
      this.m_electronWindow = null;
      this.m_webViewMap = {};
      this.close_callback = close_callback;
      this.m_JsArray = jsArray;
      this.init(object);
    }
    // 初始化
    init(object){
      this.initApp(object);
      if( openDebug ){
        this.m_electronWindow.webContents.openDevTools();
      }
    }
    // 初始化app页面
    initApp(object){
      console.log("初始化");
      // 初始化主页面
      this.m_electronWindow = new BrowserWindow(object);
      // 如果dom加载完成则注入js文件

      this.m_electronWindow.webContents.on('did-finish-load',()=>{
        if( this.m_JsArray.length != 0 ){
          for(let i=0;i<this.m_JsArray.length;i++){
            log.System("页面注入js大小："+this.m_JsArray[i].length);
            this.m_electronWindow.webContents.executeJavaScript(this.m_JsArray[i]);
          }
        }
      });

      this.m_electronWindow.on('closed', function () {
        if( this.close_callback != null ){
          // 结束进行
          log.System("程序退出");
          this.close_callback();
        }
      }.bind(this));
      // setTimeout(()=>{
      //   for(let i=0;i<js.length;i++){
      //     log.System("页面注入js大小："+js[i].length);
      //     this.m_electronWindow.webContents.executeJavaScript(js[i]);
      //   }
      // },15000);
    }
    // 打开本地文件
    loadFile(filepath){
      this.m_electronWindow.loadFile(filepath);
    }
    // 打开URL
    loadURL(url){
      this.m_electronWindow.loadURL(url)
    }
    // 返回页面控件
    getWindowWidget(){
      return this.m_electronWindow;
    }
    // 设置内嵌页面
    setBrowserView(strMark,webView,clallback){
      // 如果检测到页面已经装入
      if( this.m_webViewMap[strMark] != null ){
        clallback("此页面已经存在！！！");
      }else{
        this.m_webViewMap[strMark] = webView;
        clallback("页面载入成功！！！");
      }
    }
    // 获取页面上的html
    getHTML(){
      // this.m_electronWindow.webContents.getHTML();
    }
    // executeJavaScript注入单个js
    executeJavaScript(js){
      this.m_electronWindow.webContents.executeJavaScript(js);
      this.m_JsArray.push(js);
    }
  }

  export {
    ElectronWindowBase
  }
