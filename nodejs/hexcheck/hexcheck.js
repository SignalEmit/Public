class HexCheck {
  constructor(hexarray) {
    this.hexArray = hexarray;
  }
  // 异或校验
  XOR() {
    let result = 0x00;
    for (let hex of this.hexArray) {
      result ^= hex;
    }
    return result & 0xff;
  }
  // 和校验
  SUM() {
    let result = 0;
    for (let hex of this.hexArray) {
      result += hex;
    }
    return result & 0xff;
  }
}

module.exports = {
  HexCheck
}