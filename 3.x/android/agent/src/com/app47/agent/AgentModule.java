package com.app47.agent;

import java.util.HashMap;
import java.util.Map;

import org.appcelerator.kroll.KrollFunction;
import org.appcelerator.kroll.KrollModule;
import org.appcelerator.kroll.annotations.Kroll;
import org.appcelerator.kroll.common.Log;
import org.appcelerator.titanium.TiApplication;

import android.app.Activity;

import com.app47.embeddedagent.EmbeddedAgent;
import com.app47.embeddedagent.EmbeddedAgentLogger;

@Kroll.module(name = "Agent", id = "com.app47.agent")
public class AgentModule extends KrollModule {

	private static final String TAG = "App47AgentModule";

	public AgentModule() {
		super();
	}

	@Kroll.onAppCreate
	public static void onAppCreate(TiApplication app) {

	}

	@Kroll.method
	public void initialize(String appId) {
		Log.d(TAG, "initializing EmbeddedAgent with ID: " + appId);
		EmbeddedAgent.configureAgentWithAppID(getActivity().getApplicationContext(), appId);
	}

	@Override
	public void onPause(Activity activity) {
		super.onPause(activity);
		Log.d(TAG, "onPause invoked and title of passed in activity is :" + activity.getTitle());
		EmbeddedAgent.onPause(activity.getApplicationContext());
	}

	@Override
	public void onResume(Activity activity) {
		super.onResume(activity);
		Log.d(TAG, "onResume invoked and title of passed in activity is :" + activity.getTitle());
		EmbeddedAgent.onResume(activity.getApplicationContext());
	}

	@Kroll.method
	public void sendGenericEvent(String name, @Kroll.argument(optional = true) KrollFunction callback) {
		Log.d(TAG, "sendGenericEvent called with event name: " + name);
		EmbeddedAgent.sendEvent(name);
		invokeCallback(callback);
	}

	@Kroll.method
	public void genericEvent(String name, KrollFunction callback) {
		Log.d(TAG, "genericEvent called with event name: " + name);
		EmbeddedAgent.sendEvent(name);
		invokeCallback(callback);
	}

	@Kroll.method
	public void timedEvent(String name, KrollFunction callback) {
		Log.d(TAG, "timedEvent callback method called with event name: " + name);
		String id = EmbeddedAgent.startTimedEvent(name);
		invokeCallback(callback);
		EmbeddedAgent.endTimedEvent(id);
	}

	@Kroll.method
	public void startTimedEvent(String name, KrollFunction callback) {
		Log.d(TAG, "startTimedEvent called with event name: " + name);
		String id = EmbeddedAgent.startTimedEvent(name);
		Map<String, String> map = new HashMap<String, String>();
		map.put("id", id);
		invokeCallback(callback, (HashMap<String, String>) (map));
	}

	@Kroll.method
	public void endTimedEvent(String id, @Kroll.argument(optional = true) KrollFunction callback) {
		Log.d(TAG, "endTimedEvent called with id: " + id);
		EmbeddedAgent.endTimedEvent(id);
		invokeCallback(callback);
	}

	@Kroll.method
	public void info(String message) {
		EmbeddedAgentLogger.info(message);
	}

	@Kroll.method
	public void debug(String message) {
		EmbeddedAgentLogger.debug(message);
	}

	@Kroll.method
	public void warn(String message) {
		EmbeddedAgentLogger.warn(message);
	}

	@Kroll.method
	public void error(String message) {
		EmbeddedAgentLogger.error(message);
	}

	@Kroll.method
	public void configurationAsMap(String groupName, KrollFunction callback) {
		Map<String, String> map = EmbeddedAgent.configurationGroupAsMap(groupName);
		invokeCallback(callback, (HashMap<String, String>) map);
	}

	@Kroll.method
	public String[] configurationKeys(String groupName) {
		return EmbeddedAgent.allKeysForConfigurationGroup(groupName);
	}

	@Kroll.method
	public Object configurationValue(String group, String key) {
		return EmbeddedAgent.configurationObjectForKey(group, key);
	}

	@Kroll.method
	public String[] configurationGroupNames() {
		return EmbeddedAgent.configurationGroupNames();
	}

	private void invokeCallback(KrollFunction callback, HashMap<String, String> map) {
		if (callback != null) {
			callback.call(getKrollObject(), map);
		}
	}

	private void invokeCallback(KrollFunction callback) {
		if (callback != null) {
			callback.call(getKrollObject(), new HashMap<String, String>());
		}
	}
}
