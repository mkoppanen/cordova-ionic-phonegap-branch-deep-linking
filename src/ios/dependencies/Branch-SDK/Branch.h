//
//  Branch_SDK.h
//  Branch-SDK
//
//  Created by Alex Austin on 6/5/14.
//  Copyright (c) 2014 Branch Metrics. All rights reserved.
//
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "BNCConfig.h"
#import "BranchView.h"
#import "BNCCallbacks.h"
#import "BNCLinkCache.h"
#import "BranchViewHandler.h"
#import "BNCServerInterface.h"
#import "BNCPreferenceHelper.h"
#import "BranchLinkProperties.h"
#import "BranchUniversalObject.h"
#import "BNCServerRequestQueue.h"
#import "BranchActivityItemProvider.h"
#import "BranchDeepLinkingController.h"
#import "BNCCommerceEvent.h"
#import "BranchShareLink.h"
#import "BNCXcode7Support.h"

/**
 `Branch` is the primary interface of the Branch iOS SDK. Currently, all interactions you will make are funneled through this class. It is not meant to be instantiated or subclassed, usage should be limited to the global instance.
 
  Note, when `getInstance` is called, it assumes that you have already placed a Branch Key in your main `Info.plist` file for your project. For additional information on configuring the Branch SDK, check out the getting started guides in the Readme.
 */

///----------------
/// @name Constants
///----------------

#pragma mark Branch Link Features

/**
 ## Branch Link Features
 The following are constants used for specifying a feature parameter on a call that creates a Branch link.
 
 `BRANCH_FEATURE_SHARE`
 Indicates this link was used for sharing content. Used by the `getContentUrl` methods.
 
 `BRANCH_FEATURE_TAG_REFERRAL`
 Indicates this link was used to refer users to this app. Used by the `getReferralUrl` methods.
 
 `BRANCH_FEATURE_TAG_INVITE`
 Indicates this link is used as an invitation.
 
 `BRANCH_FEATURE_TAG_DEAL`
 Indicates this link is being used to trigger a deal, like a discounted rate.
 
 `BRANCH_FEATURE_TAG_GIFT`
 Indicates this link is being used to sned a gift to another user.
 */
extern NSString * const BRANCH_FEATURE_TAG_SHARE;
extern NSString * const BRANCH_FEATURE_TAG_REFERRAL;
extern NSString * const BRANCH_FEATURE_TAG_INVITE;
extern NSString * const BRANCH_FEATURE_TAG_DEAL;
extern NSString * const BRANCH_FEATURE_TAG_GIFT;

#pragma mark - Branch InitSession Dictionary Constants

/**
 ## Branch Link Features
 
 `BRANCH_INIT_KEY_CHANNEL`
 The channel on which the link was shared, specified at link creation time.
 
 `BRANCH_INIT_KEY_FEATURE`
 The feature, such as `invite` or `share`, specified at link creation time.
 
 `BRANCH_INIT_KEY_TAGS`
 Any tags, specified at link creation time.
 
 `BRANCH_INIT_KEY_CAMPAIGN`
 The campaign the link is associated with, specified at link creation time.
 
 `BRANCH_INIT_KEY_STAGE`
 The stage, specified at link creation time.
 
 `BRANCH_INIT_KEY_CREATION_SOURCE`
 Where the link was created ('API', 'Dashboard', 'SDK', 'iOS SDK', 'Android SDK', or 'Web SDK')
 
 `BRANCH_INIT_KEY_REFERRER`
 The referrer for the link click, if a link was clicked.
 
 `BRANCH_INIT_KEY_PHONE_NUMBER`
 The phone number of the user, if the user texted himself/herself the app.
 
 `BRANCH_INIT_KEY_IS_FIRST_SESSION`
 Denotes whether this is the first session (install) or any other session (open).
 
 `BRANCH_INIT_KEY_CLICKED_BRANCH_LINK`
 Denotes whether or not the user clicked a Branch link that triggered this session.
 */
extern NSString * const BRANCH_INIT_KEY_CHANNEL;
extern NSString * const BRANCH_INIT_KEY_FEATURE;
extern NSString * const BRANCH_INIT_KEY_TAGS;
extern NSString * const BRANCH_INIT_KEY_CAMPAIGN;
extern NSString * const BRANCH_INIT_KEY_STAGE;
extern NSString * const BRANCH_INIT_KEY_CREATION_SOURCE;
extern NSString * const BRANCH_INIT_KEY_REFERRER;
extern NSString * const BRANCH_INIT_KEY_PHONE_NUMBER;
extern NSString * const BRANCH_INIT_KEY_IS_FIRST_SESSION;
extern NSString * const BRANCH_INIT_KEY_CLICKED_BRANCH_LINK;

// BUO Constants
extern NSString * const BNCCanonicalIdList;
extern NSString * const BNCPurchaseAmount;
extern NSString * const BNCPurchaseCurrency;
extern NSString * const BNCCanonicalIdList;
extern NSString * const BNCPurchaseAmount;
extern NSString * const BNCRegisterViewEvent;
extern NSString * const BNCAddToWishlistEvent;
extern NSString * const BNCAddToCartEvent;
extern NSString * const BNCPurchaseInitiatedEvent;
extern NSString * const BNCPurchasedEvent;
extern NSString * const BNCShareInitiatedEvent;
extern NSString * const BNCShareCompletedEvent;

#pragma mark - Branch Enums
typedef NS_ENUM(NSUInteger, BranchCreditHistoryOrder) {
    BranchMostRecentFirst,
    BranchLeastRecentFirst
};

@interface Branch : NSObject

#pragma mark - Global Instance Accessors

///--------------------------------
/// @name Global Instance Accessors
///--------------------------------

/**
 Gets the global, live Branch instance.
 */
+ (Branch *)getInstance;

/**
 Gets the global, test Branch instance.
 
 @warning This method is not meant to be used in production!
 */
+ (Branch *)getTestInstance;

/**
 Gets the global Branch instance, configures using the specified key
 
 @param branchKey The Branch key to be used by the Branch instance. This can be any live or test key.
 @warning This method is not the recommended way of using Branch. Try using your project's `Info.plist` if possible.
 */
+ (Branch *)getInstance:(NSString *)branchKey;


#pragma mark - BranchActivityItemProvider methods

///-----------------------------------------
/// @name BranchActivityItemProvider methods
///-----------------------------------------

/**
 Create a BranchActivityItemProvider which subclasses the `UIActivityItemProvider` This can be used for simple sharing via a `UIActivityViewController`.
 
 Internally, this will create a short Branch Url that will be attached to the shared content.
 
 @param params A dictionary to use while building up the Branch link.
 */
+ (BranchActivityItemProvider *)getBranchActivityItemWithParams:(NSDictionary *)params;

/**
 Create a BranchActivityItemProvider which subclasses the `UIActivityItemProvider` This can be used for simple sharing via a `UIActivityViewController`.
 
 Internally, this will create a short Branch Url that will be attached to the shared content.
 
 @param params A dictionary to use while building up the Branch link.
 @param feature The feature the generated link will be associated with.
 */
+ (BranchActivityItemProvider *)getBranchActivityItemWithParams:(NSDictionary *)params feature:(NSString *)feature;

/**
 Create a BranchActivityItemProvider which subclasses the `UIActivityItemProvider` This can be used for simple sharing via a `UIActivityViewController`.
 
 Internally, this will create a short Branch Url that will be attached to the shared content.
 
 @param params A dictionary to use while building up the Branch link.
 @param feature The feature the generated link will be associated with.
 @param stage The stage used for the generated link, typically used to indicate what part of a funnel the user is in.
 */
+ (BranchActivityItemProvider *)getBranchActivityItemWithParams:(NSDictionary *)params feature:(NSString *)feature stage:(NSString *)stage;

/**
 Create a BranchActivityItemProvider which subclasses the `UIActivityItemProvider` This can be used for simple sharing via a `UIActivityViewController`.
 
 Internally, this will create a short Branch Url that will be attached to the shared content.
 
 @param params A dictionary to use while building up the Branch link.
 @param feature The feature the generated link will be associated with.
 @param stage The stage used for the generated link, typically used to indicate what part of a funnel the user is in.
 @param tags An array of tag strings to be associated with the link.
 */
+ (BranchActivityItemProvider *)getBranchActivityItemWithParams:(NSDictionary *)params feature:(NSString *)feature stage:(NSString *)stage tags:(NSArray *)tags;

/**
 Create a BranchActivityItemProvider which subclasses the `UIActivityItemProvider` This can be used for simple sharing via a `UIActivityViewController`.
 
 Internally, this will create a short Branch Url that will be attached to the shared content.
 
 @param params A dictionary to use while building up the Branch link.
 @param feature The feature the generated link will be associated with.
 @param stage The stage used for the generated link, indicating what part of a funnel the user is in.
 @param alias The alias for a link.
 @warning This can fail if the alias is already taken.
 */
+ (BranchActivityItemProvider *)getBranchActivityItemWithParams:(NSDictionary *)params feature:(NSString *)feature stage:(NSString *)stage tags:(NSArray *)tags alias:(NSString *)alias;

/**
 Create a BranchActivityItemProvider which subclasses the `UIActivityItemProvider` This can be used for simple sharing via a `UIActivityViewController`.
 
 Internally, this will create a short Branch Url that will be attached to the shared content.
 
 @param params A dictionary to use while building up the Branch link.
 @param feature The feature the generated link will be associated with.
 @param stage The stage used for the generated link, indicating what part of a funnel the user is in.
 @param campaign Use this field to organize the links by actual marketing campaign.
 @param alias The alias for a link.
 @warning This can fail if the alias is already taken.
 */
+ (BranchActivityItemProvider *)getBranchActivityItemWithParams:(NSDictionary *)params feature:(NSString *)feature stage:(NSString *)stage campaign:(NSString *)campaign tags:(NSArray *)tags alias:(NSString *)alias;

/**
 Create a BranchActivityItemProvider which subclasses the `UIActivityItemProvider` This can be used for simple sharing via a `UIActivityViewController`.
 
 Internally, this will create a short Branch Url that will be attached to the shared content.
 
 @param params A dictionary to use while building up the Branch link.
 @param feature The feature the generated link will be associated with.
 @param stage The stage used for the generated link, typically used to indicate what part of a funnel the user is in.
 @param tags An array of tag strings to be associated with the link.
 @param alias The alias for a link.
 @params delegate A delegate allowing you to override any of the parameters provided here based on the user-selected channel
 @warning This can fail if the alias is already taken.
 */
+ (BranchActivityItemProvider *)getBranchActivityItemWithParams:(NSDictionary *)params feature:(NSString *)feature stage:(NSString *)stage tags:(NSArray *)tags alias:(NSString *)alias delegate:(id <BranchActivityItemProviderDelegate>)delegate;



#pragma mark - Initialization methods

///---------------------
/// @name Initialization
///---------------------

/**
 Just initialize the Branch session with the app launch options.
 
 @param options The launch options provided by the AppDelegate's `didFinishLaunchingWithOptions:` method.
 @warning This is not the recommended method of initializing Branch. While Branch is able to properly attribute deep linking info with the launch options, you lose the ability to do anything with a callback.
 */
- (void)initSessionWithLaunchOptions:(NSDictionary *)options;

/**
 Just initialize the Branch session with the app launch options, specifying whether to allow it to be treated as a referral.
 
 @param options The launch options provided by the AppDelegate's `didFinishLaunchingWithOptions:` method.
 @param isReferrable Boolean representing whether to allow the session to be marked as referred, overriding the default behavior.
 @warning This is not the recommended method of initializing Branch. While Branch is able to properly attribute deep linking info with the launch options, you lose the ability to do anything with a callback.
 */
- (void)initSessionWithLaunchOptions:(NSDictionary *)options isReferrable:(BOOL)isReferrable;

/**
 Initialize the Branch session with the app launch options and handle the completion with a callback
 
 @param options The launch options provided by the AppDelegate's `didFinishLaunchingWithOptions:` method.
 @param callback A callback that is called when the session is opened. This will be called multiple times during the apps life, including any time the app goes through a background / foreground cycle.
 */
- (void)initSessionWithLaunchOptions:(NSDictionary *)options andRegisterDeepLinkHandler:(callbackWithParams)callback;

/**
 Initialize the Branch session with the app launch options and handle the completion with a callback
 
 @param options The launch options provided by the AppDelegate's `didFinishLaunchingWithOptions:` method.
 @param callback A callback that is called when the session is opened. This will be called multiple times during the apps life, including any time the app goes through a background / foreground cycle.
 */
- (void)initSessionWithLaunchOptions:(NSDictionary *)options andRegisterDeepLinkHandlerUsingBranchUniversalObject:(callbackWithBranchUniversalObject)callback;

/**
 Initialize the Branch session with the app launch options and handle the completion with a callback
 
 @param options The launch options provided by the AppDelegate's `didFinishLaunchingWithOptions:` method.
 @param automaticallyDisplayController Boolean indicating whether we will automatically launch into deep linked controller matched in the init session dictionary.
 */
- (void)initSessionWithLaunchOptions:(NSDictionary *)options automaticallyDisplayDeepLinkController:(BOOL)automaticallyDisplayController;

/**
 Initialize the Branch session with the app launch options and handle the completion with a callback
 
 @param options The launch options provided by the AppDelegate's `didFinishLaunchingWithOptions:` method.
 @param isReferrable Boolean representing whether to allow the session to be marked as referred, overriding the default behavior.
 @param callback A callback that is called when the session is opened. This will be called multiple times during the apps life, including any time the app goes through a background / foreground cycle.
 */
- (void)initSessionWithLaunchOptions:(NSDictionary *)options isReferrable:(BOOL)isReferrable andRegisterDeepLinkHandler:(callbackWithParams)callback;

/**
 Initialize the Branch session with the app launch options and handle the completion with a callback
 
 @param options The launch options provided by the AppDelegate's `didFinishLaunchingWithOptions:` method.
 @param isReferrable Boolean representing whether to allow the session to be marked as referred, overriding the default behavior.
 @param automaticallyDisplayController Boolean indicating whether we will automatically launch into deep linked controller matched in the init session dictionary.
 */
- (void)initSessionWithLaunchOptions:(NSDictionary *)options isReferrable:(BOOL)isReferrable automaticallyDisplayDeepLinkController:(BOOL)automaticallyDisplayController;

/**
 Initialize the Branch session with the app launch options and handle the completion with a callback
 
 @param options The launch options provided by the AppDelegate's `didFinishLaunchingWithOptions:` method.
 @param automaticallyDisplayController Boolean indicating whether we will automatically launch into deep linked controller matched in the init session dictionary.
 @param callback A callback that is called when the session is opened. This will be called multiple times during the apps life, including any time the app goes through a background / foreground cycle.
 */
- (void)initSessionWithLaunchOptions:(NSDictionary *)options automaticallyDisplayDeepLinkController:(BOOL)automaticallyDisplayController deepLinkHandler:(callbackWithParams)callback;

/**
 Initialize the Branch session with the app launch options and handle the completion with a callback
 
 @param options The launch options provided by the AppDelegate's `didFinishLaunchingWithOptions:` method.
 @param automaticallyDisplayController Boolean indicating whether we will automatically launch into deep linked controller matched in the init session dictionary.
 @param isReferrable Boolean representing whether to allow the session to be marked as referred, overriding the default behavior.
 @param callback A callback that is called when the session is opened. This will be called multiple times during the apps life, including any time the app goes through a background / foreground cycle.
 */
- (void)initSessionWithLaunchOptions:(NSDictionary *)options automaticallyDisplayDeepLinkController:(BOOL)automaticallyDisplayController isReferrable:(BOOL)isReferrable deepLinkHandler:(callbackWithParams)callback;

/**
 Allow Branch to handle a link opening the app, returning whether it was from a Branch link or not.
 
 @param url The url that caused the app to be opened.
 */
- (BOOL)handleDeepLink:(NSURL *)url;

/**
 Allow Branch to handle restoration from an NSUserActivity, returning whether or not it was
 from a Branch link.
 
 @param userActivity The NSUserActivity that caused the app to be opened.
 */
- (BOOL)continueUserActivity:(NSUserActivity *)userActivity;

/**
 Call this method from inside your app delegate's `application:openURL:sourceApplication:annotation:`
 method with the so that Branch can open the passed URL.

 @param application         The application that was passed to your app delegate.
 @param url                 The URL that was passed to your app delegate.
 @param sourceApplication   The sourceApplication that was passed to your app delegate.
 @param annotation          The annotation that was passed to your app delegate.
 @return                    Returns `YES` if Branch handled the passed URL.
 */
- (BOOL)application:(UIApplication *)application
            openURL:(NSURL *)url
  sourceApplication:(NSString *)sourceApplication
         annotation:(id)annotation;

/**
 Call this method from inside your app delegate's `application:openURL:options:`
 method with the so that Branch can open the passed URL.
 
 This method is functionally the same as calling the Branch method
 `application:openURL:sourceApplication:annotation:`. This method matches the new Apple appDelegate
 method for convenience.

 @param application         The application that was passed to your app delegate.
 @param url                 The URL that was passed to your app delegate.
 @param options             The options dictionary that was passed to your app delegate.
 @return                    Returns `YES` if Branch handled the passed URL.
 */
- (BOOL)application:(UIApplication *)application
            openURL:(NSURL *)url
            options:(NSDictionary<UIApplicationOpenURLOptionsKey,id> *)options;

///--------------------------------
/// @name Push Notification Support
///--------------------------------

#pragma mark - Push Notification support

/**
 Allow Branch to handle a push notification with a Branch link.
 
 To make use of this, when creating a push notification, specify the Branch Link as an NSString, for key @"branch".
 
 NSDictionary userInfo = @{@"branch": @"https://bnc.lt/...", ... };
 */
- (void)handlePushNotification:(NSDictionary *)userInfo;

#pragma mark - Deep Link Controller methods

///---------------------------
/// @name Deep Link Controller
///---------------------------

- (void)registerDeepLinkController:(UIViewController <BranchDeepLinkingController> *)controller forKey:(NSString *)key;

#pragma mark - Configuration methods

///--------------------
/// @name Configuration
///--------------------

/**
 Have Branch treat this device / session as a debug session, causing more information to be logged, and info to be available in the debug tab of the dashboard.
 
 @warning This should not be used in production.
 */
- (void)setDebug;

/**
 Specify additional constant parameters to be included in the response
 
 @param debugParams dictionary of keystrings/valuestrings that will be added to response 
 */
-(void)setDeepLinkDebugMode:(NSDictionary *)debugParams;

/**
 Add a scheme to a whitelist of URI schemes that will be tracked by Branch. Default to all schemes.
 
 @param scheme to add to the whitelist, i.e. @"http", @"https" or @"myapp"
 */
-(void)addWhiteListedScheme:(NSString *)scheme;

/**
 Add an array of schemes to a whitelist of URI schemes that will be tracked by Branch. Default to all schemes.
 
 @param schemes array to add to the whitelist, i.e. @[@"http", @"https", @"myapp"]
 */
-(void)setWhiteListedSchemes:(NSArray *)schemes;

/**
 Register your Facebook SDK's FBSDKAppLinkUtility class to be used by Branch for deferred deep linking from their platform
 
 @param FBSDKAppLinkUtility - call [FBSDKAppLinkUtility class] after importing #import <FBSDKCoreKit/FBSDKCoreKit.h>
 */
- (void)registerFacebookDeepLinkingClass:(id)FBSDKAppLinkUtility;

/**
 Check for Apple Search Ads before initialization. Will add about 1 second from call to initSession to callback due to Apple's latency.
 */
- (void)delayInitToCheckForSearchAds;

/**
 Set the SDK into Apple Search Ad debug mode where it passes fake campaign params back 100%
 
 @warning This should not be used in production.
 */
- (void)setAppleSearchAdsDebugMode;


/**
 Specify the time to wait in seconds between retries in the case of a Branch server error
 
 @param retryInterval Number of seconds to wait between retries.
 */
- (void)setRetryInterval:(NSTimeInterval)retryInterval;

/**
 Specify the max number of times to retry in the case of a Branch server error
 
 @param maxRetries Number of retries to make.
 */
- (void)setMaxRetries:(NSInteger)maxRetries;

/**
 Specify the amount of time before a request should be considered "timed out"
 
 @param timeout Number of seconds to before a request is considered timed out.
 */
- (void)setNetworkTimeout:(NSTimeInterval)timeout;

/**
 Specify that Branch should NOT use an invisible SFSafariViewController to attempt cookie-based matching upon install.
 If you call this method, we will fall back to using our pool of cookie-IDFA pairs for matching.
 */
- (void)disableCookieBasedMatching;

/**
 TL;DR: If you're using a version of the Facebook SDK that prevents application:didFinishLaunchingWithOptions: from
 returning YES/true when a Universal Link is clicked, you should enable this option.

 Long explanation: in application:didFinishLaunchingWithOptions: you should choose one of the following:

 1. Always `return YES;`, and do *not* invoke `[[Branch getInstance] accountForFacebookSDKPreventingAppLaunch];`
 2. Allow the Facebook SDK to determine whether `application:didFinishLaunchingWithOptions:` returns `YES` or `NO`,
    and invoke `[[Branch getInstance] accountForFacebookSDKPreventingAppLaunch];`

 The reason for this second option is that the Facebook SDK will return `NO` if a Universal Link opens the app
 but that UL is not a Facebook UL. Some developers prefer not to modify
 `application:didFinishLaunchingWithOptions:` to always return `YES` and should use this method instead.
 */
- (void)accountForFacebookSDKPreventingAppLaunch __attribute__((deprecated(("Please ensure application:didFinishLaunchingWithOptions: always returns YES/true instead of using this method. It will be removed in a future release."))));

- (void)suppressWarningLogs;

/**
 Key-value pairs to be included in the metadata on every request.
 
 @param key String to be included in request metadata
 @param value Object to be included in request metadata
 */
- (void)setRequestMetadataKey:(NSString *)key value:(NSObject *)value;

- (void)enableDelayedInit;

- (void)disableDelayedInit;

- (NSURL *)getUrlForOnboardingWithRedirectUrl:(NSString *)redirectUrl;

- (void)resumeInit;

- (void)setInstallRequestDelay:(NSInteger)installRequestDelay;


#pragma mark - Session Item methods

///--------------------
/// @name Session Items
///--------------------

/**
 Get the BranchUniversalObject from the first time this user was referred (can be empty).
 */
- (BranchUniversalObject *)getFirstReferringBranchUniversalObject;

/**
 Get the BranchLinkProperties from the first time this user was referred (can be empty).
 */
- (BranchLinkProperties *)getFirstReferringBranchLinkProperties;

/**
 Get the parameters used the first time this user was referred (can be empty).
 */
- (NSDictionary *)getFirstReferringParams;

/**
 Get the BranchUniversalObject from the most recent time this user was referred (can be empty).
 */
- (BranchUniversalObject *)getLatestReferringBranchUniversalObject;

/**
 Get the BranchLinkProperties from the most recent time this user was referred (can be empty).
 */
- (BranchLinkProperties *)getLatestReferringBranchLinkProperties;

/**
 Get the parameters used the most recent time this user was referred (can be empty).
 */
- (NSDictionary *)getLatestReferringParams;

/**
 Returns the most recent referral parameters for this user. An empty object can be returned.
 This call blocks the calling thread until the latest results are available.
 @warning This call blocks the calling thread.
 */
- (NSDictionary*) getLatestReferringParamsSynchronous;

/**
 Tells Branch to act as though initSession hadn't been called. Will require another open call (this is done automatically, internally).
 */
- (void)resetUserSession;

/**
 Indicates whether or not this user has a custom identity specified for them. Note that this is *independent of installs*. If you call setIdentity, this device
 will have that identity associated with this user until `logout` is called. This includes persisting through uninstalls, as we track device id.
 */
- (BOOL)isUserIdentified;

/**
 Set the user's identity to an ID used by your system, so that it is identifiable by you elsewhere.
 
 @param userId The ID Branch should use to identify this user.
 @warning If you use the same ID between users on different sessions / devices, their actions will be merged.
 @warning This request is not removed from the queue upon failure -- it will be retried until it succeeds.
 @warning You should call `logout` before calling `setIdentity:` a second time.
 */
- (void)setIdentity:(NSString *)userId;

/**
 Set the user's identity to an ID used by your system, so that it is identifiable by you elsewhere. Receive a completion callback, notifying you whether it succeeded or failed.
 
 @param userId The ID Branch should use to identify this user.
 @param callback The callback to be called once the request has completed (success or failure).
 @warning If you use the same ID between users on different sessions / devices, their actions will be merged.
 @warning This request is not removed from the queue upon failure -- it will be retried until it succeeds. The callback will only ever be called once, though.
 @warning You should call `logout` before calling `setIdentity:` a second time.
 */
- (void)setIdentity:(NSString *)userId withCallback:(callbackWithParams)callback;

/**
 Clear all of the current user's session items.
 
 @warning If the request to logout fails, the items will not be cleared.
 */
- (void)logout;

- (void)logoutWithCallback:(callbackWithStatus)callback;

#pragma mark - Credit methods

///--------------
/// @name Credits
///--------------

/**
 Loads credit totals from the server.
 
 @param callback The callback that is called once the request has completed.
 */
- (void)loadRewardsWithCallback:(callbackWithStatus)callback;

/**
 Redeem credits from the default bucket.
 
 @param count The number of credits to redeem.
 @warning You must `loadRewardsWithCallback:` before calling `redeemRewards`.
 */
- (void)redeemRewards:(NSInteger)count;

/**
 Redeem credits from the default bucket.
 
 @param count The number of credits to redeem.
 @param callback The callback that is called once the request has completed.
 @warning You must `loadRewardsWithCallback:` before calling `redeemRewards`.
 */
- (void)redeemRewards:(NSInteger)count callback:(callbackWithStatus)callback;

/**
 Redeem credits from the specified bucket.
 
 @param count The number of credits to redeem.
 @param bucket The bucket to redeem credits from.
 @warning You must `loadRewardsWithCallback:` before calling `redeemRewards`.
 */
- (void)redeemRewards:(NSInteger)count forBucket:(NSString *)bucket;

/**
 Redeem credits from the specified bucket.
 
 @param count The number of credits to redeem.
 @param bucket The bucket to redeem credits from.
 @param callback The callback that is called once the request has completed.
 @warning You must `loadRewardsWithCallback:` before calling `redeemRewards`.
 */
- (void)redeemRewards:(NSInteger)count forBucket:(NSString *)bucket callback:(callbackWithStatus)callback;

/**
 Get the local credit balance for the default bucket.
 
 @warning You must `loadRewardsWithCallback:` before calling `getCredits`. This method does not make a request for the balance.
 */
- (NSInteger)getCredits;

/**
 Get the local credit balance for the specified bucket.
 
 @param bucket The bucket to get credits balance from.
 @warning You must `loadRewardsWithCallback:` before calling `getCredits`. This method does not make a request for the balance.
 */
- (NSInteger)getCreditsForBucket:(NSString *)bucket;

/**
 Loads the last 100 credit transaction history items for the default bucket.
 
 @param callback The callback to call with the list of transactions.
 */
- (void)getCreditHistoryWithCallback:(callbackWithList)callback;

/**
 Loads the last 100 credit transaction history items for the specified bucket.
 
 @param bucket The bucket to get transaction history for.
 @param callback The callback to call with the list of transactions.
 */
- (void)getCreditHistoryForBucket:(NSString *)bucket andCallback:(callbackWithList)callback;

/**
 Loads the last n credit transaction history items after the specified transaction ID for the default.
 
 @param creditTransactionId The ID of the transaction to start from.
 @param length The number of transactions to pull.
 @param order The direction to order transactions in the callback list. Least recent first means oldest items will be in the front of the response array, most recent means newest items will be front.
 @param callback The callback to call with the list of transactions.
 */
- (void)getCreditHistoryAfter:(NSString *)creditTransactionId number:(NSInteger)length order:(BranchCreditHistoryOrder)order andCallback:(callbackWithList)callback;

/**
 Loads the last n credit transaction history items after the specified transaction ID for the specified bucket.
 
 @param bucket The bucket to get transaction history for.
 @param creditTransactionId The ID of the transaction to start from.
 @param length The number of transactions to pull.
 @param order The direction to order transactions in the callback list. Least recent first means oldest items will be in the front of the response array, most recent means newest items will be front.
 @param callback The callback to call with the list of transactions.
 */
- (void)getCreditHistoryForBucket:(NSString *)bucket after:(NSString *)creditTransactionId number:(NSInteger)length order:(BranchCreditHistoryOrder)order andCallback:(callbackWithList)callback;

#pragma mark - Action methods

///--------------
/// @name Actions
///--------------

/**
 Send a user action to the server. Some examples actions could be things like `viewed_personal_welcome`, `purchased_an_item`, etc.
 
 @param action The action string.
 */
- (void)userCompletedAction:(NSString *)action;

/**
 Send a user action to the server with additional state items. Some examples actions could be things like `viewed_personal_welcome`, `purchased_an_item`, etc.
 
 @param action The action string.
 @param state The additional state items associated with the action.
 */
- (void)userCompletedAction:(NSString *)action withState:(NSDictionary *)state;

/**
 Send a user action to the server with additional state items. Some examples actions could be things like `viewed_personal_welcome`, `purchased_an_item`, etc.
 
 @param action The action string.
 @param state The additional state items associated with the action.
 @param branchViewCallback Callback for Branch view state
 */
- (void)userCompletedAction:(NSString *)action withState:(NSDictionary *)state withDelegate:(id)branchViewCallback;

/**
 Sends a user commerce event to the server.

 Use commerce events to track when a user purchases an item in your online store, 
 makes an in-app purchase, or buys a subscription.  The commerce events are tracked in 
 the Branch dashboard along with your other events so you can judge the effectiveness of
 campaigns and other analytics.

 @param commerceEvent 	The BNCCommerceEvent that describes the purchase.
 @param metadata        Optional metadata you may want add to the event.
 @param completion 		The optional completion callback.
 */
- (void) sendCommerceEvent:(BNCCommerceEvent*)commerceEvent
				  metadata:(NSDictionary<NSString*,id>*)metadata
			withCompletion:(void (^) (NSDictionary*response, NSError*error))completion;

#pragma mark - Short Url Sync methods

///---------------------------------------
/// @name Synchronous Short Url Generation
///---------------------------------------

/**
 Get a short url without any items specified. The usage type will default to unlimited.
 */
- (NSString *)getShortURL;

/**
 Get a short url with specified params. The usage type will default to unlimited.
 
 @param params Dictionary of parameters to include in the link.
 @warning This method makes a synchronous url request.
 */
- (NSString *)getShortURLWithParams:(NSDictionary *)params;

/**
 Get a short url with specified params, channel, and feature. The usage type will default to unlimited.
 
 @param params Dictionary of parameters to include in the link.
 @param channel The channel for the link. Examples could be Facebook, Twitter, SMS, etc, depending on where it will be shared.
 @param feature The feature this is utilizing. Examples could be Sharing, Referring, Inviting, etc.
 @warning This method makes a synchronous url request.
 */
- (NSString *)getShortURLWithParams:(NSDictionary *)params andChannel:(NSString *)channel andFeature:(NSString *)feature;

/**
 Get a short url with specified params, channel, feature, and stage. The usage type will default to unlimited.
 
 @param params Dictionary of parameters to include in the link.
 @param channel The channel for the link. Examples could be Facebook, Twitter, SMS, etc, depending on where it will be shared.
 @param feature The feature this is utilizing. Examples could be Sharing, Referring, Inviting, etc.
 @param stage The stage used for the generated link, indicating what part of a funnel the user is in.
 @warning This method makes a synchronous url request.
 */
- (NSString *)getShortURLWithParams:(NSDictionary *)params andChannel:(NSString *)channel andFeature:(NSString *)feature andStage:(NSString *)stage;

/**
 Get a short url with specified params, channel, feature, stage, and alias. The usage type will default to unlimited.
 
 @param params Dictionary of parameters to include in the link.
 @param channel The channel for the link. Examples could be Facebook, Twitter, SMS, etc, depending on where it will be shared.
 @param feature The feature this is utilizing. Examples could be Sharing, Referring, Inviting, etc.
 @param stage The stage used for the generated link, indicating what part of a funnel the user is in.
 @param alias The alias for a link.
 @warning This method makes a synchronous url request.
 @warning This can fail if the alias is already taken.
 */
- (NSString *)getShortURLWithParams:(NSDictionary *)params andChannel:(NSString *)channel andFeature:(NSString *)feature andStage:(NSString *)stage andAlias:(NSString *)alias;

/**
 Get a short url with specified params, channel, feature, stage, and type.
 
 @param params Dictionary of parameters to include in the link.
 @param channel The channel for the link. Examples could be Facebook, Twitter, SMS, etc, depending on where it will be shared.
 @param feature The feature this is utilizing. Examples could be Sharing, Referring, Inviting, etc.
 @param stage The stage used for the generated link, indicating what part of a funnel the user is in.
 @param type The type of link this is, one of Single Use or Unlimited Use. Single use means once *per user*, not once period.
 @warning This method makes a synchronous url request.
 */
- (NSString *)getShortURLWithParams:(NSDictionary *)params andChannel:(NSString *)channel andFeature:(NSString *)feature andStage:(NSString *)stage andType:(BranchLinkType)type;

/**
 Get a short url with specified params, channel, feature, stage, and match duration. The usage type will default to unlimited.
 
 @param params Dictionary of parameters to include in the link.
 @param channel The channel for the link. Examples could be Facebook, Twitter, SMS, etc, depending on where it will be shared.
 @param feature The feature this is utilizing. Examples could be Sharing, Referring, Inviting, etc.
 @param stage The stage used for the generated link, indicating what part of a funnel the user is in.
 @param duration How long to keep an unmatched link click in the Branch backend server's queue before discarding.
 @warning This method makes a synchronous url request.
 */
- (NSString *)getShortURLWithParams:(NSDictionary *)params andChannel:(NSString *)channel andFeature:(NSString *)feature andStage:(NSString *)stage andMatchDuration:(NSUInteger)duration;

/**
 Get a short url with specified tags, params, channel, feature, and stage. The usage type will default to unlimited.
 
 @param params Dictionary of parameters to include in the link.
 @param tags An array of tags to associate with this link, useful for tracking.
 @param channel The channel for the link. Examples could be Facebook, Twitter, SMS, etc, depending on where it will be shared.
 @param feature The feature this is utilizing. Examples could be Sharing, Referring, Inviting, etc.
 @param stage The stage used for the generated link, indicating what part of a funnel the user is in.
 @warning This method makes a synchronous url request.
 */
- (NSString *)getShortURLWithParams:(NSDictionary *)params andTags:(NSArray *)tags andChannel:(NSString *)channel andFeature:(NSString *)feature andStage:(NSString *)stage;

/**
 Get a short url with specified tags, params, channel, feature, stage, and alias. The usage type will default to unlimited.
 
 @param params Dictionary of parameters to include in the link.
 @param tags An array of tags to associate with this link, useful for tracking.
 @param channel The channel for the link. Examples could be Facebook, Twitter, SMS, etc, depending on where it will be shared.
 @param feature The feature this is utilizing. Examples could be Sharing, Referring, Inviting, etc.
 @param stage The stage used for the generated link, indicating what part of a funnel the user is in.
 @param alias The alias for a link.
 @warning This method makes a synchronous url request.
 @warning This can fail if the alias is already taken.
 */
- (NSString *)getShortURLWithParams:(NSDictionary *)params andTags:(NSArray *)tags andChannel:(NSString *)channel andFeature:(NSString *)feature andStage:(NSString *)stage andAlias:(NSString *)alias;

/**
 Get a short url with specified tags, params, channel, feature, and stage. The usage type will default to unlimited.
 
 @param params Dictionary of parameters to include in the link.
 @param tags An array of tags to associate with this link, useful for tracking.
 @param channel The channel for the link. Examples could be Facebook, Twitter, SMS, etc, depending on where it will be shared.
 @param feature The feature this is utilizing. Examples could be Sharing, Referring, Inviting, etc.
 @param stage The stage used for the generated link, indicating what part of a funnel the user is in.
 @param alias The alias for a link.
 @param ignoreUAString The User Agent string to tell the server to ignore the next request from, to prevent it from treating a preview scrape as a link click.
 @warning This method makes a synchronous url request.
 @warning This method is primarily intended to be an internal Branch method, used to work around a bug with SLComposeViewController
 @warning This can fail if the alias is already taken.
 */
- (NSString *)getShortURLWithParams:(NSDictionary *)params andTags:(NSArray *)tags andChannel:(NSString *)channel andFeature:(NSString *)feature andStage:(NSString *)stage andAlias:(NSString *)alias ignoreUAString:(NSString *)ignoreUAString;

/**
 Get a short url with specified tags, params, channel, feature, stage and campaign. The usage type will default to unlimited.
 
 @param params Dictionary of parameters to include in the link.
 @param tags An array of tags to associate with this link, useful for tracking.
 @param channel The channel for the link. Examples could be Facebook, Twitter, SMS, etc, depending on where it will be shared.
 @param feature The feature this is utilizing. Examples could be Sharing, Referring, Inviting, etc.
 @param stage The stage used for the generated link, indicating what part of a funnel the user is in.
 @param campaign Use this field to organize the links by actual marketing campaign.
 @param alias The alias for a link.
 @param ignoreUAString The User Agent string to tell the server to ignore the next request from, to prevent it from treating a preview scrape as a link click.
 @param forceLinkCreation Whether we should create a link from the Branch Key even if initSession failed. Defaults to NO.
 @warning This method makes a synchronous url request.
 @warning This method is primarily intended to be an internal Branch method, used to work around a bug with SLComposeViewController
 @warning This can fail if the alias is already taken.
 */
- (NSString *)getShortURLWithParams:(NSDictionary *)params andTags:(NSArray *)tags andChannel:(NSString *)channel andFeature:(NSString *)feature andStage:(NSString *)stage andCampaign:(NSString *)campaign andAlias:(NSString *)alias ignoreUAString:(NSString *)ignoreUAString forceLinkCreation:(BOOL)forceLinkCreation;

/**
 Get a short url with specified tags, params, channel, feature, stage, and type.
 
 @param params Dictionary of parameters to include in the link.
 @param tags An array of tags to associate with this link, useful for tracking.
 @param channel The channel for the link. Examples could be Facebook, Twitter, SMS, etc, depending on where it will be shared.
 @param feature The feature this is utilizing. Examples could be Sharing, Referring, Inviting, etc.
 @param stage The stage used for the generated link, indicating what part of a funnel the user is in.
 @param type The type of link this is, one of Single Use or Unlimited Use. Single use means once *per user*, not once period.
 @warning This method makes a synchronous url request.
 */
- (NSString *)getShortURLWithParams:(NSDictionary *)params andTags:(NSArray *)tags andChannel:(NSString *)channel andFeature:(NSString *)feature andStage:(NSString *)stage andType:(BranchLinkType)type;

/**
 Get a short url with specified tags, params, channel, feature, stage, and match duration. The usage type will default to unlimited.
 
 @param params Dictionary of parameters to include in the link.
 @param tags An array of tags to associate with this link, useful for tracking.
 @param channel The channel for the link. Examples could be Facebook, Twitter, SMS, etc, depending on where it will be shared.
 @param feature The feature this is utilizing. Examples could be Sharing, Referring, Inviting, etc.
 @param stage The stage used for the generated link, indicating what part of a funnel the user is in.
 @param duration How long to keep an unmatched link click in the Branch backend server's queue before discarding.
 @warning This method makes a synchronous url request.
 */
- (NSString *)getShortURLWithParams:(NSDictionary *)params andTags:(NSArray *)tags andChannel:(NSString *)channel andFeature:(NSString *)feature andStage:(NSString *)stage andMatchDuration:(NSUInteger)duration;

/**
 Get a short url with specified tags, params, channel, feature, stage, and match duration. The usage type will default to unlimited.
 
 @param params Dictionary of parameters to include in the link.
 @param tags An array of tags to associate with this link, useful for tracking.
 @param alias The alias for a link.
 @param channel The channel for the link. Examples could be Facebook, Twitter, SMS, etc, depending on where it will be shared.
 @param feature The feature this is utilizing. Examples could be Sharing, Referring, Inviting, etc.
 @param stage The stage used for the generated link, indicating what part of a funnel the user is in.
 @param duration How long to keep an unmatched link click in the Branch backend server's queue before discarding.
 @warning This method makes a synchronous url request.
 @warning This can fail if the alias is already taken.
 */
- (NSString *)getShortUrlWithParams:(NSDictionary *)params andTags:(NSArray *)tags andAlias:(NSString *)alias andChannel:(NSString *)channel andFeature:(NSString *)feature andStage:(NSString *)stage andMatchDuration:(NSUInteger)duration;


/**
 Get a short url with specified params, channel, feature, stage, campaign and match duration. The usage type will default to unlimited.
 
 @param params Dictionary of parameters to include in the link.
 @param tags An array of tags to associate with this link, useful for tracking.
 @param alias The alias for a link.
 @param channel The channel for the link. Examples could be Facebook, Twitter, SMS, etc, depending on where it will be shared.
 @param feature The feature this is utilizing. Examples could be Sharing, Referring, Inviting, etc.
 @param stage The stage used for the generated link, indicating what part of a funnel the user is in.
 @param campaign Use this field to organize the links by actual marketing campaign.
 @param duration How long to keep an unmatched link click in the Branch backend server's queue before discarding.
 @warning This method makes a synchronous url request.
 */
- (NSString *)getShortUrlWithParams:(NSDictionary *)params andTags:(NSArray *)tags andAlias:(NSString *)alias andChannel:(NSString *)channel andFeature:(NSString *)feature andStage:(NSString *)stage andCampaign:campaign andMatchDuration:(NSUInteger)duration;

#pragma mark - Long Url generation

///--------------------------
/// @name Long Url generation
///--------------------------

/**
 Construct a long url with specified params. The usage type will default to unlimited.
 
 @param params Dictionary of parameters to include in the link.
 */
- (NSString *)getLongURLWithParams:(NSDictionary *)params;

/**
 Get a long url with specified params and feature. The usage type will default to unlimited.
 
 @param params Dictionary of parameters to include in the link.
 @param feature The feature this is utilizing. Examples could be Sharing, Referring, Inviting, etc.
 */
- (NSString *)getLongURLWithParams:(NSDictionary *)params andFeature:(NSString *)feature;

/**
 Get a long url with specified params, feature, and stage. The usage type will default to unlimited.
 
 @param params Dictionary of parameters to include in the link.
 @param feature The feature this is utilizing. Examples could be Sharing, Referring, Inviting, etc.
 @param stage The stage used for the generated link, indicating what part of a funnel the user is in.
 */
- (NSString *)getLongURLWithParams:(NSDictionary *)params andFeature:(NSString *)feature andStage:(NSString *)stage;

/**
 Get a long url with specified params, feature, stage, and tags. The usage type will default to unlimited.
 
 @param params Dictionary of parameters to include in the link.
 @param feature The feature this is utilizing. Examples could be Sharing, Referring, Inviting, etc.
 @param stage The stage used for the generated link, indicating what part of a funnel the user is in.
 @param tags An array of tags to associate with this link, useful for tracking.
 */
- (NSString *)getLongURLWithParams:(NSDictionary *)params andFeature:(NSString *)feature andStage:(NSString *)stage andTags:(NSArray *)tags;

/**
 Get a long url with specified params, feature, stage, and alias. The usage type will default to unlimited.
 
 @param params Dictionary of parameters to include in the link.
 @param feature The feature this is utilizing. Examples could be Sharing, Referring, Inviting, etc.
 @param stage The stage used for the generated link, indicating what part of a funnel the user is in.
 @param alias The alias for a link.
 @warning This can fail if the alias is already taken.
 */
- (NSString *)getLongURLWithParams:(NSDictionary *)params andFeature:(NSString *)feature andStage:(NSString *)stage andAlias:(NSString *)alias;

/**
 Get a long url with specified params, channel, tags, feature, stage, and alias. The usage type will default to unlimited.
 
 @param params Dictionary of parameters to include in the link.
 @param channel The channel for the link. Examples could be Facebook, Twitter, SMS, etc, depending on where it will be shared.
 @param tags An array of tags to associate with this link, useful for tracking.
 @param feature The feature this is utilizing. Examples could be Sharing, Referring, Inviting, etc.
 @param stage The stage used for the generated link, indicating what part of a funnel the user is in.
 @param alias The alias for a link.
 @warning This can fail if the alias is already taken.
 */
- (NSString *)getLongURLWithParams:(NSDictionary *)params andChannel:(NSString *)channel andTags:(NSArray *)tags andFeature:(NSString *)feature andStage:(NSString *)stage andAlias:(NSString *)alias;

#pragma mark - Short Url Async methods

///----------------------------------------
/// @name Asynchronous Short Url Generation
///----------------------------------------

/**
 Get a short url without any items specified. The usage type will default to unlimited.
 
 @param callback Callback called with the url.
 */
- (void)getShortURLWithCallback:(callbackWithUrl)callback;

/**
 Get a short url with the specified params. The usage type will default to unlimited.
 
 @param params Dictionary of parameters to include in the link.
 @param callback Callback called with the url.
 */
- (void)getShortURLWithParams:(NSDictionary *)params andCallback:(callbackWithUrl)callback;

/**
 Get a short url with the specified params, channel, and feature. The usage type will default to unlimited.
 
 @param params Dictionary of parameters to include in the link.
 @param channel The channel for the link. Examples could be Facebook, Twitter, SMS, etc, depending on where it will be shared.
 @param feature The feature this is utilizing. Examples could be Sharing, Referring, Inviting, etc.
 @param callback Callback called with the url.
 */
- (void)getShortURLWithParams:(NSDictionary *)params andChannel:(NSString *)channel andFeature:(NSString *)feature andCallback:(callbackWithUrl)callback;

/**
 Get a short url with the specified params, channel, feature, and stage. The usage type will default to unlimited.
 
 @param params Dictionary of parameters to include in the link.
 @param channel The channel for the link. Examples could be Facebook, Twitter, SMS, etc, depending on where it will be shared.
 @param feature The feature this is utilizing. Examples could be Sharing, Referring, Inviting, etc.
 @param stage The stage used for the generated link, indicating what part of a funnel the user is in.
 @param callback Callback called with the url.
 */
- (void)getShortURLWithParams:(NSDictionary *)params andChannel:(NSString *)channel andFeature:(NSString *)feature andStage:(NSString *)stage andCallback:(callbackWithUrl)callback;

/**
 Get a short url with the specified params, channel, feature, stage, and alias. The usage type will default to unlimited.
 
 @param params Dictionary of parameters to include in the link.
 @param channel The channel for the link. Examples could be Facebook, Twitter, SMS, etc, depending on where it will be shared.
 @param feature The feature this is utilizing. Examples could be Sharing, Referring, Inviting, etc.
 @param stage The stage used for the generated link, indicating what part of a funnel the user is in.
 @param alias The alias for a link.
 @param callback Callback called with the url.
 @warning This can fail if the alias is already taken.
 */
- (void)getShortURLWithParams:(NSDictionary *)params andChannel:(NSString *)channel andFeature:(NSString *)feature andStage:(NSString *)stage andAlias:(NSString *)alias andCallback:(callbackWithUrl)callback;

/**
 Get a short url with the specified params, channel, feature, stage, and link type.
 
 @param params Dictionary of parameters to include in the link.
 @param channel The channel for the link. Examples could be Facebook, Twitter, SMS, etc, depending on where it will be shared.
 @param feature The feature this is utilizing. Examples could be Sharing, Referring, Inviting, etc.
 @param stage The stage used for the generated link, indicating what part of a funnel the user is in.
 @param type The type of link this is, one of Single Use or Unlimited Use. Single use means once *per user*, not once period.
 @param callback Callback called with the url.
 */
- (void)getShortURLWithParams:(NSDictionary *)params andChannel:(NSString *)channel andFeature:(NSString *)feature andStage:(NSString *)stage andType:(BranchLinkType)type andCallback:(callbackWithUrl)callback;

/**
 Get a short url with the specified params, channel, feature, stage, and match duration. The usage type will default to unlimited.
 
 @param params Dictionary of parameters to include in the link.
 @param channel The channel for the link. Examples could be Facebook, Twitter, SMS, etc, depending on where it will be shared.
 @param feature The feature this is utilizing. Examples could be Sharing, Referring, Inviting, etc.
 @param stage The stage used for the generated link, indicating what part of a funnel the user is in.
 @param duration How long to keep an unmatched link click in the Branch backend server's queue before discarding.
 @param callback Callback called with the url.
 */
- (void)getShortURLWithParams:(NSDictionary *)params andChannel:(NSString *)channel andFeature:(NSString *)feature andStage:(NSString *)stage andMatchDuration:(NSUInteger)duration andCallback:(callbackWithUrl)callback;

/**
 Get a short url with the specified params, tags, channel, feature, and stage. The usage type will default to unlimited.
 
 @param params Dictionary of parameters to include in the link.
 @param tags An array of tags to associate with this link, useful for tracking.
 @param channel The channel for the link. Examples could be Facebook, Twitter, SMS, etc, depending on where it will be shared.
 @param feature The feature this is utilizing. Examples could be Sharing, Referring, Inviting, etc.
 @param stage The stage used for the generated link, indicating what part of a funnel the user is in.
 @param callback Callback called with the url.
 */
- (void)getShortURLWithParams:(NSDictionary *)params andTags:(NSArray *)tags andChannel:(NSString *)channel andFeature:(NSString *)feature andStage:(NSString *)stage andCallback:(callbackWithUrl)callback;

/**
 Get a short url with the specified params, tags, channel, feature, stage, and alias. The usage type will default to unlimited.
 
 @param params Dictionary of parameters to include in the link.
 @param channel The channel for the link. Examples could be Facebook, Twitter, SMS, etc, depending on where it will be shared.
 @param tags An array of tags to associate with this link, useful for tracking.
 @param feature The feature this is utilizing. Examples could be Sharing, Referring, Inviting, etc.
 @param stage The stage used for the generated link, indicating what part of a funnel the user is in.
 @param alias The alias for a link.
 @param callback Callback called with the url.
 @warning This can fail if the alias is already taken.
 */
- (void)getShortURLWithParams:(NSDictionary *)params andTags:(NSArray *)tags andChannel:(NSString *)channel andFeature:(NSString *)feature andStage:(NSString *)stage andAlias:(NSString *)alias andCallback:(callbackWithUrl)callback;

/**
 Get a short url with the specified params, tags, channel, feature, stage, and link type.
 
 @param params Dictionary of parameters to include in the link.
 @param channel The channel for the link. Examples could be Facebook, Twitter, SMS, etc, depending on where it will be shared.
 @param tags An array of tags to associate with this link, useful for tracking.
 @param feature The feature this is utilizing. Examples could be Sharing, Referring, Inviting, etc.
 @param stage The stage used for the generated link, indicating what part of a funnel the user is in.
 @param type The type of link this is, one of Single Use or Unlimited Use. Single use means once *per user*, not once period.
 @param callback Callback called with the url.
 */
- (void)getShortURLWithParams:(NSDictionary *)params andTags:(NSArray *)tags andChannel:(NSString *)channel andFeature:(NSString *)feature andStage:(NSString *)stage andType:(BranchLinkType)type andCallback:(callbackWithUrl)callback;

/**
 Get a short url with the specified params, tags, channel, feature, stage, and match duration. The usage type will default to unlimited.
 
 @param params Dictionary of parameters to include in the link.
 @param channel The channel for the link. Examples could be Facebook, Twitter, SMS, etc, depending on where it will be shared.
 @param tags An array of tags to associate with this link, useful for tracking.
 @param feature The feature this is utilizing. Examples could be Sharing, Referring, Inviting, etc.
 @param stage The stage used for the generated link, indicating what part of a funnel the user is in.
 @param duration How long to keep an unmatched link click in the Branch backend server's queue before discarding.
 @param callback Callback called with the url.
 */
- (void)getShortURLWithParams:(NSDictionary *)params andTags:(NSArray *)tags andChannel:(NSString *)channel andFeature:(NSString *)feature andStage:(NSString *)stage andMatchDuration:(NSUInteger)duration andCallback:(callbackWithUrl)callback;

/**
 Get a short url with the specified params, tags, channel, feature, stage, and match duration. The usage type will default to unlimited.
 
 @param params Dictionary of parameters to include in the link.
 @param channel The channel for the link. Examples could be Facebook, Twitter, SMS, etc, depending on where it will be shared.
 @param tags An array of tags to associate with this link, useful for tracking.
 @param feature The feature this is utilizing. Examples could be Sharing, Referring, Inviting, etc.
 @param stage The stage used for the generated link, indicating what part of a funnel the user is in.
 @param duration How long to keep an unmatched link click in the Branch backend server's queue before discarding.
 @param callback Callback called with the url.
 @param alias The alias for a link.
 @warning This can fail if the alias is already taken.
 */
- (void)getShortUrlWithParams:(NSDictionary *)params andTags:(NSArray *)tags andAlias:(NSString *)alias andMatchDuration:(NSUInteger)duration andChannel:(NSString *)channel andFeature:(NSString *)feature andStage:(NSString *)stage andCallback:(callbackWithUrl)callback;

/**
 Get a short url with the specified params, tags, channel, feature, stage, campaign and match duration. The usage type will default to unlimited.
 
 @param params Dictionary of parameters to include in the link.
 @param channel The channel for the link. Examples could be Facebook, Twitter, SMS, etc, depending on where it will be shared.
 @param tags An array of tags to associate with this link, useful for tracking.
 @param feature The feature this is utilizing. Examples could be Sharing, Referring, Inviting, etc.
 @param stage The stage used for the generated link, indicating what part of a funnel the user is in.
 @param duration How long to keep an unmatched link click in the Branch backend server's queue before discarding.
 @param campaign Use this field to organize the links by actual marketing campaign.
 @param callback Callback called with the url.
 @param alias The alias for a link.
 @warning This can fail if the alias is already taken.
 */
- (void)getShortUrlWithParams:(NSDictionary *)params andTags:(NSArray *)tags andAlias:(NSString *)alias andMatchDuration:(NSUInteger)duration andChannel:(NSString *)channel andFeature:(NSString *)feature andStage:(NSString *)stage andCampaign:(NSString *)campaign andCallback:(callbackWithUrl)callback;

- (void)getSpotlightUrlWithParams:(NSDictionary *)params callback:(callbackWithParams)callback;

#pragma mark - Content Discovery methods

///--------------------------------
/// @name Content Discovery methods
///--------------------------------

/**
 Take the current screen and make it discoverable, adding it to Apple's Core Spotlight index. It will not be public by default. Type defaults to kUTTypeImage.
 
 @param title Title for the spotlight preview item.
 @param description Description for the spotlight preview item.
 @warning These functions are only usable on iOS 9 or above. Earlier versions will simply receive the callback with an error.
 */
- (void)createDiscoverableContentWithTitle:(NSString *)title description:(NSString *)description;

/**
 Take the current screen and make it discoverable, adding it to Apple's Core Spotlight index. It will not be public by default. Type defaults to kUTTypeImage.
 
 @param title Title for the spotlight preview item.
 @param description Description for the spotlight preview item.
 @param callback Callback called with the Branch url this will fallback to.
 @warning These functions are only usable on iOS 9 or above. Earlier versions will simply receive the callback with an error.
 */
- (void)createDiscoverableContentWithTitle:(NSString *)title description:(NSString *)description callback:(callbackWithUrl)callback;

/**
 Take the current screen and make it discoverable, adding it to Apple's Core Spotlight index. Will be public if specified. Type defaults to kUTTypeImage.
 
 @param title Title for the spotlight preview item.
 @param description Description for the spotlight preview item.
 @param publiclyIndexable Whether or not this item should be added to Apple's public search index.
 @param callback Callback called with the Branch url this will fallback to.
 @warning These functions are only usable on iOS 9 or above. Earlier versions will simply receive the callback with an error.
 */
- (void)createDiscoverableContentWithTitle:(NSString *)title description:(NSString *)description publiclyIndexable:(BOOL)publiclyIndexable callback:(callbackWithUrl)callback;

/**
 Take the current screen and make it discoverable, adding it to Apple's Core Spotlight index. Will be public if specified. You can override the type as desired, using one of the types provided in MobileCoreServices.
 
 @param title Title for the spotlight preview item.
 @param description Description for the spotlight preview item.
 @param type The type to use for the NSUserActivity, taken from the list of constants provided in the MobileCoreServices framework.
 @param publiclyIndexable Whether or not this item should be added to Apple's public search index.
 @param callback Callback called with the Branch url this will fallback to.
 @warning These functions are only usable on iOS 9 or above. Earlier versions will simply receive the callback with an error.
 */
- (void)createDiscoverableContentWithTitle:(NSString *)title description:(NSString *)description type:(NSString *)type publiclyIndexable:(BOOL)publiclyIndexable callback:(callbackWithUrl)callback;

/**
 Take the current screen and make it discoverable, adding it to Apple's Core Spotlight index. Will be public if specified. You can override the type as desired, using one of the types provided in MobileCoreServices.
 
 @param title Title for the spotlight preview item.
 @param description Description for the spotlight preview item.
 @param thumbnailUrl Url to an image to be used for the thumnbail in spotlight.
 @param type The type to use for the NSUserActivity, taken from the list of constants provided in the MobileCoreServices framework.
 @param publiclyIndexable Whether or not this item should be added to Apple's public search index.
 @param callback Callback called with the Branch url this will fallback to.
 @warning These functions are only usable on iOS 9 or above. Earlier versions will simply receive the callback with an error.
 */
- (void)createDiscoverableContentWithTitle:(NSString *)title description:(NSString *)description thumbnailUrl:(NSURL *)thumbnailUrl type:(NSString *)type publiclyIndexable:(BOOL)publiclyIndexable callback:(callbackWithUrl)callback;

/**
 Take the current screen and make it discoverable, adding it to Apple's Core Spotlight index. Will be public if specified. You can override the type as desired, using one of the types provided in MobileCoreServices.
 
 @param title Title for the spotlight preview item.
 @param description Description for the spotlight preview item.
 @param publiclyIndexable Whether or not this item should be added to Apple's public search index.
 @param thumbnailUrl Url to an image to be used for the thumnbail in spotlight.
 @param type The type to use for the NSUserActivity, taken from the list of constants provided in the MobileCoreServices framework.
 @param keywords A set of keywords to be used in Apple's search index.
 @param callback Callback called with the Branch url this will fallback to.
 @warning These functions are only usable on iOS 9 or above. Earlier versions will simply receive the callback with an error.
 */
- (void)createDiscoverableContentWithTitle:(NSString *)title description:(NSString *)description thumbnailUrl:(NSURL *)thumbnailUrl type:(NSString *)type publiclyIndexable:(BOOL)publiclyIndexable keywords:(NSSet *)keywords callback:(callbackWithUrl)callback;

/**
 Take the current screen and make it discoverable, adding it to Apple's Core Spotlight index. Will be public if specified. You can override the type as desired, using one of the types provided in MobileCoreServices.
 
 @param title Title for the spotlight preview item.
 @param description Description for the spotlight preview item.
 @param thumbnailUrl Url to an image to be used for the thumnbail in spotlight.
 @param linkParams Additional params to be added to the NSUserActivity. These will also be added to the Branch link.
 @param publiclyIndexable Whether or not this item should be added to Apple's public search index.
 @param keywords A set of keywords to be used in Apple's search index.
 @warning These functions are only usable on iOS 9 or above. Earlier versions will simply receive the callback with an error.
 */
- (void)createDiscoverableContentWithTitle:(NSString *)title description:(NSString *)description thumbnailUrl:(NSURL *)thumbnailUrl linkParams:(NSDictionary *)linkParams publiclyIndexable:(BOOL)publiclyIndexable keywords:(NSSet *)keywords;

/**
 Take the current screen and make it discoverable, adding it to Apple's Core Spotlight index. Will be public if specified. You can override the type as desired, using one of the types provided in MobileCoreServices.
 
 @param title Title for the spotlight preview item.
 @param description Description for the spotlight preview item.
 @param thumbnailUrl Url to an image to be used for the thumnbail in spotlight.
 @param linkParams Additional params to be added to the NSUserActivity. These will also be added to the Branch link.
 @param type The type to use for the NSUserActivity, taken from the list of constants provided in the MobileCoreServices framework.
 @param publiclyIndexable Whether or not this item should be added to Apple's public search index.
 @param keywords A set of keywords to be used in Apple's search index.
 @warning These functions are only usable on iOS 9 or above. Earlier versions will simply receive the callback with an error.
 */
- (void)createDiscoverableContentWithTitle:(NSString *)title description:(NSString *)description thumbnailUrl:(NSURL *)thumbnailUrl linkParams:(NSDictionary *)linkParams type:(NSString *)type publiclyIndexable:(BOOL)publiclyIndexable keywords:(NSSet *)keywords;

/**
 Take the current screen and make it discoverable, adding it to Apple's Core Spotlight index. Will be public if specified. You can override the type as desired, using one of the types provided in MobileCoreServices.
 
 @param title Title for the spotlight preview item.
 @param description Description for the spotlight preview item.
 @param thumbnailUrl Url to an image to be used for the thumnbail in spotlight.
 @param type The type to use for the NSUserActivity, taken from the list of constants provided in the MobileCoreServices framework.
 @param publiclyIndexable Whether or not this item should be added to Apple's public search index.
 @param keywords A set of keywords to be used in Apple's search index.
 @warning These functions are only usable on iOS 9 or above. Earlier versions will simply receive the callback with an error.
 */
- (void)createDiscoverableContentWithTitle:(NSString *)title description:(NSString *)description thumbnailUrl:(NSURL *)thumbnailUrl type:(NSString *)type publiclyIndexable:(BOOL)publiclyIndexable keywords:(NSSet *)keywords;

/**
 Take the current screen and make it discoverable, adding it to Apple's Core Spotlight index. Will be public if specified. You can override the type as desired, using one of the types provided in MobileCoreServices.
 
 @param title Title for the spotlight preview item.
 @param description Description for the spotlight preview item.
 @param thumbnailUrl Url to an image to be used for the thumnbail in spotlight.
 @param publiclyIndexable Whether or not this item should be added to Apple's public search index.
 @param linkParams A set of keywords to be used in Apple's search index.
 @warning These functions are only usable on iOS 9 or above. Earlier versions will simply receive the callback with an error.
 */
- (void)createDiscoverableContentWithTitle:(NSString *)title description:(NSString *)description thumbnailUrl:(NSURL *)thumbnailUrl linkParams:(NSDictionary *)linkParams publiclyIndexable:(BOOL)publiclyIndexable;

/**
 Take the current screen and make it discoverable, adding it to Apple's Core Spotlight index. Will be public if specified. You can override the type as desired, using one of the types provided in MobileCoreServices.
 
 @param title Title for the spotlight preview item.
 @param description Description for the spotlight preview item.
 @param thumbnailUrl Url to an image to be used for the thumnbail in spotlight.
 @param linkParams Additional params to be added to the NSUserActivity. These will also be added to the Branch link.
 @param publiclyIndexable Whether or not this item should be added to Apple's public search index.
 @param type The type to use for the NSUserActivity, taken from the list of constants provided in the MobileCoreServices framework.
 @param keywords A set of keywords to be used in Apple's search index.
 @param callback Callback called with the Branch url this will fallback to.
 @warning These functions are only usable on iOS 9 or above. Earlier versions will simply receive the callback with an error.
 */

- (void)createDiscoverableContentWithTitle:(NSString *)title description:(NSString *)description thumbnailUrl:(NSURL *)thumbnailUrl linkParams:(NSDictionary *)linkParams type:(NSString *)type publiclyIndexable:(BOOL)publiclyIndexable keywords:(NSSet *)keywords callback:(callbackWithUrl)callback;
/**
 Take the current screen and make it discoverable, adding it to Apple's Core Spotlight index. Will be public if specified. You can override the type as desired, using one of the types provided in MobileCoreServices.
 
 @param title Title for the spotlight preview item.
 @param description Description for the spotlight preview item.
 @param thumbnailUrl Url to an image to be used for the thumnbail in spotlight.
 @param linkParams Additional params to be added to the NSUserActivity. These will also be added to the Branch link.
 @param publiclyIndexable Whether or not this item should be added to Apple's public search index.
 @param type The type to use for the NSUserActivity, taken from the list of constants provided in the MobileCoreServices framework.
 @param keywords A set of keywords to be used in Apple's search index.
 @param expirationDate ExpirationDate after which this will not appear in Apple's search index.
 @param callback Callback called with the Branch url this will fallback to.
 @warning These functions are only usable on iOS 9 or above. Earlier versions will simply receive the callback with an error.
 */
- (void)createDiscoverableContentWithTitle:(NSString *)title description:(NSString *)description thumbnailUrl:(NSURL *)thumbnailUrl linkParams:(NSDictionary *)linkParams type:(NSString *)type publiclyIndexable:(BOOL)publiclyIndexable keywords:(NSSet *)keywords expirationDate:(NSDate *)expirationDate callback:(callbackWithUrl)callback;

/**
 Take the current screen and make it discoverable, adding it to Apple's Core Spotlight index. Will be public if specified. You can override the type as desired, using one of the types provided in MobileCoreServices.
 
 @param title Title for the spotlight preview item.
 @param description Description for the spotlight preview item.
 @param thumbnailUrl Url to an image to be used for the thumnbail in spotlight.
 @param linkParams Additional params to be added to the NSUserActivity. These will also be added to the Branch link.
 @param publiclyIndexable Whether or not this item should be added to Apple's public search index.
 @param type The type to use for the NSUserActivity, taken from the list of constants provided in the MobileCoreServices framework.
 @param keywords A set of keywords to be used in Apple's search index.
 @param expirationDate ExpirationDate after which this will not appear in Apple's search index.
 @param spotlightCallback Callback called with the Branch url this will fallback to.
 @warning These functions are only usable on iOS 9 or above. Earlier versions will simply receive the callback with an error.
 */
- (void)createDiscoverableContentWithTitle:(NSString *)title description:(NSString *)description thumbnailUrl:(NSURL *)thumbnailUrl linkParams:(NSDictionary *)linkParams type:(NSString *)type publiclyIndexable:(BOOL)publiclyIndexable keywords:(NSSet *)keywords expirationDate:(NSDate *)expirationDate spotlightCallback:(callbackWithUrlAndSpotlightIdentifier)spotlightCallback;

/**
 Method for creating a one of Branch instance and specifying its dependencies.
 
 @warning This is meant for use internally only (exposed for the sake of testing) and should not be used by apps.
 */
- (id)initWithInterface:(BNCServerInterface *)interface queue:(BNCServerRequestQueue *)queue cache:(BNCLinkCache *)cache preferenceHelper:(BNCPreferenceHelper *)preferenceHelper key:(NSString *)key;

/**
 Method used by BranchUniversalObject to register a view on content
 
 @warning This is meant for use internally only and should not be used by apps.
 */
- (void)registerViewWithParams:(NSDictionary *)params andCallback:(callbackWithParams)callback;

@end
