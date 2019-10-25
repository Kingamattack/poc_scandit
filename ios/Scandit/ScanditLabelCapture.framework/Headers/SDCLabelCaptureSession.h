/*
 * This file is part of the Scandit Data Capture SDK
 *
 * Copyright (C) 2017- Scandit AG. All rights reserved.
 */

#import <Foundation/Foundation.h>

#import <ScanditCaptureCore/SDCBase.h>

NS_ASSUME_NONNULL_BEGIN

@class SDCCapturedLabel;

/**
 * Holds the ongoing state of capturing data contained in one or more labels. An instance of this class is passed to SDCLabelCaptureListener.labelCapture:didUpdateSession:frameData: when new labels are captured, or existing labels are updated or lost. Methods and properties of this class are only meant to be used from within the SDCLabelCaptureListener.labelCapture:didUpdateSession:frameData: callback and should not be called from other threads. The data returned from this class, however can be accessed from any thread.
 */
NS_SWIFT_NAME(LabelCaptureSession)
SDC_EXPORTED_SYMBOL
@interface SDCLabelCaptureSession : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/**
 * The identifier of the last processed frame.
 */
@property (nonatomic, readonly) NSInteger lastProcessedFrameId;

/**
 * List of currently captured labels.
 */
@property (nonatomic, nonnull, readonly) NSArray<SDCCapturedLabel *> *capturedLabels;

@end

NS_ASSUME_NONNULL_END
