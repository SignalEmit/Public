class YDate {
  constructor() {
    this.date = new Date();
  }

  getYear() {
    return this.date.getFullYear();
  }

  getMonth() {
    return this.date.getMonth() + 1;
  }

  getWeek() {
    return this.date.getDay();
  }

  getDay() {
    return this.date.getDate();
  }

  getHour() {
    return this.date.getHours();
  }

  getMinutes() {
    return this.date.getMinutes()
  }

  getSeconds() {
    return this.date.getSeconds();
  }

}

module.exports = {
  YDate
}