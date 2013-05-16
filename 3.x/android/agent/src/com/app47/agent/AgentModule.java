package com.app47.agent;

import java.io.IOException;
import java.util.Map;
import java.util.Scanner;

import org.appcelerator.kroll.KrollModule;
import org.appcelerator.kroll.annotations.Kroll;
import org.appcelerator.kroll.common.Log;
import org.appcelerator.titanium.TiApplication;
import org.appcelerator.titanium.io.TiResourceFile;

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
		TiResourceFile res = new TiResourceFile("res/values/AgentAppId");
		if (res.exists()) {
			try {
				Scanner s = new Scanner(res.getInputStream()).useDelimiter("\\A");
				String value = s.hasNext() ? s.next() : "";
				EmbeddedAgent.configureAgentWithAppID(app.getApplicationContext(), value);
			} catch (IOException e) {
				Log.e(TAG, "Exception is: " + e.getLocalizedMessage() + " in trying to read file  " + res.name()
						+ " at path: " + res.nativePath() + " and it is a file? " + res.isFile(), e);
			}
		} else {
			Log.e(TAG, "The file AgentAppId could not be located, the App47 Agent will NOT work. "
					+ "It should be located in Resources/android/res/values/ ");
		}
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
	public void sendGenericEvent(String name) {
		Log.d(TAG, "sendGenericEvent called with event name: " + name);
		EmbeddedAgent.sendEvent(name);
	}

	@Kroll.method
	public String startTimedEvent(String name) {
		Log.d(TAG, "startTimedEvent called with event name: " + name);
		return EmbeddedAgent.startTimedEvent(name);
	}

	@Kroll.method
	public void endTimedEvent(String id) {
		Log.d(TAG, "endTimedEvent called with id: " + id);
		EmbeddedAgent.endTimedEvent(id);
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
	public Map<String, String> configurationAsMap(String groupName) {
		return EmbeddedAgent.configurationGroupAsMap(groupName);
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

}
