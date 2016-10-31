typedef NS_OPTIONS (unsigned int, CAEdgeAntialiasingMask)
{
	kCALayerLeftEdge      = 1U << 0,      /* Minimum X edge. */
	kCALayerRightEdge     = 1U << 1,      /* Maximum X edge. */
	kCALayerBottomEdge    = 1U << 2,      /* Minimum Y edge. */
	kCALayerTopEdge       = 1U << 3,      /* Maximum Y edge. */
};

/** The base layer class. **/

@interface CALayer : NSObject <NSCoding, CAMediaTiming>

+ (instancetype)layer;
- (instancetype)init;
- (instancetype)initWithLayer:(id)layer;
// 动画时获取 layer 其他(nil)
- (nullable id)presentationLayer;
// ???
- (id)modelLayer;

#pragma mark - Property methods
// 获取属性默认值 如果该属性没有默认值返回nil
+ (nullable id)defaultValueForKey:(NSString *)key;

+ (BOOL)needsDisplayForKey:(NSString *)key;

- (BOOL)shouldArchiveValueForKey:(NSString *)key;

#pragma mark - Geometry and layer hierarchy properties.
@property						CGRect			bounds;
@property						CGPoint			position;
@property						CGFloat			zPosition;
@property						CGPoint			anchorPoint;
@property						CGFloat			anchorPointZ;
@property						CATransform3D	transform;
@property						CATransform3D	sublayerTransform;
@property(nullable, strong)		CALayer			*mask;
@property						BOOL			masksToBounds;
@property(nullable, readonly)	CALayer			*superlayer;
@property(nullable, copy)		NSArray<CALayer *> *sublayers;
@property						CGRect			frame;
@property(getter=isHidden)		BOOL			hidden;
@property(getter=isDoubleSided) BOOL			doubleSided;
@property(getter=isGeometryFlipped) BOOL		geometryFlipped;
- (BOOL)contentsAreFlipped;
- (CGAffineTransform)affineTransform;
- (void)setAffineTransform:(CGAffineTransform)m;
- (void)removeFromSuperlayer;
- (void)addSublayer:(CALayer *)layer;
- (void)insertSublayer:(CALayer *)layer atIndex:(unsigned)idx;
- (void)insertSublayer:(CALayer *)layer below:(nullable CALayer *)sibling;
- (void)insertSublayer:(CALayer *)layer above:(nullable CALayer *)sibling;
- (void)replaceSublayer:(CALayer *)layer with:(CALayer *)layer2;

#pragma mark - Mapping between layer coordinate and time spaces.

- (CGPoint)convertPoint:(CGPoint)p fromLayer:(nullable CALayer *)l;
- (CGPoint)convertPoint:(CGPoint)p toLayer:(nullable CALayer *)l;
- (CGRect)convertRect:(CGRect)r fromLayer:(nullable CALayer *)l;
- (CGRect)convertRect:(CGRect)r toLayer:(nullable CALayer *)l;
- (CFTimeInterval)convertTime:(CFTimeInterval)t fromLayer:(nullable CALayer *)l;
- (CFTimeInterval)convertTime:(CFTimeInterval)t toLayer:(nullable CALayer *)l;

#pragma mark - Hit testing methods.
- (nullable CALayer *)hitTest:(CGPoint)p;

- (BOOL)containsPoint:(CGPoint)p;

#pragma mark - Layer content properties and methods.

@property(nullable, strong) id contents;

@property				CGRect		contentsRect;
@property(copy)			NSString	*contentsGravity;
@property				CGFloat		contentsScale;
@property				CGRect		contentsCenter;
@property(copy)			NSString	*minificationFilter;
@property(copy)			NSString	*magnificationFilter;
@property				float		minificationFilterBias;
@property(getter=isOpaque) BOOL		opaque;
@property				BOOL		needsDisplayOnBoundsChange;
@property				BOOL		drawsAsynchronously;

- (void)display;
- (void)setNeedsDisplay;
- (void)setNeedsDisplayInRect:(CGRect)r;
- (BOOL)needsDisplay;
- (void)displayIfNeeded;
- (void)drawInContext:(CGContextRef)ctx;

#pragma mark - Rendering properties and methods.

- (void)renderInContext:(CGContextRef)ctx;
@property CAEdgeAntialiasingMask edgeAntialiasingMask;
@property BOOL allowsEdgeAntialiasing;

@property(nullable)			CGColorRef		backgroundColor;				// 背景色
@property					CGFloat			cornerRadius;					// 圆角
@property					CGFloat			borderWidth;					// 边框宽度
@property(nullable)			CGColorRef		borderColor;					// 边框颜色
@property					float			opacity;						// 透明度?
@property					BOOL			allowsGroupOpacity;				//
@property(nullable, strong) id				compositingFilter;				//
@property(nullable, copy)	NSArray			*filters;
@property(nullable, copy)	NSArray			*backgroundFilters;
@property					BOOL			shouldRasterize;
@property					CGFloat			rasterizationScale;

#pragma mark - Shadow properties.
// 阴影
@property(nullable) CGColorRef	shadowColor;
@property			float		shadowOpacity;
@property			CGSize		shadowOffset;
@property			CGFloat		shadowRadius;
@property(nullable) CGPathRef	shadowPath;

#pragma mark - Layout methods.
- (CGSize)preferredFrameSize;
- (void)setNeedsLayout;
- (BOOL)needsLayout;
- (void)layoutIfNeeded;
- (void)layoutSublayers;

#pragma mark - Action methods.
+ (nullable id<CAAction>)defaultActionForKey:(NSString *)event;
- (nullable id<CAAction>)actionForKey:(NSString *)event;
@property(nullable, copy) NSDictionary<NSString *, id<CAAction>> *actions;

#pragma mark - Animation methods.
- (void)addAnimation:(CAAnimation *)anim forKey:(nullable NSString *)key;

- (void)removeAllAnimations;

- (void)removeAnimationForKey:(NSString *)key;

- (nullable NSArray<NSString *> *)animationKeys;

- (nullable CAAnimation *)animationForKey:(NSString *)key;

#pragma mark - Miscellaneous properties.
@property(nullable, copy) NSString		*name;
@property(nullable, weak) id			delegate;
@property(nullable, copy) NSDictionary	*style;

@end

/** Action (event handler) protocol. **/

@protocol CAAction

- (void)runActionForKey:(NSString *)event object:(id)anObject
			  arguments:(nullable NSDictionary *)dict;

@end

/** NSNull protocol conformance. **/
@interface NSNull (CAActionAdditions) <CAAction>

@end

/** Delegate methods. **/

@interface NSObject (CALayerDelegate)

- (void)displayLayer:(CALayer *)layer;
- (void)drawLayer:(CALayer *)layer inContext:(CGContextRef)ctx;
- (void)layoutSublayersOfLayer:(CALayer *)layer;
- (nullable id<CAAction>)actionForLayer:(CALayer *)layer forKey:(NSString *)event;

@end

/** Layer `contentsGravity' values. **/

CA_EXTERN NSString * const kCAGravityCenter
__OSX_AVAILABLE_STARTING (__MAC_10_5, __IPHONE_2_0);
CA_EXTERN NSString * const kCAGravityTop
__OSX_AVAILABLE_STARTING (__MAC_10_5, __IPHONE_2_0);
CA_EXTERN NSString * const kCAGravityBottom
__OSX_AVAILABLE_STARTING (__MAC_10_5, __IPHONE_2_0);
CA_EXTERN NSString * const kCAGravityLeft
__OSX_AVAILABLE_STARTING (__MAC_10_5, __IPHONE_2_0);
CA_EXTERN NSString * const kCAGravityRight
__OSX_AVAILABLE_STARTING (__MAC_10_5, __IPHONE_2_0);
CA_EXTERN NSString * const kCAGravityTopLeft
__OSX_AVAILABLE_STARTING (__MAC_10_5, __IPHONE_2_0);
CA_EXTERN NSString * const kCAGravityTopRight
__OSX_AVAILABLE_STARTING (__MAC_10_5, __IPHONE_2_0);
CA_EXTERN NSString * const kCAGravityBottomLeft
__OSX_AVAILABLE_STARTING (__MAC_10_5, __IPHONE_2_0);
CA_EXTERN NSString * const kCAGravityBottomRight
__OSX_AVAILABLE_STARTING (__MAC_10_5, __IPHONE_2_0);
CA_EXTERN NSString * const kCAGravityResize
__OSX_AVAILABLE_STARTING (__MAC_10_5, __IPHONE_2_0);
CA_EXTERN NSString * const kCAGravityResizeAspect
__OSX_AVAILABLE_STARTING (__MAC_10_5, __IPHONE_2_0);
CA_EXTERN NSString * const kCAGravityResizeAspectFill
__OSX_AVAILABLE_STARTING (__MAC_10_5, __IPHONE_2_0);

/** Contents filter names. **/

CA_EXTERN NSString * const kCAFilterNearest
__OSX_AVAILABLE_STARTING (__MAC_10_5, __IPHONE_2_0);
CA_EXTERN NSString * const kCAFilterLinear
__OSX_AVAILABLE_STARTING (__MAC_10_5, __IPHONE_2_0);

/* Trilinear minification filter. Enables mipmap generation. Some
 * renderers may ignore this, or impose additional restrictions, such
 * as source images requiring power-of-two dimensions. */

CA_EXTERN NSString * const kCAFilterTrilinear
__OSX_AVAILABLE_STARTING (__MAC_10_6, __IPHONE_3_0);

/** Layer event names. **/

CA_EXTERN NSString * const kCAOnOrderIn
__OSX_AVAILABLE_STARTING (__MAC_10_5, __IPHONE_2_0);
CA_EXTERN NSString * const kCAOnOrderOut
__OSX_AVAILABLE_STARTING (__MAC_10_5, __IPHONE_2_0);

/** The animation key used for transitions. **/

CA_EXTERN NSString * const kCATransition
__OSX_AVAILABLE_STARTING (__MAC_10_5, __IPHONE_2_0);

NS_ASSUME_NONNULL_END
