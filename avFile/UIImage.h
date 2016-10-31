// 图片方向
typedef NS_ENUM(NSInteger, UIImageOrientation) {
	UIImageOrientationUp,            // default orientation
	UIImageOrientationDown,          // 180 deg rotation
	UIImageOrientationLeft,          // 90 deg CCW
	UIImageOrientationRight,         // 90 deg CW
	UIImageOrientationUpMirrored,    // as above but image mirrored along other axis. horizontal flip
	UIImageOrientationDownMirrored,  // horizontal flip
	UIImageOrientationLeftMirrored,  // vertical flip
	UIImageOrientationRightMirrored, // vertical flip
};
// ???
typedef NS_ENUM(NSInteger, UIImageResizingMode) {
	UIImageResizingModeTile,
	UIImageResizingModeStretch,
};
//
typedef NS_ENUM(NSInteger, UIImageRenderingMode) {
	UIImageRenderingModeAutomatic,          // Use the default rendering mode for the context where the image is used
	UIImageRenderingModeAlwaysOriginal,     // Always draw the original image, without treating it as a template
	UIImageRenderingModeAlwaysTemplate,     // Always draw the image as a template image, ignoring its color information
};

// =============================================================================
@interface UIImage : NSObject <NSSecureCoding>

// 1. 纯文件创建 UIImage 对象
+ (nullable UIImage *)imageNamed:(NSString *)name;
+ (nullable UIImage *)imageNamed:(NSString *)name
						inBundle:(nullable NSBundle *)bundle
   compatibleWithTraitCollection:(nullable UITraitCollection *)traitCollection;
+ (nullable UIImage *)imageWithContentsOfFile:(NSString *)path;

// 2. 纯数据创建 UIImage 对象
+ (nullable UIImage *)imageWithData:(NSData *)data;
+ (nullable UIImage *)imageWithData:(NSData *)data scale:(CGFloat)scale;

// 3. CGImage
+ (UIImage *)imageWithCGImage:(CGImageRef)cgImage;
+ (UIImage *)imageWithCGImage:(CGImageRef)cgImage
						scale:(CGFloat)scale
				  orientation:(UIImageOrientation)orientation;
// 4. CIImage
+ (UIImage *)imageWithCIImage:(CIImage *)ciImage;
+ (UIImage *)imageWithCIImage:(CIImage *)ciImage
						scale:(CGFloat)scale
				  orientation:(UIImageOrientation)orientation;

// 1.
- (nullable instancetype)initWithContentsOfFile:(NSString *)path;
- (nullable instancetype)initWithData:(NSData *)data;
- (nullable instancetype)initWithData:(NSData *)data
								scale:(CGFloat)scale;
- (instancetype)initWithCGImage:(CGImageRef)cgImage;
- (instancetype)initWithCGImage:(CGImageRef)cgImage
						  scale:(CGFloat)scale
					orientation:(UIImageOrientation)orientation;
- (instancetype)initWithCIImage:(CIImage *)ciImage NS_AVAILABLE_IOS(5_0);
- (instancetype)initWithCIImage:(CIImage *)ciImage
						  scale:(CGFloat)scale
					orientation:(UIImageOrientation)orientation;

@property(nonatomic,readonly)			CGSize			size;
@property(nullable, nonatomic,readonly) CGImageRef		CGImage;
@property(nullable,nonatomic,readonly)	CIImage			*CIImage;

@property(nonatomic,readonly) UIImageOrientation imageOrientation; // this will affect how the image is composited
@property(nonatomic,readonly) CGFloat scale NS_AVAILABLE_IOS(4_0);

+ (nullable UIImage *)animatedImageNamed:(NSString *)name duration:(NSTimeInterval)duration;
+ (nullable UIImage *)animatedResizableImageNamed:(NSString *)name
										capInsets:(UIEdgeInsets)capInsets
										 duration:(NSTimeInterval)duration ; // sequence of files

+ (nullable UIImage *)animatedResizableImageNamed:(NSString *)name
										capInsets:(UIEdgeInsets)capInsets
									 resizingMode:(UIImageResizingMode)resizingMode
										 duration:(NSTimeInterval)duration;

+ (nullable UIImage *)animatedImageWithImages:(NSArray<UIImage *> *)images
									 duration:(NSTimeInterval)duration;

@property(nullable, nonatomic,readonly) NSArray<UIImage *> *images;

@property(nonatomic,readonly) NSTimeInterval duration; // total duration for all frames. default is 0 for non-animated images

- (nullable CGImageRef)CGImage;
- (void)drawAtPoint:(CGPoint)point;                                                        // mode = kCGBlendModeNormal, alpha = 1.0
- (void)drawAtPoint:(CGPoint)point blendMode:(CGBlendMode)blendMode alpha:(CGFloat)alpha;
- (void)drawInRect:(CGRect)rect;                                                           // mode = kCGBlendModeNormal, alpha = 1.0
- (void)drawInRect:(CGRect)rect blendMode:(CGBlendMode)blendMode alpha:(CGFloat)alpha;

- (void)drawAsPatternInRect:(CGRect)rect; // draws the image as a CGPattern

- (UIImage *)resizableImageWithCapInsets:(UIEdgeInsets)capInsets NS_AVAILABLE_IOS(5_0); // create a resizable version of this image. the interior is tiled when drawn.
- (UIImage *)resizableImageWithCapInsets:(UIEdgeInsets)capInsets resizingMode:(UIImageResizingMode)resizingMode NS_AVAILABLE_IOS(6_0); // the interior is resized according to the resizingMode

@property(nonatomic,readonly) UIEdgeInsets capInsets               NS_AVAILABLE_IOS(5_0);   // default is UIEdgeInsetsZero for non resizable images
@property(nonatomic,readonly) UIImageResizingMode resizingMode NS_AVAILABLE_IOS(6_0); // default is UIImageResizingModeTile

// Support for constraint-based layout (auto layout)
// The alignmentRectInsets of a UIImage are used by UIImageView and other UIView and UIControl
//  subclasses that take custom images to determine the view's alignment rect insets for
//  constraint-based layout.
// The default alignmentRectInsets are UIEdgeInsetsZero.
- (UIImage *)imageWithAlignmentRectInsets:(UIEdgeInsets)alignmentInsets NS_AVAILABLE_IOS(6_0);
@property(nonatomic,readonly) UIEdgeInsets alignmentRectInsets NS_AVAILABLE_IOS(6_0);

// Create a version of this image with the specified rendering mode. By default, images have a rendering mode of UIImageRenderingModeAutomatic.
- (UIImage *)imageWithRenderingMode:(UIImageRenderingMode)renderingMode NS_AVAILABLE_IOS(7_0);
@property(nonatomic, readonly) UIImageRenderingMode renderingMode NS_AVAILABLE_IOS(7_0);

@property (nonatomic, readonly, copy) UITraitCollection *traitCollection NS_AVAILABLE_IOS(8_0);
@property (nullable, nonatomic, readonly) UIImageAsset *imageAsset;

- (UIImage *)imageFlippedForRightToLeftLayoutDirection NS_AVAILABLE_IOS(9_0);
@property (nonatomic, readonly) BOOL flipsForRightToLeftLayoutDirection NS_AVAILABLE_IOS(9_0);

@end

// =============================================================================
@interface UIImage(UIImageDeprecated)

- (UIImage *)stretchableImageWithLeftCapWidth:(NSInteger)leftCapWidth
								 topCapHeight:(NSInteger)topCapHeight;
@property(nonatomic,readonly) NSInteger leftCapWidth __TVOS_PROHIBITED;
@property(nonatomic,readonly) NSInteger topCapHeight __TVOS_PROHIBITED;

@end

// =============================================================================
@interface CIImage(UIKitAdditions)

- (nullable instancetype)initWithImage:(UIImage *)image NS_AVAILABLE_IOS(5_0);
- (nullable instancetype)initWithImage:(UIImage *)image options:(nullable NSDictionary *)options NS_AVAILABLE_IOS(5_0);

@end

UIKIT_EXTERN  NSData * __nullable UIImagePNGRepresentation(UIImage * __nonnull image);
UIKIT_EXTERN  NSData * __nullable UIImageJPEGRepresentation(UIImage * __nonnull image, CGFloat compressionQuality);
