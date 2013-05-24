// This is a test harness for your module
// You should do something interesting in this harness 
// to test out the module and to provide instructions 
// to users on how to use it by example.


// open a single window
var win = Ti.UI.createWindow({
	backgroundColor:'white'
});
var label = Ti.UI.createLabel();
win.add(label);
win.open();

// TODO: write your module tests here
var agent = require('com.app47.agent');
Ti.API.info("module is => " + agent);

var agent = require('com.app47.agent');

//agent.initialize("5192af2a42c56f2d45000092", {ConfigurationUpdateFrequency: 0.000000001, SendActualDeviceIdentifier: true});
agent.initialize("5192af2a42c56f2d45000092");

agent.genericEvent("app started up (ios)", function() {
	main.open();
});

agent.timedEvent("openCrust 2.0.27", function() {
	openCrust({});
});


agent.debug("main.js opened!");

