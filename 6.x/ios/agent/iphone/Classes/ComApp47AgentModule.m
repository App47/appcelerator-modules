/**
 * agent
 *
 * Created by Your Name
 * Copyright (c) 2017 Your Company. All rights reserved.
 */

#import "ComApp47AgentModule.h"
#import "TiBase.h"
#import "TiHost.h"
#import "TiUtils.h"
#import <EmbeddedAgent/EmbeddedAgent.h>


NSString * const CONFIGURATION_COMPLETE = @"agent-configuration-complete";

@implementation ComApp47AgentModule

#pragma mark Internal

// this is generated for your module, please do not change it
-(id)moduleGUID
{
	return @"eff8eb94-8985-4f78-8d4a-d20dc86f742e";
}

// this is generated for your module, please do not change it
-(NSString*)moduleId
{
	return @"com.app47.agent";
}

#pragma mark Lifecycle

-(void)startup
{
	// this method is called when the module is first loaded
	// you *must* call the superclass
	[super startup];
    [[NSNotificationCenter defaultCenter]addObserver:self selector:@selector(agentNotificationReceived) name:EmbeddedAgentAppConfigurationUpdateDidFinish object:nil];
	NSLog(@"[DEBUG] %@ loaded",self);
}

-(void)agentNotificationReceived
{
    NSLog(@"[INFO] agentNotificationReceived invoked");
    [self fireEvent:@"agent-configuration-complete" withObject:nil];
}


-(void)shutdown:(id)sender
{
	// this method is called when the module is being unloaded
	// typically this is during shutdown. make sure you don't do too
	// much processing here or the app will be quit forceably

	// you *must* call the superclass
	[super shutdown:sender];
    [[NSNotificationCenter defaultCenter]removeObserver:self name:EmbeddedAgentAppConfigurationUpdateDidFinish object:nil];
}

#pragma mark Internal Memory Management

-(void)didReceiveMemoryWarning:(NSNotification*)notification
{
	// optionally release any resources that can be dynamically
	// reloaded once memory is available - such as caches
	[super didReceiveMemoryWarning:notification];
}

#pragma mark Listener Notifications

-(void)_listenerAdded:(NSString *)type count:(int)count
{
	if (count == 1 && [type isEqualToString:@"my_event"])
	{
		// the first (of potentially many) listener is being added
		// for event named 'my_event'
	}
}

-(void)_listenerRemoved:(NSString *)type count:(int)count
{
	if (count == 0 && [type isEqualToString:@"my_event"])
	{
		// the last listener called for event named 'my_event' has
		// been removed, we can optionally clean up any resources
		// since no body is listening at this point for that event
	}
}

#pragma TiExceptionHandlerDelegate requirements

- (void)handleUncaughtException:(NSException *)exception withStackTrace:(NSArray *)stackTrace
{
    EALogCrashException(exception, @"Uncaught Exception, application Crashed");
    [[TiExceptionHandler defaultExceptionHandler] setDelegate:nil];
    [[TiExceptionHandler defaultExceptionHandler] handleUncaughtException:exception withStackTrace:stackTrace];
}

- (void)handleScriptError:(TiScriptError *)error
{
    [EmbeddedAgent logMessage:[error message] fileName:[error sourceURL] lineNumber:[error lineNo] level:@"crash" error:nil exception:nil tags:nil];
    [[TiExceptionHandler defaultExceptionHandler] setDelegate:nil];
    [[TiExceptionHandler defaultExceptionHandler] handleScriptError:error];
}

#pragma Public APIs

-(void)crashMeOnPurpose
{
    NSString* str = @"value";
    
}


-(id)CONFIGURATION_COMPLETE
{
    return CONFIGURATION_COMPLETE;
}

- (void)initialize:(id)args
{
    // we now only care about the AppID, any other params will be ignored
    // due to dynamic configuration
    NSString* appId = [args objectAtIndex:0];

    NSLog(@"configureAgentWithAppID is being invoked with %@", appId);
    [EmbeddedAgent configureAgentWithAppID:appId];

    [EmbeddedAgent InstallExceptionHandlers];
    [[TiExceptionHandler defaultExceptionHandler] setDelegate:self];
}

- (void)sendGenericEvent:(id)args
{
    NSString* eventName = [args objectAtIndex:0];
    
    [EmbeddedAgent sendGenericEvent:eventName];
    
    if([args count] > 1){
        KrollCallback* callback = [args objectAtIndex:1];
        if(callback){
            [callback call:nil thisObject:nil];
        }
    }
}

// this method assumes a callback (no check for 2nd argument)
- (void)genericEvent:(id)args
{
    NSString* eventName = [args objectAtIndex:0];
    [EmbeddedAgent sendGenericEvent:eventName];
    KrollCallback* callback = [args objectAtIndex:1];
    if(callback){
        [callback call:nil thisObject:nil];
    }
}

- (void)timedEvent:(id)args
{
    NSString* eventName = [args objectAtIndex:0];
    NSString* eventID = [EmbeddedAgent startTimedEvent:eventName];
    
    KrollCallback* callback = [args objectAtIndex:1];
    if(callback){
        [callback call:nil thisObject:nil];
    }
    
    [EmbeddedAgent endTimedEvent:eventID];
}

- (void)startTimedEvent:(id)args
{
    NSString* eventName = [args objectAtIndex:0];
    NSString* eventID = [EmbeddedAgent startTimedEvent:eventName];
    
    KrollCallback* callback = [args objectAtIndex:1];
    if(callback){
        NSDictionary* dict = [[NSDictionary alloc] initWithObjectsAndKeys:@"id", eventID, nil];
        NSArray* arrayOfValues = [NSArray arrayWithObjects: dict, nil];
        [callback call:arrayOfValues thisObject:nil];
    }
}

- (void)endTimedEvent:(id)args
{
    NSString* eventID = [args objectAtIndex:0];
    [EmbeddedAgent endTimedEvent:eventID];
    
    if([args count] > 1){
        KrollCallback* callback = [args objectAtIndex:1];
        if(callback){
            [callback call:nil thisObject:nil];
        }
    }
}

- (void)configurationValue:(id)args
{
    NSString* group = [args objectAtIndex:0];
    NSString* key = [args objectAtIndex:1];
    id obj =  [EmbeddedAgent configurationObjectForKey:key group:group];
    if([args count] > 1){
        KrollCallback* callback = [args objectAtIndex:2];
        if(callback){
            NSArray* arrayOfValues = [NSArray arrayWithObjects: obj, nil];
            [callback call:arrayOfValues thisObject:nil];
        }
    }
}

- (void)configurationAsMap:(id)args
{
    NSString* group = [args objectAtIndex:0];
    NSDictionary* dict = [EmbeddedAgent configurationGroupAsDictionary:group];
    
    if([args count] > 1){
        KrollCallback* callback = [args objectAtIndex:1];
        if(callback){
            NSArray* arrayOfValues = [NSArray arrayWithObjects: dict, nil];
            [callback call:arrayOfValues thisObject:nil];
        }
    }
}

- (void)configurationGroupNames:(id)args
{
    NSArray* arry = [EmbeddedAgent configurationGroupNames];
    KrollCallback* callback = [args objectAtIndex:0];
    if(callback){
        [callback call:arry thisObject:nil];
    }
}

- (void)configurationKeys:(id)args
{
    NSString* group = [args objectAtIndex:0];
    NSArray* arry = [EmbeddedAgent allKeysForConfigurationGroup:group];
    if([args count] > 1){
        KrollCallback* callback = [args objectAtIndex:1];
        if(callback){
            [callback call:arry thisObject:nil];
        }
    }
}

- (void)info:(id)msg
{
    ENSURE_SINGLE_ARG(msg, NSString);
    EALogInfo(@"%@", msg);
}

- (void)debug:(id)msg
{
    ENSURE_SINGLE_ARG(msg, NSString);
    EALogDebug(@"%@", msg);
}

- (void)warn:(id)msg
{
    ENSURE_SINGLE_ARG(msg, NSString);
    EALogWarn(@"%@", msg);
}

- (void)error:(id)msg
{
    ENSURE_SINGLE_ARG(msg, NSString);
    EALogError(@"%@", msg);
}



@end
