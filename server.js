/*
Weather clock server code
GET request to darksky.net to obtain weather data (JSON format)
POST request to particle.io to pass weather data (string)

Emily Lam, November 2016
*/

// Dependencies
var dotenv = require('dotenv').config();
var timer = setTimeout(myfunc, 2000);
var requestDarkSky = require('request');
var requestParticle = require('request');
var Particle = require('particle-api-js');
var math = require('mathjs');

// URLs
var host = 'https://api.darksky.net/forecast/',
    apiKey = process.env.APIKEY,
    lat = '42.349362',
    lon = '-71.106458',
    exclude = 'daily,hourly,flags,minutely,alerts';
var urlDarkSky = host + apiKey + '/' + lat + ',' + lon + '?exclude=' + exclude;

var host2 = 'https://api.particle.io/v1/devices/',
    deviceID = '350027000b47353235303037',
    func = 'temp',
    accessToken = '5360d735172348bc8b13e1be1f1bd65683c3b943';
var urlParticle = host2 + deviceID + '/' + func + '?access_token=' + accessToken;

// Variables
var currentTemp;
var objDarkSky;
var msg;

// Timer function to request weather data every 10 seconds
function myfunc() {
  requestDarkSky(urlDarkSky, {timeout: 1500}, callbackDarkSky);
  timer = setTimeout(myfunc, 10000);
}

// Callback function to receive, parse, and forward weather data
function callbackDarkSky(error, response, body) {
  if (!error && response.statusCode == 200) {
    objDarkSky = JSON.parse(body);
    if(objDarkSky.currently.hasOwnProperty('temperature')) {
      currentTemp = objDarkSky.currently.temperature;
      msg = JSON.stringify(currentTemp);
      requestParticle(urlParticle, {method: 'POST', json: {mes: msg}}, callbackParticle);
      console.log('Temp:', currentTemp);
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
