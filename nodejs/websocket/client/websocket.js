'use strict'
// 引入定时器类
// 引入socket
// const WebSocket = require('ws');
const {Timer} = require("../timer/timer.js");
class YWebSocket{
    // websocket初始化
    constructor(){
        this.websocket = null;
        this.message_callback = null;
        this.connectsucess_callback = null;
        this.url = null;
        this.bHeartBeat = false;
        // 环境变量
        this.environment = null;
        this.timer = new Timer(this,(environment)=>{
            environment.checkHeartBeat();
        });
    }
    // 初始化
    init(string,environment,messagecallback,connectsucesscallback){
        this.message_callback= messagecallback;
        this.connectsucess_callback = connectsucesscallback;
        this.environment = environment;
        this.url  = string;
        this.getWebsocket();
    }
    // 获取websocket实现断开重连机制
    getWebsocket(){
        this.websocket = new WebSocket(this.url);
        // websocket连接成功后
        this.websocket.onopen = (event)=>{
            // 连接建立成功
            console.log("connect sucess!")
            // 建立成功后将生成一个随机的code
            this.connectsucess_callback(this.environment);
            // 定时器启动30s
            this.timer.start(10*1000);
        };
        // websocket断开后
        this.websocket.close = (event)=>{
            console.log("websocketserver close,restart websocket");
            // 断开后尝试重连
            this.getWebsocket();
        };
        // websock有数据过来的时候
        this.websocket.onmessage = (event)=>{
            if( event.data == "heartbeat" ){
                this.bHeartBeat = true;
                return;
            }
            this.bHeartBeat = true;
            this.message_callback(this.environment,event);
        };
        
    }
    // 检查websocket心跳数据是否接收到
    checkHeartBeat(){
        if( this.bHeartBeat){
            // 监测过心跳后将心跳设置为false
            this.bHeartBeat = false;
        }else{
            // 未重置心跳尝试重连
            this.getWebsocket();
        }
    }
    // 发送数据
    send(obj){
        this.websocket.send(JSON.stringify(obj));
    }
}
module.exports = {
    YWebSocket
}