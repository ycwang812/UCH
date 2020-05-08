var request = require("request");
var cheerio = require("cheerio");

var jp = function() {
  request({
    url: "http://rate.bot.com.tw/Pages/Static/UIP003.zh-TW.htm",
    method: "GET"
  }, function(error, response, body) {
    if (error || !body) {
      return;
    }else{

    // 爬完網頁後要做的事情
    var $ = cheerio.load(body);
    var target = $(".rate-content-sight.text-right.print_hide");
    console.log(target[15].children[0].data);
    }
  });
};

