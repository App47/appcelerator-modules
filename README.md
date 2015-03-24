# App47 Agent Appcelerator Modules


This repository contains two code bases: one for the Android Agent and another for the iOS Agent. You can find the zip files containing the built and supported versions of these platform modules in the [App47 Resource center](https://cirrus.app47.com) located in your account's dashboard.

## Android support
If you are building to the Android platform, please make sure that you include the Android Support jar from the Android distribution with your app. This is normally included with our agent, but not included here to prevent double binding in the class loader within Titanium.

## How to use the App47 Agent

Regardless of mobile platform, the JavaScript API for the App47 Agent Appcelerator module has a consistent API. To include the Agent, follow the instructions for adding an Appcelerator module (i.e. download the corresponding zip file, place it in the root of your project, and update your `tiapp.xml` file). 

Include the module like so:

```
var agent = require('com.app47.agent');
```

Then you'll need to provide the App47 Agent your App ID:

```
agent.initialize("5192af2a42asd23200092");
```

### Configuring the Agent

The `initialize` takes an optional hash of configuration values. You can find details of these values on the [App47 wiki](http://app47.com/wiki/doku.php):

* [Configuring Android Agent](http://app47.com/wiki/doku.php?id=configure:androidapp#configure_embedded_agent)
* [Configuring iOS Agent](http://app47.com/wiki/doku.php?id=configure:iosapp#configure_the_embedded_agent)

While each Agent platform library has its own configuration values, the Appcelerator App47 Agent module has a consistent set of keys:

 * `ConfigurationEndpoint`
 * `SendActualDeviceIdentifier`
 * `DelayDataUploadInterval`
 * `ConfigurationUpdateFrequency`
 * `ShowNetworkActivity`
 * `AgentLoggingLevel`
 * `SendEventsImmediately`
 * `UploadOnExit`

You must use these keys in configuring the Agent via the Appcelerator module. For example:

 ```
 agent.initialize("5192af2a42c56f2d45000092", 
   {ConfigurationUpdateFrequency: 0.000000001, SendActualDeviceIdentifier: true});
 ```

Please note, if no configuration values are provided, the Agent will still work with intelligent default values. 

### Agent configuration finished listener

The App47 Agent is designed to be lightweight and unobtrusive to the app it is embedded in; consequently, the Agent works in an asynchronous manner. Calling the `initialize` method, for example, does not guarantee that the Agent is immediately available once that call returns. Therefore, you can attach a listener for an event that signals the underlying Agent has finished initializing. 

The event is called `CONFIGURATION_COMPLETE`; you can register to listen for it in your Appcelerator app like so:

```
agent.addEventListener(agent.CONFIGURATION_COMPLETE, function(e) {
	Ti.API.info("Agent finished loading all configuration data and is ready to go!");
});
```


### Events API

The JavaScript API supports two method style calls -- a traditional one and a more JavaScript friendly callback style. For example, to execute a timed event, you can code it like so:

```
agent.timedEvent("openCrust 2.0.27", function() {
	openCrust({});
});
```

Where the timed event wraps the corresponding callback (in this case, `openCrust` is invoked and a resultant event, named "openCrust 2.0.27", is sent to App47 w/a time). That is, there is no need to explicitly call `endTimedEvent` as this is automatically handled for you. 

On the other hand, you can execute timed events in a traditional manner as well:

```
agent.startTimedEvent("openCrust 2.0.27", function(result) {
	var id = result['id'];
	openCrust({});
	agent.endTimedEvent(id);
});
```

Note, in this case, the callback is given the event id. 

You can omit the callback as well:

```
var id = agent.startTimedEvent("openCrust 2.0.27");
openCrust({});
agent.endTimedEvent(id);
```

Due to JavaScript's nature, it's recommended that you leverage the succinct idiomatic callback style as outlined first. 

Generic events share the same API:

```
agent.genericEvent("include clock", function() {
	Ti.include('../includes/clock.js');
});
```

You can omit the callback as well and invoke a Generic Event as usual. 

### Logging

The App47 Agent supports logging -- each logging call is routed to the appropriate platform's default logger (i.e. in Android a call to `EmbeddedAgentLogger.debug` will send the log message to App47 _and_ route the debug message to `android.util.Log`.)

To leverage the Agent logging API, simply call any of the following methods:

```
agent.info("main.js opened.");
agent.debug("main.js opened!");
agent.warn("warning, main.js was opened!");
agent.error("good grief, main.js opened!?");
agent.crash("oh no! main.js opened?!!? Bye....");
```

### Configuration Groups

Configuration Groups allows you to set a collection of key value pairs through the App47 Dashboard that are then downloaded by the Agent at initial startup, and then subsequently at a frequency set by the `ConfigurationUpdateFrequency` configuration variable. Configuration items must be requested by group name and key name.

For example, if your app has a group named "Test Group" and a key named "host", you can get its value like so:

```
agent.configurationValue("Test Group", "host", function(result){
	var host_value = result[0];
});
```

There are a few other calls available to you as well. You can retrieve all group names for an app like so:

```
agent.configurationGroupNames(function(result){
	//result is a string array of group names
});
```

You can retrieve all keys for a group:

```
agent.configurationKeys("Test Group", function(result){
	//result is a string array of keys in the Test Group
});
```

And you can retrieve a dictionary representation of the keys and values in a group like so:

```
agent.configurationAsMap("Test Group", function(result){
	//result is an associative array of keys & values in the Test Group
});
```






