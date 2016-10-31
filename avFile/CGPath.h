typedef CF_ENUM(int32_t, CGLineJoin) {
	kCGLineJoinMiter,
	kCGLineJoinRound,
	kCGLineJoinBevel
};

/* Line cap styles. */
typedef CF_ENUM(int32_t, CGLineCap) {
	kCGLineCapButt,
	kCGLineCapRound,
	kCGLineCapSquare
};

/* Return the CFTypeID for CGPathRefs. */
CG_EXTERN CFTypeID CGPathGetTypeID(void)

/*******************************************************************************/
/*创建路径*/
/*******************************************************************************/
// 创建一个可变路径
CG_EXTERN CGMutablePathRef  CGPathCreateMutable(void)
// 复制一个路径
CG_EXTERN CGPathRef __nullable CGPathCreateCopy(CGPathRef __nullable path)
// 根据路径创建路径
CG_EXTERN CGPathRef __nullable CGPathCreateCopyByTransformingPath(
																  CGPathRef __nullable path, const CGAffineTransform * __nullable transform)
// 根据路径创建路径
CG_EXTERN CGMutablePathRef __nullable CGPathCreateMutableCopy(
															  CGPathRef __nullable path)
// 根据路径创建路径
CG_EXTERN CGMutablePathRef __nullable CGPathCreateMutableCopyByTransformingPath(
																				CGPathRef __nullable path, const CGAffineTransform * __nullable transform)

CG_EXTERN CGPathRef  CGPathCreateWithRect(CGRect rect,
										  const CGAffineTransform * __nullable transform)

CG_EXTERN CGPathRef  CGPathCreateWithEllipseInRect(CGRect rect,
												   const CGAffineTransform * __nullable transform)

CG_EXTERN CGPathRef  CGPathCreateWithRoundedRect(CGRect rect,
												 CGFloat cornerWidth, CGFloat cornerHeight,
												 const CGAffineTransform * __nullable transform)

CG_EXTERN void CGPathAddRoundedRect(CGMutablePathRef __nullable path,
									const CGAffineTransform * __nullable transform, CGRect rect,
									CGFloat cornerWidth, CGFloat cornerHeight)

CG_EXTERN CGPathRef __nullable CGPathCreateCopyByDashingPath(
															 CGPathRef __nullable path, const CGAffineTransform * __nullable transform,
															 CGFloat phase, const CGFloat * __nullable lengths, size_t count)

CG_EXTERN CGPathRef __nullable CGPathCreateCopyByStrokingPath(
															  CGPathRef __nullable path, const CGAffineTransform * __nullable transform,
															  CGFloat lineWidth, CGLineCap lineCap,
															  CGLineJoin lineJoin, CGFloat miterLimit)

CG_EXTERN CGPathRef __nullable CGPathRetain(CGPathRef __nullable path)
CG_AVAILABLE_STARTING(__MAC_10_2, __IPHONE_2_0);

CG_EXTERN void CGPathRelease(CGPathRef __nullable path)

CG_EXTERN bool CGPathEqualToPath(CGPathRef __nullable path1,
								 CGPathRef __nullable path2)


/*******************************************************************************/
/******************* Path construction functions. 创建路径函数 *******************/
/*******************************************************************************/
// 创建一个点
CG_EXTERN void CGPathMoveToPoint(CGMutablePathRef __nullable path,
								 const CGAffineTransform * __nullable m, CGFloat x, CGFloat y)
// 连线到某个点
CG_EXTERN void CGPathAddLineToPoint(CGMutablePathRef __nullable path,
									const CGAffineTransform * __nullable m, CGFloat x, CGFloat y)

// 创建一个贝塞尔曲线 (3个点)
CG_EXTERN void CGPathAddQuadCurveToPoint(CGMutablePathRef __nullable path,
										 const CGAffineTransform *__nullable m, CGFloat cpx, CGFloat cpy,
										 CGFloat x, CGFloat y)

// 创建一个贝塞尔曲线 (4个点)
CG_EXTERN void CGPathAddCurveToPoint(CGMutablePathRef __nullable path,
									 const CGAffineTransform * __nullable m, CGFloat cp1x, CGFloat cp1y,
									 CGFloat cp2x, CGFloat cp2y, CGFloat x, CGFloat y)

// 关闭路径
CG_EXTERN void CGPathCloseSubpath(CGMutablePathRef __nullable path)

/*******************************************************************************/
/******************* Path construction convenience functions *******************/
/*******************************************************************************/

// 绘制矩形
CG_EXTERN void CGPathAddRect(CGMutablePathRef __nullable path,
							 const CGAffineTransform * __nullable m, CGRect rect)
// 绘制多个矩形
CG_EXTERN void CGPathAddRects(CGMutablePathRef __nullable path,
							  const CGAffineTransform * __nullable m, const CGRect * __nullable rects,
							  size_t count)
// 绘制多条线
CG_EXTERN void CGPathAddLines(CGMutablePathRef __nullable path,
							  const CGAffineTransform * __nullable m, const CGPoint * __nullable points,
							  size_t count)
// 画圆 根据 矩形
CG_EXTERN void CGPathAddEllipseInRect(CGMutablePathRef __nullable path,
									  const CGAffineTransform * __nullable m, CGRect rect)
// 绘制圆形
CG_EXTERN void CGPathAddRelativeArc(CGMutablePathRef __nullable path,
									const CGAffineTransform * __nullable matrix, CGFloat x, CGFloat y,
									CGFloat radius, CGFloat startAngle, CGFloat delta)

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
CG_EXTERN void CGPathAddArc(CGMutablePathRef __nullable path,
							const CGAffineTransform * __nullable m,
							CGFloat x, CGFloat y, CGFloat radius, CGFloat startAngle, CGFloat endAngle,
							bool clockwise)

// 绘制弧线
CG_EXTERN void CGPathAddArcToPoint(CGMutablePathRef __nullable path,
								   const CGAffineTransform * __nullable m, CGFloat x1, CGFloat y1,
								   CGFloat x2, CGFloat y2, CGFloat radius)

// 添加路径
CG_EXTERN void CGPathAddPath(CGMutablePathRef __nullable path1,
							 const CGAffineTransform * __nullable m, CGPathRef __nullable path2)


/*******************************************************************************/
/*******************       Path information functions.       *******************/
/*******************************************************************************/
// 判断路径是否为空
CG_EXTERN bool CGPathIsEmpty(CGPathRef __nullable path)
// 是否包含某个矩形
CG_EXTERN bool CGPathIsRect(CGPathRef __nullable path, CGRect * __nullable rect)
// 获取当前路径所在点
CG_EXTERN CGPoint CGPathGetCurrentPoint(CGPathRef __nullable path)
// 获取 path 所在得rect
CG_EXTERN CGRect CGPathGetBoundingBox(CGPathRef __nullable path)
// 获取 path 所在得rect
CG_EXTERN CGRect CGPathGetPathBoundingBox(CGPathRef __nullable path)
// 是否包含某个点
CG_EXTERN bool CGPathContainsPoint(CGPathRef __nullable path,
								   const CGAffineTransform * __nullable m, CGPoint point, bool eoFill)

typedef CF_ENUM(int32_t, CGPathElementType) {
	kCGPathElementMoveToPoint,
	kCGPathElementAddLineToPoint,
	kCGPathElementAddQuadCurveToPoint,
	kCGPathElementAddCurveToPoint,
	kCGPathElementCloseSubpath
};

/* An element of a path returned by `CGPathApply'. */
struct CGPathElement {
	CGPathElementType type;
	CGPoint *  points;
};
