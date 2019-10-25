/*
 * This file is part of the Scandit Data Capture SDK
 *
 * Copyright (C) 2017- Scandit AG. All rights reserved.
 */

#import <Foundation/NSObject.h>

#import <ScanditCaptureCore/SDCBase.h>
#import <ScanditCaptureCore/SDCDataCaptureMode.h>

NS_ASSUME_NONNULL_BEGIN

@class SDCLabelCaptureSession;
@class SDCLabelCapture;

/**
 * Protocol to be implemented by listeners that want to observe a label capture mode and get informed whenever new labels have been captured, existing labels have been updated or lost.
 */
NS_SWIFT_NAME(LabelCaptureListener)
@protocol SDCLabelCaptureListener <NSObject>

@required

/**
 * Invoked after label capture has completed to process a frame. The session contains a list of the currently captured labels. The list may be empty in case no label is currently present.
 */
- (void)labelCapture:(SDCLabelCapture *)labelCapture
    didUpdateSession:(SDCLabelCaptureSession *)session
           frameData:(id<SDCFrameData>)frameData;

@optional

/**
 * Invoked when the listener starts observing the label capture instance.
 */
- (void)didStartObservingLabelCapture:(SDCLabelCapture *)labelCapture;

/**
 * Invoked when the listener stops observing the label capture instance.
 */
- (void)didStopObservingLabelCapture:(SDCLabelCapture *)labelCapture;

@end

NS_ASSUME_NONNULL_END
