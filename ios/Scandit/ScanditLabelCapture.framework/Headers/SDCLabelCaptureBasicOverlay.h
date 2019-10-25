/*
 * This file is part of the Scandit Data Capture SDK
 *
 * Copyright (C) 2017- Scandit AG. All rights reserved.
 */

#import <Foundation/NSObject.h>

#import <ScanditCaptureCore/SDCBase.h>
#import <ScanditCaptureCore/SDCDataCaptureOverlay.h>

NS_ASSUME_NONNULL_BEGIN

@class SDCLabelCapture;
@class SDCDataCaptureView;
@class SDCBrush;
@class SDCLabelField;
@class SDCCapturedLabel;
@class SDCLabelCaptureBasicOverlay;

/**
 * SDCLabelCaptureBasicOverlayDelegate can be implemented to customize the visual appearance of highlighted labels and their fields. When label capture identifies a new field, or when the SDCLabelField.state property changes, labelCaptureBasicOverlay:brushForField:ofLabel: is called to determine the brush of the field.
 */
NS_SWIFT_NAME(LabelCaptureBasicOverlayDelegate)
@protocol SDCLabelCaptureBasicOverlayDelegate <NSObject>

/**
 * Called for each field to determine its brush whenever the field’s state changes. In case the field is tracked over multiple frames and its state does not change, the same brush is used. The field brush can be changed by explicit calls to SDCLabelCaptureBasicOverlay.setBrush:forField:ofLabel:.
 */
- (nullable SDCBrush *)labelCaptureBasicOverlay:(nonnull SDCLabelCaptureBasicOverlay *)overlay
                                  brushForField:(nonnull SDCLabelField *)field
                                        ofLabel:(nonnull SDCCapturedLabel *)label;

/**
 * Called for each label to determine its brush whenever one of the label’s fields changes it’s state/data. In case the field is tracked over multiple frames and none of the fields changes its state, the same brush is used. The label brush can be changed by explicit calls to SDCLabelCaptureBasicOverlay.setBrush:forLabel:.
 */
- (nullable SDCBrush *)labelCaptureBasicOverlay:(nonnull SDCLabelCaptureBasicOverlay *)overlay
                                  brushForLabel:(nonnull SDCCapturedLabel *)label;

@end

/**
 * Overlay for label capture that displays captured labels and their fields on top of the frames. When labels are successfully recognized, the label background as well as the fields are highlighted. Fields are highlighted using a default brush (defaultCapturedFieldBrush, defaultPredictedFieldBrush), a brush set through a user-defined SDCLabelCaptureBasicOverlayDelegate or calls to setBrush:forField:ofLabel:.
 */
NS_SWIFT_NAME(LabelCaptureBasicOverlay)
SDC_EXPORTED_SYMBOL
@interface SDCLabelCaptureBasicOverlay : NSObject <SDCDataCaptureOverlay>

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/**
 * Constructs a new overlay to visualize the process of label capture. The overlay needs to be added through a call to SDCDataCaptureView.addOverlay:.
 */
+ (instancetype)overlayWithLabelCapture:(nonnull SDCLabelCapture *)labelCapture;
/**
 * Constructs a new overlay to visualize the process of label capture. When view is non-nil, the overlay is automatically added to the view. Otherwise, the overlay needs to be added through a call to SDCDataCaptureView.addOverlay:.
 */
+ (instancetype)overlayWithLabelCapture:(nonnull SDCLabelCapture *)labelCapture
                     forDataCaptureView:(nullable SDCDataCaptureView *)view;

/**
 * The method can be called to change the visualization style of a field. This method is thread-safe; it can be called from any thread.
 *
 * When delegate is set to a non-nil instance, the delegate continues to be asked for the brush to use for this field whenever the state changes, thereby replacing any brushes set by calling setBrush:forField:ofLabel:.
 */
- (void)setBrush:(SDCBrush *)brush
        forField:(SDCLabelField *)field
         ofLabel:(SDCCapturedLabel *)label;

/**
 * The method can be called to change the visualization style of a label. This method is thread-safe; it can be called from any thread.
 *
 * When delegate is set to a non-nil instance, the delegate continues to be asked for the brush to use for this label whenever the state of one its fields changes, thereby replacing any brushes set by calling setBrush:forLabel:.
 */
- (void)setBrush:(SDCBrush *)brush forLabel:(SDCCapturedLabel *)label;

@property (nonatomic, weak, nullable) id<SDCLabelCaptureBasicOverlayDelegate> delegate;
/**
 * The default brush applied to predicted fields. This is the brush used if SDCLabelCaptureBasicOverlayDelegate is not set.
 */
@property (nonatomic, strong, nonnull) SDCBrush *defaultPredictedFieldBrush;
/**
 * The default brush applied to captured fields. This is the brush used if SDCLabelCaptureBasicOverlayDelegate is not set.
 */
@property (nonatomic, strong, nonnull) SDCBrush *defaultCapturedFieldBrush;
/**
 * The default brush used for drawing labels. This brush is used when no delegate is set, or the SDCLabelCaptureBasicOverlayDelegate.labelCaptureBasicOverlay:brushForLabel: returns a nil brush.
 */
@property (nonatomic, strong, nonnull) SDCBrush *defaultLabelBrush;

/**
 * Whether to show scan area guides on top of the preview. This property is useful during development to visualize the current scan areas on screen. It is not meant to be used for production. By default this property is NO.
 */
@property (nonatomic, assign) BOOL shouldShowScanAreaGuides;

@end

NS_ASSUME_NONNULL_END
