# Build the App47 Agent Appcelerator Modules

To update the module for release, follow the steps below to ensure a complete and accurate update.

This module is delivered pre-compiled for App47's customers. This file is for the App47 development team to build and update the Appcelerator Modules for delivery. It is NOT required to follow these steps to integrate App47 into your Appcelerator Project.

## Setup and configuration

### Appcelerator Installation

Ensure that you have the Appcelerator Titanium Studio installed and updated

### Android SDK

Ensure you have the Android SDK installed with the Android-8 SDK available.

### Python

Ensure you have a version of python loaded on your computer.

### ANT

Ensure you have a version of ant loaded on your computer.

## Update Libraries

### Android

Update the android.jar file in 3.x/android/agent/lib/

Update the file 3.x/android/agent/manifest with the proper version number for the android agent.

### iOS

Update the files in 3.x/ios/agent/app47
  * apache_license.txt - license file for apache open source software used.
  * EmbeddedAgent.h - Header file for the App47 Agent.
  * libGMStackTrace.a - Capture crash logs
  * EmbeddedAgentSettings.plist - Sample settings file for Agent
  * version - Version number for the Appcelerator iOS Module
  * libEmbeddedAgentWithNoCoreLocation.a - updated library for the App47 Agent


Update the file 3.x/android/agent/manifest with the proper version number for the iOS agent.


## Build the modules

### Android

cd 3.x/android/agent
run
# ant dist

### iOS

cd 3.x/android/ios
run
# ./build.py
