/*
 *	CTFramesetter.h
 *	CoreText
 *
 *	Copyright (c) 2003-2015 Apple Inc. All rights reserved.
 *
 */

/*!
 @header
 
 Thread Safety Information
 
 All functions in this header are thread safe unless otherwise specified.
 */

#ifndef __CTFRAMESETTER__
#define __CTFRAMESETTER__

#include <CoreText/CTDefines.h>
#include <CoreText/CTFrame.h>
#include <CoreText/CTTypesetter.h>

CF_IMPLICIT_BRIDGING_ENABLED
CF_EXTERN_C_BEGIN
CF_ASSUME_NONNULL_BEGIN

/* --------------------------------------------------------------------------- */
/* Framesetter Types */
/* --------------------------------------------------------------------------- */

typedef const struct CF_BRIDGED_TYPE(id) __CTFramesetter * CTFramesetterRef;


/*!
	@function	CTFramesetterGetTypeID
	@abstract	Returns the CFType of the framesetter object
 */

CFTypeID CTFramesetterGetTypeID( void ) CT_AVAILABLE(10_5, 3_2);


/* --------------------------------------------------------------------------- */
/* Framesetter Creation */
/* --------------------------------------------------------------------------- */

/*!
	@function	CTFramesetterCreateWithAttributedString
	@abstract	Creates an immutable(不可变的) framesetter object from an attributed
 string.
 
	@discussion The resultant framesetter object can be used to create and
 fill text frames with the CTFramesetterCreateFrame call.
 
	@param		string
 The run with which you want to construct the framesetter
 object with.
 
	@result		This function will return a reference to a CTFramesetter if
 the call was successful. Otherwise, it will return NULL.
 */

/**
 CTFramesetterCreateWithAttributedString
 使用 AttributedString 创建 CTFramesetter
 @param string AttributedString
 @return CTFramesetter
 */
CTFramesetterRef CTFramesetterCreateWithAttributedString(CFAttributedStringRef string );


/* --------------------------------------------------------------------------- */
/* Frame Creation */
/* --------------------------------------------------------------------------- */

/*!
	@function	CTFramesetterCreateFrame
	@abstract	Creates an immutable frame from a framesetter.
 
	@discussion This call will create a frame full of glyphs in the shape of
 the path provided by the "path" parameter. The framesetter
 will continue to fill the frame until it either runs out of
 text or it finds that text no longer fits.
 
	@param		framesetter
 The framesetter that will be used to create the frame.
 
	@param		stringRange
 The string range which the new frame will be based on. The
 string range is a range over the string that was used to
 create the framesetter. If the length portion of the range
 is set to 0, then the framesetter will continue to add lines
 until it runs out of text or space.
 
	@param		path
 A CGPath object that specifies the shape which the frame will
 take on.
 
	@param		frameAttributes
 Additional attributes that control the frame filling process
 can be specified here, or NULL if there are no such attributes.
 See CTFrame.h for available attributes.
 
	@result		This function will return a reference to a new CTFrame object.
 */

CTFrameRef CTFramesetterCreateFrame(
									CTFramesetterRef framesetter,
									CFRange stringRange,
									CGPathRef path,
									CFDictionaryRef __nullable frameAttributes ) CT_AVAILABLE(10_5, 3_2);


/*!
	@function	CTFramesetterGetTypesetter
	@abstract	Returns the typesetter object being used by the framesetter.
 
	@discussion Each framesetter uses a typesetter internally to perform
 line breaking and other contextual analysis based on the
 characters in a string; this function returns the typesetter
 being used by a particular framesetter if the caller would
 like to perform other operations on that typesetter.
 
	@param		framesetter
 The framesetter from which a typesetter is being requested.
 
	@result		This function will return a reference to a CTTypesetter
 object, which should not be released by the caller.
 */

CTTypesetterRef CTFramesetterGetTypesetter(
										   CTFramesetterRef framesetter ) CT_AVAILABLE(10_5, 3_2);


/* --------------------------------------------------------------------------- */
/* Frame Sizing */
/* --------------------------------------------------------------------------- */

/*!
	@function	CTFramesetterSuggestFrameSizeWithConstraints
	@abstract	Determines the frame size needed for a string range.
 
	@discussion	This function may be used to determine how much space is needed
 to display a string, optionally by constraining the space along
 either dimension.
 
	@param		framesetter
 The framesetter that will be used for measuring the frame size.
 
	@param		stringRange
 The string range to which the frame size will apply. The
 string range is a range over the string that was used to
 create the framesetter. If the length portion of the range
 is set to 0, then the framesetter will continue to add lines
 until it runs out of text or space.
 
	@param		frameAttributes
 Additional attributes that control the frame filling process
 can be specified here, or NULL if there are no such attributes.
 
	@param		constraints
 The width and height to which the frame size will be constrained,
 A value of CGFLOAT_MAX for either dimension indicates that it
 should be treated as unconstrained.
 
	@param		fitRange
 The range of the string that actually fit in the constrained size.
 
	@result		The actual dimensions for the given string range and constraints.
 */

CGSize CTFramesetterSuggestFrameSizeWithConstraints(
													CTFramesetterRef framesetter,
													CFRange stringRange,
													CFDictionaryRef __nullable frameAttributes,
													CGSize constraints,
													CFRange * __nullable fitRange ) CT_AVAILABLE(10_5, 3_2);


CF_ASSUME_NONNULL_END
CF_EXTERN_C_END
CF_IMPLICIT_BRIDGING_DISABLED

#endif
