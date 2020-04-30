class Hex {
  // 传入一个16进制数
  constructor(arg) {
    this.hex = arg;
  }

  // 将16进制数转换为低字节在前 高字节在后
  translateLowHigh() {
    let high = this.hex >> 8;
    let low = this.hex & 0xff00 >> 8;
    return [low, high];
  }

  // 转换为有符号数 低字节在前  高字节在后
  translateSymbolLowHigh() {
    //先将负值转换
    if (this.hex <= 0) {
      this.hex = Math.abs(this.hex) ^ 0xffff;
    }
    return this.translateLowHigh();
  }
}

module.exports = {
  Hex
}
