
// 1. CGContextRef		获取图形上下文


// 2. CGPathRef
CGPathRef：用于向量图，可创建路径，并进行填充或描画(stroke)
CGImageRef：用于表示bitmap图像和基于采样数据的bitmap图像遮罩。
CGLayerRef：用于表示可用于重复绘制(如背景)和幕后(offscreen)绘制的绘画层
CGPatternRef：用于重绘图
CGShadingRef、CGGradientRef：用于绘制渐变
CGFunctionRef：用于定义回调函数，该函数包含一个随机的浮点值参数。当为阴影创建渐变时使用该类型
CGColorRef, CGColorSpaceRef：用于告诉Quartz如何解释颜色
CGImageSourceRef,CGImageDestinationRef：用于在Quartz中移入移出数据
CGFontRef：用于绘制文本
CGPDFDictionaryRef, CGPDFObjectRef, CGPDFPageRef, CGPDFStream, CGPDFStringRef, and CGPDFArrayRef：用于访问PDF的元数据
CGPDFScannerRef, CGPDFContentStreamRef：用于解析PDF元数据
CGPSConverterRef：用于将PostScript转化成PDF。在iOS中不能使用。