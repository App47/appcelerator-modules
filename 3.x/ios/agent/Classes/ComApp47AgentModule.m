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

@implementation ComApp47AgentModule

#pragma mark Internal

// this is generated for your module, please do not change it
-(id)moduleGUID
{
	return @"b94c02ec-484a-47cb-91c2-5bc192d0b824";
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
	
	NSLog(@"[INFO] %@ loaded",self);
}

-(void)shutdown:(id)sender
{
	// this method is called when the module is being unloaded
	// typically this is during shutdown. make sure you don't do too
	// much processing here or the app will be quit forceably
	
	// you *must* call the superclass
	[super shutdown:sender];
}

#pragma mark Cleanup 

-(void)dealloc
{
	// release any resources that have been retained by the module
	[super dealloc];
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

#pragma Public APIs

- (void)initialize:(id)args
{
    NSString* appId = [args objectAtIndex:0];
    if([args count] > 1){
        NSDictionary* options = [args objectAtIndex:1];
        NSMutableDictionary* dict = [[NSMutableDictionary alloc] init];

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
        }
        
        [EmbeddedAgent configureAgentWithAppID:appId withSettings: dict];
    }else{
        [EmbeddedAgent configureAgentWithAppID:appId];
    }
    [EmbeddedAgent InstallExceptionHandlers];
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

//
//
//-(id)example:(id)args
//{
//	// example method
//	return @"hello world";
//}
//
//-(id)exampleProp
//{
//	// example property getter
//	return @"hello world";
//}
//
//-(void)setExampleProp:(id)value
//{
//	// example property setter
//}

@end
