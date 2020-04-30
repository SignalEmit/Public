const mysql = require("mysql");
const { log } = require("../log/log.js");
class DataBase {
    // 构造函数
    constructor() {
        this.connect = null;
        this.connect_obj = null;
        this.connect_sucess = false;
    }
    // 初始化
    init(object) {
        console.log("数据库初始化");
        this.connect_obj = object;
        this.connectDB();
    }
    connectDB() {

        // trycatch.on('error', (er) => {
        //     log.Info("数据库断线");
        //     setTimeout(()=>{
        //         this.connectDB();
        //     },2000);

        //   }).bind(this);
        //   trycatch.run(() => {
        this.connect = mysql.createConnection(this.connect_obj);
        //  });


        if (this.connect != null) {
            this.connect.connect((error) => {
                if ("connected" == this.connect.state) {
                    log.System("Database Connect success!!! " + JSON.stringify(this.connect_obj));
                } else {
                    this.connect = null;
                    setTimeout(() => {
                        this.connectDB();
                    }, 2000);
                    log.Info("数据库断线重连");
                    return;
                }
            })

            this.connect.on('error', (err) => {
                log.Info('db error:' + err);
                if (err.code === 'PROTOCOL_CONNECTION_LOST') {
                    log.Info('db error执行重连:' + err.message);
                    this.connectDB();
                } else {
                    throw err;
                }
            });
        }


    }
    // 执行sql
    query(sqlstring, params, callback) {
        this.connect.query(sqlstring, params, (error, results, fields) => {
            if (error) {
                log.Info("数据库错误" + error);
                throw error;
            } else {
                // 回调结果
                callback(results);
            }
        })
    }
}

module.exports = {
    DataBase
}