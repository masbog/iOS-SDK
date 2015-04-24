//
//   ______     _   _                 _          _____ _____  _  __
//  |  ____|   | | (_)               | |        / ____|  __ \| |/ /
//  | |__   ___| |_ _ _ __ ___   ___ | |_ ___  | (___ | |  | | ' /
//  |  __| / __| __| | '_ ` _ \ / _ \| __/ _ \  \___ \| |  | |  <
//  | |____\__ \ |_| | | | | | | (_) | ||  __/  ____) | |__| | . \
//  |______|___/\__|_|_| |_| |_|\___/ \__\___| |_____/|_____/|_|\_\
//
//
//  Version: 3.2.1
//  Copyright (c) 2015 Estimote. All rights reserved.

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <CoreBluetooth/CoreBluetooth.h>
#import "ESTBeaconDefinitions.h"

@class ESTBeaconConnection;

enum
{
    ESTConnectionInternetConnectionError,
    ESTConnectionIdentifierMissingError,
    ESTConnectionNotAuthorizedError,
    ESTConnectionNotConnectedToReadWrite
};

/**
 * The `ESTBeaconConnectionDelegate` protocol defines the delegate methods used to receive updates about `<ESTBeaconConnection>` connection status, as well as sensor related updates once a connection to the beacon has been established.
 */

@protocol ESTBeaconConnectionDelegate <NSObject>

@optional

/**
 * Tells the delegate that an attempt to connect to a beacon succeeded and the connection has been established.
 *
 * @param connection The beacon connection object reporting the event.
 */
- (void)beaconConnectionDidSucceed:(ESTBeaconConnection *)connection;

/**
 * Tells the delegate that an attempt to connect to a beacon has failed.
 *
 * @param connection The beacon connection object reporting the event.
 * @param error An error object containing the error code that indicates why connection failed.
 */
- (void)beaconConnection:(ESTBeaconConnection *)connection didFailWithError:(NSError *)error;

/**
 * Tells the delegate that a previously connected beacon has disconnected.
 *
 * @param connection The beacon connection object reporting the event.
 * @param error An error object containing the error code that indicates why the beacon disconnected.
 */
- (void)beaconConnection:(ESTBeaconConnection *)connection didDisconnectWithError:(NSError *)error;

/**
 * Tells the delegate that a beacon's `<[ESTBeaconConnection motionState]>` value has changed.
 *
 * @param connection The beacon connection object reporting the event.
 * @param state The new `motionState` value.
 */
- (void)beaconConnection:(ESTBeaconConnection *)connection motionStateChanged:(ESTBeaconMotionState)state;

@end

/**
 * The `ESTBeaconConnection` class defines the interface for interacting with a single Estimote beacon. It enables you to connect to the device, retrieve properties and change its configuration settings.
 *
 * The ESTBeaconConnection instance can be initialized using CLBeacon object or mac address being unique identifier of particular device. Fetch required beacon details you can use:
 *
 * - `startRangingBeaconsInRegion:` - which is a CoreLocation based scan and delivers `CLBeacon` objects.
 *
 * - `startEstimoteBeaconsDiscovery` - which is a CoreBluetooth based scan and delivers `ESTBluetoothBeacon` object containing mac address.
 *
 * Properties become editable once connected to the beacon. See connect for more details about connecting to the beacon. You will also need to assign a delegate to be notified about connection and disconnection events. The delegate needs to conform to the `<ESTBeaconConnectionDelegate>` protocol.
 */

@interface ESTBeaconConnection : NSObject

/**
 *  Delegate object receiving callbacks.
 */
@property (nonatomic, weak) id<ESTBeaconConnectionDelegate> delegate;

/**
 * Identifier of the device that you aim to connect. 
 * Based on the method you used to initialize it may contain:
 * - Device Mac address
 * - Device iBeacon properties formatted as follows: ProximityUUUID:Major:Minor
 *
 */
@property (nonatomic, strong, readonly) NSString *identifier;

/**
 * The connection status between the user device and the beacon.
 *
 */
@property (readonly, nonatomic) ESTConnectionStatus connectionStatus;

/**
 *  Static method initializing connection object with Estimote beacon
 *
 *  @param proximityUUID discovered beacons Proximity UUID
 *  @param major discovered beacons Major
 *  @param minor discovered beacons Minor
 *  @param delegate delegate reference
 *
 *  @return beacon connection object
 */
+ (instancetype)connectionWithProximityUUID:(NSUUID *)proximityUUID
                                      major:(CLBeaconMajorValue)major
                                      minor:(CLBeaconMinorValue)minor
                              delegate:(id<ESTBeaconConnectionDelegate>)delegate;

/**
 *  Static method initializing connection object with Estimote beacon
 *
 *  @param beacon discovered beacon
 *  @param delegate delegate reference
 *
 *  @return beacon connection object
 */
+ (instancetype)connectionWithBeacon:(CLBeacon *)beacon
                            delegate:(id<ESTBeaconConnectionDelegate>)delegate;

/**
 *  Static method initializing connection object with Estimote beacon
 *
 *  @param macAddress discovered beacon object MAC address
 *  @param delegate delegate reference
 *
 *  @return beacon connection object
 */
+ (instancetype)connectionWithMacAddress:(NSString *)macAddress
                                delegate:(id<ESTBeaconConnectionDelegate>)delegate;

/**
 *  Method initializing connection object with Estimote beacon with
 *  delegate object support
 *
 *  @param proximityUUID discovered beacons Proximity UUID
 *  @param major discovered beacons Major
 *  @param minor discovered beacons Minor
 *  @param delegate delegate to handle callbacks
 *  @param startImmediately indicates if created object should start connection immediately
 *
 *  @return beacon connection object
 */
- (instancetype)initWithProximityUUID:(NSUUID *)proximityUUID
                                major:(CLBeaconMajorValue)major
                                minor:(CLBeaconMinorValue)minor
                             delegate:(id<ESTBeaconConnectionDelegate>)delegate
                     startImmediately:(BOOL)startImmediately;

/**
 *  Method initializing connection object with Estimote beacon with
 *  delegate object support
 *
 *  @param beacon discovered beacon
 *  @param delegate delegate to handle callbacks
 *  @param startImmediately indicates if created object should start connection immediately
 *
 *  @return beacon connection object
 */
- (instancetype)initWithBeacon:(CLBeacon *)beacon
                      delegate:(id<ESTBeaconConnectionDelegate>)delegate
              startImmediately:(BOOL)startImmediately;

/**
 *  Method initializing connection object with beacon with
 *  delegate object support
 *
 *  @param macAddress discovered beacon object MAC address
 *  @param delegate delegate to handle callbacks
 *  @param startImmediately indicates if created object should start connection immediately
 *
 *  @return beacon connection object
 */
- (instancetype)initWithMacAddress:(NSString *)macAddress
                          delegate:(id<ESTBeaconConnectionDelegate>)delegate
                  startImmediately:(BOOL)startImmediately;


#pragma mark Connection handling
///--------------------------------------------------------------------
/// @name Connection handling
///--------------------------------------------------------------------

/**
 *  Initiates connection procedure
 */
- (void)startConnection;


/**
 *  Initiates connection procedure with additional params
 *
 *  @param attempts number of connection attempts
 *  @param timeout  timeout of single connection
 */
- (void)startConnectionWithAttempts:(NSInteger)attempts
                  connectionTimeout:(NSInteger)timeout;

/**
 *  Cancels connection procedure
 */
- (void)cancelConnection;

/**
 *  Performs disconnect procedure for connected device.
 */
- (void)disconnect;


#pragma mark - Device identification
///--------------------------------------------------------------------
/// @name Device identification
///--------------------------------------------------------------------

/**
 * The MAC address of the beacon.
 */
@property (readonly, nonatomic) NSString *macAddress;

/**
 * The name of the beacon.
 *
 * This value is stored and retrieved from the Estimote Cloud.
 */
@property (readonly, nonatomic) NSString *name;

/**
 * The color of the beacon.
 *
 * This value is stored and retrieved from the Estimote Cloud, which means it might be unavailable under certain circumstances - e.g. no Internet connectivity.
 *
 */
@property (readonly, nonatomic) ESTColor color;

/**
 *  The underlying Bluetooth peripheral device.
 */
@property (readonly, nonatomic) CBPeripheral *peripheral;

#pragma mark - iBeacon settings
///--------------------------------------------------------------------
/// @name iBeacon settings
///--------------------------------------------------------------------

/**
 * The proximity ID of the beacon.
 *
 * @see writeProximityUUID:completion:
 */
@property (readonly, nonatomic) NSUUID *proximityUUID;

/**
 * The proximity ID of the beacon when it's in motion.
 *
 * This default to the same value as the `<proximityUUID>`. Setting it to a different value enables you to detect whether a beacon is in motion or not without a need to connect to the beacon. This can be achieved in two ways:
 *
 * 1. When ranging beacons - if the beacon is in motion, the `proximityUUID` property will be equal to the `motionProximityUUID`. Note that the `motionProximityUUID` property is not available unless connected to the beacon, so you need to know its value in advance.
 *
 * 2. When monitoring regions - you can have two separate regions, one with the regular `proximityUUID` and one with the `motionProximityUUID`. Enter and exit notifications will then correspond to the beacon starting and stopping to move.
 *
 * @warning This feature is disabled by default. The option to enable it will be made available in an upcoming update to the SDK.
 *
 * @since Estimote OS 2.0
 *
 */
@property (readonly, nonatomic) NSUUID *motionProximityUUID;

/**
 * The most significant value in the beacon.
 *
 * @see writeMajor:completion:
 */
@property (readonly, nonatomic) NSNumber *major;

/**
 * The least significant value in the beacon.
 *
 * @see writeMinor:completion:
 */
@property (readonly, nonatomic) NSNumber *minor;

/**
 * The power of the beacon's radio signal in dBm.
 *
 * This is a `char` value, so the proper way to retrieve it is `[beacon.power charValue]`.
 *
 * @see writePower:completion:
 */
@property (readonly, nonatomic) NSNumber *power;

/**
 * The advertising interval of the beacon in ms.
 *
 * @see writeAdvInterval:completion:
 */
@property (readonly, nonatomic) NSNumber *advInterval;

#pragma mark - Hardware and software information

/**
 * The hardware version of the beacon.
 */
@property (readonly, nonatomic) NSString *hardwareVersion;

/**
 * The firmware version of the beacon.
 *
 * @see checkFirmwareUpdateWithCompletion:
 * @see updateFirmwareWithProgress:completion:
 */
@property (readonly, nonatomic) NSString *firmwareVersion;

#pragma mark - Power management
///--------------------------------------------------------------------
/// @name Power management
///--------------------------------------------------------------------

/**
 * The battery charge level for the beacon.
 *
 * Battery level ranges from 0 (fully discharged) to 100 (fully charged).
 */
@property (readonly, nonatomic) NSNumber *batteryLevel;

/**
 * The battery model.
 *
 * @see ESTBeaconBatteryType
 */
@property (readonly, nonatomic) ESTBeaconBatteryType batteryType;

/**
 *    Remaining lifetime in days, based on current battery level, advertising interval and broadcasting power values
 */
@property (readonly, nonatomic) NSNumber *remainingLifetime;

/**
 * A flag indicating availability and status of the Basic Power Mode.
 *
 * @since Estimote OS A2.1
 *
 * @see ESTBeaconPowerSavingMode
 */
@property (readonly, nonatomic) ESTBeaconPowerSavingMode basicPowerMode;

/**
 * A flag indicating availability and status of the Smart Power Mode.
 *
 * @since Estimote OS A2.1
 *
 * @see ESTBeaconPowerSavingMode
 */
@property (readonly, nonatomic) ESTBeaconPowerSavingMode smartPowerMode;

/**
 *  A flag indicating status of Estimote Secure UUID.
 *
 *  @since Estimote OS 2.2
 *  @see ESTBeaconEstimoteSecureUUID
 */
@property (readonly, nonatomic) ESTBeaconEstimoteSecureUUID estimoteSecureUUIDState;

/**
 * A flag indicating if motion UUID is enabled.
 *
 * @since Estimote OS A2.1
 *
 * @see writeMotionUUIDEnabled:completion:
 */
@property (readonly, nonatomic) ESTBeaconMotionUUID motionUUIDState;

#pragma mark - Sensors handling
///--------------------------------------------------------------------
/// @name Sensors handling
///--------------------------------------------------------------------

/**
 * A flag indicating if the beacon is in motion or not.
 *
 * This value changes:
 *
 * - from NO to YES immediately after a still beacon starts moving,
 *
 * - from YES to NO after a beacon stops moving and remains still for 2 seconds.
 *
 */
@property (readonly, nonatomic) ESTBeaconMotionState motionState;

/**
 *  State of temperature sensor.
 */
@property (readonly, nonatomic) ESTBeaconTemperatureState temperatureState;

/**
 * A flag indicating which type of broadcasting is enabled
 *
 * @since Estimote OS A3.0.0
 *
 * @see writeConditionalBroadcastingType:completion:
 */
@property (readonly, nonatomic) ESTBeaconConditionalBroadcasting conditionalBroadcastingState;

/**
 * A flag indicating if accelerometer is enabled.
 *
 * @since Estimote OS A2.1
 *
 * @see writeMotionDetectionEnabled:completion:
 */
@property (readonly, nonatomic) ESTBeaconMotionDetection motionDetectionState;

#pragma mark - Reading methods for sensors
///--------------------------------------------------------------------
/// @name Reading methods for sensors
///--------------------------------------------------------------------

/**
 * Retrieves the temperature of surrounding environment reported by the beacon.
 *
 * @param completion A block that is called when the temperature has been retrieved from the beacon.
 *
 * The completion block receives the following parameters:
 *
 * - `NSNumber *value` - The temperature in Celsius degrees.
 *
 * - `NSError *error` - If an error occurred, this error object describes the error. If the operation completed successfully, the value is `nil`.
 *
 * @see writeCalibratedTemperature:completion:
 */
- (void)readTemperatureWithCompletion:(ESTNumberCompletionBlock)completion;

/**
 * Retrieves the number of times the beacon has been in motion since the last `<resetAccelerometerCountWithCompletion:>`.
 *
 * @param completion A block that is called when the counter has been retrieved.
 *
 * The completion block receives the following parameters:
 *
 * - `NSNumber *value` - The value of the counter.
 *
 * - `NSError *error` - If an error occurred, this error object describes the error. If the operation completed successfully, the value is `nil`.
 */
- (void)readAccelerometerCountWithCompletion:(ESTNumberCompletionBlock)completion;

/**
 * Resets the counter - number of times the beacon has been in motion since the last reset.
 *
 * @param completion A block that is called when the counter has been reset.
 *
 * The completion block receives the following parameters:
 *
 * - `NSNumber *value` - The new value of the counter.
 *
 * - `NSError *error` - If an error occurred, this error object describes the error. If the operation completed successfully, the value is `nil`.
 */
- (void)resetAccelerometerCountWithCompletion:(ESTUnsignedShortCompletionBlock)completion;

#pragma mark - Writing methods for iBeacon settings
///--------------------------------------------------------------------
/// @name Writing methods for iBeacon settings
///--------------------------------------------------------------------

/**
 * Sets the `<name>` of the beacon.
 *
 * @param name The new name of the beacon.
 * @param completion A block that is called when the new name has been set.
 *
 * The completion block receives the following parameters:
 *
 * - `NSString *value` - The new name of the beacon.
 *
 * - `NSError *error` - If an error occurred, this error object describes the error. If the operation completed successfully, the value is `nil`.
 */
- (void)writeName:(NSString *)name completion:(ESTStringCompletionBlock)completion;

/**
 * Sets the `<proximityUUID>`.
 *
 * @param pUUID The new `proximityUUID`.
 * @param completion A block that is called when the new `proximityUUID` has been set.
 *
 * The completion block receives the following parameters:
 *
 * - `NSString *value` - The new `proximityUUID`.
 *
 * - `NSError *error` - If an error occurred, this error object describes the error. If the operation completed successfully, the value is `nil`.
 *
 * @warning If you change the `proximityUUID`, you might want to consider changing the `<motionProximityUUID>` as well. If you don't, the beacon will broadcast two different `proximityUUIDs` depending on whether its in motion or not!@
 */
- (void)writeProximityUUID:(NSString *)pUUID completion:(ESTStringCompletionBlock)completion;

/**
 * Sets the `<major>` value.
 *
 * @param major The new `major` value.
 * @param completion A block that is called when the new `major` value has been set.
 *
 * The completion block receives the following parameters:
 *
 * - `unsigned short value` - The new `major` value.
 *
 * - `NSError *error` - If an error occurred, this error object describes the error. If the operation completed successfully, the value is `nil`.
 */
- (void)writeMajor:(unsigned short)major completion:(ESTUnsignedShortCompletionBlock)completion;

/**
 * Sets the `<minor>` value.
 *
 * @param minor The new `minor` value.
 * @param completion A block that is called when the new `minor` value has been set.
 *
 * The completion block receives the following parameters:
 *
 * - `unsigned short value` - The new `minor` value.
 *
 * - `NSError *error` - If an error occurred, this error object describes the error. If the operation completed successfully, the value is `nil`.
 */
- (void)writeMinor:(unsigned short)minor completion:(ESTUnsignedShortCompletionBlock)completion;

/**
 * Sets the advertising interval, i.e. `<advInterval>`.
 *
 * @param interval The new `advInterval` in milliseconds. The value must be in range from 100 to 2000.
 * @param completion A block that is called when the new `advInterval` has been set.
 *
 * The completion block receives the following parameters:
 *
 * - `unsigned short value` - The new `advInterval`.
 *
 * - `NSError *error` - If an error occurred, this error object describes the error. If the operation completed successfully, the value is `nil`.
 */
- (void)writeAdvInterval:(unsigned short)interval completion:(ESTUnsignedShortCompletionBlock)completion;

/**
 * Sets the broadcasting `<power>`.
 *
 * @param power The new broadcasting `power`. Must be one of the <ESTBeaconPower> values.
 * @param completion A block that is called when the new broadcasting power has been set.
 *
 * The completion block receives the following parameters:
 *
 * - `ESTBeaconPower value` - The new broadcasting `power`.
 * - `NSError *error` - If an error occurred, this error object describes the error. If the operation completed successfully, the value is `nil`.
 */
- (void)writePower:(ESTBeaconPower)power completion:(ESTPowerCompletionBlock)completion;

#pragma mark - Writing methods for power management
///--------------------------------------------------------------------
/// @name Writing methods for power management
///--------------------------------------------------------------------

/**
 * Enables or disables the `<basicPowerMode>`.
 *
 * @param enable YES to enable, NO to disable the Basic Power Mode.
 * @param completion A block that is called when the Basic Power Mode has been enabled or disabled.
 *
 * The completion block receives the following parameters:
 *
 * - `BOOL value` - YES if the Basic Power Mode has been enabled, NO if the Basic Power Mode has been disabled.
 *
 * - `NSError *error` - If an error occurred, this error object describes the error. If the operation completed successfully, the value is `nil`.
 */
- (void)writeBasicPowerModeEnabled:(BOOL)enable
                        completion:(ESTBoolCompletionBlock)completion;

/**
 * Enables or disables the `<smartPowerMode>`.
 *
 * @param enable YES to enable, NO to disable the Smart Power Mode.
 * @param completion A block that is called when the Smart Power Mode has been enabled or disabled.
 *
 * The completion block receives the following parameters:
 *
 * - `BOOL value` - YES if the Smart Power Mode has been enabled, NO if the Smart Power Mode has been disabled.
 *
 * - `NSError *error` - If an error occurred, this error object describes the error. If the operation completed successfully, the value is `nil`.
 */
- (void)writeSmartPowerModeEnabled:(BOOL)enable
                        completion:(ESTBoolCompletionBlock)completion;

/**
 *  Changes the conditional broadcasting type. Note that the accelerometer must be enabled for this feature to work
 *  i.e. you must set Motion Detection Flag in order to use this feature.
 *  Possible options are:
 *  - ESTBeaconConditionalBroadcastingOff - the default mode, beacon is broadcasting all the time
 *  - ESTBeaconConditionalBroadcastingMotionOnly – beacon only advertises when it's in motion.
 *    Note that UUID used in advertising packet depends on Motion UUID Flag state.
 *  - ESTBeaconConditionalBroadcastingFlipToStop – beacon does not advertise when it's stationary and facing gecko pad up.
 *    If the beacon is moving or oriented differently it acts normally.
 *
 *  @since Estimote OS A3.0.0
 *
 *  @param conditionalBroadcasting Conditional broadcasting mode to be set in the beacon.
 *  @param completion A block that is called when the belly mode has been enabled or disabled.
 *
 */
- (void)writeConditionalBroadcastingType:(ESTBeaconConditionalBroadcasting)conditionalBroadcasting
                              completion:(ESTBoolCompletionBlock)completion;

#pragma mark - Writing methods for security features
///--------------------------------------------------------------------
/// @name Writing methods for security features
///--------------------------------------------------------------------

/**
 *  Enables Estimote Secure UUID.
 *
 *  @param enable     Yes to enable, No to disable Estimote Secure UUID.
 *  @param completion Block with operation result.
 */
- (void)writeEstimoteSecureUUIDEnabled:(BOOL)enable
                            completion:(ESTBoolCompletionBlock)completion;

#pragma mark - Writing methods for sensors
///--------------------------------------------------------------------
/// @name Writing methods for sensors
///--------------------------------------------------------------------

/**
 * Enables or disables the accelerometer allowing to detect if beacon is in motion.
 *
 * @param enable YES to enable, NO to disable the accelerometer.
 * @param completion A block that is called when the accelerometer has been enabled or disabled.
 *
 * The completion block receives the following parameters:
 *
 * - `BOOL value` - YES if the accelerometer has been enabled, NO if the accelerometer has been disabled.
 *
 * - `NSError *error` - If an error occurred, this error object describes the error. If the operation completed successfully, the value is `nil`.
 *
 * @since Estimote OS A2.1
 *
 */
- (void)writeMotionDetectionEnabled:(BOOL)enable
                         completion:(ESTBoolCompletionBlock)completion;

/**
 * Enables or disables the motion UUID.
 *
 * @param enable YES to enable, NO to disable the motion UUID.
 * @param completion A block that is called when the motion UUID has been enabled or disabled.
 *
 * The completion block receives the following parameters:
 *
 * - `BOOL value` - YES if the motion UUID has been enabled, NO if the motion UUID has been disabled.
 *
 * - `NSError *error` - If an error occurred, this error object describes the error. If the operation completed successfully, the value is `nil`.
 *
 * @since Estimote OS A2.1
 *
 */
- (void)writeMotionUUIDEnabled:(BOOL)enable
                    completion:(ESTBoolCompletionBlock)completion;

/**
 * Calibrates the beacon's thermometer sensor.
 *
 * Beacons are basically calibrated out of the box, but additional manual calibration is recommended in order to minimize measurement error. When the sensor is not calibrated, measurement error is ±4 ℃. After calibration it's ±2 ℃.
 *
 * To perform calibration you need to keep the beacon at room temperature for a couple of minutes. Use a separate thermometer to read the actual value (in Celsius degrees) and pass it to this method.
 *
 * @param temperature The reference temperature in Celsius degrees.
 * @param completion A block that is called when the calibration has been completed.
 *
 * The completion block receives the following parameters:
 *
 * - `NSNumber *value` - The current temperature in Celsius degrees, after the calibration.
 *
 * - `NSError *error` - If an error occurred, this error object describes the error. If the operation completed successfully, the value is `nil`.
 */
- (void)writeCalibratedTemperature:(NSNumber *)temperature
                        completion:(ESTNumberCompletionBlock)completion;

#pragma mark - Reset to factory settings
///--------------------------------------------------------------------
/// @name Reset to factory settings
///--------------------------------------------------------------------

/**
 * Resets the beacon's `<major>`, `<minor>`, `<proximityUUID>`, broadcasting `<power>` and `<advInterval>` to factory settings.
 *
 * @param completion A block that is called when the settings have been reset.
 *
 * The completion block receives the following parameters:
 *
 * - `NSError *error` - If an error occurred, this error object describes the error. If the operation completed successfully, the value is `nil`.
 *
 * @warning This method does not reset the `<motionProximityUUID>`. You can reset it yourself to the default value of `ESTIMOTE_PROXIMITY_UUID` using the `<writeMotionProximityUUID:completion:>` method.
 */
- (void)resetToFactorySettingsWithCompletion:(ESTCompletionBlock)completion;


/**
 *  Allows to find CBPeripheral device using CBCentralManager scan.
 *
 *  @param timeout    timeout of scan operation
 *  @param completion completion block returning reference to ESTBeaconConnection object performing operation.
 */
- (void)findPeripheralForBeaconWithTimeout:(NSUInteger)timeout completion:(ESTObjectCompletionBlock)completion;

#pragma mark - Firmware update
///--------------------------------------------------------------------
/// @name Firmware update
///--------------------------------------------------------------------

/**
 * Checks if an updated firmware is available.
 *
 * The result of the check is available as a `ESTBeaconFirmwareInfoVO` structure in the completion block and has the following properties:
 *
 * - `BOOL isUpdateAvailable` - YES if an update is available, NO if there's no update available. In the latter case, all the other properties of this structure will be `nil`.
 *
 * - `NSString *hardwareVersion` - The version of hardware this firmware update is dedicated for.
 *
 * - `NSString *firmwareVersion` - The version of the firmware available for update.
 *
 * - `NSString *changelog` - Changes introduced in the new version.
 *
 * @param completion A block that is called when the check has been completed.
 *
 * The completion block receives the following parameters:
 *
 * - `ESTBeaconFirmwareInfoVO value` - Indicates whether an update is available. If so, it also holds additional information about the update.
 *
 * - `NSError *error` - If an error occurred, this error object describes the error. If the operation completed successfully, the value is `nil`.
 */
- (void)checkFirmwareUpdateWithCompletion:(ESTFirmwareInfoCompletionBlock)completion;

/**
 * Updates the beacon's firmware.
 *
 * @param progress A block that is called throughout the update process to report on the progress.
 *
 * The progress block receives the following parameters:
 *
 * - `NSInteger value` - A percentage value (0-100) indicating the update progress.
 *
 * - `NSString *description` - A description of the current stage of the update.
 *
 * - `NSError *error` - If an error occurred, this error object describes the error. If the operation completed successfully, the value is `nil`.
 *
 * @param completion A block that is called when the update has been completed.
 *
 * The completion block receives the following parameters:
 *
 * - `NSError *error` - If an error occurred, this error object describes the error. If the operation completed successfully, the value is `nil`.
 */
- (void)updateFirmwareWithProgress:(ESTProgressBlock)progress
                        completion:(ESTCompletionBlock)completion;

@end
