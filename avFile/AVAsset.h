gem install mini_portile2 -v '2.0.0'
gem install babosa -v '1.0.2'
gem install highline -v '1.7.8'
gem install security -v '0.1.3'
gem install excon -v '0.45.4'
gem install plist -v '3.1.0'
gem install rubyzip -v '1.1.7'
gem install multipart-post -v '2.0.0'
gem install terminal-table -v '1.4.5'
gem install unf_ext -v '0.0.7.1'
gem install multi_xml -v '0.5.5'
gem install coderay -v '1.1.0'
gem install method_source -v '0.8.2'
gem install slop -v '3.6.0'
gem install molinillo -v '0.4.1'
gem install git -v '1.2.9.1'
gem install mini_magick -v '4.0.4'
gem install rouge -v '1.10.1'
gem install net-ssh -v '3.0.2'
gem install slack-notifier -v '1.5.1'












@interface AVAsset : NSObject <NSCopying, AVAsynchronousKeyValueLoading>
+ (instancetype)assetWithURL:(NSURL *)URL;
@property (nonatomic, readonly) CMTime duration;
// 默认速度
@property (nonatomic, readonly) float preferredRate;
// 默认音量
@property (nonatomic, readonly) float preferredVolume;

@property (nonatomic, readonly) CGAffineTransform preferredTransform;

@property (nonatomic, readonly) CGSize naturalSize NS_DEPRECATED(10_7, 10_8, 4_0, 5_0);

@end

@interface AVAsset (AVAssetAsynchronousLoading)

@property (nonatomic, readonly) BOOL providesPreciseDurationAndTiming;

- (void)cancelLoading;

@end


@interface AVAsset (AVAssetReferenceRestrictions)

typedef NS_OPTIONS(NSUInteger, AVAssetReferenceRestrictions) {
	AVAssetReferenceRestrictionForbidNone = 0UL,
	AVAssetReferenceRestrictionForbidRemoteReferenceToLocal = (1UL << 0),
	AVAssetReferenceRestrictionForbidLocalReferenceToRemote = (1UL << 1),
	AVAssetReferenceRestrictionForbidCrossSiteReference = (1UL << 2),
	AVAssetReferenceRestrictionForbidLocalReferenceToLocal = (1UL << 3),
	AVAssetReferenceRestrictionForbidAll = 0xFFFFUL,
};


@property (nonatomic, readonly) AVAssetReferenceRestrictions referenceRestrictions NS_AVAILABLE(10_7, 5_0);

@end


@interface AVAsset (AVAssetTrackInspection)

@property (nonatomic, readonly) NSArray<AVAssetTrack *> *tracks;

- (nullable AVAssetTrack *)trackWithTrackID:(CMPersistentTrackID)trackID;

- (NSArray<AVAssetTrack *> *)tracksWithMediaType:(NSString *)mediaType;

- (NSArray<AVAssetTrack *> *)tracksWithMediaCharacteristic:(NSString *)mediaCharacteristic;

@property (nonatomic, readonly) NSArray<AVAssetTrackGroup *> *trackGroups NS_AVAILABLE(10_9, 7_0);

@end

@interface AVAsset (AVAssetMetadataReading)

@property (nonatomic, readonly, nullable) AVMetadataItem *creationDate NS_AVAILABLE(10_8, 5_0);

@property (nonatomic, readonly, nullable) NSString *lyrics;

/* Provides access to an array of AVMetadataItems for each common metadata key for which a value is available; items can be filtered according to language via +[AVMetadataItem metadataItemsFromArray:filteredAndSortedAccordingToPreferredLanguages:] and according to identifier via +[AVMetadataItem metadataItemsFromArray:filteredByIdentifier:].
 */
@property (nonatomic, readonly) NSArray<AVMetadataItem *> *commonMetadata;

/* Provides access to an array of AVMetadataItems for all metadata identifiers for which a value is available; items can be filtered according to language via +[AVMetadataItem metadataItemsFromArray:filteredAndSortedAccordingToPreferredLanguages:] and according to identifier via +[AVMetadataItem metadataItemsFromArray:filteredByIdentifier:].
 */
@property (nonatomic, readonly) NSArray<AVMetadataItem *> *metadata NS_AVAILABLE(10_10, 8_0);

/* Provides an NSArray of NSStrings, each representing a metadata format that's available to the asset (e.g. ID3, iTunes metadata, etc.). Metadata formats are defined in AVMetadataFormat.h.
 */
@property (nonatomic, readonly) NSArray<NSString *> *availableMetadataFormats;

/*!
 @method		metadataForFormat:
 @abstract		Provides an NSArray of AVMetadataItems, one for each metadata item in the container of the specified format; can subsequently be filtered according to language via +[AVMetadataItem metadataItemsFromArray:filteredAndSortedAccordingToPreferredLanguages:], according to locale via +[AVMetadataItem metadataItemsFromArray:withLocale:], or according to key via +[AVMetadataItem metadataItemsFromArray:withKey:keySpace:].
 @param		format
 The metadata format for which items are requested.
 @result		An NSArray containing AVMetadataItems; may be empty if there is no metadata of the specified format.
 @discussion	Becomes callable without blocking when the key @"availableMetadataFormats" has been loaded
 */
- (NSArray<AVMetadataItem *> *)metadataForFormat:(NSString *)format;

@end


@interface AVAsset (AVAssetChapterInspection)

/* array of NSLocale
 */
@property (readonly) NSArray<NSLocale *> *availableChapterLocales NS_AVAILABLE(10_7, 4_3);

/*!
 @method		chapterMetadataGroupsWithTitleLocale:containingMetadataItemsWithCommonKeys:
 @abstract		Provides an array of chapters.
 @param		locale
 Locale of the metadata items carrying chapter titles to be returned (supports the IETF BCP 47 specification).
 @param		commonKeys
 Array of common keys of AVMetadataItem to be included; can be nil.
 AVMetadataCommonKeyArtwork is the only supported key for now.
 @result		An NSArray of AVTimedMetadataGroup.
 @discussion
	This method returns an array of AVTimedMetadataGroup objects. Each object in the array always contains an AVMetadataItem representing the chapter title; the timeRange property of the AVTimedMetadataGroup object is equal to the time range of the chapter title item.
 
	An AVMetadataItem with the specified common key will be added to an existing AVTimedMetadataGroup object if the time range (timestamp and duration) of the metadata item and the metadata group overlaps. The locale of items not carrying chapter titles need not match the specified locale parameter.
 
	Further filtering of the metadata items in AVTimedMetadataGroups according to language can be accomplished using +[AVMetadataItem metadataItemsFromArray:filteredAndSortedAccordingToPreferredLanguages:]; filtering of the metadata items according to locale can be accomplished using +[AVMetadataItem metadataItemsFromArray:withLocale:].
 */
- (NSArray<AVTimedMetadataGroup *> *)chapterMetadataGroupsWithTitleLocale:(NSLocale *)locale containingItemsWithCommonKeys:(nullable NSArray<NSString *> *)commonKeys NS_AVAILABLE(10_7, 4_3);

/*!
 @method		chapterMetadataGroupsBestMatchingPreferredLanguages:
 @abstract		Tests, in order of preference, for a match between language identifiers in the specified array of preferred languages and the available chapter locales, and returns the array of chapters corresponding to the first match that's found.
 @param			preferredLanguages
 An array of language identifiers in order of preference, each of which is an IETF BCP 47 (RFC 4646) language identifier. Use +[NSLocale preferredLanguages] to obtain the user's list of preferred languages.
 @result		An NSArray of AVTimedMetadataGroup.
 @discussion
 Safe to call without blocking when the AVAsset key availableChapterLocales has status AVKeyValueStatusLoaded.
 
 Returns an array of AVTimedMetadataGroup objects. Each object in the array always contains an AVMetadataItem representing the chapter title; the timeRange property of the AVTimedMetadataGroup object is equal to the time range of the chapter title item.
 
 All of the available chapter metadata is included in the metadata groups, including items with the common key AVMetadataCommonKeyArtwork, if such items are present. Items not carrying chapter titles will be added to an existing AVTimedMetadataGroup object if the time range (timestamp and duration) of the metadata item and that of the metadata group overlaps. The locale of such items need not match the locale of the chapter titles.
 
 Further filtering of the metadata items in AVTimedMetadataGroups according to language can be accomplished using +[AVMetadataItem metadataItemsFromArray:filteredAndSortedAccordingToPreferredLanguages:]; filtering of the metadata items according to locale can be accomplished using +[AVMetadataItem metadataItemsFromArray:withLocale:].
 .
 */
- (NSArray<AVTimedMetadataGroup *> *)chapterMetadataGroupsBestMatchingPreferredLanguages:(NSArray<NSString *> *)preferredLanguages NS_AVAILABLE(10_8, 6_0);


@end


@interface AVAsset (AVAssetMediaSelection)

/* Provides an NSArray of NSStrings, each NSString indicating a media characteristic for which a media selection option is available.
 */
@property (nonatomic, readonly) NSArray<NSString *> *availableMediaCharacteristicsWithMediaSelectionOptions NS_AVAILABLE(10_8, 5_0);

/*!
 @method		mediaSelectionGroupForMediaCharacteristic:
 @abstract		Provides an instance of AVMediaSelectionGroup that contains one or more options with the specified media characteristic.
 @param		mediaCharacteristic
	A media characteristic for which you wish to obtain the available media selection options. AVMediaCharacteristicAudible, AVMediaCharacteristicLegible, and AVMediaCharacteristicVisual are currently supported.
 
	Pass AVMediaCharacteristicAudible to obtain the group of available options for audio media in various languages and for various purposes, such as descriptive audio.
	Pass AVMediaCharacteristicLegible to obtain the group of available options for subtitles in various languages and for various purposes.
	Pass AVMediaCharacteristicVisual to obtain the group of available options for video media.
 @result		An instance of AVMediaSelectionGroup. May be nil.
 @discussion
	Becomes callable without blocking when the key @"availableMediaCharacteristicsWithMediaSelectionOptions" has been loaded.
 
	If the asset has no AVMediaSelectionGroup containing options with the specified media characteristic, the return value will be nil.
	
	Filtering of the options in the returned AVMediaSelectionGroup according to playability, locale, and additional media characteristics can be accomplished using the category AVMediaSelectionOptionFiltering defined on AVMediaSelectionGroup.
 */
- (nullable AVMediaSelectionGroup *)mediaSelectionGroupForMediaCharacteristic:(NSString *)mediaCharacteristic NS_AVAILABLE(10_8, 5_0);

/*!
 @property		preferredMediaSelection
 @abstract		Provides an instance of AVMediaSelection with default selections for each of the receiver's media selection groups.
 */
@property (nonatomic, readonly) AVMediaSelection *preferredMediaSelection NS_AVAILABLE(10_11, 9_0);

@end


@interface AVAsset (AVAssetProtectedContent)

/* Indicates whether or not the asset has protected content.
 */
@property (nonatomic, readonly) BOOL hasProtectedContent NS_AVAILABLE(10_7, 4_2);

@end


@interface AVAsset (AVAssetFragments)

/*!
 @property		canContainFragments
 @abstract		Indicates whether the asset is capable of being extended by fragments.
 @discussion	For QuickTime movie files and MPEG-4 files, the value of canContainFragments is YES if an 'mvex' box is present in the 'moov' box. For those types, the 'mvex' box signals the possible presence of later 'moof' boxes.
 */

@property (nonatomic, readonly) BOOL canContainFragments NS_AVAILABLE(10_11, 9_0);

/*!
 @property		containsFragments
 @abstract		Indicates whether the asset is extended by at least one movie fragment.
 @discussion	For QuickTime movie files and MPEG-4 files, the value of this property is YES if canContainFragments is YES and at least one 'moof' box is present after the 'moov' box.
 */
@property (nonatomic, readonly) BOOL containsFragments NS_AVAILABLE(10_11, 9_0);

@end


@interface AVAsset (AVAssetUsability)

/* indicates whether an AVPlayerItem can be initialized with the receiver or with its URL
 */
@property (nonatomic, readonly, getter=isPlayable) BOOL playable NS_AVAILABLE(10_7, 4_3);

/* indicates whether an AVAssetExportSession can be used with the receiver for export
 */
@property (nonatomic, readonly, getter=isExportable) BOOL exportable NS_AVAILABLE(10_7, 4_3);

/* indicates whether an AVAssetReader can be used with the receiver for extracting media data
 */
@property (nonatomic, readonly, getter=isReadable) BOOL readable NS_AVAILABLE(10_7, 4_3);

/* indicates whether the receiver can be used to build an AVMutableComposition
 */
@property (nonatomic, readonly, getter=isComposable) BOOL composable NS_AVAILABLE(10_7, 4_3);

#if TARGET_OS_IPHONE

/* indicates whether the receiver can be written to the saved photos album
 */
@property (nonatomic, readonly, getter=isCompatibleWithSavedPhotosAlbum) BOOL compatibleWithSavedPhotosAlbum NS_AVAILABLE_IOS(5_0);

#endif	// TARGET_OS_IPHONE

/*!
 @property		compatibleWithAirPlayVideo
 @abstract		Indicates whether the asset is compatible with AirPlay Video.
 @discussion	YES if an AVPlayerItem initialized with the receiver can be played by an external device via AirPlay Video.
 */
@property (nonatomic, readonly, getter=isCompatibleWithAirPlayVideo) BOOL compatibleWithAirPlayVideo NS_AVAILABLE(10_11, 9_0);

@end


AVF_EXPORT NSString *const AVURLAssetPreferPreciseDurationAndTimingKey NS_AVAILABLE(10_7, 4_0);

AVF_EXPORT NSString *const AVURLAssetReferenceRestrictionsKey NS_AVAILABLE(10_7, 5_0);

AVF_EXPORT NSString *const AVURLAssetHTTPCookiesKey NS_AVAILABLE_IOS(8_0);


@interface AVURLAsset : AVAsset

+ (NSArray<NSString *> *)audiovisualTypes NS_AVAILABLE(10_7, 5_0);

+ (NSArray<NSString *> *)audiovisualMIMETypes NS_AVAILABLE(10_7, 5_0);

+ (BOOL)isPlayableExtendedMIMEType: (NSString *)extendedMIMEType NS_AVAILABLE(10_7, 5_0);

+ (instancetype)URLAssetWithURL:(NSURL *)URL options:(nullable NSDictionary<NSString *, id> *)options;

- (instancetype)initWithURL:(NSURL *)URL options:(nullable NSDictionary<NSString *, id> *)options;

@property (nonatomic, readonly, copy) NSURL *URL;

@end


@interface AVURLAsset (AVURLAssetURLHandling)

/*!
 @property resourceLoader
 @abstract
 Provides access to an instance of AVAssetResourceLoader, which offers limited control over the handling of URLs that may be loaded in the course of performing operations on the asset, such as playback.
 The loading of file URLs cannot be mediated via use of AVAssetResourceLoader.
 Note that copies of an AVAsset will vend the same instance of AVAssetResourceLoader.
 */
@property (nonatomic, readonly) AVAssetResourceLoader *resourceLoader NS_AVAILABLE(10_9, 6_0);

@end


@interface AVURLAsset (AVAssetCompositionUtility )

/*!
 @method		compatibleTrackForCompositionTrack:
 @abstract		Provides a reference to an AVAssetTrack of the target from which any timeRange
 can be inserted into a mutable composition track (via -[AVMutableCompositionTrack insertTimeRange:ofTrack:atTime:error:]).
 @param		compositionTrack
 The composition track for which a compatible AVAssetTrack is requested.
 @result		an instance of AVAssetTrack
 @discussion
	Finds a track of the target with content that can be accommodated by the specified composition track.
	The logical complement of -[AVMutableComposition mutableTrackCompatibleWithTrack:].
 */
- (nullable AVAssetTrack *)compatibleTrackForCompositionTrack:(AVCompositionTrack *)compositionTrack;

@end


AVF_EXPORT NSString *const AVAssetDurationDidChangeNotification NS_AVAILABLE(10_11, 9_0);

AVF_EXPORT NSString *const AVAssetContainsFragmentsDidChangeNotification NS_AVAILABLE_MAC(10_11);

AVF_EXPORT NSString *const AVAssetWasDefragmentedNotification NS_AVAILABLE_MAC(10_11);

AVF_EXPORT NSString *const AVAssetChapterMetadataGroupsDidChangeNotification NS_AVAILABLE(10_11, 9_0);

AVF_EXPORT NSString *const AVAssetMediaSelectionGroupsDidChangeNotification NS_AVAILABLE(10_11, 9_0);


@protocol AVFragmentMinding

@property (nonatomic, readonly, getter=isAssociatedWithFragmentMinder) BOOL associatedWithFragmentMinder NS_AVAILABLE_MAC(10_11);

@end

@interface AVFragmentedAsset : AVURLAsset <AVFragmentMinding>

+ (instancetype)fragmentedAssetWithURL:(NSURL *)URL options:(nullable NSDictionary<NSString *, id> *)options;

@property (nonatomic, readonly) NSArray<AVFragmentedAssetTrack *> *tracks;

@end

@interface AVFragmentedAsset (AVFragmentedAssetTrackInspection)

- (nullable AVFragmentedAssetTrack *)trackWithTrackID:(CMPersistentTrackID)trackID;

- (NSArray<AVFragmentedAssetTrack *> *)tracksWithMediaType:(NSString *)mediaType;

- (NSArray<AVFragmentedAssetTrack *> *)tracksWithMediaCharacteristic:(NSString *)mediaCharacteristic;

@end

#pragma mark --- AVFragmentedAssetMinder ---
@interface AVFragmentedAssetMinder : NSObject

+ (instancetype)fragmentedAssetMinderWithAsset:(AVAsset<AVFragmentMinding> *)asset
							   mindingInterval:(NSTimeInterval)mindingInterval;

@property (nonatomic) NSTimeInterval mindingInterval;

@property (nonatomic, readonly) NSArray<AVAsset<AVFragmentMinding> *> *assets;

- (void)addFragmentedAsset:(AVAsset<AVFragmentMinding> *)asset;

- (void)removeFragmentedAsset:(AVAsset<AVFragmentMinding> *)asset;

@end









