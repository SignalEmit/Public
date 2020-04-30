class UserType
{
    constructor( ws,status ){
        this.ws = ws;
        this.status = status;
    }
    // 获取websocket
    getWebsocket(){
        return this.ws;
    }
    // 获取状态
    getLoginStatus(){
        return this.status;
    }
    // 设置状态
    setLoginStatus(status){
        this.status = status;
    }
}

module.exports = {
    UserType
}