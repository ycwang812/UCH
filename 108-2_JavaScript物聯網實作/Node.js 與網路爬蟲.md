---
breaks: false  # false 表示採用 "軟換行規則"，即 "換行符號" 不會換到新行。
---

# Node.js 與網路爬蟲

###### tags: `課程講義`, `108-2_健行`, `JavaScript物聯網實作`


## Node.js 第一支程式 - Hello world 網站

```javascript=
const http = require('http');

const hostname = '127.0.0.1';
const port = 3000;

const server = http.createServer((req, res) => {
  res.statusCode = 200;
  res.setHeader('Content-Type', 'text/plain');
  res.end('Hello World');
});

server.listen(port, hostname, () => {
  console.log(`Server running at http://${hostname}:${port}/`);
});
```


## 安裝套件

```javascript=
// request：抓取整個網頁的程式碼
npm install request

// cheerio：後端的 jQuery
npm install cheerio
```


## 建立 queryjp.js 檔案，取得台銀牌告網頁資料

```javascript=
var request = require("request");
var cheerio = require("cheerio");

var jp = function() {
  request({
    url: "http://rate.bot.com.tw/Pages/Static/UIP003.zh-TW.htm",
    method: "GET"
  }, function(error, response, body) {
    if (error || !body) {
      return;
    } else {

    // 爬完網頁後要做的事情
    console.log(body);
    }
  });
};

jp();
```


### 取得台銀牌告匯率資料

```javascript=
var request = require("request");
var cheerio = require("cheerio");

var jp = function() {
  request({
    url: "http://rate.bot.com.tw/Pages/Static/UIP003.zh-TW.htm",
    method: "GET"
  }, function(error, response, body) {
    if (error || !body) {
      return;
    } else {

    // 爬完網頁後要做的事情
    var $ = cheerio.load(body);
    var target = $(".rate-content-sight.text-right.print_hide");
    console.log(target);
    }
  });
};

jp();
```


:::info
* target 印出的是一個很嚇人的陣列
* .rate-content-sight.text-right.print_hide 的數量多達 38 個
* 從陣列中看不出日幣在哪裡 (因都隱藏在 children 裡)

![](https://i.imgur.com/LcHTkH4.jpg)
:::


:::info
日幣的位置排在第 16 位，也就是陣列的 15

![](https://i.imgur.com/6Q1RFJt.jpg)
:::


### 取得日幣匯率資料

```javascript=
var request = require("request");
var cheerio = require("cheerio");

var jp = function() {
  request({
    url: "http://rate.bot.com.tw/Pages/Static/UIP003.zh-TW.htm",
    method: "GET"
  }, function(error, response, body) {
    if (error || !body) {
      return;
    } else {

    // 爬完網頁後要做的事情
    var $ = cheerio.load(body);
    var target = $(".rate-content-sight.text-right.print_hide");
    console.log(target[15].children);
    }
  });
};

jp();
```


![](https://i.imgur.com/nc6BgSz.png)


### 精準取得日幣匯率數值

```javascript=
var request = require("request");
var cheerio = require("cheerio");

var jp = function() {
  request({
    url: "http://rate.bot.com.tw/Pages/Static/UIP003.zh-TW.htm",
    method: "GET"
  }, function(error, response, body) {
    if (error || !body) {
      return;
    } else {

    // 爬完網頁後要做的事情
    var $ = cheerio.load(body);
    var target = $(".rate-content-sight.text-right.print_hide");
    console.log(target[15].children[0].data);
    }
  });
};

jp();
```


### 定時取日幣匯率數值

```javascript=
var request = require("request");
var cheerio = require("cheerio");

var jp = function() {
  request({
    url: "http://rate.bot.com.tw/Pages/Static/UIP003.zh-TW.htm",
    method: "GET"
  }, function(error, response, body) {
    if (error || !body) {
      return;
    } else {

    // 爬完網頁後要做的事情
    var $ = cheerio.load(body);
    var target = $(".rate-content-sight.text-right.print_hide");
    console.log(target[15].children[0].data);
    }
  });
};

jp();
setInterval(jp, 10000);
```
