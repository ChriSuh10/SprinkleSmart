var minTemp = $("#minTemp");
var maxHum = $("#maxHum");
var currTemp = $("#currT");
var currHum = $("#currH");
var btn = $("#btn");

$(document).ready(function() {

  
});

function onClick() {
    $.getJSON("https://api.particle.io/v1/devices/2f0028000747343337373738/humidity?access_token=f6dfdf2f289013dd18a0ed27cfb35c80b723357a", function(json) {
      maxHum.html(json.result);
    });
    
    $.getJSON("https://api.particle.io/v1/devices/2f0028000747343337373738/temperature?access_token=f6dfdf2f289013dd18a0ed27cfb35c80b723357a", function(json) {
      minTemp.html(ktoF(json.result));
    });
    
      $.getJSON("https://api.particle.io/v1/devices/2f0028000747343337373738/c_temp?access_token=f6dfdf2f289013dd18a0ed27cfb35c80b723357a", function(json) {
      currTemp.html("Current Temperature: " + ktoF(json.result));
    });
    
    $.getJSON("https://api.particle.io/v1/devices/2f0028000747343337373738/c_hum?access_token=f6dfdf2f289013dd18a0ed27cfb35c80b723357a", function(json) {
      currHum.html("Current Humidity: " + json.result);
    });

}

function ktoF(f) {
  return Math.round((f * 9.0/5) - 459.67);
}