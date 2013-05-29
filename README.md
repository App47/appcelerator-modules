# App47 Agent Appcelerator Modules

This repository contains two code bases: one for the Android Agent and another for the iOS Agent. You can find the zip files containing the built and supported versions of these platform modules in the App47 Resource center located in your account's dashboard.

## How to use the App47 Agent

Regardless of mobile platform, the JavaScript API for the App47 Agent Appcelerator module has a consistent API. To include the Agent, follow the instructions for adding an Appcelerator module (i.e. download the corresponding zip file and update your `tiapp.xml` file. 

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