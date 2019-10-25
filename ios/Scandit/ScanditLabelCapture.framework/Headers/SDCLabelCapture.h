/*
 * This file is part of the Scandit Data Capture SDK
 *
 * Copyright (C) 2017- Scandit AG. All rights reserved.
 */

#import <Foundation/NSObject.h>
#import <ScanditCaptureCore/SDCBase.h>
#import <ScanditCaptureCore/SDCDataCaptureMode.h>

NS_ASSUME_NONNULL_BEGIN

@class SDCLabelCaptureSettings;
@class SDCDataCaptureContext;
@class SDCCameraSettings;

@protocol SDCLabelCaptureListener;

/**
 * Data capture mode to scan labels, e.g. groups of barcodes, or a combination of text and barcode in a fixed spatial arrangement.
 */
NS_SWIFT_NAME(LabelCapture)
SDC_EXPORTED_SYMBOL
@interface SDCLabelCapture : NSObject <SDCDataCaptureMode>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/**
 * Construct a new label capture mode with the provided context and settings. The capture mode is automatically added to the context.
 */
+ (instancetype)labelCaptureWithContext:(nonnull SDCDataCaptureContext *)context
                               settings:(nonnull SDCLabelCaptureSettings *)settings;

/**
 * Asynchronously apply the new settings to label capture. If label capture is currently running, the task will complete when the next frame is processed, and will use the new settings for that frame. If label capture is currently not running, the task will complete as soon as the settings have been stored and won’t wait until the next frame is going to be processed.
 */
- (void)applySettings:(nonnull SDCLabelCaptureSettings *)settings
    completionHandler:(nullable void (^)(void))completionHandler;

/**
 * Add listener to observe the label capture mode and get notified when a label or some of its fields got scanned.
 *
 * In case the same listener is already observing this instance, calling this method will not add the listener again. Once the listener is no longer required, make sure to remove it again. The listener is stored using a weak reference and must thus be retained by the caller for it to not go out of scope.
 */
- (void)addListener:(nullable id<SDCLabelCaptureListener>)listener NS_SWIFT_NAME(addListener(_:));
/**
 * Remove a previously registered listener. In case the listener is not currently observing this instance, calling this method has no effect.
 */
- (void)removeListener:(nullable id<SDCLabelCaptureListener>)listener
    NS_SWIFT_NAME(removeListener(_:));

/**
 * Implemented from SDCDataCaptureMode. See SDCDataCaptureMode.context.
 */
@property (nonatomic, nullable, readonly) SDCDataCaptureContext *context;
/**
 * Implemented from SDCDataCaptureMode. See SDCDataCaptureMode.enabled.
 */
@property (nonatomic, assign, getter=isEnabled) BOOL enabled;

/**
 * Returns the recommended camera settings for use with label capture.
 */
+ (SDCCameraSettings *)recommendedCameraSettings;

@end

NS_ASSUME_NONNULL_END
