/*
 * This file is part of the Scandit Data Capture SDK
 *
 * Copyright (C) 2017- Scandit AG. All rights reserved.
 */

#import <Foundation/Foundation.h>

#import <ScanditCaptureCore/SDCBase.h>

NS_ASSUME_NONNULL_BEGIN

extern NSString *_Nonnull const SDCLabelCaptureSettingsErrorDomain;

NS_SWIFT_NAME(LabelCaptureSettings)
SDC_EXPORTED_SYMBOL
@interface SDCLabelCaptureSettings : NSObject <NSCopying>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/**
 * Loads the settings from a label blueprint, provided to you by Scandit.
 *
 * Load the settings from the string representation (JSON) of a label blueprint, provided to you by Scandit.
 */
+ (nullable instancetype)settingsFromString:(nonnull NSString *)string
                                      error:(NSError *_Nullable *_Nullable)error
    NS_SWIFT_NAME(init(string:));

@end

NS_ASSUME_NONNULL_END
