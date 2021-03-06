/* Drawing modes for paths. */
typedef CF_ENUM (int32_t, CGPathDrawingMode) {
	kCGPathFill,
	kCGPathEOFill,
	kCGPathStroke,
	kCGPathFillStroke,
	kCGPathEOFillStroke
};

/* Drawing modes for text. */
typedef CF_ENUM (int32_t, CGTextDrawingMode) {
	kCGTextFill,
	kCGTextStroke,
	kCGTextFillStroke,
	kCGTextInvisible,
	kCGTextFillClip,
	kCGTextStrokeClip,
	kCGTextFillStrokeClip,
	kCGTextClip
};

/* Text encodings. */
typedef CF_ENUM (int32_t, CGTextEncoding) {
	kCGEncodingFontSpecific,
	kCGEncodingMacRoman
} CG_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_9, __IPHONE_2_0, __IPHONE_7_0);

/* Interpolation quality. */
typedef CF_ENUM (int32_t, CGInterpolationQuality) {
	kCGInterpolationDefault = 0,  /* Let the context decide. */
	kCGInterpolationNone = 1,     /* Never interpolate. */
	kCGInterpolationLow = 2,      /* Low quality, fast interpolation. */
	kCGInterpolationMedium = 4,   /* Medium quality, slower than kCGInterpolationLow. */
	kCGInterpolationHigh = 3      /* Highest quality, slower than kCGInterpolationMedium. */
};

typedef CF_ENUM (int32_t, CGBlendMode) {
	/* Available in Mac OS X 10.4 & later. */
	kCGBlendModeNormal,
	kCGBlendModeMultiply,
	kCGBlendModeScreen,
	kCGBlendModeOverlay,
	kCGBlendModeDarken,
	kCGBlendModeLighten,
	kCGBlendModeColorDodge,
	kCGBlendModeColorBurn,
	kCGBlendModeSoftLight,
	kCGBlendModeHardLight,
	kCGBlendModeDifference,
	kCGBlendModeExclusion,
	kCGBlendModeHue,
	kCGBlendModeSaturation,
	kCGBlendModeColor,
	kCGBlendModeLuminosity,
	kCGBlendModeClear,                  /* R = 0 */
	kCGBlendModeCopy,                   /* R = S */
	kCGBlendModeSourceIn,               /* R = S*Da */
	kCGBlendModeSourceOut,              /* R = S*(1 - Da) */
	kCGBlendModeSourceAtop,             /* R = S*Da + D*(1 - Sa) */
	kCGBlendModeDestinationOver,        /* R = S*(1 - Da) + D */
	kCGBlendModeDestinationIn,          /* R = D*Sa */
	kCGBlendModeDestinationOut,         /* R = D*(1 - Sa) */
	kCGBlendModeDestinationAtop,        /* R = S*(1 - Da) + D*Sa */
	kCGBlendModeXOR,                    /* R = S*(1 - Da) + D*(1 - Sa) */
	kCGBlendModePlusDarker,             /* R = MAX(0, (1 - D) + (1 - S)) */
	kCGBlendModePlusLighter             /* R = MIN(1, S + D) */
};

/* Return the CFTypeID for CGContextRefs. */

CG_EXTERN CFTypeID CGContextGetTypeID(void)
CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/*******************************************************************************/
/************************** Graphics state functions. **************************/
/*******************************************************************************/

/* Push a copy of the current graphics state onto the graphics state stack.
 Note that the path is not considered part of the graphics state, and is
 not saved. */

CG_EXTERN void CGContextSaveGState(CGContextRef __nullable c)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Restore the current graphics state from the one on the top of the
 graphics state stack, popping the graphics state stack in the process. */

CG_EXTERN void CGContextRestoreGState(CGContextRef __nullable c)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/** Coordinate space transformations. **/

/* Scale the current graphics state's transformation matrix (the CTM) by
 `(sx, sy)'. */

CG_EXTERN void CGContextScaleCTM(CGContextRef __nullable c,
								 CGFloat sx, CGFloat sy)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Translate the current graphics state's transformation matrix (the CTM) by
 `(tx, ty)'. */

CG_EXTERN void CGContextTranslateCTM(CGContextRef __nullable c,
									 CGFloat tx, CGFloat ty)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Rotate the current graphics state's transformation matrix (the CTM) by
 `angle' radians. */

CG_EXTERN void CGContextRotateCTM(CGContextRef __nullable c, CGFloat angle)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Concatenate the current graphics state's transformation matrix (the CTM)
 with the affine transform `transform'. */

CG_EXTERN void CGContextConcatCTM(CGContextRef __nullable c,
								  CGAffineTransform transform)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the current graphics state's transformation matrix. Returns
 CGAffineTransformIdentity in case of inavlid context. */

CG_EXTERN CGAffineTransform CGContextGetCTM(CGContextRef __nullable c)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);


/*******************************************************************************/
/************************ Drawing attribute functions.**************************/
/*******************************************************************************/
// 设置线宽度
CG_EXTERN void CGContextSetLineWidth(CGContextRef __nullable c, CGFloat width)
// 设置线头尾样式
CG_EXTERN void CGContextSetLineCap(CGContextRef __nullable c, CGLineCap cap)
// 设置线拐角样式
CG_EXTERN void CGContextSetLineJoin(CGContextRef __nullable c, CGLineJoin join)
/* Set the miter limit in the current graphics state to `limit'. */
CG_EXTERN void CGContextSetMiterLimit(CGContextRef __nullable c, CGFloat limit)
// 绘制虚线
CG_EXTERN void CGContextSetLineDash(CGContextRef __nullable c, CGFloat phase,
									const CGFloat * __nullable lengths, size_t count)
/* Set the path flatness parameter in the current graphics state of `c' to
 `flatness'. */
CG_EXTERN void CGContextSetFlatness(CGContextRef __nullable c, CGFloat flatness)
// 调整透明度
CG_EXTERN void CGContextSetAlpha(CGContextRef __nullable c, CGFloat alpha)
// blend mode
CG_EXTERN void CGContextSetBlendMode(CGContextRef __nullable c, CGBlendMode mode)


/*******************************************************************************/
/************************** Path construction functions. ***********************/
/*******************************************************************************/

// 创建一个新的路径, 就得路径将被放弃
CG_EXTERN void CGContextBeginPath(CGContextRef __nullable c)
// 创建一个新的路径从 (x,y) 开始
CG_EXTERN void CGContextMoveToPoint(CGContextRef __nullable c,
									CGFloat x, CGFloat y)
// 添加一条线, 从当前点到(x,y)
CG_EXTERN void CGContextAddLineToPoint(CGContextRef __nullable c,
									   CGFloat x, CGFloat y)
// 贝塞尔曲线
CG_EXTERN void CGContextAddCurveToPoint(CGContextRef __nullable c, CGFloat cp1x,
										CGFloat cp1y, CGFloat cp2x, CGFloat cp2y, CGFloat x, CGFloat y)

/* Append a quadratic curve from the current point to `(x, y)', with control
 point `(cpx, cpy)'. */

CG_EXTERN void CGContextAddQuadCurveToPoint(CGContextRef __nullable c,
											CGFloat cpx, CGFloat cpy, CGFloat x, CGFloat y)

/* Close the current subpath of the context's path. */
CG_EXTERN void CGContextClosePath(CGContextRef __nullable c)

/*******************************************************************************/
/****************** Path construction convenience functions. *******************/
/*******************************************************************************/
// 矩形
CG_EXTERN void CGContextAddRect(CGContextRef __nullable c, CGRect rect)
// 多个矩形
CG_EXTERN void CGContextAddRects(CGContextRef __nullable c,
								 const CGRect * __nullable rects, size_t count)
// 绘制多条直线
CG_EXTERN void CGContextAddLines(CGContextRef __nullable c,
								 const CGPoint * __nullable points, size_t count)
// 椭圆
CG_EXTERN void CGContextAddEllipseInRect(CGContextRef __nullable c, CGRect rect)

/**
 *  绘制圆形
 *
 *  @param path       路径
 *  @param m          矩阵
 *  @param x          圆心x
 *  @param y          圆心y
 *  @param radius     半径
 *  @param startAngle 开始弧度
 *  @param endAngle   结束弧度
 *  @param clockwise  是否反选
 */
CG_EXTERN void CGContextAddArc(CGContextRef __nullable c, CGFloat x, CGFloat y,
							   CGFloat radius, CGFloat startAngle, CGFloat endAngle, int clockwise)
// 画圆
CG_EXTERN void CGContextAddArcToPoint(CGContextRef __nullable c,
									  CGFloat x1, CGFloat y1, CGFloat x2, CGFloat y2, CGFloat radius)
// 添加路径
CG_EXTERN void CGContextAddPath(CGContextRef __nullable c,
								CGPathRef __nullable path)

/*******************************************************************************/
/******************************  Path stroking.  *******************************/
/*******************************************************************************/

CG_EXTERN void CGContextReplacePathWithStrokedPath(CGContextRef __nullable c)
CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/*******************************************************************************/
/************************* Path information functions. *************************/
/*******************************************************************************/
// 是否为空
CG_EXTERN bool CGContextIsPathEmpty(CGContextRef __nullable c)
// 获取当前点
CG_EXTERN CGPoint CGContextGetPathCurrentPoint(CGContextRef __nullable c)
// GET Rect
CG_EXTERN CGRect CGContextGetPathBoundingBox(CGContextRef __nullable c)
// 复制路径
CG_EXTERN CGPathRef __nullable CGContextCopyPath(CGContextRef __nullable c)
// 是否包含某个点
CG_EXTERN bool CGContextPathContainsPoint(CGContextRef __nullable c,
										  CGPoint point, CGPathDrawingMode mode)


/** Path drawing functions. **/

/* Draw the context's path using drawing mode `mode'. */

CG_EXTERN void CGContextDrawPath(CGContextRef __nullable c,
								 CGPathDrawingMode mode)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/** Path drawing convenience functions. **/

/* Fill the context's path using the winding-number fill rule. Any open
 subpath of the path is implicitly closed. */

CG_EXTERN void CGContextFillPath(CGContextRef __nullable c)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Fill the context's path using the even-odd fill rule. Any open subpath of
 the path is implicitly closed. */

CG_EXTERN void CGContextEOFillPath(CGContextRef __nullable c)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Stroke the context's path. */

CG_EXTERN void CGContextStrokePath(CGContextRef __nullable c)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Fill `rect' with the current fill color. */

CG_EXTERN void CGContextFillRect(CGContextRef __nullable c, CGRect rect)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Fill `rects', an array of `count' CGRects, with the current fill
 color. */

CG_EXTERN void CGContextFillRects(CGContextRef __nullable c,
								  const CGRect * __nullable rects, size_t count)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Stroke `rect' with the current stroke color and the current linewidth. */

CG_EXTERN void CGContextStrokeRect(CGContextRef __nullable c, CGRect rect)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Stroke `rect' with the current stroke color, using `width' as the the
 line width. */

CG_EXTERN void CGContextStrokeRectWithWidth(CGContextRef __nullable c,
											CGRect rect, CGFloat width)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Clear `rect' (that is, set the region within the rect to transparent). */

CG_EXTERN void CGContextClearRect(CGContextRef __nullable c, CGRect rect)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Fill an ellipse (an oval) inside `rect'. */

CG_EXTERN void CGContextFillEllipseInRect(CGContextRef __nullable c,
										  CGRect rect)
CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Stroke an ellipse (an oval) inside `rect'. */

CG_EXTERN void CGContextStrokeEllipseInRect(CGContextRef __nullable c,
											CGRect rect)
CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Stroke a sequence of line segments one after another in `context'. The
 line segments are specified by `points', an array of `count' CGPoints.
 This function is equivalent to
 
 CGContextBeginPath(context);
 for (k = 0; k < count; k += 2) {
 CGContextMoveToPoint(context, s[k].x, s[k].y);
 CGContextAddLineToPoint(context, s[k+1].x, s[k+1].y);
 }
 CGContextStrokePath(context); */

CG_EXTERN void CGContextStrokeLineSegments(CGContextRef __nullable c,
										   const CGPoint * __nullable points, size_t count)
CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/** Clipping functions. **/

/* Intersect the context's path with the current clip path and use the
 resulting path as the clip path for subsequent rendering operations. Use
 the winding-number fill rule for deciding what's inside the path. */

CG_EXTERN void CGContextClip(CGContextRef __nullable c)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Intersect the context's path with the current clip path and use the
 resulting path as the clip path for subsequent rendering operations. Use
 the even-odd fill rule for deciding what's inside the path. */

CG_EXTERN void CGContextEOClip(CGContextRef __nullable c)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Add `mask' transformed to `rect' to the clipping area of `context'. The
 mask, which may be either an image mask or an image, is mapped into the
 specified rectangle and intersected with the current clipping area of the
 context.
 
 If `mask' is an image mask, then it clips in a manner identical to the
 behavior if it were used with "CGContextDrawImage": it indicates an area
 to be masked out (left unchanged) when drawing. The source samples of the
 image mask determine which points of the clipping area are changed,
 acting as an "inverse alpha": if the value of a source sample in the
 image mask is S, then the corresponding point in the current clipping
 area will be multiplied by an alpha of (1-S). (For example, if S is 1,
 then the point in the clipping area becomes clear, while if S is 0, the
 point in the clipping area is unchanged.
 
 If `mask' is an image, then it serves as alpha mask and is blended with
 the current clipping area. The source samples of mask determine which
 points of the clipping area are changed: if the value of the source
 sample in mask is S, then the corresponding point in the current clipping
 area will be multiplied by an alpha of S. (For example, if S is 0, then
 the point in the clipping area becomes clear, while if S is 1, the point
 in the clipping area is unchanged.
 
 If `mask' is an image, then it must be in the DeviceGray color space, may
 not have alpha, and may not be masked by an image mask or masking
 color. */

CG_EXTERN void CGContextClipToMask(CGContextRef __nullable c, CGRect rect,
								   CGImageRef __nullable mask)
CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Return the bounding box of the clip path of `c' in user space. The
 bounding box is the smallest rectangle completely enclosing all points in
 the clip. */

CG_EXTERN CGRect CGContextGetClipBoundingBox(CGContextRef __nullable c)
CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/** Clipping convenience functions. **/

/* Intersect the current clipping path with `rect'. Note that this function
 resets the context's path to the empty path. */

CG_EXTERN void CGContextClipToRect(CGContextRef __nullable c, CGRect rect)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Intersect the current clipping path with the clipping region formed by
 creating a path consisting of all rects in `rects'. Note that this
 function resets the context's path to the empty path. */

CG_EXTERN void CGContextClipToRects(CGContextRef __nullable c,
									const CGRect *  rects, size_t count)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/** Primitive color functions. **/

/* Set the current fill color in the context `c' to `color'. */

CG_EXTERN void CGContextSetFillColorWithColor(CGContextRef __nullable c,
											  CGColorRef __nullable color)
CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Set the current stroke color in the context `c' to `color'. */

CG_EXTERN void CGContextSetStrokeColorWithColor(CGContextRef __nullable c,
												CGColorRef __nullable color)
CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/** Color space functions. **/

/* Set the current fill color space in `context' to `space'. As a
 side-effect, set the fill color to a default value appropriate for the
 color space. */

CG_EXTERN void CGContextSetFillColorSpace(CGContextRef __nullable c,
										  CGColorSpaceRef __nullable space)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Set the current stroke color space in `context' to `space'. As a
 side-effect, set the stroke color to a default value appropriate for the
 color space. */

CG_EXTERN void CGContextSetStrokeColorSpace(CGContextRef __nullable c,
											CGColorSpaceRef __nullable space)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/** Color functions. **/

/* Set the components of the current fill color in `context' to the values
 specifed by `components'. The number of elements in `components' must be
 one greater than the number of components in the current fill color space
 (N color components + 1 alpha component). The current fill color space
 must not be a pattern color space. */

CG_EXTERN void CGContextSetFillColor(CGContextRef __nullable c,
									 const CGFloat * __nullable components)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Set the components of the current stroke color in `context' to the values
 specifed by `components'. The number of elements in `components' must be
 one greater than the number of components in the current stroke color
 space (N color components + 1 alpha component). The current stroke color
 space must not be a pattern color space. */

CG_EXTERN void CGContextSetStrokeColor(CGContextRef __nullable c,
									   const CGFloat * __nullable components)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/** Pattern functions. **/

/* Set the components of the current fill color in `context' to the values
 specifed by `components', and set the current fill pattern to `pattern'.
 The number of elements in `components' must be one greater than the
 number of components in the current fill color space (N color components
 + 1 alpha component). The current fill color space must be a pattern
 color space. */

CG_EXTERN void CGContextSetFillPattern(CGContextRef __nullable c,
									   CGPatternRef __nullable pattern, const CGFloat * __nullable components)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Set the components of the current stroke color in `context' to the values
 specifed by `components', and set the current stroke pattern to
 `pattern'. The number of elements in `components' must be one greater
 than the number of components in the current stroke color space (N color
 components + 1 alpha component). The current stroke color space must be a
 pattern color space. */

CG_EXTERN void CGContextSetStrokePattern(CGContextRef __nullable c,
										 CGPatternRef __nullable pattern, const CGFloat * __nullable components)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Set the pattern phase in the current graphics state of `context' to
 `phase'. */

CG_EXTERN void CGContextSetPatternPhase(CGContextRef __nullable c, CGSize phase)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/** Color convenience functions. **/

/* Set the current fill color space in `context' to `DeviceGray' and set the
 components of the current fill color to `(gray, alpha)'. */

CG_EXTERN void CGContextSetGrayFillColor(CGContextRef __nullable c,
										 CGFloat gray, CGFloat alpha)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Set the current stroke color space in `context' to `DeviceGray' and set
 the components of the current stroke color to `(gray, alpha)'. */

CG_EXTERN void CGContextSetGrayStrokeColor(CGContextRef __nullable c,
										   CGFloat gray, CGFloat alpha)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Set the current fill color space in `context' to `DeviceRGB' and set the
 components of the current fill color to `(red, green, blue, alpha)'. */

CG_EXTERN void CGContextSetRGBFillColor(CGContextRef __nullable c, CGFloat red,
										CGFloat green, CGFloat blue, CGFloat alpha)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Set the current stroke color space in `context' to `DeviceRGB' and set
 the components of the current stroke color to `(red, green, blue,
 alpha)'. */

CG_EXTERN void CGContextSetRGBStrokeColor(CGContextRef __nullable c,
										  CGFloat red, CGFloat green, CGFloat blue, CGFloat alpha)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Set the current fill color space in `context' to `DeviceCMYK' and set the
 components of the current fill color to `(cyan, magenta, yellow, black,
 alpha)'. */

CG_EXTERN void CGContextSetCMYKFillColor(CGContextRef __nullable c,
										 CGFloat cyan, CGFloat magenta, CGFloat yellow, CGFloat black, CGFloat alpha)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Set the current stroke color space in `context' to `DeviceCMYK' and set
 the components of the current stroke color to `(cyan, magenta, yellow,
 black, alpha)'. */

CG_EXTERN void CGContextSetCMYKStrokeColor(CGContextRef __nullable c,
										   CGFloat cyan, CGFloat magenta, CGFloat yellow, CGFloat black, CGFloat alpha)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/** Rendering intent. **/

/* Set the rendering intent in the current graphics state of `context' to
 `intent'. */

CG_EXTERN void CGContextSetRenderingIntent(CGContextRef __nullable c,
										   CGColorRenderingIntent intent)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/** Image functions. **/

/* Draw `image' in the rectangular area specified by `rect' in the context
 `c'. The image is scaled, if necessary, to fit into `rect'. */

CG_EXTERN void CGContextDrawImage(CGContextRef __nullable c, CGRect rect,
								  CGImageRef __nullable image)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Draw `image' tiled in the context `c'. The image is scaled to the size
 specified by `rect' in user space, positioned at the origin of `rect' in
 user space, then replicated, stepping the width of `rect' horizontally
 and the height of `rect' vertically, to fill the current clip region.
 Unlike patterns, the image is tiled in user space, so transformations
 applied to the CTM affect the final result. */

CG_EXTERN void CGContextDrawTiledImage(CGContextRef __nullable c, CGRect rect,
									   CGImageRef __nullable image)
CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* Return the interpolation quality for image rendering of `context'. The
 interpolation quality is a gstate parameter which controls the level of
 interpolation performed when an image is interpolated (for example, when
 scaling the image). Note that it is merely a hint to the context: not all
 contexts support all interpolation quality levels. */

CG_EXTERN CGInterpolationQuality
CGContextGetInterpolationQuality(CGContextRef __nullable c)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Set the interpolation quality of `context' to `quality'. */

CG_EXTERN void CGContextSetInterpolationQuality(CGContextRef __nullable c,
												CGInterpolationQuality quality)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/** Shadow support. **/

/* Set the shadow parameters in `context'. `offset' specifies a translation
 in base-space; `blur' is a non-negative number specifying the amount of
 blur; `color' specifies the color of the shadow, which may contain a
 non-opaque alpha value. If `color' is NULL, it's equivalent to specifying
 a fully transparent color. The shadow is a gstate parameter. After a
 shadow is specified, all objects drawn subsequently will be shadowed. To
 turn off shadowing, set the shadow color to a fully transparent color (or
 pass NULL as the color), or use the standard gsave/grestore mechanism. */

CG_EXTERN void CGContextSetShadowWithColor(CGContextRef __nullable c,
										   CGSize offset, CGFloat blur, CGColorRef __nullable color)
CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Equivalent to calling
 CGContextSetShadowWithColor(context, offset, blur, color)
 where color is black with 1/3 alpha (i.e., RGBA = {0, 0, 0, 1.0/3.0}) in
 the DeviceRGB color space. */

CG_EXTERN void CGContextSetShadow(CGContextRef __nullable c, CGSize offset,
								  CGFloat blur)
CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/** Gradient and shading functions. **/

/* Fill the current clipping region of `context' with a linear gradient from
 `startPoint' to `endPoint'. The location 0 of `gradient' corresponds to
 `startPoint'; the location 1 of `gradient' corresponds to `endPoint';
 colors are linearly interpolated between these two points based on the
 values of the gradient's locations. The option flags control whether the
 gradient is drawn before the start point or after the end point. */

CG_EXTERN void CGContextDrawLinearGradient(CGContextRef __nullable c,
										   CGGradientRef __nullable gradient, CGPoint startPoint, CGPoint endPoint,
										   CGGradientDrawingOptions options)
CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* Fill the current clipping region of `context' with a radial gradient
 between two circles defined by the center point and radius of each
 circle. The location 0 of `gradient' corresponds to a circle centered at
 `startCenter' with radius `startRadius'; the location 1 of `gradient'
 corresponds to a circle centered at `endCenter' with radius `endRadius';
 colors are linearly interpolated between these two circles based on the
 values of the gradient's locations. The option flags control whether the
 gradient is drawn before the start circle or after the end circle. */

CG_EXTERN void CGContextDrawRadialGradient(CGContextRef __nullable c,
										   CGGradientRef __nullable gradient, CGPoint startCenter, CGFloat startRadius,
										   CGPoint endCenter, CGFloat endRadius, CGGradientDrawingOptions options)
CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* Fill the current clipping region of `context' with `shading'. */

CG_EXTERN void CGContextDrawShading(CGContextRef __nullable c,
									__nullable CGShadingRef shading)
CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/** Text functions. **/

/* Set the current character spacing in `context' to `spacing'. The
 character spacing is added to the displacement between the origin of one
 character and the origin of the next. */

CG_EXTERN void CGContextSetCharacterSpacing(CGContextRef __nullable c,
											CGFloat spacing)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Set the user-space point at which text will be drawn in the context `c'
 to `(x, y)'. */

CG_EXTERN void CGContextSetTextPosition(CGContextRef __nullable c,
										CGFloat x, CGFloat y)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the user-space point at which text will be drawn in `context'. */

CG_EXTERN CGPoint CGContextGetTextPosition(CGContextRef __nullable c)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Set the text matrix in the context `c' to `t'. */

CG_EXTERN void CGContextSetTextMatrix(CGContextRef __nullable c,
									  CGAffineTransform t)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Return the text matrix in the context `c'. Returns CGAffineTransformIdentity
 if `c' is not a valid context. */

CG_EXTERN CGAffineTransform CGContextGetTextMatrix(CGContextRef __nullable c)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Set the text drawing mode in the current graphics state of the context
 `c' to `mode'. */

CG_EXTERN void CGContextSetTextDrawingMode(CGContextRef __nullable c,
										   CGTextDrawingMode mode)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Set the font in the current graphics state of the context `c' to
 `font'. */

CG_EXTERN void CGContextSetFont(CGContextRef __nullable c,
								CGFontRef __nullable font)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Set the font size in the current graphics state of the context `c' to
 `size'. */

CG_EXTERN void CGContextSetFontSize(CGContextRef __nullable c, CGFloat size)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Draw `glyphs', an array of `count' CGGlyphs, at the points specified by
 `positions'. Each element of `positions' specifies the position from the
 associated glyph; the positions are specified in user space. */

CG_EXTERN void CGContextShowGlyphsAtPositions(CGContextRef __nullable c,
											  const CGGlyph * __nullable glyphs, const CGPoint * __nullable Lpositions,
											  size_t count)
CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/** PDF functions. **/

/* Draw `page' in the current user space of the context `c'. */

CG_EXTERN void CGContextDrawPDFPage(CGContextRef __nullable c,
									CGPDFPageRef __nullable page)
CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/** Output page functions. **/

/* Begin a new page. */

CG_EXTERN void CGContextBeginPage(CGContextRef __nullable c,
								  const CGRect * __nullable mediaBox)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* End the current page. */

CG_EXTERN void CGContextEndPage(CGContextRef __nullable c)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/** Context functions. **/

/* Equivalent to `CFRetain(c)'. */

CG_EXTERN CGContextRef __nullable CGContextRetain(CGContextRef __nullable c)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Equivalent to `CFRelease(c)'. */

CG_EXTERN void CGContextRelease(CGContextRef __nullable c)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Flush all drawing to the destination. */

CG_EXTERN void CGContextFlush(CGContextRef __nullable c)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Synchronized drawing. */

CG_EXTERN void CGContextSynchronize(CGContextRef __nullable c)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/** Antialiasing functions. **/

/* Turn on antialiasing if `shouldAntialias' is true; turn it off otherwise.
 This parameter is part of the graphics state. */

CG_EXTERN void CGContextSetShouldAntialias(CGContextRef __nullable c,
										   bool shouldAntialias)
CG_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);

/* Allow antialiasing in `context' if `allowsAntialiasing' is true; don't
 allow it otherwise. This parameter is not part of the graphics state. A
 context will perform antialiasing if both `allowsAntialiasing' and the
 graphics state parameter `shouldAntialias' are true. */

CG_EXTERN void CGContextSetAllowsAntialiasing(CGContextRef __nullable c,
											  bool allowsAntialiasing)
CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/** Font display functions. **/

/* Turn on font smoothing if `shouldSmoothFonts' is true; turn it off
 otherwise. This parameter is part of the graphics state. Note that this
 doesn't guarantee that font smoothing will occur: not all destination
 contexts support font smoothing. */

CG_EXTERN void CGContextSetShouldSmoothFonts(CGContextRef __nullable c,
											 bool shouldSmoothFonts)
CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* If `allowsFontSmoothing' is true, then allow font smoothing when
 displaying text in `context'; otherwise, don't allow font smoothing. This
 parameter is not part of the graphics state. Fonts will be smoothed if
 they are antialiased when drawn and if both `allowsFontSmoothing' and the
 graphics state parameter `shouldSmoothFonts' are true. */

CG_EXTERN void CGContextSetAllowsFontSmoothing(CGContextRef __nullable c,
											   bool allowsFontSmoothing)
CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

/* If `shouldSubpixelPositionFonts' is true, then glyphs may be placed at
 subpixel positions (if allowed) when displaying text in `context';
 otherwise, glyphs will be forced to integer pixel boundaries. This
 parameter is part of the graphics state. */

CG_EXTERN void CGContextSetShouldSubpixelPositionFonts(
													   CGContextRef __nullable c, bool shouldSubpixelPositionFonts)
CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* If `allowsFontSubpixelPositioning' is true, then allow font subpixel
 positioning when displaying text in `context'; otherwise, don't allow
 subpixel positioning. This parameter is not part of the graphics state. A
 context will place glyphs at subpixel positions if fonts will be
 antialiased when drawn and if both `allowsFontSubpixelPositioning' and
 the graphics state parameter `shouldSubpixelPositionFonts' are true. */

CG_EXTERN void CGContextSetAllowsFontSubpixelPositioning(
														 CGContextRef __nullable c, bool allowsFontSubpixelPositioning)
CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* If `shouldSubpixelQuantizeFonts' is true, then quantize the subpixel
 positions of glyphs when displaying text in `context'; otherwise, don't
 quantize the subpixel positions. This parameter is part of the graphics
 state. */

CG_EXTERN void CGContextSetShouldSubpixelQuantizeFonts(
													   CGContextRef __nullable c, bool shouldSubpixelQuantizeFonts)
CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* If `allowsFontSubpixelQuantization' is true, then allow font subpixel
 quantization when displaying text in `context'; otherwise, don't allow
 subpixel quantization. This parameter is not part of the graphics state.
 A context quantizes subpixel positions if glyphs will be drawn at
 subpixel positions and `allowsFontSubpixelQuantization' and the graphics
 state parameter `shouldSubpixelQuantizeFonts' are both true. */

CG_EXTERN void CGContextSetAllowsFontSubpixelQuantization(
														  CGContextRef __nullable c, bool allowsFontSubpixelQuantization)
CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/** Transparency layer support. **/

/* Begin a transparency layer in `context'. All subsequent drawing
 operations until a corresponding `CGContextEndTransparencyLayer' are
 composited into a fully transparent backdrop (which is treated as a
 separate destination buffer from the context). After the transparency
 layer is ended, the result is composited into the context using the
 global alpha and shadow state of the context. This operation respects the
 clipping region of the context. After a call to this function, all of the
 parameters in the graphics state remain unchanged with the exception of
 the following:
 - The global alpha is set to 1.
 - The shadow is turned off.
 - The blend mode is set to `kCGBlendModeNormal'.
 Ending the transparency layer restores these parameters to the values
 they had before `CGContextBeginTransparencyLayer' was called.
 Transparency layers may be nested. */

CG_EXTERN void CGContextBeginTransparencyLayer(CGContextRef __nullable c,
											   CFDictionaryRef __nullable auxiliaryInfo)
CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/* Begin a transparency layer in `context'. This function is identical to
 `CGContextBeginTransparencyLayer' except that the content of the
 transparency layer will be bounded by `rect' (specified in user space). */

CG_EXTERN void CGContextBeginTransparencyLayerWithRect(
													   CGContextRef __nullable c, CGRect rect, CFDictionaryRef __nullable auxInfo)
CG_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

/* End a tranparency layer. */

CG_EXTERN void CGContextEndTransparencyLayer(CGContextRef __nullable c)
CG_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/** User space to device space tranformations. **/

/* Return the affine transform mapping the user space (abstract coordinates)
 of `context' to device space (pixels). */

CG_EXTERN CGAffineTransform
CGContextGetUserSpaceToDeviceSpaceTransform(CGContextRef __nullable c)
CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Transform `point' from the user space of `context' to device space. */

CG_EXTERN CGPoint CGContextConvertPointToDeviceSpace(CGContextRef __nullable c,
													 CGPoint point)
CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Transform `point' from device space to the user space of `context'. */

CG_EXTERN CGPoint CGContextConvertPointToUserSpace(CGContextRef __nullable c,
												   CGPoint point)
CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Transform `size' from the user space of `context' to device space. */

CG_EXTERN CGSize CGContextConvertSizeToDeviceSpace(CGContextRef __nullable c,
												   CGSize size)
CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Transform `size' from device space to the user space of `context'. */

CG_EXTERN CGSize CGContextConvertSizeToUserSpace(CGContextRef __nullable c,
												 CGSize size)
CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Transform `rect' from the user space of `context' to device space. Since
 affine transforms do not preserve rectangles in general, this function
 returns the smallest rectangle which contains the transformed corner
 points of `rect'. */

CG_EXTERN CGRect CGContextConvertRectToDeviceSpace(CGContextRef __nullable c,
												   CGRect rect)
CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Transform `rect' from device space to the user space of `context'. Since
 affine transforms do not preserve rectangles in general, this function
 returns the smallest rectangle which contains the transformed corner
 points of `rect'. */

CG_EXTERN CGRect CGContextConvertRectToUserSpace(CGContextRef __nullable c,
												 CGRect rect)
CG_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* DEPRECATED; use the CGPDFPage API instead. */

CG_EXTERN void CGContextDrawPDFDocument(CGContextRef __nullable c, CGRect rect,
										CGPDFDocumentRef __nullable document, int page)
CG_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_5,
							__IPHONE_NA, __IPHONE_NA);

CF_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED

#endif /* CGCONTEXT_H_ */
