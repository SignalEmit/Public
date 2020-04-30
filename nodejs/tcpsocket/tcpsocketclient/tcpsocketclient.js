var net = require("net");
const { log } = require("../../log/log");
class TcpSocket {
  constructor(ip, port, connect_callback, recv_callback) {
    this.ip = ip;
    this.port = port;
    this.connectTimer = null;
    this.tcpsocket = null;
    this.connectState = false;
    this.connect_callback = connect_callback;
    this.recv_callback = recv_callback;
  }
  // 开始通讯
  start() {
    this.connect();
    this.connectTimer = setInterval(() => {
      if (!this.connectState) {
        log.Info("尝试连接服务器:[ip:" + this.ip + " ] [port:" + this.port + "]");
        this.connect();
      }
    }, 2000)
  }
  // 连接到指定的ip端口
  connect() {
    try {
      this.tcpsocket = new net.Socket();
      this.tcpsocket.connect(this.port, this.ip);
      this.tcpsocket.on("connect", () => {
        this.connectState = true;
        if (this.connect_callback != null) {
          this.connect_callback(true);
        }
      });
      this.tcpsocket.on("data", (data) => {
        if (null != this.recv_callback) {
          this.recv_callback(data);
        }
      });
      this.tcpsocket.on("close", () => {
        this.connectState = false;
        this.tcpsocket = null;
        if (this.connect_callback != null) {
          this.connect_callback(false);
        }
      });
      this.tcpsocket.on("error", (error) => {
        log.Error("[ip:" + this.ip + " ] [port:" + this.port + "]发生错误:" + error);
      })
    } catch (error) {
      this.Info(error);
    }
  }

  // 发送数据英语
  sendData(data) {
    this.tcpsocket.write(data);
  }

  // 关闭socket
  colse() {
    clearInterval(this.connectTimer);
    if (this.connectState) {
      this.tcpsocket.destroy();
    }
    this.connectState = false;
    this.tcpsocket = null;
  }

}


module.exports = {
  TcpSocket
}
