# App47 Agent Appcelerator Modules

This repo contains two code bases: one for the Android Agent and another for the iOS Agent. 

## Details

Regardless of mobile platform, the JavaScript API for the App47 Agent Appcelerator module has a consistent API. To include the Agent, follow the instructions for adding an Appcelerator module. Include the code like so:

```
var agent = require('com.app47.agent');
```

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