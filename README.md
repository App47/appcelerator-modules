# App47 Agent Appcelerator Modules

This repo contains two code bases: one for the Android Agent and another for the iOS Agent. 

## Details

Regardless of mobile platform, the JavaScript API for the App47 Agent Appcelerator module has a consistent API. To include the Agent, follow the instructions for adding an Appcelerator module (i.e. download the corresponding zip file and update your `tiapp.xml` file. 

Include the module like so:

```
var agent = require('com.app47.agent');
```

### Configuring the Agent

Then you'll need to provide the App47 Agent your App ID:

```
agent.initialize("5192af2a42asd23200092");
```

The `initialize` takes an optional hash of configuration values. You can find details of these values on the [App47 wiki](http://app47.com/wiki/doku.php):

* [Configuring Android Agent](http://app47.com/wiki/doku.php?id=configure:androidapp#configure_embedded_agent)
* [Configuring iOS Agent](http://app47.com/wiki/doku.php?id=configure:iosapp#configure_the_embedded_agent)

While each Agent platform library has its own configuration values, the Appcelerator App47 Agent module has a consistent set of keys:

 * ConfigurationEndpoint
 * SendActualDeviceIdentifier
 * DelayDataUploadInterval
 * ConfigurationUpdateFrequency
 * ShowNetworkActivity
 * AgentLoggingLevel
 * SendEventsImmediately
 * UploadOnExit

You must use these keys in configuring the Agent via the Appcelerator module. For example:

 ```
 agent.initialize("5192af2a42c56f2d45000092", 
   {ConfigurationUpdateFrequency: 0.000000001, SendActualDeviceIdentifier: true});
 ```

### Events

The JavaScript API supports two method style calls -- a traditional one and a more JavaScript friendly callback style. For example, to execute a timed event, you can code it like so:

```
agent.timedEvent("openCrust 2.0.27", function() {
	openCrust({});
});
```

Where the timed event wraps the corresponding callback (in this case, `openCrust` is invoked and a resultant event, named "openCrust 2.0.27", is sent to App47 w/a time).

On the other hand, you can execute timed events in a traditional manner as well:

```
agent.startTimedEvent("openCrust 2.0.27", function(result) {
	var id = result['id'];
	openCrust({});
	agent.endTimedEvent(id);
});
```

Or you can omit the callback:

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