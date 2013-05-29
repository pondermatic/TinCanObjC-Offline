//
//  RSTinCanConnector.h
//  RSTCAPI
//
//  Created by Brian Rogers on 2/28/13.
//  Copyright (c) 2013 Brian Rogers. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "TCError.h"
#import "TCStatement.h"
#import "TCOfflineStatementCollection.h"
#import "TCLRS.h"
#import "TCQueryOptions.h"
#import "TCAgent.h"

@interface RSTinCanOfflineConnector : NSObject


/**
 Calls initWithOptions with a configured LRS
 
 @method initWithOptions
 @param {NSDictionary} options containing LRS endpoint information
 */

- (id) initWithOptions:(NSDictionary *)options;


/**
 Calls saveStatement on each configured LRS, provide callback to make it asynchronous
 
 @method sendStatementToServer
 @param statementToSend statement Send statement to LRS
 @param completionBlock code to execute on completion
 @param errorBlock code to execute on error
 */
- (void) sendStatementToServer:(TCStatement *)statementToSend withCompletionBlock:(void (^)())completionBlock withErrorBlock:(void(^)(TCError *))errorBlock;

/**
 Calls retrieveStatement on each configured LRS until it gets a result, provide callback to make it asynchronous
 
 @method getStatement
 @param {String} statement Statement ID to get
 @param {Function} [callback] Callback function to execute on completion
 @return {TinCan.Statement} Retrieved statement from LRS
 
 TODO: make TinCan track statements it has seen in a local cache to be returned easily
 */
- (void) getStatementWithId:(NSString *)statementId withOptions:(NSDictionary *)options withCompletionBlock:(void(^)(TCStatement *))completionBlock withErrorBlock:(void(^)(TCError *))errorBlock;

/**
 Calls saveStatements with list of prepared statements
 
 @method sendStatementsToServer
 @param {Array} Array of statements to send
 @param {Function} Callback function to execute on completion
 */
- (void) sendStatementsToServer:(TCStatementCollection *)statementArray withCompletionBlock:(void(^)())completionBlock withErrorBlock:(void(^)(TCError *))errorBlock;

/**
 @method getStatements
 @param {Object} [cfg] Configuration for request
 @param {Boolean} [cfg.sendActor] Include default actor in query params
 @param {Boolean} [cfg.sendActivity] Include default activity in query params
 @param {Object} [cfg.params] Parameters used to filter
 
 @param {Function} [cfg.callback] Function to run at completion
 
 TODO: support multiple LRSs and flag to use single
 */
- (void) getStatementsWithOptions:(TCQueryOptions *)options withCompletionBlock:(void(^)(NSArray *))completionBlock withErrorBlock:(void(^)(TCError *))errorBlock;

/**
 @method getState
 @param {String} key Key to retrieve from the state
 @param {Object} [cfg] Configuration for request
 @param {Object} [cfg.agent] Agent used in query,
 defaults to 'actor' property if empty
 @param {Object} [cfg.activity] Activity used in query,
 defaults to 'activity' property if empty
 @param {Object} [cfg.registration] Registration used in query,
 defaults to 'registration' property if empty
 @param {Function} [cfg.callback] Function to run with state
 */
- (void) getStateWithStateId:(NSString *)stateId withActivityId:(NSString *)activityId withAgent:(TCAgent *)agent withRegistration:(NSString *)registration withOptions:(NSDictionary *)options withCompletionBlock:(void(^)(NSDictionary *))completionBlock withErrorBlock:(void(^)(TCError *))errorBlock;

/**
 @method setState
 @param {String} key Key to store into the state
 @param {String|Object} val Value to store into the state, objects will be stringified to JSON
 @param {Object} [cfg] Configuration for request
 @param {Object} [cfg.agent] Agent used in query,
 defaults to 'actor' property if empty
 @param {Object} [cfg.activity] Activity used in query,
 defaults to 'activity' property if empty
 @param {Object} [cfg.registration] Registration used in query,
 defaults to 'registration' property if empty
 @param {Function} [cfg.callback] Function to run with state
 */
- (void) setStateWithValue:(NSDictionary *)value withStateId:(NSString *)stateId withActivityId:(NSString *)activityId withAgent:(TCAgent *)agent withRegistration:(NSString *)registration withOptions:(NSDictionary *)options withCompletionBlock:(void(^)())completionBlock withErrorBlock:(void(^)(TCError *))errorBlock;

/**
 @method deleteState
 @param {String|null} key Key to remove from the state, or null to clear all
 @param {Object} [cfg] Configuration for request
 @param {Object} [cfg.agent] Agent used in query,
 defaults to 'actor' property if empty
 @param {Object} [cfg.activity] Activity used in query,
 defaults to 'activity' property if empty
 @param {Object} [cfg.registration] Registration used in query,
 defaults to 'registration' property if empty
 @param {Function} [cfg.callback] Function to run with state
 */
- (void) deleteStateWithStateId:(NSString *)stateId withActivityId:(NSString *)activityId withAgent:(TCAgent *)agent withRegistration:(NSString *)registration withOptions:(NSDictionary *)options withCompletionBlock:(void(^)())completionBlock withErrorBlock:(void(^)(TCError *))errorBlock;

/**
 @method getActivityProfile
 @param {String} key Key to retrieve from the profile
 @param {Object} [cfg] Configuration for request
 @param {Object} [cfg.activity] Activity used in query,
 defaults to 'activity' property if empty
 @param {Function} [cfg.callback] Function to run with activity profile
 */
- (void) getActivityProfile:(NSString *)key withOptions:(NSDictionary *)options withCompletionBlock:(void(^)(NSDictionary *))completionBlock withErrorBlock:(void(^)(TCError *))errorBlock;

/**
 @method setActivityProfile
 @param {String} key Key to store into the activity profile
 @param {String|Object} val Value to store into the activity profile, objects will be stringified to JSON
 @param {Object} [cfg] Configuration for request
 @param {Object} [cfg.activity] Activity used in query,
 defaults to 'activity' property if empty
 @param {Function} [cfg.callback] Function to run with activity profile
 */
- (void) setActivityProfile:(NSString *)key withValue:(NSDictionary *)value withOptions:(NSDictionary *)options withCompletionBlock:(void(^)())completionBlock withErrorBlock:(void(^)(TCError *))errorBlock;

/**
 @method deleteActivityProfile
 @param {String|null} key Key to remove from the activity profile, or null to clear all
 @param {Object} [cfg] Configuration for request
 @param {Object} [cfg.activity] Activity used in query,
 defaults to 'activity' property if empty
 @param {Function} [cfg.callback] Function to run with activity profile
 */
- (void) deleteActivityProfile:(NSString *)key withOptions:(NSDictionary *)options withCompletionBlock:(void(^)())completionBlock withErrorBlock:(void(^)(TCError *))errorBlock;

- (void) enqueueStatement:(TCStatement *)statement withCompletionBlock:(void(^)())completionBlock withErrorBlock:(void(^)(NSError *))errorBlock;
- (NSArray *) getCachedStatements;
- (void) sendOldestStatementFromQueueWithCompletionBlock:(void(^)())completionBlock;

- (void) sendAllStatementsToServerWithCompletionBlock:(void(^)())completionBlock withErrorBlock:(void (^)(NSError *))errorBlock;

- (void) sendLocalStateToServerWithCompletionBlock:(void(^)())completionBlock withErrorBlock:(void(^)(NSError *))errorBlock;

@end