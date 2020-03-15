const Alexa = require('alexa-sdk');
const AWS = require('aws-sdk');

//parameters for calling different functions
var pHostname = "api.particle.io";
var pPort = 443;
var pPath = "/v1/devices/";
var id1 = "270038001347353136383631";
var token1 = "cd80211aa8ebe0e80cd48729994cf2244151197d";
var functionName;
var data;
var https = require("https");
var requestType = "POST"
var bedMade = true; 

function getOptions(){
    return {
        hostname : pHostname,
        port: pPort, 
        path: pPath + id1 + "/" +functionName,
        method: requestType, 
        headers: {
            'Content-Type': 'application/x-www-form-urlencoded'
        }
    };
}

function makePOSTRequest(){
    options = getOptions();
    console.log(options.path)
    var req = https.request(options); 
    req.write(data);
    req.end();
}

function makeBed(){
    functionName = "makeBed2"; 
    var status = "false";
    data = "access_token=" + token1 + "&args=" + status; 
    console.log(data);
    makePOSTRequest();
    bedMade = true; 
}

function unmakeBed(){
    functionName = "unmakeBed2"; 
        var status = "true";
        data = "access_token=" + token1 + "&args=" + status; 
        console.log(data);
        makePOSTRequest();
        bedMade = false; 
}


const handlers = {
    'makeBed': function () {
        if (!bedMade){
            makeBed();
            this.emit(":tell", "Mister snoozle is making your bed ");
        } else {
            this.emit(":tell", "Mister snoozle says your bed is already made.");
        }
    },
    
    'unmakeBed': function () {
        if (bedMade){
            unmakeBed();
            this.emit(":tell", "Mister snoozle is preparing your bed ");
        } else {
            this.emit(":tell", "Mister snoozle says your bed isn't even made.");
        }
    }
};

exports.handler = (event, context, callback) => {
    var alexa = Alexa.handler(event, context, callback);
    alexa.registerHandlers(handlers);
    alexa.execute();
};
