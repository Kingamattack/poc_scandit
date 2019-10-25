/*
 * This file is part of the Scandit Data Capture SDK
 *
 * Copyright (C) 2017- Scandit AG. All rights reserved.
 */

#import <Foundation/Foundation.h>

#import <ScanditCaptureCore/SDCBase.h>
#import <ScanditCaptureCore/SDCQuadrilateral.h>

@class SDCLabelField;

NS_ASSUME_NONNULL_BEGIN

/**
 * A captured label tracked over multiple frames. This class holds the list of label fields as well as the predicted boundary of the label. Each instance of a found label has a unique tracking Id which remains constant over multiple frames.
 */
NS_SWIFT_NAME(CapturedLabel)
SDC_EXPORTED_SYMBOL
@interface SDCCapturedLabel : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/**
 * List of fields in the form. For each field in the label description, exactly one captured field is returned.
 */
@property (nonatomic, nonnull, readonly) NSArray<SDCLabelField *> *fields;
/**
 * The name of this label, e.g. label-a. This property can be used in case multiple different label definitions are used at the same time.
 */
@property (nonatomic, nonnull, readonly) NSString *name;
/**
 * The tracking identifier for this label.
 */
@property (nonatomic, readonly) NSInteger trackingId;
/**
 * Whether the label has been completely scanned. True as soon as all the required fields are present. Optional fields do not need to be present for this property to be true.
 */
@property (nonatomic, readonly) BOOL isComplete;
/**
 * The predicted label bounds in image coordinates. These coordinates will need to be converted to view coordinates before they can be visualized.
 */
@property (nonatomic, readonly) SDCQuadrilateral predictedBounds;
/**
 * The delta time  used for predicting the label bounds (predictedBounds) as well as the field locations (available as SDCLabelField.predictedLocation).
 */
@property (nonatomic, readonly) NSTimeInterval deltaTimeToPrediction;

@end

NS_ASSUME_NONNULL_END
