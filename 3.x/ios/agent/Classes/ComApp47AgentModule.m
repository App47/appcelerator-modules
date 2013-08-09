/**
 * Andrew Glover
 * license: MIT
 * Copyright (c) 2013 by App47
 *
 * Appcelerator Titanium is Copyright (c) 2009-2010 by Appcelerator, Inc.
 * and licensed under the Apache Public License (version 2)
 */
#import "ComApp47AgentModule.h"
#import "TiBase.h"
#import "TiHost.h"
#import "TiUtils.h"
#import "EmbeddedAgent.h"



NSString * const CONFIGURATION_COMPLETE = @"agent-configuration-complete";

@implementation ComApp47AgentModule

#pragma mark Internal

-(id)moduleGUID
{
	return @"b94c02ec-484a-47cb-91c2-5bc192d0b824";
}

-(NSString*)moduleId
{
	return @"com.app47.agent";
}

#pragma mark Lifecycle

-(void)startup
{
	[super startup];
    [[NSNotificationCenter defaultCenter]addObserver:self selector:@selector(agentNotificationReceived) name:EmbeddedAgentAppConfigurationUpdateDidFinish object:nil];
	NSLog(@"[INFO] %@ loaded", self);
}

-(void)agentNotificationReceived
{
    NSLog(@"[INFO] agentNotificationReceived invoked");
    [self fireEvent:@"agent-configuration-complete" withObject:nil];
}

-(void)shutdown:(id)sender
{
	[super shutdown:sender];
    [[NSNotificationCenter defaultCenter]removeObserver:self name:EmbeddedAgentAppConfigurationUpdateDidFinish object:nil];
}

#pragma mark Properties

//MAKE_SYSTEM_PROP(CONFIGURATION_COMPLETE, CONFIGURATION_COMPLETE);


#pragma mark Cleanup 

-(void)dealloc
{
	[super dealloc];
}

#pragma mark Internal Memory Management

-(void)didReceiveMemoryWarning:(NSNotification*)notification
{
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
    [str nothing];
}


-(id)CONFIGURATION_COMPLETE
{
    return CONFIGURATION_COMPLETE;
}

- (void)initialize:(id)args
{
    NSString* appId = [args objectAtIndex:0];
    if([args count] > 1){
        NSDictionary* options = [args objectAtIndex:1];
        NSMutableDictionary* dict = [[[NSMutableDictionary alloc] init] autorelease];

        for(id key in options){
            
            if([key isEqualToString:@"ConfigurationEndpoint"]){
                [dict setObject: [options objectForKey:key] forKey: @"configuration endpoint"];
            }
            if([key isEqualToString:@"SendActualDeviceIdentifier"]){
                [dict setObject: [options objectForKey:key] forKey: @"send actual device identifier"];
            }
            if([key isEqualToString:@"DelayDataUploadInterval"]){
                [dict setObject: [options objectForKey:key] forKey: @"delay data upload interval"];
            }
            if([key isEqualToString:@"ConfigurationUpdateFrequency"]){
                [dict setObject: [options objectForKey:key] forKey: @"configuration update frequency"];
            }
            if([key isEqualToString:@"ShowNetworkActivity"]){
                [dict setObject: [options objectForKey:key] forKey: @"show network activity"];
            }
            if([key isEqualToString:@"AgentLoggingLevel"]){
                [dict setObject: [options objectForKey:key] forKey: @"agent logging level"];
            }
            if([key isEqualToString:@"SendEventsImmediately"]){
                [dict setObject: [options objectForKey:key] forKey: @"send events immediately"];
            }
            if([key isEqualToString:@"UploadOnExit"]){
                [dict setObject: [options objectForKey:key] forKey: @"upload on exit"];
            }
        }
        NSLog(@"configureAgentWithAppID is being invoked with %@, and dict %@!", appId, dict);
        [EmbeddedAgent configureAgentWithAppID:appId withSettings: dict];
    }else{
        NSLog(@"configureAgentWithAppID is being invoked with %@ and w/o dict", appId);
        [EmbeddedAgent configureAgentWithAppID:appId];
    }
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
        NSDictionary* dict = [[[NSDictionary alloc] initWithObjectsAndKeys:@"id", eventID, nil] autorelease];
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
