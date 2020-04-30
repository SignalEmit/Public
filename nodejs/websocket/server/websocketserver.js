var websocketserver = require("ws");
const WebSocket = require('ws');
const { log } = require("../../log/log.js");
const { UserType } = require("./type/type.js");
class WebSocketServer {
    // 初始化类
    constructor(){
        this.m_websocketserver = null;
        // key：用户名 value：UserType 详情参见定义
        this.m_websocketArray = {};
        // 环境变量
        this.environment = null;
    }
    // 监听类
    listen(environment,port,callback){
        this.environment = environment;
        log.System("listen websocketserver port:"+port);
        this.m_websocketserver = new websocketserver.Server({port:port});
        this.m_websocketserver.on("connection",(ws)=>{
            // 连接成功后接收消息
            ws.on("message",(message)=>{
                log.Info("reciveMessage:"+message);
                // 将环境变量透上去
                callback(this.environment,ws,message);
            });
            // websocket关闭
            ws.on("close",(event)=>{
                
            });
        });
        // 3s检查一次所有连接的状态,并下发一次心跳
        setInterval(() => {
            for(let key in this.m_websocketArray){
                // 如果这个节点已经断开连接
                if( this.m_websocketArray[key].getWebsocket().readyState == WebSocket.CLOSED ){
                    // 如果断开
                    log.Info("close with websocket key:"+key);
                    delete this.m_websocketArray[key];
                }else{
                    // 向客户端发送心跳
                    this.m_websocketArray[key].getWebsocket().send("heartbeat");
                }
            }
        }, 3000);
    }
    // 代替访客的名称
    replaceSocket(oldname,newname,websocket){
        if( null == this.m_websocketArray[oldname] ){
            log.Info("add new name:"+newname);
            this.m_websocketArray[newname] = new UserType(websocket,false);
        }else{
            delete this.m_websocketArray[oldname];
            this.m_websocketArray[newname] = new UserType(websocket,true);
            log.Info("replace username ["+oldname+"] is ["+newname+"].");
        }
    }
    // 在管理中新增用户的websocket(这个只是加入访客名字)
    addWebSocket(name,websocket){
        // 若果这个连接不存在
        if( null == this.m_websocketArray[name] ){
            log.Info("add new name:"+name);
            this.m_websocketArray[name] = new UserType(websocket,false);
        }else{
            // 如果存在相当于异地登录则提示异地登录
            this.m_websocketArray[name].getWebsocket().send("异地登录");
            websocket.close();
            // 将这个节点重数组里删除
            delete this.m_websocketArray[name];
            // close后将之前存储的对象覆盖掉 这段代码还需要调试一下
            this.m_websocketArray[name] = new UserType(websocket,true);
        } 
    }
    // 向某个用户发送数据
    sendMessageToUser(name,status,statusDesc,type,data){
        if(!this.checkWebSocketStatus(name)){
            log.Warring("用户:"+name+" 数据:type["+type+"] data:["+data+"]发送失败,用户已断线");
            return;
        }
        if( this.m_websocketArray[name] == null ){
            log.Info("useraccount not find.");
        }else{
            let obj = {
                "status":status,
                "info":statusDesc,
                "type":type,
                "data":data
            };
            this.m_websocketArray[name].getWebsocket().send(JSON.stringify(obj));
        }
    }
    // 向某个websocket套接字直接发消息
    sendMessageToWs(ws,status,statusDesc,type,data){
        if(ws.readyState == WebSocket.CLOSED){
            return;
        }
        if( ws == null ){
            log.Info("套接字报错");
        }else{
            let obj = {
                "status":status,
                "info":statusDesc,
                "type":type,
                "data":data
            };
            ws.send(JSON.stringify(obj));
        }
    }
    // 向所有的用户
    sendMessageToAllUser(status,statusDesc,type,data){
        for(let key in this.m_websocketArray){
            if(!this.checkWebSocketStatus(key)){
                continue;
            }
            let obj = {
                "status":status,
                "info":statusDesc,
                "type":type,
                "data":data
            };
            this.m_websocketArray[key].getWebsocket().send(JSON.stringify(obj));
        }
    }
    // 检查websocket的状态(如果连接断开则将websocket从map中直接删除)
    checkWebSocketStatus(name){
        // 如果这个节点已经断开连接
        if( this.m_websocketArray[name].getWebsocket().readyState == WebSocket.CLOSED ){
            // 如果断开
            log.Info("close with websocket key:"+name);
            delete this.m_websocketArray[name];
            return false;
        }
        return true;
    }
}

module.exports = {
    WebSocketServer
}