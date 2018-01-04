//
//  EmbeddedAgent.h
//
//  Copyright 2011 App47. All rights reserved.
//



@interface EmbeddedAgent : NSObject {
  
}

//////////////////////////////////////////////////////////////////
// Use one of the three following methods to startup the agent with the appID given on the web site. 
// 
// Insert the following line into your application:didFinishLaunchingWithOptions:launchOptions
//
//- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {    
//  
//  [AgentService configureAgentWithAppID:@"4d3610c21a78a943ea000001"];
//  // OR, assuming you have a an "EmbeddedAgentSettings.plist" file included in your project.
//  [AgentService configureAgent];
//  // OR, use a settings file with your own file name.
//  [AgentService configureAgentWithSettingsFilePath:mySettingsFilePath];
//  
//   ....
//
//  Finish app setup
//
//  return YES;
//}
//
// Use configureAgentWithAppID to configure the agent with the app id given on the web site and 
// all default settings for the embedded agent. 
// See https://cirrus.app47.com/resource_center for more information.

+ (void) configureAgentWithAppID:(NSString *) appID;
+ (void) configureAgentWithAppID:(NSString *) appID withSettings:(NSDictionary *) settings;

// Use configureAgentWithSettingsFilePath to load the fully qualified file path (plist file) 
// containing all default agent settings, including the app id.
+ (void) configureAgentWithSettingsFilePath:(NSString *) filePath;

// Use configureAgent to load the default settings file named EmbeddedAgentSettings.plist located
// in the application main bundle.
+ (void) configureAgent;

// Use the following methods to send generic events to the service, these will be found 
// in your "Events" tab for the App and will be broken out by name.
+ (void) sendGenericEvent:(NSString *) name;
+ (void) sendGenericEvent:(NSString *) name tags:(NSArray *) tags;
+ (void) sendGenericEvent:(NSString *) name tags:(NSArray *) tags userInfo:(NSDictionary *)userInfo;
+ (void) sendGenericEvent:(NSString *) name userInfo:(NSDictionary *)userInfo;

//////////////////////////////////////////////////////////////////
// Timed events allow you to keep track of significant events in your app and how long they take.
// This may be a transcation, download time, or any other performance attribute you want to 
// measure. Each timed event is identified by a name you give it. This name will be used for 
// report aggeration on the service platform.
//
// Along with each timed event you can pass in additional tags with the event both at the start of
// the event as well as the end of the event. In both cases they are optionals and the two lists 
// will be merged together when sent to the server. Tags must be an NSArray of NSStrings.
//
// In addition to tags, you may pass in a collection of key/value pairs using the userInfo parameter.
// All keys and values must be NSStrings.
// 
// When creating a timed event you must give it at least a name, tags and userInfo are optional. The 
// return of startTimedEvent: is a UUID in a NSString object that will later be used to end the timed
// event.
+ (NSString *) startTimedEvent:(NSString *)name;
+ (NSString *) startTimedEvent:(NSString *)name tags:(NSArray *)tags;
+ (NSString *) startTimedEvent:(NSString *)name userInfo:(NSDictionary *)userInfo;
+ (NSString *) startTimedEvent:(NSString *)name tags:(NSArray *)tags userInfo:(NSDictionary *)userInfo;

// To clear a timed event that you do not want sent to the server. This will remove
// it from the local cache.
+ (void) clearTimedEvent:(NSString *) uuid;
// Clear out any time events older than the given time interval. The value is in 
// seconds. Use the value 0 to clear all currently cached timed events.
+ (void) clearTimedEventsOlderThanTimeInterval:(NSTimeInterval)timeInternval;

// To end a timed event, pass the uuid received when creating the event using one of the methods below.
// If additional tags or userInfo dictionaries are passed in when ending an event, the lists/dictionaries
// will be merged and any duplicates removed. In the case of the userInfo NSDictionary, any duplicate
// keys will override current values passed in when creating the timed event.
+ (void) endTimedEvent:(NSString *)uuid;
+ (void) endTimedEvent:(NSString *)uuid tags:(NSArray *)tags;
+ (void) endTimedEvent:(NSString *)uuid userInfo:(NSDictionary *)userInfo;
+ (void) endTimedEvent:(NSString *)uuid tags:(NSArray *)tags userInfo:(NSDictionary *)userInfo;

//////////////////////////////////////////////////////////////////
// Configuration allows you to get updated configuration from the service based on application data
// determined at runtime like App version, OS Version and/or platform. Configuration items are organizied
// by groups and must be retrieved by group name and key name. You may use the defaultValue signature to 
// pass in a default to use if the configuration item is not found by group/key name. If a default value is
// not given, and the key is not found in the requested group, the value nil is returned.
// 
// Use the "Configuration" tab on the web interface to manage the group configuration items. The agent will update
// this configuration information based on the frequency set in the EmbeddedAgentSettings.plist file. This is
// based on the parameter "configuration update frequency".
//
//
// Retrieve all group names and all keys for a given group.
+ (NSArray *) configurationGroupNames;
+ (NSArray *) allKeysForConfigurationGroup:(NSString *) groupName;
// Return a NSDictionary for the given group name. The NSDictionary will have an entry for each kev value pair
// listed on the Admin UI web site. As expected, the NSDictionary key will be the key from
// the AdminUI and the NSDictionary value will be the value. To loop through the dictionary and print
// out it's contents:
//  NSDictionary *groupData = [EmbeddedAgent configurationGroupAsDictionary:groupName];
//  for (NSString *key in [groupData allKeys])
//    NSLog(@"Key %@ - value %@", key, [groupData valueForKey:key]);

+ (NSDictionary *) configurationGroupAsDictionary:(NSString *) groupName;

// Retrieve a configuration item as a string.
+ (NSString *) configurationStringForKey:(NSString *) key group:(NSString *)group;
+ (NSString *) configurationStringForKey:(NSString *) key group:(NSString *)group defaultValue:(NSString *)defaultValue;
// 
// Retrieve a configuration value by key only. If more than one configuration group has the requested 
// key, the value in the first configuration group is returned. Order of the configuration groups is
// arbitrary. See + (NSArray *) configurationObjectsForKey:(NSString *) key for a list of all values
// for a given configuration item.
//
+ (NSString *) configurationStringForKey:(NSString *) key;
+ (NSString *) configurationStringForKey:(NSString *) key defaultValue:(NSString *)defaultValue;

// Retrieve a configuration item as a numrical value.
+ (NSNumber *) configurationNumberForKey:(NSString *) key group:(NSString *)group;
+ (NSNumber *) configurationNumberForKey:(NSString *) key group:(NSString *)group defaultValue:(NSNumber *)defaultValue;
// 
// Retrieve a configuration value by key only. If more than one configuration group has the requested 
// key, the value in the first configuration group is returned. Order of the configuration groups is
// arbitrary. See + (NSArray *) configurationObjectsForKey:(NSString *) key for a list of all values
// for a given configuration item.
//
+ (NSNumber *) configurationNumberForKey:(NSString *) key;
+ (NSNumber *) configurationNumberForKey:(NSString *) key defaultValue:(NSNumber *)defaultValue;

// Retrieve a configuration item as a date
+ (NSDate *) configurationDateForKey:(NSString *) key group:(NSString *)group;
+ (NSDate *) configurationDateForKey:(NSString *) key group:(NSString *)group defaultValue:(NSDate *)defaultValue;
// 
// Retrieve a configuration value by key only. If more than one configuration group has the requested 
// key, the value in the first configuration group is returned. Order of the configuration groups is
// arbitrary. See + (NSArray *) configurationObjectsForKey:(NSString *) key for a list of all values
// for a given configuration item.
//
+ (NSDate *) configurationDateForKey:(NSString *) key;
+ (NSDate *) configurationDateForKey:(NSString *) key defaultValue:(NSDate *)defaultValue;

// Retrieve a configuration item as a boolean value.
+ (BOOL) configurationBoolForKey:(NSString *) key group:(NSString *)group;
+ (BOOL) configurationBoolForKey:(NSString *) key group:(NSString *)group defaultValue:(BOOL)defaultValue;
// 
// Retrieve a configuration value by key only. If more than one configuration group has the requested 
// key, the value in the first configuration group is returned. Order of the configuration groups is
// arbitrary. See + (NSArray *) configurationObjectsForKey:(NSString *) key for a list of all values
// for a given configuration item.
//
+ (BOOL) configurationBoolForKey:(NSString *) key;
+ (BOOL) configurationBoolForKey:(NSString *) key defaultValue:(BOOL)defaultValue;

// Retrieve a configuration item as a file, the file is wrapped in an NSData object and can be used for 
// webviews, UIImages and the ilk.
+ (NSData *) configurationFileForKey:(NSString *) key group:(NSString *) group;
+ (NSString *) configurationFilePathForKey:(NSString *) key group:(NSString *) group;
// Retrieve a configuration value by key only. If more than one configuration group has the requested 
// key, the value in the first configuration group is returned. Order of the configuration groups is
// arbitrary. See + (NSArray *) configurationObjectsForKey:(NSString *) key for a list of all values
// for a given configuration item.
+ (NSData *) configurationFileForKey:(NSString *) key;
+ (NSString *) configurationFilePathForKey:(NSString *) key;


// Retrieve a configuration item as a base object.
+ (id) configurationObjectForKey:(NSString *) key group:(NSString *)group;
+ (id) configurationObjectForKey:(NSString *) key group:(NSString *)group defaultValue:(id)defaultValue;
// 
// Retrieve a configuration value by key only. If more than one configuration group has the requested 
// key, the value in the first configuration group is returned. Order of the configuration groups is
// arbitrary. See + (NSArray *) configurationObjectsForKey:(NSString *) key for a list of all values
// for a given configuration item.
//
+ (id) configurationObjectForKey:(NSString *) key;
+ (id) configurationObjectForKey:(NSString *) key defaultValue:(id)defaultValue;
+ (NSArray *) configurationObjectsForKey:(NSString *) key;

// Register with the NSNotification center to receive these events.

// Configuration updates happen on a background thread, subsequently the App can be notified when
// the configuration of a group did change. You will recieved one message for each configuration group
// change.
extern NSString * const EmbeddedAgentAppConfigurationGroupDidInsert;
extern NSString * const EmbeddedAgentAppConfigurationGroupDidUpdate;
extern NSString * const EmbeddedAgentAppConfigurationGroupDidDelete;
// Each message will contain a single value in the userInfo with the following key. The value returned
// by the key is the name of the group that was either added, updated, or deleted.
extern NSString * const EmbeddedAgentAppConfigurationGroupNameKey;
// Message if a particular group failed to update.
extern NSString * const EmbeddedAgentAppConfigurationGroupFetchDidFail;
// Alternatively, you can register a single notification when any configuration group changes.
// The name of the configuration group and specific action is NOT sent, only the fact that 
// the configurationg group was change.
extern NSString * const EmbeddedAgentAppConfigurationGroupDidChange;
// Message is sent when all configuration groups has started and finished. If no configuration
// groups are present, these message is not sent.
extern NSString * const EmbeddedAgentAppConfigurationUpdateDidStart;
extern NSString * const EmbeddedAgentAppConfigurationUpdateDidFinish;
// Starting the agent configuration process.
extern NSString * const EmbeddedAgentConfigurationDidStart;
// Sent when the agent is done checking configuration and ready to operate. This will kick off the
// data upload process.
extern NSString * const EmbeddedAgentConfigurationDidFinish;
// If the agent cannot check in, either new or update, this message is sent to know the update operation
// is done, but was not able to complete, check the logs for more information.
extern NSString * const EmbeddedAgentConfigurationDidFail;
// If the agent is unable to register with the server, which it only does once, the register did fail
// message will be sent.
extern NSString * const EmbeddedAgentRegistrationDidFail;



//////////////////////////////////////////////////////////////////
// Exception handling and crash loggin
+ (void) InstallExceptionHandlers;

//////////////////////////////////////////////////////////////////
// Logging.

+ (void) sendCachedData;


+ (void) logMessage:(NSString *) message 
           fileName:(NSString *) fileName 
         lineNumber:(int)lineNumber 
              level:(NSString *)level
          error:(NSError *) error 
          exception:(NSException *) exception 
               tags:(NSArray *)tags;

// Macros for logging, accessible from Objective-C
//
#define EALogDebug( format, ... ) [EmbeddedAgent logMessage:[NSString stringWithFormat:(format), ##__VA_ARGS__] fileName:[[NSString stringWithUTF8String:__FILE__] lastPathComponent] lineNumber:__LINE__ level:@"debug" error:nil exception:nil tags:nil]
#define EALogDebugWithException(e,  format, ... ) [EmbeddedAgent logMessage:[NSString stringWithFormat:(format), ##__VA_ARGS__] fileName:[[NSString stringWithUTF8String:__FILE__] lastPathComponent] lineNumber:__LINE__ level:@"debug" error:nil exception:e tags:nil]
#define EALogDebugWithError(err, format, ... ) [EmbeddedAgent logMessage:[NSString stringWithFormat:(format), ##__VA_ARGS__] fileName:[[NSString stringWithUTF8String:__FILE__] lastPathComponent] lineNumber:__LINE__ level:@"debug" error:err exception:nil tags:nil]
#define EALogDebugWithTags( arrayOfTags,format, ... ) [EmbeddedAgent logMessage:[NSString stringWithFormat:(format), ##__VA_ARGS__] fileName:[[NSString stringWithUTF8String:__FILE__] lastPathComponent] lineNumber:__LINE__ level:@"debug" error:nil exception:nil tags:arrayOfTags]
#define EALogDebugWithTagsException(e, arrayOfTags, format, ... ) [EmbeddedAgent logMessage:[NSString stringWithFormat:(format), ##__VA_ARGS__] fileName:[[NSString stringWithUTF8String:__FILE__] lastPathComponent] lineNumber:__LINE__ level:@"debug" error:nil exception:e tags:nil]
#define EALogDebugWithTagsError(err, arrayOfTags, format, ... ) [EmbeddedAgent logMessage:[NSString stringWithFormat:(format), ##__VA_ARGS__] fileName:[[NSString stringWithUTF8String:__FILE__] lastPathComponent] lineNumber:__LINE__ level:@"debug" error:err exception:nil tags:nil]


#define EALogInfo( format, ... ) [EmbeddedAgent logMessage:[NSString stringWithFormat:(format), ##__VA_ARGS__] fileName:[[NSString stringWithUTF8String:__FILE__] lastPathComponent] lineNumber:__LINE__ level:@"info"  error:nil exception:nil tags:nil]
#define EALogInfoWithException(e,  format, ... ) [EmbeddedAgent logMessage:[NSString stringWithFormat:(format), ##__VA_ARGS__] fileName:[[NSString stringWithUTF8String:__FILE__] lastPathComponent] lineNumber:__LINE__ level:@"info" error:nil exception:e tags:nil]
#define EALogInfoWithError(err, format, ... ) [EmbeddedAgent logMessage:[NSString stringWithFormat:(format), ##__VA_ARGS__] fileName:[[NSString stringWithUTF8String:__FILE__] lastPathComponent] lineNumber:__LINE__ level:@"info" error:err exception:nil tags:nil]
#define EALogInfoWithTags( arrayOfTags,format, ... ) [EmbeddedAgent logMessage:[NSString stringWithFormat:(format), ##__VA_ARGS__] fileName:[[NSString stringWithUTF8String:__FILE__] lastPathComponent] lineNumber:__LINE__ level:@"info" error:nil exception:nil  tags:arrayOfTags]
#define EALogInfoWithTagsException(e, arrayOfTags, format, ... ) [EmbeddedAgent logMessage:[NSString stringWithFormat:(format), ##__VA_ARGS__] fileName:[[NSString stringWithUTF8String:__FILE__] lastPathComponent] lineNumber:__LINE__ level:@"info" error:nil exception:e tags:nil]
#define EALogInfoWithTagsError(err, arrayOfTags, format, ... ) [EmbeddedAgent logMessage:[NSString stringWithFormat:(format), ##__VA_ARGS__] fileName:[[NSString stringWithUTF8String:__FILE__] lastPathComponent] lineNumber:__LINE__ level:@"info" error:err exception:nil tags:nil]


#define EALogWarn( format, ... ) [EmbeddedAgent logMessage:[NSString stringWithFormat:(format), ##__VA_ARGS__] fileName:[[NSString stringWithUTF8String:__FILE__] lastPathComponent] lineNumber:__LINE__ level:@"warn"  error:nil exception:nil tags:nil]
#define EALogWarnWithException(e,  format, ... ) [EmbeddedAgent logMessage:[NSString stringWithFormat:(format), ##__VA_ARGS__] fileName:[[NSString stringWithUTF8String:__FILE__] lastPathComponent] lineNumber:__LINE__ level:@"warn" error:nil exception:e tags:nil]
#define EALogWarnWithError(err, format, ... ) [EmbeddedAgent logMessage:[NSString stringWithFormat:(format), ##__VA_ARGS__] fileName:[[NSString stringWithUTF8String:__FILE__] lastPathComponent] lineNumber:__LINE__ level:@"warn" error:err exception:nil tags:nil]
#define EALogWarnWithTags( arrayOfTags,format, ... ) [EmbeddedAgent logMessage:[NSString stringWithFormat:(format), ##__VA_ARGS__] fileName:[[NSString stringWithUTF8String:__FILE__] lastPathComponent] lineNumber:__LINE__ level:@"warn" error:nil exception:nil tags:arrayOfTags]
#define EALogWarnWithTagsException(e, arrayOfTags, format, ... ) [EmbeddedAgent logMessage:[NSString stringWithFormat:(format), ##__VA_ARGS__] fileName:[[NSString stringWithUTF8String:__FILE__] lastPathComponent] lineNumber:__LINE__ level:@"warn" error:nil exception:e tags:nil]
#define EALogWarnWithTagsError(err, arrayOfTags, format, ... ) [EmbeddedAgent logMessage:[NSString stringWithFormat:(format), ##__VA_ARGS__] fileName:[[NSString stringWithUTF8String:__FILE__] lastPathComponent] lineNumber:__LINE__ level:@"warn" error:err exception:nil tags:nil]


#define EALogError( format, ... ) [EmbeddedAgent logMessage:[NSString stringWithFormat:(format), ##__VA_ARGS__] fileName:[[NSString stringWithUTF8String:__FILE__] lastPathComponent] lineNumber:__LINE__ level:@"error" error:nil exception:nil  tags:nil]
#define EALogErrorWithException(ex, format, ... ) [EmbeddedAgent logMessage:[NSString stringWithFormat:(format), ##__VA_ARGS__] fileName:[[NSString stringWithUTF8String:__FILE__] lastPathComponent] lineNumber:__LINE__ level:@"error" error:nil exception:ex  tags:nil]
#define EALogErrorWithError(err, format, ... ) [EmbeddedAgent logMessage:[NSString stringWithFormat:(format), ##__VA_ARGS__] fileName:[[NSString stringWithUTF8String:__FILE__] lastPathComponent] lineNumber:__LINE__ level:@"error" error:err exception:nil  tags:nil]
#define EALogErrorWithTags( arrayOfTags,format, ... ) [EmbeddedAgent logMessage:[NSString stringWithFormat:(format), ##__VA_ARGS__] fileName:[[NSString stringWithUTF8String:__FILE__] lastPathComponent] lineNumber:__LINE__ level:@"error" error:nil exception:nil tags:arrayOfTags]
#define EALogErrorWithTagsError(err, tags,format, ... ) [EmbeddedAgent logMessage:[NSString stringWithFormat:(format), ##__VA_ARGS__] fileName:[[NSString stringWithUTF8String:__FILE__] lastPathComponent] lineNumber:__LINE__ level:@"error" error:err exception:nil tags:tags]
#define EALogErrorWithTagsException(ex, arrayOfTags,format, ... ) [EmbeddedAgent logMessage:[NSString stringWithFormat:(format), ##__VA_ARGS__] fileName:[[NSString stringWithUTF8String:__FILE__] lastPathComponent] lineNumber:__LINE__ level:@"error" error:nil exception:ex tags:arrayOfTags]


#define EALogCrashException(ex, format, ... ) [EmbeddedAgent logMessage:[NSString stringWithFormat:(format), ##__VA_ARGS__] fileName:[[NSString stringWithUTF8String:__FILE__] lastPathComponent] lineNumber:__LINE__ level:@"crash" error:nil exception:ex  tags:nil]

// Helper methods for logging, best used from Swift
//
+ (void)logDebugWithMessage:(NSString*)message fileName:(NSString*)fileName lineNumber:(int)lineNumber;
+ (void)logDebugWithException:(NSException*)exception message:(NSString*)message fileName:(NSString*)fileName lineNumber:(int)lineNumber;
+ (void)logDebugWithError:(NSError*)error message:(NSString*)message fileName:(NSString*)fileName lineNumber:(int)lineNumber;
+ (void)logDebugWithTags:(NSArray*)tags message:(NSString*)message fileName:(NSString*)fileName lineNumber:(int)lineNumber;
+ (void)logDebugWithException:(NSException*)exception tags:(NSArray*)tags message:(NSString*)message fileName:(NSString*)fileName lineNumber:(int)lineNumber;
+ (void)logDebugWithError:(NSError*)error tags:(NSArray*)tags message:(NSString*)message fileName:(NSString*)fileName lineNumber:(int)lineNumber;


+ (void)logInfoWithMessage:(NSString*)message fileName:(NSString*)fileName lineNumber:(int)lineNumber;
+ (void)logInfoWithException:(NSException*)exception message:(NSString*)message fileName:(NSString*)fileName lineNumber:(int)lineNumber;
+ (void)logInfoWithError:(NSError*)error message:(NSString*)message fileName:(NSString*)fileName lineNumber:(int)lineNumber;
+ (void)logInfoWithTags:(NSArray*)tags message:(NSString*)message fileName:(NSString*)fileName lineNumber:(int)lineNumber;
+ (void)logInfoWithException:(NSException*)exception tags:(NSArray*)tags message:(NSString*)message fileName:(NSString*)fileName lineNumber:(int)lineNumber;
+ (void)logInfoWithError:(NSError*)error tags:(NSArray*)tags message:(NSString*)message fileName:(NSString*)fileName lineNumber:(int)lineNumber;


+ (void)logWarningWithMessage:(NSString*)message fileName:(NSString*)fileName lineNumber:(int)lineNumber;
+ (void)logWarningWithException:(NSException*)exception message:(NSString*)message fileName:(NSString*)fileName lineNumber:(int)lineNumber;
+ (void)logWarningWithError:(NSError*)error message:(NSString*)message fileName:(NSString*)fileName lineNumber:(int)lineNumber;
+ (void)logWarningWithTags:(NSArray*)tags message:(NSString*)message fileName:(NSString*)fileName lineNumber:(int)lineNumber;
+ (void)logWarningWithException:(NSException*)exception tags:(NSArray*)tags message:(NSString*)message fileName:(NSString*)fileName lineNumber:(int)lineNumber;
+ (void)logWarningWithError:(NSError*)error tags:(NSArray*)tags message:(NSString*)message fileName:(NSString*)fileName lineNumber:(int)lineNumber;


+ (void)logErrorWithMessage:(NSString*)message fileName:(NSString*)fileName lineNumber:(int)lineNumber;
+ (void)logErrorWithException:(NSException*)exception message:(NSString*)message fileName:(NSString*)fileName lineNumber:(int)lineNumber;
+ (void)logErrorWithError:(NSError*)error message:(NSString*)message fileName:(NSString*)fileName lineNumber:(int)lineNumber;
+ (void)logErrorWithTags:(NSArray*)tags message:(NSString*)message fileName:(NSString*)fileName lineNumber:(int)lineNumber;
+ (void)logErrorWithException:(NSException*)exception tags:(NSArray*)tags message:(NSString*)message fileName:(NSString*)fileName lineNumber:(int)lineNumber;
+ (void)logErrorWithError:(NSError*)error tags:(NSArray*)tags message:(NSString*)message fileName:(NSString*)fileName lineNumber:(int)lineNumber;

+ (void)logCrashWithException:(NSException*)exception message:(NSString*)message fileName:(NSString*)fileName lineNumber:(int)lineNumber;

@end
