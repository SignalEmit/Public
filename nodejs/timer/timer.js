class Timer{
    // 初始化
    constructor(environment,callback){
        this.timer = null;
        this.callback = callback;
        // 环境变量
        this.environment = environment;
    }
    // 定时器启动(毫秒级)
    start(time){
        // 先停止，在启动防止重复启动定时器
        this.stop();
        this.timer = setInterval(()=>{
            this.callback(this.environment);
        },time);
    }
    // 定时器清除
    stop(){
        if( this.timer == null ){
            return;
        }else{
            clearInterval(this.timer);
            this.timer = null;
        }
    }
}

export {
    Timer
}