/*
Weather clock server code
GET request to darksky.net to obtain weather data (JSON format)
POST request to particle.io to pass weather data (string)

Emily Lam, November 2016
*/

// Dependencies/Initializations
var dotenv = require('dotenv').config();
var timer = setTimeout(myfunc, 2000);
var requestDarkSky = require('request');
var requestParticle = require('request');
var Particle = require('particle-api-js');
var math = require('mathjs');

// Construct URLs
var host = 'https://api.darksky.net/forecast/',
    apiKey = process.env.APIKEY,
    lat = process.env.LAT,
    lon = process.env.LONG,
    exclude = 'daily,hourly,flags,minutely,alerts';
var urlDarkSky = host + apiKey + '/' + lat + ',' + lon + '?exclude=' + exclude;

var host2 = 'https://api.particle.io/v1/devices/',
    deviceID = process.env.DEVICEID,
    func1 = 'temp',
    func2 = 'icon',
    accessToken = process.env.ACCESSTOKEN;
var urlParticle1 = host2 + deviceID + '/' + func1 + '?access_token=' + accessToken;
var urlParticle2 = host2 + deviceID + '/' + func2 + '?access_token=' + accessToken;

// Variables
var currentTemp;
var currentIcon;
var objDarkSky;
var msg;

// Timer function to request weather data every 2 minute
function myfunc() {
  requestDarkSky(urlDarkSky, {timeout: 1500}, callbackDarkSky);
  timer = setTimeout(myfunc, 120000);
}

// Callback function to receive, parse, and forward weather data
function callbackDarkSky(error, response, body) {
  if (!error && response.statusCode == 200) {
    objDarkSky = JSON.parse(body);
    if(objDarkSky.currently.hasOwnProperty('temperature')) {
      currentTemp = objDarkSky.currently.temperature;
      msg = JSON.stringify(currentTemp);
      requestParticle(urlParticle1, {method: 'POST', json: {mes: msg}}, callbackParticle);
      console.log('Temp:', currentTemp);
    }
    if(objDarkSky.currently.hasOwnProperty('icon')) {
      currentIcon = objDarkSky.currently.icon;
      msg = JSON.stringify(currentIcon);
      requestParticle(urlParticle2, {method: 'POST', json: {mes: msg}}, callbackParticle);
      console.log('Icon:', currentIcon);
    }
  }
  else {
    console.log(error);
  }
}

// Callback function to print error if post to Particle Cloud fails
function callbackParticle(error, response, body) {
  if (error) {
    console.log(error);
  }
}
