- ####[Overview of Quartz 2D](#Text) 
- ####[Graphics Contexts](#about)
- ####[Paths](#about)
- ####[Color and Color Spaces](#about)
- ####[Transforms](#about)
- ####[Patterns](#about)
- ####[Shadows](#about)
- ####[Gradients](#about)
- ####[Transparency Layers](#about)
- ####[Data Management in Quartz 2D](#about)
- ####[Bitmap Images and Image Masks](#about)
- ####[Core Graphics Layer Drawing](#about)
- ####[PDF Document Creation, Viewing, and Transforming](#about)
- ####[PDF Document Parsing](#about)
- ####[PostScript Conversion](#about)
- ####[Text](#about)
- ####[Glossary](#about)
- ####[Document Revision History](#about)


##Introduction

Quartz 2D is an advanced, two-dimensional drawing engine available for iOS application development and to all Mac OS X application environments outside of the kernel. Quartz 2D provides low-level, lightweight 2D rendering with unmatched output fidelity regardless of display or printing device. Quartz 2D is resolution- and device-independent; you don’t need to think about the final destination when you use the Quartz 2D application programming interface (API) for drawing.

The Quartz 2D API is easy to use and provides access to powerful features such as transparency layers, path-based drawing, offscreen rendering, advanced color management, anti-aliased rendering, and PDF document creation, display, and parsing.

The Quartz 2D API is part of the Core Graphics framework, so you may see Quartz referred to as Core Graphics or, simply, CG.

###Who Should Read This Document?
This document is intended for iOS and Mac OS X developers who need to perform any of the following tasks:

* Draw graphics
* Provide graphics editing capabilities in an application
* Create or display bitmap images
* Work with PDF documents

###Organization of This Document
This document is organized into the following chapters:

* Overview of Quartz 2D describes the page, drawing destinations, Quartz opaque data types, graphics states, coordinates, and memory management, and it takes a look at how Quartz works “under the hood.”
* Graphics Contexts describes the kinds of drawing destinations and provides step-by-step instructions for creating all flavors of graphics contexts.
* Paths discusses the basic elements that make up paths, shows how to create and paint them, shows how to set up a clipping area, and explains how blend modes affect painting.
* Color and Color Spaces discusses color values and using alpha values for transparency, and it describes how to create a color space, set colors, create color objects, and set rendering intent.
* Transforms describes the current transformation matrix and explains how to modify it, shows how to set up affine transforms, shows how to convert between user and device space, and provides background information on the mathematical operations that Quartz performs.
* Patterns defines what a pattern and its parts are, tells how Quartz renders them, and shows how to create colored and stenciled patterns.
* Shadows describes what shadows are, explains how they work, and shows how to paint with them.
* Gradients discusses axial and radial gradients and shows how to create and use CGShading and CGGradient objects.
* Transparency Layers gives examples of what transparency layers look like, discusses how they work, and provides step-by-step instructions for implementing them.
* Data Management in Quartz 2D discusses how to move data into and out of Quartz.
* Bitmap Images and Image Masks describes what makes up a bitmap image definition and shows how to use a bitmap image as a Quartz drawing primitive. It also describes masking techniques you can use on images and shows the various effects you can achieve by using blend modes when drawing images.
* Core Graphics Layer Drawing describes how to create and use drawing layers to achieve high-performance patterned drawing or to draw offscreen.
* PDF Document Creation, Viewing, and Transforming shows how to open and view PDF documents, apply transforms to them, create a PDF file, access PDF metadata, add links, and add security features (such as password protection).
* PDF Document Parsing describes how to use CGPDFScanner and CGPDFContentStream objects to parse and inspect PDF documents.
PostScript Conversion gives an overview of the functions you can use in Mac * OS X to convert a PostScript file to a PDF document. These functions are not available in iOS.
* Text describes Quartz 2D low-level support for text and glyphs, and alternatives that provide higher-level and Unicode text support. It also discusses how to copy font variations.
* Glossary defines the terms used in this guide.

###See Also

These items are essential reading for anyone using Quartz 2D:

* Quartz 2D Reference Collection provides a complete reference for the Quartz 2D application programming interface.
* Color Management Overview is a brief introduction to the principles of color perception, color spaces, and color management systems.
* Mailing lists. Join the quartz-dev mailing list to discuss problems using Quartz 2D.



##Overview of Quartz 2D
Quartz 2D is a two-dimensional drawing engine accessible in the iOS environment and from all Mac OS X application environments outside of the kernel. You can use the Quartz 2D application programming interface (API) to gain access to features such as path-based drawing, painting with transparency, shading, drawing shadows, transparency layers, color management, anti-aliased rendering, PDF document generation, and PDF metadata access. Whenever possible, Quartz 2D leverages the power of the graphics hardware.

In Mac OS X, Quartz 2D can work with all other graphics and imaging technologies—Core Image, Core Video, OpenGL, and QuickTime. It’s possible to create an image in Quartz from a QuickTime graphics importer, using the QuickTime function GraphicsImportCreateCGImage. See QuickTime Framework Reference for details. Moving Data Between Quartz 2D and Core Image in Mac OS X describes how you can provide images to Core Image, which is a framework that supports image processing.

Similarly, in iOS, Quartz 2D works with all available graphics and animation technologies, such as Core Animation, OpenGL ES, and the UIKit classes.

###The Page
Quartz 2D uses the painter’s model for its imaging. In the painter’s model, each successive drawing operation applies a layer of “paint” to an output “canvas,” often called a page. The paint on the page can be modified by overlaying more paint through additional drawing operations. An object drawn on the page cannot be modified except by overlaying more paint. This model allows you to construct extremely sophisticated images from a small number of powerful primitives.

Figure 1-1 shows how the painter’s model works. To get the image in the top part of the figure, the shape on the left was drawn first followed by the solid shape. The solid shape overlays the first shape, obscuring all but the perimeter of the first shape. The shapes are drawn in the opposite order in the bottom of the figure, with the solid shape drawn first. As you can see, in the painter’s model the drawing order is important.

######Figure 1-1  The painter’s model

![Smaller icon](https://developer.apple.com/library/content/documentation/GraphicsImaging/Conceptual/drawingwithquartz2d/Art/painters_model.gif")

The page may be a real sheet of paper (if the output device is a printer); it may be a virtual sheet of paper (if the output device is a PDF file); it may even be a bitmap image. The exact nature of the page depends on the particular graphics context you use.

###Drawing Destinations: The Graphics Context
A graphics context is an opaque data type (CGContextRef) that encapsulates the information Quartz uses to draw images to an output device, such as a PDF file, a bitmap, or a window on a display. The information inside a graphics context includes graphics drawing parameters and a device-specific representation of the paint on the page. All objects in Quartz are drawn to, or contained by, a graphics context.

You can think of a graphics context as a drawing destination, as shown in Figure 1-2. When you draw with Quartz, all device-specific characteristics are contained within the specific type of graphics context you use. In other words, you can draw the same image to a different device simply by providing a different graphics context to the same sequence of Quartz drawing routines. You do not need to perform any device-specific calculations; Quartz does it for you.

######Figure 1-2  Quartz drawing destinations
![Smaller icon](https://developer.apple.com/library/content/documentation/GraphicsImaging/Conceptual/drawingwithquartz2d/Art/draw_destinations.gif")

These graphics contexts are available to your application:

* A bitmap graphics context allows you to paint RGB colors, CMYK colors, or grayscale into a bitmap. A bitmap is a rectangular array (or raster) of pixels, each pixel representing a point in an image. Bitmap images are also called sampled images. See Creating a Bitmap Graphics Context.
* A PDF graphics context allows you to create a PDF file. In a PDF file, your drawing is preserved as a sequence of commands. There are some significant differences between PDF files and bitmaps:
	* PDF files, unlike bitmaps, may contain more than one page.
	* When you draw a page from a PDF file on a different device, the resulting image is optimized for the display characteristics of that device.
	* PDF files are resolution independent by nature—the size at which they are drawn can be increased or decreased infinitely without sacrificing image detail. The user-perceived quality of a bitmap image is tied to the resolution at which the bitmap is intended to be viewed.
See Creating a PDF Graphics Context.
* A window graphics context is a graphics context that you can use to draw into a window. Note that because Quartz 2D is a graphics engine and not a window management system, you use one of the application frameworks to obtain a graphics context for a window. 

See Creating a Window Graphics Context in Mac OS X for details.

* A layer context (CGLayerRef) is an offscreen drawing destination associated with another graphics context. It is designed for optimal performance when drawing the layer to the graphics context that created it. A layer context can be a much better choice for offscreen drawing than a bitmap graphics context. See Core Graphics Layer Drawing.
* When you want to print in Mac OS X, you send your content to a PostScript graphics context that is managed by the printing framework. See Obtaining a Graphics Context for Printing for more information.

###Quartz 2D Opaque Data Types

The Quartz 2D API defines a variety of opaque data types in addition to graphics contexts. Because the API is part of the Core Graphics framework, the data types and the routines that operate on them use the CG prefix.

Quartz 2D creates objects from opaque data types that your application operates on to achieve a particular drawing output. Figure 1-3 shows the sorts of results you can achieve when you apply drawing operations to three of the objects provided by Quartz 2D. For example:

* You can rotate and display a PDF page by creating a PDF page object, applying a rotation operation to the graphics context, and asking Quartz 2D to draw the page to a graphics context.
* You can draw a pattern by creating a pattern object, defining the shape that makes up the pattern, and setting up Quartz 2D to use the pattern as paint when it draws to a graphics context.
* You can fill an area with an axial or radial shading by creating a shading object, providing a function that determines the color at each point in the shading, and then asking Quartz 2D to use the shading as a fill color.

######Figure 1-3  Opaque data types are the basis of drawing primitives in Quartz 2D

![Smaller icon](https://developer.apple.com/library/content/documentation/GraphicsImaging/Conceptual/drawingwithquartz2d/Art/drawing_primitives.gif")

The opaque data types available in Quartz 2D include the following:

* CGPathRef, used for vector graphics to create paths that you fill or stroke. See Paths.
* CGImageRef, used to represent bitmap images and bitmap image masks based on sample data that you supply. See Bitmap Images and Image Masks.
* CGLayerRef, used to represent a drawing layer that can be used for repeated drawing (such as for backgrounds or patterns) and for offscreen drawing. See Core Graphics Layer Drawing
* CGPatternRef, used for repeated drawing. See Patterns.
* CGShadingRef and CGGradientRef, used to paint gradients. See Gradients.
* CGFunctionRef, used to define callback functions that take an arbitrary number of floating-point arguments. You use this data type when you create gradients for a shading. See Gradients.
* CGColorRef and CGColorSpaceRef, used to inform Quartz how to interpret color. See Color and Color Spaces.
* CGImageSourceRef and CGImageDestinationRef, which you use to move data into and out of Quartz. See Data Management in Quartz 2D and Image I/O Programming Guide.
* CGFontRef, used to draw text. See Text.
* CGPDFDictionaryRef, CGPDFObjectRef, CGPDFPageRef, CGPDFStream, * CGPDFStringRef, and CGPDFArrayRef, which provide access to PDF metadata. See * PDF Document Creation, Viewing, and Transforming.
* CGPDFScannerRef and CGPDFContentStreamRef, which parse PDF metadata. See PDF Document Parsing.
* CGPSConverterRef, used to convert PostScript to PDF. It is not available in iOS. See PostScript Conversion.

###Graphics States

Quartz modifies the results of drawing operations according to the parameters in the current graphics state. The graphics state contains parameters that would otherwise be taken as arguments to drawing routines. Routines that draw to a graphics context consult the graphics state to determine how to render their results. For example, when you call a function to set the fill color, you are modifying a value stored in the current graphics state. Other commonly used elements of the current graphics state include the line width, the current position, and the text font size.

The graphics context contains a stack of graphics states. When Quartz creates a graphics context, the stack is empty. When you save the graphics state, Quartz pushes a copy of the current graphics state onto the stack. When you restore the graphics state, Quartz pops the graphics state off the top of the stack. The popped state becomes the current graphics state.

To save the current graphics state, use the function CGContextSaveGState to push a copy of the current graphics state onto the stack. To restore a previously saved graphics state, use the function CGContextRestoreGState to replace the current graphics state with the graphics state that’s on top of the stack.

Note that not all aspects of the current drawing environment are elements of the graphics state. For example, the current path is not considered part of the graphics state and is therefore not saved when you call the function CGContextSaveGState. The graphics state parameters that are saved when you call this function are listed in Table 1-1.

######Table 1-1  Parameters that are associated with the graphics state



Parameters							 | Discussed in this chapter
----------------------------------- | ---------------------------
Current transformation matrix (CTM) | Transforms
Clipping area                       | Paths
Line: width, join, cap, dash, miter limit | Paths
Accuracy of curve estimation (flatness) | Paths
Anti-aliasing setting |Graphics Contexts
Color: fill and stroke settings | Color and Color Spaces
Alpha value (transparency) | Color and Color Spaces
Rendering intent | Color and Color Spaces
Color space: fill and stroke settings | Color and Color Spaces
Text: font, font size, character spacing, text drawing mode | Text
Blend mode | Paths and Bitmap Images and Image Masks

###Quartz 2D Coordinate Systems
A coordinate system, shown in Figure 1-4, defines the range of locations used to express the location and sizes of objects to be drawn on the page. You specify the location and size of graphics in the user-space coordinate system, or, more simply, the user space. Coordinates are defined as floating-point values.

######Figure 1-4  The Quartz coordinate system

![Smaller icon](https://developer.apple.com/library/content/documentation/GraphicsImaging/Conceptual/drawingwithquartz2d/Art/quartz_coordinates.gif")

Because different devices have different underlying imaging capabilities, the locations and sizes of graphics must be defined in a device-independent manner. For example, a screen display device might be capable of displaying no more than 96 pixels per inch, while a printer might be capable of displaying 300 pixels per inch. If you define the coordinate system at the device level (in this example, either 96 pixels or 300 pixels), objects drawn in that space cannot be reproduced on other devices without visible distortion. They will appear too large or too small.

Quartz accomplishes device independence with a separate coordinate system—user space—mapping it to the coordinate system of the output device—device space—using the current transformation matrix, or CTM. A matrix is a mathematical construct used to efficiently describe a set of related equations. The current transformation matrix is a particular type of matrix called an affine transform, which maps points from one coordinate space to another by applying translation, rotation, and scaling operations (calculations that move, rotate, and resize a coordinate system).

The current transformation matrix has a secondary purpose: It allows you to transform how objects are drawn. For example, to draw a box rotated by 45 degrees, you rotate the coordinate system of the page (the CTM) before you draw the box. Quartz draws to the output device using the rotated coordinate system.

A point in user space is represented by a coordinate pair (x,y), where x represents the location along the horizontal axis (left and right) and y represents the vertical axis (up and down). The origin of the user coordinate space is the point (0,0). The origin is located at the lower-left corner of the page, as shown in Figure 1-4. In the default coordinate system for Quartz, the x-axis increases as it moves from the left toward the right of the page. The y-axis increases in value as it moves from the bottom toward the top of the page.

Some technologies set up their graphics contexts using a different default coordinate system than the one used by Quartz. Relative to Quartz, such a coordinate system is a modified coordinate system and must be compensated for when performing some Quartz drawing operations. The most common modified coordinate system places the origin in the upper-left corner of the context and changes the y-axis to point towards the bottom of the page. A few places where you might see this specific coordinate system used are the following:

* In Mac OS X, a subclass of NSView that overrides its isFlipped method to return YES.
* In iOS, a drawing context returned by an UIView.
* In iOS, a drawing context created by calling the UIGraphicsBeginImageContextWithOptions function.

The reason UIKit returns Quartz drawing contexts with modified coordinate systems is that UIKit uses a different default coordinate convention; it applies the transform to Quartz contexts it creates so that they match its conventions. If your application wants to use the same drawing routines to draw to both a UIView object and a PDF graphics context (which is created by Quartz and uses the default coordinate system), you need to apply a transform so that the PDF graphics context receives the same modified coordinate system. To do this, apply a transform that translates the origin to the upper-left corner of the PDF context and scales the y-coordinate by -1.

Using a scaling transform to negate the y-coordinate alters some conventions in Quartz drawing. For example, if you call CGContextDrawImage to draw an image into the context, the image is modified by the transform when it is drawn into the destination. Similarly, path drawing routines accept parameters that specify whether an arc is drawn in a clockwise or counterclockwise direction in the default coordinate system. If a coordinate system is modified, the result is also modified, as if the image were reflected in a mirror. In Figure 1-5, passing the same parameters into Quartz results in a clockwise arc in the default coordinate system and a counterclockwise arc after the y-coordinate is negated by the transform.

######Figure 1-5  Modifying the coordinate system creates a mirrored image.

![Smaller icon](https://developer.apple.com/library/content/documentation/GraphicsImaging/Conceptual/drawingwithquartz2d/Art/flipped_coordinates.jpg")

It is up to your application to adjust any Quartz calls it makes to a context that has a transform applied to it. For example, if you want an image or PDF to draw correctly into a graphics context, your application may need to temporarily adjust the CTM of the graphics context. In iOS, if you use a UIImage object to wrap a CGImage object you create, you do not need to modify the CTM. The UIImage object automatically compensates for the modified coordinate system applied by UIKit.

```
Important: The above discussion is essential to understand if you plan to write applications that directly target Quartz on iOS, but it is not sufficient. On iOS 3.2 and later, when UIKit creates a drawing context for your application, it also makes additional changes to the context to match the default UIKIt conventions. In particular, patterns and shadows, which are not affected by the CTM, are adjusted separately so that their conventions match UIKit’s coordinate system. In this case, there is no equivalent mechanism to the CTM that your application can use to change a context created by Quartz to match the behavior for a context provided by UIKit; your application must recognize the what kind of context it is drawing into and adjust its behavior to match the expectations of the context.

```

###Memory Management: Object Ownership

Quartz uses the Core Foundation memory management model, in which objects are reference counted. When created, Core Foundation objects start out with a reference count of 1. You can increment the reference count by calling a function to retain the object, and decrement the reference count by calling a function to release the object. When the reference count is decremented to 0, the object is freed. This model allows objects to safely share references to other objects.

There are a few simple rules to keep in mind:

* If you create or copy an object, you own it, and therefore you must release it. That is, in general, if you obtain an object from a function with the words “Create” or “Copy” in its name, you must release the object when you’re done with it. Otherwise, a memory leak results.
* If you obtain an object from a function that does not contain the words “Create” or “Copy” in its name, you do not own a reference to the object, and you must not release it. The object will be released by its owner at some point in the future.
* If you do not own an object and you need to keep it around, you must retain it and release it when you’re done with it. You use the Quartz 2D functions specific to an object to retain and release that object. For example, if you receive a reference to a CGColorspace object, you use the functions CGColorSpaceRetain and CGColorSpaceRelease to retain and release the object as needed. You can also use the Core Foundation functions CFRetain and CFRelease, but you must be careful not to pass NULL to these functions.








##Graphics Contexts
A graphics context represents a drawing destination. It contains drawing parameters and all device-specific information that the drawing system needs to perform any subsequent drawing commands. A graphics context defines basic drawing attributes such as the colors to use when drawing, the clipping area, line width and style information, font information, compositing options, and several others.

You can obtain a graphics context by using Quartz context creation functions or by using higher-level functions provided by one of the Mac OS X frameworks or the UIKit framework in iOS. Quartz provides functions for various flavors of Quartz graphics contexts including bitmap and PDF, which you can use to create custom content.

This chapter shows you how to create a graphics context for a variety of drawing destinations. A graphics context is represented in your code by the data type CGContextRef, which is an opaque data type. After you obtain a graphics context, you can use Quartz 2D functions to draw to the context, perform operations (such as translations) on the context, and change graphics state parameters, such as line width and fill color.

###Drawing to a View Graphics Context in iOS
To draw to the screen in an iOS application, you set up a UIView object and implement its drawRect: method to perform drawing. The view’s drawRect: method is called when the view is visible onscreen and its contents need updating. Before calling your custom drawRect: method, the view object automatically configures its drawing environment so that your code can start drawing immediately. As part of this configuration, the UIView object creates a graphics context (a CGContextRef opaque type) for the current drawing environment. You obtain this graphics context in your drawRect: method by calling the UIKit function UIGraphicsGetCurrentContext.

The default coordinate system used throughout UIKit is different from the coordinate system used by Quartz. In UIKit, the origin is in the upper-left corner, with the positive-y value pointing downward. The UIView object modifies the CTM of the Quartz graphics context to match the UIKit conventions by translating the origin to the upper left corner of the view and inverting the y-axis by multiplying it by -1. For more information on modified-coordinate systems and the implications in your own drawing code, see Quartz 2D Coordinate Systems.

UIView objects are described in detail in View Programming Guide for iOS.

###Creating a Window Graphics Context in Mac OS X
When drawing in Mac OS X, you need to create a window graphics context that’s appropriate for the framework you are using. The Quartz 2D API itself provides no functions to obtain a windows graphics context. Instead, you use the Cocoa framework to obtain a context for a window created in Cocoa.

You obtain a Quartz graphics context from within the drawRect: routine of a Cocoa application using the following line of code:

```
CGContextRef myContext = [[NSGraphicsContext currentContext] graphicsPort];
```
The method currentContext returns the NSGraphicsContext instance of the current thread. The method graphicsPort returns the low-level, platform-specific graphics context represented by the receiver, which is a Quartz graphics context. (Don’t get confused by the method names; they are historical.) For more information see NSGraphicsContext Class Reference.

After you obtain the graphics context, you can call any of the Quartz 2D drawing functions in your Cocoa application. You can also mix Quartz 2D calls with Cocoa drawing calls. You can see an example of Quartz 2D drawing to a Cocoa view by looking at Figure 2-1. The drawing consists of two overlapping rectangles, an opaque red one and a partially transparent blue one. You’ll learn more about transparency in Color and Color Spaces. The ability to control how much you can “see through” colors is one of the hallmark features of Quartz 2D.

######Figure 2-1  A view in the Cocoa framework that contains Quartz drawing

![Smaller icon](https://developer.apple.com/library/content/documentation/GraphicsImaging/Conceptual/drawingwithquartz2d/Art/cocoa_draw.gif")

To create the drawing in Figure 2-1, you first create a Cocoa application Xcode project. In Interface Builder, drag a Custom View to the window and subclass it. Then write an implementation for the subclassed view, similar to what Listing 2-1 shows. For this example, the subclassed view is named MyQuartzView. The drawRect: method for the view contains all the Quartz drawing code. A detailed explanation for each numbered line of code appears following the listing.
```
Note: The drawRect: method of the NSView class is invoked automatically each time the view needs to be drawn. To find out more about overriding the drawRect: method, see NSView Class Reference.
```
######Listing 2-1  Drawing to a window graphics context

```
@implementation MyQuartzView
 
- (id)initWithFrame:(NSRect)frameRect
{
    self = [super initWithFrame:frameRect];
    return self;
}
 
- (void)drawRect:(NSRect)rect
{
    CGContextRef myContext = [[NSGraphicsContext // 1
                                currentContext] graphicsPort];
   // ********** Your drawing code here ********** // 2
    CGContextSetRGBFillColor (myContext, 1, 0, 0, 1);// 3
    CGContextFillRect (myContext, CGRectMake (0, 0, 200, 100 ));// 4
    CGContextSetRGBFillColor (myContext, 0, 0, 1, .5);// 5
    CGContextFillRect (myContext, CGRectMake (0, 0, 100, 200));// 6
  }
 
@end
```

Here’s what the code does:

1. Obtains a graphics context for the view.
2. This is where you insert your drawing code. The four lines of code that follow are examples of using Quartz 2D functions.
3. Sets a red fill color that’s fully opaque. For information on colors and alpha (which sets opacity), see Color and Color Spaces.
4. Fills a rectangle whose origin is (0,0) and whose width is 200 and height is 100. For information on drawing rectangles, see Paths.
5. Sets a blue fill color that’s partially transparent.
6. Fills a rectangle whose origin is (0,0) and whose width is 100 and height is 200.


###Creating a PDF Graphics Context
When you create a PDF graphics context and draw to that context, Quartz records your drawing as a series of PDF drawing commands written to a file. You supply a location for the PDF output and a default media box—a rectangle that specifies bounds of the page. Figure 2-2 shows the result of drawing to a PDF graphics context and then opening the resulting PDF in Preview.

######Figure 2-2  A PDF created by using CGPDFContextCreateWithURL

![Smaller icon](https://developer.apple.com/library/content/documentation/GraphicsImaging/Conceptual/drawingwithquartz2d/Art/pdf_context_draw.gif")

The Quartz 2D API provides two functions that create a PDF graphics context:

* CGPDFContextCreateWithURL, which you use when you want to specify the location for the PDF output as a Core Foundation URL. Listing 2-2 shows how to use this function to create a PDF graphics context.
* CGPDFContextCreate, which you use when you want the PDF output sent to a data consumer. (For more information see Data Management in Quartz 2D.) Listing 2-3 shows how to use this function to create a PDF graphics context.
A detailed explanation for each numbered line of code follows each listing.

```
iOS Note: A PDF graphics context in iOS uses the default coordinate system provided by Quartz, without applying a transform to match the UIKit coordinate system. If your application plans on sharing drawing code between your PDF graphics context and the graphics context provided by UIView object, your application should modify the CTM of the PDF graphics context to modify the coordinate system. See Quartz 2D Coordinate Systems.
```
######Listing 2-2  Calling CGPDFContextCreateWithURL to create a PDF graphics context
```
CGContextRef MyPDFContextCreate (const CGRect *inMediaBox,
                                    CFStringRef path)
{
    CGContextRef myOutContext = NULL;
    CFURLRef url;
 
    url = CFURLCreateWithFileSystemPath (NULL, // 1
                                path,
                                kCFURLPOSIXPathStyle,
                                false);
    if (url != NULL) {
        myOutContext = CGPDFContextCreateWithURL (url,// 2
                                        inMediaBox,
                                        NULL);
        CFRelease(url);// 3
    }
    return myOutContext;// 4
}
```

Here’s what the code does:

1. Calls the Core Foundation function to create a CFURL object from the CFString object supplied to the MyPDFContextCreate function. You pass NULL as the first parameter to use the default allocator. You also need to specify a path style, which for this example is a POSIX-style pathname.
2. Calls the Quartz 2D function to create a PDF graphics context using the PDF location just created (as a CFURL object) and a rectangle that specifies the bounds of the PDF. The rectangle (CGRect) was passed to the MyPDFContextCreate function and is the default page media bounding box for the PDF.
3. Releases the CFURL object.
4. Returns the PDF graphics context. The caller must release the graphics context when it is no longer needed.

######Listing 2-3  Calling CGPDFContextCreate to create a PDF graphics context

```
CGContextRef MyPDFContextCreate (const CGRect *inMediaBox,
                                    CFStringRef path)
{
    CGContextRef        myOutContext = NULL;
    CFURLRef            url;
    CGDataConsumerRef   dataConsumer;
 
    url = CFURLCreateWithFileSystemPath (NULL, // 1
                                        path,
                                        kCFURLPOSIXPathStyle,
                                        false);
 
    if (url != NULL)
    {
        dataConsumer = CGDataConsumerCreateWithURL (url);// 2
        if (dataConsumer != NULL)
        {
            myOutContext = CGPDFContextCreate (dataConsumer, // 3
                                        inMediaBox,
                                        NULL);
            CGDataConsumerRelease (dataConsumer);// 4
        }
        CFRelease(url);// 5
    }
    return myOutContext;// 6
}
```

Here’s what the code does:

1. Calls the Core Foundation function to create a CFURL object from the CFString object supplied to the MyPDFContextCreate function. You pass NULL as the first parameter to use the default allocator. You also need to specify a path style, which for this example is a POSIX-style pathname.
2. Creates a Quartz data consumer object using the CFURL object. If you don’t want to use a CFURL object (for example, you want to place the PDF data in a location that can’t be specified by a CFURL object), you can instead create a data consumer from a set of callback functions that you implement in your application. For more information, see Data Management in Quartz 2D.
3. Calls the Quartz 2D function to create a PDF graphics context passing as parameters the data consumer and the rectangle (of type CGRect) that was passed to the MyPDFContextCreate function. This rectangle is the default page media bounding box for the PDF.
4. Releases the data consumer.
5. Releases the CFURL object.
6. Returns the PDF graphics context. The caller must release the graphics context when it is no longer needed.

Listing 2-4 shows how to call the MyPDFContextCreate routine and draw to it. A detailed explanation for each numbered line of code appears following the listing.

###### Listing 2-4  Drawing to a PDF graphics context
```
CGRect mediaBox;// 1
 
    mediaBox = CGRectMake (0, 0, myPageWidth, myPageHeight);// 2
    myPDFContext = MyPDFContextCreate (&mediaBox, CFSTR("test.pdf"));// 3
 
    CFStringRef myKeys[1];// 4
    CFTypeRef myValues[1];
    myKeys[0] = kCGPDFContextMediaBox;
    myValues[0] = (CFTypeRef) CFDataCreate(NULL,(const UInt8 *)&mediaBox, sizeof (CGRect));
    CFDictionaryRef pageDictionary = CFDictionaryCreate(NULL, (const void **) myKeys,
                                                        (const void **) myValues, 1,
                                                        &kCFTypeDictionaryKeyCallBacks,
                                                        & kCFTypeDictionaryValueCallBacks);
    CGPDFContextBeginPage(myPDFContext, &pageDictionary);// 5
        // ********** Your drawing code here **********// 6
        CGContextSetRGBFillColor (myPDFContext, 1, 0, 0, 1);
        CGContextFillRect (myPDFContext, CGRectMake (0, 0, 200, 100 ));
        CGContextSetRGBFillColor (myPDFContext, 0, 0, 1, .5);
        CGContextFillRect (myPDFContext, CGRectMake (0, 0, 100, 200 ));
    CGPDFContextEndPage(myPDFContext);// 7
    CFRelease(pageDictionary);// 8
    CFRelease(myValues[0]);
    CGContextRelease(myPDFContext);
```

Here’s what the code does:

1. Declares a variable for the rectangle that you use to define the PDF media box.
2. Sets the origin of the media box to (0,0) and the width and height to variables supplied by the application.
3. Calls the function MyPDFContextCreate (See Listing 2-3) to obtain a PDF graphics context, supplying a media box and a pathname. The macro CFSTR converts a string to a CFStringRef data type.
4. Sets up a dictionary with the page options. In this example, only the media box is specified. You don’t have to pass the same rectangle you used to set up the PDF graphics context. The media box you add here supersedes the rectangle you pass to set up the PDF graphics context.
5. Signals the start of a page. This function is used for page-oriented graphics, which is what PDF drawing is.
6. Calls Quartz 2D drawing functions. You replace this and the following four lines of code with the drawing code appropriate for your application.
7. Signals the end of the PDF page.
8. Releases the dictionary and the PDF graphics context when they are no longer needed.

You can write any content to a PDF that’s appropriate for your application—images, text, path drawing—and you can add links and encryption. For more information see PDF Document Creation, Viewing, and Transforming.





###Creating a Bitmap Graphics Context

A bitmap graphics context accepts a pointer to a memory buffer that contains storage space for the bitmap. When you paint into the bitmap graphics context, the buffer is updated. After you release the graphics context, you have a fully updated bitmap in the pixel format you specify.

```
Note: Bitmap graphics contexts are sometimes used for drawing offscreen. Before you decide to use a bitmap graphics context for this purpose, see Core Graphics Layer Drawing. CGLayer objects (CGLayerRef) are optimized for offscreen drawing because, whenever possible, Quartz caches layers on the video card.
```
```
iOS Note: iOS applications should use the function UIGraphicsBeginImageContextWithOptions instead of using the low-level Quartz functions described here. If your application creates an offscreen bitmap using Quartz, the coordinate system used by bitmap graphics context is the default Quartz coordinate system. In contrast, if your application creates an image context by calling the function UIGraphicsBeginImageContextWithOptions, UIKit applies the same transformation to the context’s coordinate system as it does to a UIView object’s graphics context. This allows your application to use the same drawing code for either without having to worry about different coordinate systems. Although your application can manually adjust the coordinate transformation matrix to achieve the correct results, in practice, there is no performance benefit to doing so.
```

You use the function CGBitmapContextCreate to create a bitmap graphics context. This function takes the following parameters:

* data. Supply a pointer to the destination in memory where you want the drawing rendered. The size of this memory block should be at least (bytesPerRow*height) bytes.
* width. Specify the width, in pixels, of the bitmap.
* height. Specify the height, in pixels, of the bitmap.
* bitsPerComponent. Specify the number of bits to use for each component of a pixel in memory. For example, for a 32-bit pixel format and an RGB color space, you would specify a value of 8 bits per component. See Supported Pixel Formats.
* bytesPerRow. Specify the number of bytes of memory to use per row of the bitmap.

```
Tip:  When you create a bitmap graphics context, you’ll get the best performance if you make sure the data and bytesPerRow are 16-byte aligned.
```

* colorspace. The color space to use for the bitmap context. You can provide a Gray, RGB, CMYK, or NULL color space when you create a bitmap graphics context. For detailed information on color spaces and color management principles, see Color Management Overview. For information on creating and using color spaces in Quartz, see Color and Color Spaces. For information about supported color spaces, see Color Spaces and Bitmap Layout in the Bitmap Images and Image Masks chapter.
* bitmapInfo. Bitmap layout information, expressed as a CGBitmapInfo constant, that specifies whether the bitmap should contain an alpha component, the relative location of the alpha component (if there is one) in a pixel, whether the alpha component is premultiplied, and whether the color components are integer or floating-point values. For detailed information on what these constants are, when each is used, and Quartz-supported pixel formats for bitmap graphics contexts and images, see Color Spaces and Bitmap Layout in the Bitmap Images and Image Masks chapter.


Listing 2-5 shows how to create a bitmap graphics context. When you draw into the resulting bitmap graphics context, Quartz records your drawing as bitmap data in the specified block of memory. A detailed explanation for each numbered line of code follows the listing.

######Listing 2-5  Creating a bitmap graphics context
```
CGContextRef MyCreateBitmapContext (int pixelsWide,
                            int pixelsHigh)
{
    CGContextRef    context = NULL;
    CGColorSpaceRef colorSpace;
    void *          bitmapData;
    int             bitmapByteCount;
    int             bitmapBytesPerRow;
 
    bitmapBytesPerRow   = (pixelsWide * 4);// 1
    bitmapByteCount     = (bitmapBytesPerRow * pixelsHigh);
 
    colorSpace = CGColorSpaceCreateWithName(kCGColorSpaceGenericRGB);// 2
    bitmapData = calloc( bitmapByteCount );// 3
    if (bitmapData == NULL)
    {
        fprintf (stderr, "Memory not allocated!");
        return NULL;
    }
    context = CGBitmapContextCreate (bitmapData,// 4
                                    pixelsWide,
                                    pixelsHigh,
                                    8,      // bits per component
                                    bitmapBytesPerRow,
                                    colorSpace,
                                    kCGImageAlphaPremultipliedLast);
    if (context== NULL)
    {
        free (bitmapData);// 5
        fprintf (stderr, "Context not created!");
        return NULL;
    }
    CGColorSpaceRelease( colorSpace );// 6
 
    return context;// 7
}
```
Here’s what the code does:

1. Declares a variable to represent the number of bytes per row. Each pixel in the bitmap in this example is represented by 4 bytes; 8 bits each of red, green, blue, and alpha.
2. Creates a generic RGB color space. You can also create a CMYK color space. See Color and Color Spaces for more information and for a discussion of generic color spaces versus device dependent ones.
3. Calls the calloc function to create and clear a block of memory in which to store the bitmap data. This example creates a 32-bit RGBA bitmap (that is, an array with 32 bits per pixel, each pixel containing 8 bits each of red, green, blue, and alpha information). Each pixel in the bitmap occupies 4 bytes of memory. In Mac OS X 10.6 and iOS 4, this step can be omitted—if you pass NULL as bitmap data, Quartz automatically allocates space for the bitmap.
4. Creates a bitmap graphics context, supplying the bitmap data, the width and height of the bitmap, the number of bits per component, the bytes per row, the color space, and a constant that specifies whether the bitmap should contain an alpha channel and its relative location in a pixel. The constant kCGImageAlphaPremultipliedLast indicates that the alpha component is stored in the last byte of each pixel and that the color components have already been multiplied by this alpha value. See The Alpha Value for more information on premultiplied alpha.
5. If the context isn’t created for some reason, frees the memory allocated for the bitmap data.
6. Releases the color space.
7. Returns the bitmap graphics context. The caller must release the graphics context when it is no longer needed.


Listing 2-6 shows code that calls MyCreateBitmapContext to create a bitmap graphics context, uses the bitmap graphics context to create a CGImage object, then draws the resulting image to a window graphics context. Figure 2-3 shows the image drawn to the window. A detailed explanation for each numbered line of code follows the listing.

######Listing 2-6  Drawing to a bitmap graphics context
```
    CGRect myBoundingBox;// 1
 
    myBoundingBox = CGRectMake (0, 0, myWidth, myHeight);// 2
    myBitmapContext = MyCreateBitmapContext (400, 300);// 3
    // ********** Your drawing code here ********** // 4
    CGContextSetRGBFillColor (myBitmapContext, 1, 0, 0, 1);
    CGContextFillRect (myBitmapContext, CGRectMake (0, 0, 200, 100 ));
    CGContextSetRGBFillColor (myBitmapContext, 0, 0, 1, .5);
    CGContextFillRect (myBitmapContext, CGRectMake (0, 0, 100, 200 ));
    myImage = CGBitmapContextCreateImage (myBitmapContext);// 5
    CGContextDrawImage(myContext, myBoundingBox, myImage);// 6
    char *bitmapData = CGBitmapContextGetData(myBitmapContext); // 7
    CGContextRelease (myBitmapContext);// 8
    if (bitmapData) free(bitmapData); // 9
    CGImageRelease(myImage);// 10
```

Here’s what the code does:

1. Declares a variable to store the origin and dimensions of the bounding box into which Quartz will draw an image created from the bitmap graphics context.
2. Sets the origin of the bounding box to (0,0) and the width and height to variables previously declared, but whose declaration are not shown in this code.
3. Calls the application-supplied function MyCreateBitmapContext (see Listing 2-5) to create a bitmap context that is 400 pixels wide and 300 pixels high. You can create a bitmap graphics context using any dimensions that are appropriate for your application.
4. Calls Quartz 2D functions to draw into the bitmap graphics context. You would replace this and the next four lines of code with drawing code appropriate for your application.
5. Creates a Quartz 2D image (CGImageRef) from the bitmap graphics context.
6. Draws the image into the location in the window graphics context that is specified by the bounding box. The bounding box specifies the location and dimensions in user space in which to draw the image.
This example does not show the creation of the window graphics context. See Creating a Window Graphics Context in Mac OS X for information on how to create one.

7. Gets the bitmap data associated with the bitmap graphics context.
8. Releases the bitmap graphics context when it is no longer needed.
9. Free the bitmap data if it exists.
10. Releases the image when it is no longer needed.

######Figure 2-3  An image created from a bitmap graphics context and drawn to a window graphics context

![Smaller icon](https://developer.apple.com/library/content/documentation/GraphicsImaging/Conceptual/drawingwithquartz2d/Art/cocoa_draw.gif")

###Supported Pixel Formats
Table 2-1 summarizes the pixel formats that are supported for bitmap graphics context, the associated color space (cs), and the version of Mac OS X in which the format was first available. The pixel format is specified as bits per pixel (bpp) and bits per component (bpc). The table also includes the bitmap information constant associated with that pixel format. See CGImage Reference for details on what each of the bitmap information format constants represent.

######Table 2-1  Pixel formats supported for bitmap graphics contexts

CS  | Pixel format and bitmap information constant              |     Availability
--- | ----------------------------------------------------------|-----------------
Null | 8 bpp, 8 bpc, kCGImageAlphaOnly |Mac OS X, iOS
Gray | 8 bpp, 8 bpc,kCGImageAlphaNone |  Mac OS X, iOS
Gray | 8 bpp, 8 bpc,kCGImageAlphaOnly |Mac OS X, iOS
Gray | 16 bpp, 16 bpc, kCGImageAlphaNone | Mac OS X
Gray | 32 bpp, 32 bpc, kCGImageAlphaNone|kCGBitmapFloatComponents | Mac OS X
RGB | 16 bpp, 5 bpc, kCGImageAlphaNoneSkipFirst | Mac OS X, iOS
RGB | 32 bpp, 8 bpc, kCGImageAlphaNoneSkipFirst | Mac OS X, iOS
RGB | 32 bpp, 8 bpc, kCGImageAlphaNoneSkipLast  |Mac OS X, iOS
RGB | 32 bpp, 8 bpc, kCGImageAlphaPremultipliedFirst |Mac OS X, iOS
RGB | 32 bpp, 8 bpc, kCGImageAlphaPremultipliedLast | Mac OS X, iOS
RGB | 64 bpp, 16 bpc, kCGImageAlphaPremultipliedLast | Mac OS X
RGB | 64 bpp, 16 bpc, kCGImageAlphaNoneSkipLast | Mac OS X
RGB | 128 bpp, 32 bpc, kCGImageAlphaNoneSkipLast |kCGBitmapFloatComponents | Mac OS X
RGB | 128 bpp, 32 bpc, kCGImageAlphaPremultipliedLast |kCGBitmapFloatComponents | Mac OS X
CMYK | 32 bpp, 8 bpc, kCGImageAlphaNone | Mac OS X
CMYK | 64 bpp, 16 bpc, kCGImageAlphaNone | Mac OS X
CMYK | 128 bpp, 32 bpc, kCGImageAlphaNone |kCGBitmapFloatComponents | Mac OS X


###Anti-Aliasing
Bitmap graphics contexts support anti-aliasing, which is the process of artificially correcting the jagged (or aliased) edges you sometimes see in bitmap images when text or shapes are drawn. These jagged edges occur when the resolution of the bitmap is significantly lower than the resolution of your eyes. To make objects appear smooth in the bitmap, Quartz uses different colors for the pixels that surround the outline of the shape. By blending the colors in this way, the shape appears smooth. You can see the effect of using anti-aliasing in Figure 2-4. You can turn anti-aliasing off for a particular bitmap graphics context by calling the function CGContextSetShouldAntialias. The anti-aliasing setting is part of the graphics state.

You can control whether to allow anti-aliasing for a particular graphics context by using the function CGContextSetAllowsAntialiasing. Pass true to this function to allow anti-aliasing; false not to allow it. This setting is not part of the graphics state. Quartz performs anti-aliasing when the context and the graphic state settings are set to true.

######Figure 2-4  A comparison of aliased and anti-aliasing drawing

![Smaller icon](https://developer.apple.com/library/content/documentation/GraphicsImaging/Conceptual/drawingwithquartz2d/Art/antialias.jpg)


###Obtaining a Graphics Context for Printing
Cocoa applications in Mac OS X implement printing through custom NSView subclasses. A view is told to print by invoking its print: method. The view then creates a graphics context that targets a printer and calls its drawRect: method. Your application uses the same drawing code to draw to the printer that it uses to draw to the screen. It can also customize the drawRect: call to an image to the printer that is different from the one sent to the screen.

For a detailed discussion of printing in Cocoa, see Printing Programming Guide for Mac.





##Paths
A path defines one or more shapes, or subpaths. A subpath can consist of straight lines, curves, or both. It can be open or closed. A subpath can be a simple shape, such as a line, circle, rectangle, or star, or a more complex shape such as the silhouette of a mountain range or an abstract doodle. Figure 3-1 shows some of the paths you can create. The straight line (at the upper left of the figure) is dashed; lines can also be solid. The squiggly path (in the middle top) is made up of several curves and is an open path. The concentric circles are filled, but not stroked. The State of California is a closed path, made up of many curves and lines, and the path is both stroked and filled. The stars illustrate two options for filling paths, which you’ll read about later in this chapter.

######Figure 3-1  Quartz supports path-based drawing

![Smaller icon](https://developer.apple.com/library/content/documentation/GraphicsImaging/Conceptual/drawingwithquartz2d/Art/path_vector_examples.gif)

In this chapter, you’ll learn about the building blocks that make up paths, how to stroke and paint paths, and the parameters that affect the appearance of paths.

###Path Creation and Path Painting

Path creation and path painting are separate tasks. First you create a path. When you want to render a path, you request Quartz to paint it. As you can see in Figure 3-1, you can choose to stroke the path, fill the path, or both stroke and fill the path. You can also use a path to constrain the drawing of other objects within the bounds of the path creating, in effect, a clipping area.

Figure 3-2 shows a path that has been painted and that contains two subpaths. The subpath on the left is a rectangle, and the subpath on the right is an abstract shape made up of straight lines and curves. Each subpath is filled and its outline stroked.

######Figure 3-2  A path that contains two shapes, or subpaths
![Smaller icon](https://developer.apple.com/library/content/documentation/GraphicsImaging/Conceptual/drawingwithquartz2d/Art/subpaths.gif)

Figure 3-3 shows multiple paths drawn independently. Each path contains a randomly generated curve, some of which are filled and others stroked. Drawing is constrained to a circular area by a clipping area.

######Figure 3-3  A clipping area constrains drawing

![Smaller icon](https://developer.apple.com/library/content/documentation/GraphicsImaging/Conceptual/drawingwithquartz2d/Art/circle_clipping.gif)

###The Building Blocks

Subpaths are built from lines, arcs, and curves. Quartz also provides convenience functions to add rectangles and ellipses with a single function call. Points are also essential building blocks of paths because points define starting and ending locations of shapes.


####Points
Points are x and y coordinates that specify a location in user space. You can call the function CGContextMoveToPoint to specify a starting position for a new subpath. Quartz keeps track of the current point, which is the last location used for path construction. For example, if you call the function CGContextMoveToPoint to set a location at (10,10), that moves the current point to (10,10). If you then draw a horizontal line 50 units long, the last point on the line, that is, (60,10), becomes the current point. Lines, arcs, and curves are always drawn starting from the current point.

Most of the time you specify a point by passing to Quartz functions two floating-point values to specify x and y coordinates. Some functions require that you pass a CGPoint data structure, which holds two floating-point values.

####Lines
A line is defined by its endpoints. Its starting point is always assumed to be the current point, so when you create a line, you specify only its endpoint. You use the function CGContextAddLineToPoint to append a single line to a subpath.

You can add a series of connected lines to a path by calling the function CGContextAddLines. You pass this function an array of points. The first point must be the starting point of the first line; the remaining points are endpoints. Quartz begins a new subpath at the first point and connects a straight line segment to each endpoint.

####Arcs
Arcs are circle segments. Quartz provides two functions that create arcs. The function CGContextAddArc creates a curved segment from a circle. You specify the center of the circle, the radius, and the radial angle (in radians). You can create a full circle by specifying a radial angle of 2 pi. Figure 3-4 shows multiple paths drawn independently. Each path contains a randomly generated circle; some are filled and others are stroked.

######Figure 3-4  Multiple paths; each path contains a randomly generated circle
![Smaller icon](https://developer.apple.com/library/content/documentation/GraphicsImaging/Conceptual/drawingwithquartz2d/Art/circles.gif)

The function CGContextAddArcToPoint is ideal to use when you want to round the corners of a rectangle. Quartz uses the endpoints you supply to create two tangent lines. You also supply the radius of the circle from which Quartz slices the arc. The center point of the arc is the intersection of two radii, each of which is perpendicular to one of the two tangent lines. Each endpoint of the arc is a tangent point on one of the tangent lines, as shown in Figure 3-5. The red portion of the circle is what’s actually drawn.

######Figure 3-5  Defining an arc with two tangent lines and a radius

![Smaller icon](https://developer.apple.com/library/content/documentation/GraphicsImaging/Conceptual/drawingwithquartz2d/Art/rounded_corner.gif)

If the current path already contains a subpath, Quartz appends a straight line segment from the current point to the starting point of the arc. If the current path is empty, Quartz creates a new subpath at the starting point for the arc and does not add the initial straight line segment.

###Curves


Quadratic and cubic Bézier curves are algebraic curves that can specify any number of interesting curvilinear shapes. Points on these curves are calculated by applying a polynomial formula to starting and ending points, and one or more control points. Shapes defined in this way are the basis for vector graphics. A formula is much more compact to store than an array of bits and has the advantage that the curve can be re-created at any resolution.

Figure 3-6 shows a variety of curves created by drawing multiple paths independently. Each path contains a randomly generated curve; some are filled and others are stroked.


######Figure 3-6  Multiple paths; each path contains a randomly generated curve
![Smaller icon](https://developer.apple.com/library/content/documentation/GraphicsImaging/Conceptual/drawingwithquartz2d/Art/bezier_paths.gif)

The polynomial formulas that give to rise to quadratic and cubic Bézier curves, and the details on how to generate the curves from the formulas, are discussed in many mathematics texts and online sources that describe computer graphics. These details are not discussed here.

You use the function CGContextAddCurveToPoint to append a cubic Bézier curve from the current point, using control points and an endpoint you specify. Figure 3-7 shows the cubic Bézier curve that results from the current point, control points, and endpoint shown in the figure. The placement of the two control points determines the geometry of the curve. If the control points are both above the starting and ending points, the curve arches upward. If the control points are both below the starting and ending points, the curve arches downward.

######Figure 3-7  A cubic Bézier curve uses two control points

![Smaller icon](https://developer.apple.com/library/content/documentation/GraphicsImaging/Conceptual/drawingwithquartz2d/Art/cubic_bezier_curve.gif)

You can append a quadratic Bézier curve from the current point by calling the function CGContextAddQuadCurveToPoint, and specifying a control point and an endpoint. Figure 3-8 shows two curves that result from using the same endpoints but different control points. The control point determines the direction that the curve arches. It’s not possible to create as many interesting shapes with a quadratic Bézier curve as you can with a cubic one because quadratic curves use only one control point. For example, it’s not possible to create a crossover using a single control point.

######Figure 3-8  A quadratic Bézier curve uses one control point

![Smaller icon](https://developer.apple.com/library/content/documentation/GraphicsImaging/Conceptual/drawingwithquartz2d/Art/quadratic_bezier_curve.gif)

###Closing a Subpath

To close the current subpath, your application should call CGContextClosePath. This function adds a line segment from the current point to the starting point of the subpath and closes the subpath. Lines, arcs, and curves that end at the starting point of a subpath do not actually close the subpath. You must explicitly call CGContextClosePath to close a subpath.

Some Quartz functions treat a path’s subpaths as if they were closed by your application. Those commands treat each subpath as if your application had called CGContextClosePath to close it, implicitly adding a line segment to the starting point of the subpath.

After closing a subpath, if your application makes additional calls to add lines, arcs, or curves to the path, Quartz begins a new subpath starting at the starting point of the subpath you just closed.

###Ellipses
An ellipse is essentially a squashed circle. You create one by defining two focus points and then plotting all the points that lie at a distance such that adding the distance from any point on the ellipse to one focus to the distance from that same point to the other focus point is always the same value. Figure 3-9 shows multiple paths drawn independently. Each path contains a randomly generated ellipse; some are filled and others are stroked.

######Figure 3-9  Multiple paths; each path contains a randomly generated ellipse

![Smaller icon](https://developer.apple.com/library/content/documentation/GraphicsImaging/Conceptual/drawingwithquartz2d/Art/ellipses.gif)

You can add an ellipse to the current path by calling the function CGContextAddEllipseInRect. You supply a rectangle that defines the bounds of the ellipse. Quartz approximates the ellipse using a sequence of Bézier curves. The center of the ellipse is the center of the rectangle. If the width and height of the rectangle are equal (that is, a square), the ellipse is circular, with a radius equal to one-half the width (or height) of the rectangle. If the width and height of the rectangle are unequal, they define the major and minor axes of the ellipse.

The ellipse that is added to the path starts with a move-to operation and ends with a close-subpath operation, with all moves oriented in the clockwise direction.

###Rectangles
You can add a rectangle to the current path by calling the function CGContextAddRect. You supply a CGRect structure that contains the origin of the rectangle and its width and height.

The rectangle that is added to the path starts with a move-to operation and ends with a close-subpath operation, with all moves oriented in the counter-clockwise direction.

You can add many rectangles to the current path by calling the function CGContextAddRects and supplying an array of CGRect structures. Figure 3-10 shows multiple paths drawn independently. Each path contains a randomly generated rectangle; some are filled and others are stroked.

######Figure 3-10  Multiple paths; each path contains a randomly generated rectangle

![Smaller icon](https://developer.apple.com/library/content/documentation/GraphicsImaging/Conceptual/drawingwithquartz2d/Art/rectangles.gif)

###Creating a Path

When you want to construct a path in a graphics context, you signal Quartz by calling the function CGContextBeginPath . Next, you set the starting point for the first shape, or subpath, in the path by calling the function CGContextMoveToPoint. After you establish the first point, you can add lines, arcs, and curves to the path, keeping in mind the following:

* Before you begin a new path, call the function CGContextBeginPath.
* Lines, arcs, and curves are drawn starting at the current point. An empty path has no current point; you must call CGContextMoveToPoint to set the starting point for the first subpath or call a convenience function that implicitly does this for you.
* When you want to close the current subpath within a path, call the function CGContextClosePath to connect a segment to the starting point of the subpath. Subsequent path calls begin a new subpath, even if you do not explicitly set a new starting point.
* When you draw arcs, Quartz draws a line between the current point and the starting point of the arc.
* Quartz routines that add ellipses and rectangles add a new closed subpath to the path.
* You must call a painting function to fill or stroke the path because creating a path does not draw the path. See Painting a Path for detailed information.


After you paint a path, it is flushed from the graphics context. You might not want to lose your path so easily, especially if it depicts a complex scene you want to use over and over again. For that reason, Quartz provides two data types for creating reusable paths—CGPathRef and CGMutablePathRef. You can call the function CGPathCreateMutable to create a mutable CGPath object to which you can add lines, arcs, curves, and rectangles. Quartz provides a set of CGPath functions that parallel the functions discussed in The Building Blocks. The path functions operate on a CGPath object instead of a graphics context. These functions are:

* CGPathCreateMutable, which replacesCGContextBeginPath
* CGPathMoveToPoint, which replaces CGContextMoveToPoint
* CGPathAddLineToPoint, which replaces CGContextAddLineToPoint
* CGPathAddCurveToPoint, which replaces CGContextAddCurveToPoint
* CGPathAddEllipseInRect, which replaces CGContextAddEllipseInRect
* CGPathAddArc, which replaces CGContextAddArc
* CGPathAddRect, which replaces CGContextAddRect
* CGPathCloseSubpath, which replaces CGContextClosePath


See Quartz 2D Reference Collection for a complete list of the path functions.

When you want to append the path to a graphics context, you call the function CGContextAddPath. The path stays in the graphics context until Quartz paints it. You can add the path again by calling CGContextAddPath.

```
Note:  You can replace the path in a graphics context with the stroked version of the path by calling the function CGContextReplacePathWithStrokedPath.
```

###Painting a Path


You can paint the current path by stroking or filling or both. Stroking paints a line that straddles the path. Filling paints the area contained within the path. Quartz has functions that let you stroke a path, fill a path, or both stroke and fill a path. The characteristics of the stroked line (width, color, and so forth), the fill color, and the method Quartz uses to calculate the fill area are all part of the graphics state (see Graphics States).

####Parameters That Affect Stroking
You can affect how a path is stroked by modifying the parameters listed in Table 3-1. These parameters are part of the graphics state, which means that the value you set for a parameter affects all subsequent stroking until you set the parameter to another value.

######Table 3-1  Parameters that affect how Quartz strokes the current path
Parameter       | Function to set parameter value
--------------- | ------------------------------------------------------------
Line width      |CGContextSetLineWidth
Line join | CGContextSetLineJoin
Line cap | CGContextSetLineCap
Miter limit | CGContextSetMiterLimit
Line dash pattern | CGContextSetLineDash
Stroke color space | CGContextSetStrokeColorSpace
Stroke color | CGContextSetStrokeColorCGContextSetStrokeColorWithColor
Stroke pattern | CGContextSetStrokePattern

The line width is the total width of the line, expressed in units of the user space. The line straddles the path, with half of the total width on either side.

The line join specifies how Quartz draws the junction between connected line segments. Quartz supports the line join styles described in Table 3-2. The default style is miter join.

######Table 3-2  Line join styles


Style          | Appearance        | Description
-------------- | ------------------|---------------
Miter join | ![Smaller icon](https://developer.apple.com/library/content/documentation/GraphicsImaging/Conceptual/drawingwithquartz2d/Art/linejoinmiter.gif) | Quartz extends the outer edges of the strokes for the two segments until they meet at an angle, as in a picture frame. If the segments meet at too sharp an angle, a bevel join is used instead. A segment is too sharp if the length of the miter divided by the line width is greater than the miter limit.
Round join | ![Smaller icon](https://developer.apple.com/library/content/documentation/GraphicsImaging/Conceptual/drawingwithquartz2d/Art/linejoinround.gif) | Quartz draws a semicircular arc with a diameter equal to the line width around the endpoint. The enclosed area is filled in.
Bevel join | ![Smaller icon](https://developer.apple.com/library/content/documentation/GraphicsImaging/Conceptual/drawingwithquartz2d/Art/linejoinbevel.gif)  | Quartz finishes the two segments with butt caps. The resulting notch beyond the ends of the segments is filled with a triangle.

The line cap specifies the method used by CGContextStrokePath to draw the endpoint of the line. Quartz supports the line cap styles described in Table 3-3. The default style is butt cap.

######Table 3-3  Line cap styles

Style          | Appearance          | Description
-------------- |---------------------|--------------
Butt cap |![Smaller icon](https://developer.apple.com/library/content/documentation/GraphicsImaging/Conceptual/drawingwithquartz2d/Art/linecapbutt.gif) | Quartz squares off the stroke at the endpoint of the path. There is no projection beyond the end of the path.
Round cap | ![Smaller icon](https://developer.apple.com/library/content/documentation/GraphicsImaging/Conceptual/drawingwithquartz2d/Art/linecapround.gif) | Quartz draws a circle with a diameter equal to the line width around the point where the two segments meet, producing a rounded corner. The enclosed area is filled in.
Projecting square cap | ![Smaller icon](https://developer.apple.com/library/content/documentation/GraphicsImaging/Conceptual/drawingwithquartz2d/Art/linecapsquare.gif) | Quartz extends the stroke beyond the endpoint of the path for a distance equal to half the line width. The extension is squared off.


A closed subpath treats the starting point as a junction between connected line segments; the starting point is rendered using the selected line-join method. In contrast, if you close the path by adding a line segment that connects to the starting point, both ends of the path are drawn using the selected line-cap method.

A line dash pattern allows you to draw a segmented line along the stroked path. You control the size and placement of dash segments along the line by specifying the dash array and the dash phase as parameters to CGContextSetLineDash:

```
void CGContextSetLineDash (
    CGContextRef ctx,
    CGFloat phase,
    const CGFloat lengths[],
    size_t count
);
```

The elements of the lengths parameter specify the widths of the dashes, alternating between the painted and unpainted segments of the line. The phase parameter specifies the starting point of the dash pattern. Figure 3-11 shows some line dash patterns.

######Figure 3-11  Examples of line dash patterns
![Smaller icon](https://developer.apple.com/library/content/documentation/GraphicsImaging/Conceptual/drawingwithquartz2d/Art/linedash.gif)

The stroke color space determines how the stroke color values are interpreted by Quartz. You can also specify a Quartz color (CGColorRef data type) that encapsulates both color and color space. For more information on setting color space and color, see Color and Color Spaces.

###Functions for Stroking a Path
Quartz provides the functions shown in Table 3-4 for stroking the current path. Some are convenience functions for stroking rectangles or ellipses.

######Table 3-4  Functions that stroke paths

Function               | Description           
---------------------- | ----------------------
CGContextStrokePath  | Strokes the current path. 
CGContextStrokeRect | Strokes the specified rectangle.
CGContextStrokeRectWithWidth | Strokes the specified rectangle, using the specified line width.
CGContextStrokeEllipseInRect | Strokes an ellipse that fits inside the specified rectangle.
CGContextStrokeLineSegments | Strokes a sequence of lines.
CGContextDrawPath | If you pass the constant kCGPathStroke, strokes the current path. See Filling a Path if you want to both fill and stroke a path.

The function CGContextStrokeLineSegments is equivalent to the following code:

```
CGContextBeginPath (context);
for (k = 0; k < count; k += 2) {
    CGContextMoveToPoint(context, s[k].x, s[k].y);
    CGContextAddLineToPoint(context, s[k+1].x, s[k+1].y);
}
CGContextStrokePath(context);
```

When you call CGContextStrokeLineSegments, you specify the line segments as an array of points, organized as pairs. Each pair consists of the starting point of a line segment followed by the ending point of a line segment. For example, the first point in the array specifies the starting position of the first line, the second point specifies the ending position of the first line, the third point specifies the starting position of the second line, and so forth.

###Filling a Path
When you fill the current path, Quartz acts as if each subpath contained in the path were closed. It then uses these closed subpaths and calculates the pixels to fill. There are two ways Quartz can calculate the fill area. Simple paths such as ovals and rectangles have a well-defined area. But if your path is composed of overlapping segments or if the path includes multiple subpaths, such as the concentric circles shown in Figure 3-12, there are two rules you can use to determine the fill area.

The default fill rule is called the nonzero winding number rule. To determine whether a specific point should be painted, start at the point and draw a line beyond the bounds of the drawing. Starting with a count of 0, add 1 to the count every time a path segment crosses the line from left to right, and subtract 1 every time a path segment crosses the line from right to left. If the result is 0, the point is not painted. Otherwise, the point is painted. The direction that the path segments are drawn affects the outcome. Figure 3-12 shows two sets of inner and outer circles that are filled using the nonzero winding number rule. When each circle is drawn in the same direction, both circles are filled. When the circles are drawn in opposite directions, the inner circle is not filled.

You can opt to use the even-odd rule. To determine whether a specific point should be painted, start at the point and draw a line beyond the bounds of the drawing. Count the number of path segments that the line crosses. If the result is odd, the point is painted. If the result is even, the point is not painted. The direction that the path segments are drawn doesn’t affect the outcome. As you can see in Figure 3-12, it doesn’t matter which direction each circle is drawn, the fill will always be as shown.

######Figure 3-12  Concentric circles filled using different fill rules
![Smaller icon](https://developer.apple.com/library/content/documentation/GraphicsImaging/Conceptual/drawingwithquartz2d/Art/eosampleone.gif)

Quartz provides the functions shown in Table 3-5 for filling the current path. Some are convenience functions for stroking rectangles or ellipses.

######Table 3-5  Functions that fill paths

Function                         | Description
-------------------------------- | ---------------
CGContextEOFillPath | Fills the current path using the even-odd rule.
CGContextFillPath | Fills the current path using the nonzero winding number rule.
CGContextFillRect | Fills the area that fits inside the specified rectangle.
CGContextFillRects | Fills the areas that fits inside the specified rectangles.
CGContextFillEllipseInRect | Fills an ellipse that fits inside the specified rectangle.
CGContextDrawPath | Fills the current path if you pass kCGPathFill (nonzero winding number rule) or kCGPathEOFill (even-odd rule). Fills and strokes the current path if you pass kCGPathFillStroke or kCGPathEOFillStroke.


###Setting Blend Modes
Blend modes specify how Quartz applies paint over a background. Quartz uses normal blend mode by default, which combines the foreground painting with the background painting using the following formula:
```
result = (alpha * foreground) + (1 - alpha) * background
```
Color and Color Spaces provides a detailed discussion of the alpha component of a color, which specifies the opacity of a color. For the examples in this section, you can assume a color is completely opaque (alpha value = 1.0). For opaque colors, when you paint using normal blend mode, anything you paint over the background completely obscures the background.

You can set the blend mode to achieve a variety of effects by calling the function CGContextSetBlendMode, passing the appropriate blend mode constant. Keep in mind that the blend mode is part of the graphics state. If you use the function CGContextSaveGState prior to changing the blend mode, then calling the function CGContextRestoreGState resets the blend mode to normal.

The rest of this section show the results of painting the rectangles shown in Figure 3-13 over the rectangles shown in Figure 3-14. In each case (Figure 3-15 through Figure 3-30), the background rectangles are painted using normal blend mode. Then the blend mode is changed by calling the function CGContextSetBlendMode with the appropriate constant. Finally, the foreground rectangles are painted.

######Figure 3-13  The rectangles painted in the foreground
![Smaller icon](https://developer.apple.com/library/content/documentation/GraphicsImaging/Conceptual/drawingwithquartz2d/Art/vertical.gif)


######Figure 3-14  The rectangles painted in the background
![Smaller icon](https://developer.apple.com/library/content/documentation/GraphicsImaging/Conceptual/drawingwithquartz2d/Art/horizontal.gif)


```
Note:  You can also use blend modes to composite two images or to composite an image over any content that’s already drawn to the graphics context. Using Blend Modes with Images provides information on how to use blend modes to composite images and shows the results of applying blend modes to two images.
```

####Normal Blend Mode

Because normal blend mode is the default blend mode, you call the function CGContextSetBlendMode with the constant kCGBlendModeNormal only to reset the blend mode back to the default after you’ve used one of the other blend mode constants. Figure 3-15 shows the result of painting Figure 3-13 over Figure 3-14 using normal blend mode.

######Figure 3-15  Rectangles painted using normal blend mode
![Smaller icon](https://developer.apple.com/library/content/documentation/GraphicsImaging/Conceptual/drawingwithquartz2d/Art/blm_normal.gif)

####Multiply Blend Mode

Multiply blend mode specifies to multiply the foreground image samples with the background image samples. The resulting colors are at least as dark as either of the two contributing sample colors. Figure 3-16 shows the result of painting Figure 3-13 over Figure 3-14 using multiply blend mode. To use this blend mode, call the function CGContextSetBlendMode with the constant kCGBlendModeMultiply.

######Figure 3-16  Rectangles painted using multiply blend mode
![Smaller icon](https://developer.apple.com/library/content/documentation/GraphicsImaging/Conceptual/drawingwithquartz2d/Art/blm_multiply.gif)

####Screen Blend Mode

Screen blend mode specifies to multiply the inverse of the foreground image samples with the inverse of the background image samples. The resulting colors are at least as light as either of the two contributing sample colors. Figure 3-17 shows the result of painting Figure 3-13 over Figure 3-14 using screen blend mode. To use this blend mode, call the function CGContextSetBlendMode with the constant kCGBlendModeScreen.

######Figure 3-17  Rectangles painted using screen blend mode
![Smaller icon](https://developer.apple.com/library/content/documentation/GraphicsImaging/Conceptual/drawingwithquartz2d/Art/blm_screen.gif)

####Overlay Blend Mode

Overlay blend mode specifies to either multiply or screen the foreground image samples with the background image samples, depending on the background color. The background color mixes with the foreground color to reflect the lightness or darkness of the background. Figure 3-18 shows the result of painting Figure 3-13 over Figure 3-14 using overlay blend mode. To use this blend mode, call the function CGContextSetBlendMode with the constant kCGBlendModeOverlay.

######Figure 3-18  Rectangles painted using overlay blend mode
![Smaller icon](https://developer.apple.com/library/content/documentation/GraphicsImaging/Conceptual/drawingwithquartz2d/Art/blm_overlay.gif)

####Darken Blend Mode

Specifies to create the composite image samples by choosing the darker samples (either from the foreground image or the background). The background image samples are replaced by any foreground image samples that are darker. Otherwise, the background image samples are left unchanged. Figure 3-19 shows the result of painting Figure 3-13 over Figure 3-14 using darken blend mode. To use this blend mode, call the function CGContextSetBlendMode with the constant kCGBlendModeDarken.

######Figure 3-19  Rectangles painted using darken blend mode
![Smaller icon](https://developer.apple.com/library/content/documentation/GraphicsImaging/Conceptual/drawingwithquartz2d/Art/blm_darken.gif)

####Lighten Blend Mode

Specifies to create the composite image samples by choosing the lighter samples (either from the foreground or the background). The result is that the background image samples are replaced by any foreground image samples that are lighter. Otherwise, the background image samples are left unchanged. Figure 3-20 shows the result of painting Figure 3-13 over Figure 3-14 using lighten blend mode. To use this blend mode, call the function CGContextSetBlendMode with the constant kCGBlendModeLighten.

######Figure 3-20  Rectangles painted using lighten blend mode
![Smaller icon](https://developer.apple.com/library/content/documentation/GraphicsImaging/Conceptual/drawingwithquartz2d/Art/blm_lighten.gif)
####Color Dodge Blend Mode

Specifies to brighten the background image samples to reflect the foreground image samples. Foreground image sample values that specify black do not produce a change. Figure 3-21 shows the result of painting Figure 3-13 over Figure 3-14 using color dodge blend mode. To use this blend mode, call the function CGContextSetBlendMode with the constant kCGBlendModeColorDodge.

######Figure 3-21  Rectangles painted using color dodge blend mode
![Smaller icon](https://developer.apple.com/library/content/documentation/GraphicsImaging/Conceptual/drawingwithquartz2d/Art/blm_color_dodge.gif)
####Color Burn Blend Mode

Specifies to darken the background image samples to reflect the foreground image samples. Foreground image sample values that specify white do not produce a change. Figure 3-22 shows the result of painting Figure 3-13 over Figure 3-14 using color burn blend mode. To use this blend mode, call the function CGContextSetBlendMode with the constant kCGBlendModeColorBurn.

######Figure 3-22  Rectangles painted using color burn blend mode
![Smaller icon](https://developer.apple.com/library/content/documentation/GraphicsImaging/Conceptual/drawingwithquartz2d/Art/blm_color_burn.gif)
####Soft Light Blend Mode

Specifies to either darken or lighten colors, depending on the foreground image sample color. If the foreground image sample color is lighter than 50% gray, the background is lightened, similar to dodging. If the foreground image sample color is darker than 50% gray, the background is darkened, similar to burning. If the foreground image sample color is equal to 50% gray, the background is not changed. Image samples that are equal to pure black or pure white produce darker or lighter areas, but do not result in pure black or white. The overall effect is similar to what you’d achieve by shining a diffuse spotlight on the foreground image. Use this to add highlights to a scene. Figure 3-23 shows the result of painting Figure 3-13 over Figure 3-14 using soft light blend mode. To use this blend mode, call the function CGContextSetBlendMode with the constant kCGBlendModeSoftLight.

######Figure 3-23  Rectangles painted using soft light blend mode
![Smaller icon](https://developer.apple.com/library/content/documentation/GraphicsImaging/Conceptual/drawingwithquartz2d/Art/blm_soft_light.gif)
####Hard Light Blend Mode

Specifies to either multiply or screen colors, depending on the foreground image sample color. If the foreground image sample color is lighter than 50% gray, the background is lightened, similar to screening. If the foreground image sample color is darker than 50% gray, the background is darkened, similar to multiplying. If the foreground image sample color is equal to 50% gray, the foreground image is not changed. Image samples that are equal to pure black or pure white result in pure black or white. The overall effect is similar to what you’d achieve by shining a harsh spotlight on the foreground image. Use this to add highlights to a scene. Figure 3-24 shows the result of painting Figure 3-13 over Figure 3-14 using hard light blend mode. To use this blend mode, call the function CGContextSetBlendMode with the constant kCGBlendModeHardLight.

######Figure 3-24  Rectangles painted using hard light blend mode
![Smaller icon](https://developer.apple.com/library/content/documentation/GraphicsImaging/Conceptual/drawingwithquartz2d/Art/blm_hard_light.gif)
####Difference Blend Mode

Specifies to subtract either the foreground image sample color from the background image sample color, or the reverse, depending on which sample has the greater brightness value. Foreground image sample values that are black produce no change; white inverts the background color values. Figure 3-25 shows the result of painting Figure 3-13 over Figure 3-14 using difference blend mode. To use this blend mode, call the function CGContextSetBlendMode with the constant kCGBlendModeDifference.

######Figure 3-25  Rectangles painted using difference blend mode
![Smaller icon](https://developer.apple.com/library/content/documentation/GraphicsImaging/Conceptual/drawingwithquartz2d/Art/blm_difference.gif)
####Exclusion Blend Mode

Specifies an effect similar to that produced by kCGBlendModeDifference, but with lower contrast. Foreground image sample values that are black don’t produce a change; white inverts the background color values. Figure 3-26 shows the result of painting Figure 3-13 over Figure 3-14 using exclusion blend mode. To use this blend mode, call the function CGContextSetBlendMode with the constant kCGBlendModeExclusion.

######Figure 3-26  Rectangles painted using exclusion blend mode
![Smaller icon](https://developer.apple.com/library/content/documentation/GraphicsImaging/Conceptual/drawingwithquartz2d/Art/blm_exclusion.gif)
####Hue Blend Mode

Specifies to use the luminance and saturation values of the background with the hue of the foreground image. Figure 3-27 shows the result of painting Figure 3-13 over Figure 3-14 using hue blend mode. To use this blend mode, call the function CGContextSetBlendMode with the constant kCGBlendModeHue.

######Figure 3-27  Rectangles painted using hue blend mode
![Smaller icon](https://developer.apple.com/library/content/documentation/GraphicsImaging/Conceptual/drawingwithquartz2d/Art/blm_hue.gif)
####Saturation Blend Mode

Specifies to use the luminance and hue values of the background with the saturation of the foreground image. Areas of the background that have no saturation (that is, pure gray areas) don’t produce a change. Figure 3-28 shows the result of painting Figure 3-13 over Figure 3-14 using saturation blend mode. To use this blend mode, call the function CGContextSetBlendMode with the constant kCGBlendModeSaturation.

######Figure 3-28  Rectangles painted using saturation blend mode
![Smaller icon](https://developer.apple.com/library/content/documentation/GraphicsImaging/Conceptual/drawingwithquartz2d/Art/blm_saturation.gif)

####Color Blend Mode

Specifies to use the luminance values of the background with the hue and saturation values of the foreground image. This mode preserves the gray levels in the image. You can use this mode to color monochrome images or to tint color images. Figure 3-29 shows the result of painting Figure 3-13 over Figure 3-14 using color blend mode. To use this blend mode, call the function CGContextSetBlendMode with the constant kCGBlendModeColor.

######Figure 3-29  Rectangles painted using color blend mode
![Smaller icon](https://developer.apple.com/library/content/documentation/GraphicsImaging/Conceptual/drawingwithquartz2d/Art/blm_color.gif)


####Luminosity Blend Mode

Specifies to use the hue and saturation of the background with the luminance of the foreground image. This mode creates an effect that is inverse to the effect created by kCGBlendModeColor. Figure 3-30 shows the result of painting Figure 3-13 over Figure 3-14 using luminosity blend mode. To use this blend mode, call the function CGContextSetBlendMode with the constant kCGBlendModeLuminosity.

######Figure 3-30  Rectangles painted using luminosity blend mode
![Smaller icon](https://developer.apple.com/library/content/documentation/GraphicsImaging/Conceptual/drawingwithquartz2d/Art/blm_luminosity.gif)

###Clipping to a Path

The current clipping area is created from a path that serves as a mask, allowing you to block out the part of the page that you don’t want to paint. For example, if you have a very large bitmap image and want to show only a small portion of it, you could set the clipping area to display only the portion you want to show.

When you paint, Quartz renders paint only within the clipping area. Drawing that occurs inside the closed subpaths of the clipping area is visible; drawing that occurs outside the closed subpaths of the clipping area is not.

When the graphics context is initially created, the clipping area includes all of the paintable area of the context (for example, the media box of a PDF context). You alter the clipping area by setting the current path and then using a clipping function instead of a drawing function. The clipping function intersects the filled area of the current path with the existing clipping area. Thus, you can intersect the clipping area, shrinking the visible area of the picture, but you cannot increase the area of the clipping area.

The clipping area is part of the graphics state. To restore the clipping area to a previous state, you can save the graphics state before you clip, and restore the graphics state after you’re done with clipped drawing.

Listing 3-1 shows a code fragment that sets up a clipping area in the shape of a circle. This code causes drawing to be clipped, similar to what’s shown in Figure 3-3. (For another example, see Clip the Context in the chapter Gradients.)

######Listing 3-1  Setting up a circular clip area
```
CGContextBeginPath (context);
CGContextAddArc (context, w/2, h/2, ((w>h) ? h : w)/2, 0, 2*PI, 0);
CGContextClosePath (context);
CGContextClip (context);
```
######Table 3-6  Functions that clip the graphics context
Function                |  Description             
----------------------- | ------------------------------------
CGContextClip | Uses the nonzero winding number rule to calculate the intersection of the current path with the current clipping path.
CGContextEOClip | Uses the even-odd rule to calculate the intersection of the current path with the current clipping path.
CGContextClipToRect | Sets the clipping area to the area that intersects both the current clipping path and the specified rectangle.
CGContextClipToRects | Sets the clipping area to the area that intersects both the current clipping path and region within the specified rectangles.
CGContextClipToMask | Maps a mask into the specified rectangle and intersects it with the current clipping area of the graphics context. Any subsequent path drawing you perform to the graphics context is clipped. (See Masking an Image by Clipping the Context.)




##Color and Color Spaces

Devices (displays, printers, scanners, cameras) don’t treat color the same way; each has its own range of colors that the device can produce faithfully. A color produced on one device might not be able to be produced on another device.

To work with color effectively and to understand the Quartz 2D functions for using color spaces and color, you should be familiar with the terminology discussed in Color Management Overview. That document discusses color perception, color values, device-independent and device color spaces, the color-matching problem, rendering intent, color management modules, and ColorSync.

In this chapter, you’ll learn how Quartz represents color and color spaces, and what the alpha component is. This chapter also discusses how to:

* Create color spaces
* Create and set colors
* Set rendering intent

###About Color and Color Spaces

A color in Quartz is represented by a set of values. The values are meaningless without a color space that dictates how to interpret color information. For example, the values in Table 4-1 all represent the color blue at full intensity. But without knowing the color space or the allowable range of values for each color space, you have no way of knowing which color each set of values represents.

######Table 4-1  Color values in different color spaces

Values                     |  Color space      | Components
-------------------------- | ------------------| -------------
240 degrees, 100%, 100% |HSB |Hue, saturation, brightness
0, 0, 1 | RGB |Red, green, blue 
1, 1, 0, 0 |CMYK | Cyan, magenta, yellow, black 
1, 0, 0 | BGR | Blue, green, red

If you provide the wrong color space, you can get quite dramatic differences, as shown in Figure 4-1. Although the green color is interpreted the same in BGR and RGB color spaces, the red and blue values are flipped.

######Figure 4-1  Applying a BGR and an RGB color profile to the same image

![Smaller icon](https://developer.apple.com/library/content/documentation/GraphicsImaging/Conceptual/drawingwithquartz2d/Art/color_profiles.gif)

Color spaces can have different numbers of components. Three of the color spaces in the table have three components, while the CMYK color space has four. Value ranges are relative to that color space. For most color spaces, color values in Quartz range from 0.0 to 1.0, with 1.0 meaning full intensity. For example, the color blue at full intensity, specified in the RGB color space in Quartz, has the values (0, 0, 1.0). In Quartz, color also has an alpha value that specifies the transparency of a color. The color values in Table 4-1 don’t show an alpha value.

###The Alpha Value

The alpha value is the graphics state parameter that Quartz uses to determine how to composite newly painted objects to the existing page. At full intensity, newly painted objects are opaque. At zero intensity, newly painted objects are invisible. Figure 4-2 shows five large rectangles, drawn using alpha values of 1.0, 0.75, 0.5, 0.1, and 0.0. As the large rectangle becomes transparent, it exposes a smaller, opaque red rectangle drawn underneath.

######Figure 4-2  A comparison of large rectangles painted using various alpha values

![Smaller icon](https://developer.apple.com/library/content/documentation/GraphicsImaging/Conceptual/drawingwithquartz2d/Art/alpha_demo.gif)

You can make both the objects on the page and the page itself transparent by setting the alpha value globally in the graphics context before painting. Figure 4-3 compares a global alpha setting of 0.5 with the default value of 1.0.

######Figure 4-3  A comparison of global alpha values

![Smaller icon](https://developer.apple.com/library/content/documentation/GraphicsImaging/Conceptual/drawingwithquartz2d/Art/set_alpha.gif)

In the normal blend mode (which is the default for the graphics state) Quartz performs alpha blending by combining the components of the source color with the components of the destination color using the formula:

```
destination = (alpha * source) + (1 - alpha) * destination
```

where source is one component of the new paint color and destination is one component of the background color. This formula is executed for each newly painted shape or image.

For object transparency, set the alpha value to 1.0 to specify that objects you draw should be fully opaque; set it to 0.0 to specify that newly drawn objects are fully transparent. An alpha value between 0.0 and 1.0 specifies a partially transparent object. You can supply an alpha value as the last color component to all routines that accept colors. You can also set the global alpha value using the CGContextSetAlpha function. Keep in mind that if you set both, Quartz multiplies the alpha color component by the global alpha value.

To allow the page itself to be fully transparent, you can explicitly clear the alpha channel of the graphics context using the CGContextClearRect function, as long as the graphics context is a window or bitmap graphics context. You might want to do this when creating a transparency mask for an icon, for example, or to make the background of a window transparent.

###Creating Color Spaces

Quartz supports the standard color spaces used by color management systems for device-independent color spaces and also supports generic, indexed, and pattern color spaces. Device-independent color spaces represent color in a way that is portable between devices. They are used for the interchanges of color data from the native color space of one device to the native color space of another device. Colors in a device-independent color space appear the same when displayed on different devices, to the extent that the capabilities of the device allow. For that reason, device-independent color spaces are your best choice for representing color.

Applications that have precise color requirements should always use a device-independent color space. A common device independent color space is the generic color space. Generic color spaces let the operating system provide the best color space for your application. Drawing to the display looks as good as printing the same content to a printer.

```
Important: iOS does not support device-independent or generic color spaces. iOS applications must use device color spaces instead.
```
####Creating Device-Independent Color Spaces
To create a device-independent color space, you provide Quartz with the reference white point, reference black point, and gamma values for a particular device. Quartz uses this information to convert colors from your source color space into the color space of the output device.

The device-independent color spaces supported by Quartz, and the functions that create them are:

* L*a*b* is a nonlinear transformation of the Munsell color notation system (a system that specifies colors by hue, value, and saturation—or chroma —values). This color space matches perceived color difference with quantitative distance in color space. The L* component represents the lightness value, the a* component represents values from green to red, and the b* component represents values from blue to yellow. This color space is designed to mimic how the human brain decodes color. Use the function CGColorSpaceCreateLab.
* ICC is a color space from an ICC color profile, as defined by the International Color Consortium. ICC profiles define the gamut of colors supported by a device along with other device characteristics so that this information can be used to accurately transform the color space of one device to the color space of another. The manufacturer of the device typically provides an ICC profile. Some color monitors and printers contain embedded ICC profile information, as do some bitmap formats such as TIFF. Use the function CGColorSpaceCreateICCBased.
* Calibrated RGB is a device-independent RGB color space that represents colors relative to a reference white point that is based on the whitest light that can be generated by the output device. Use the function CGColorSpaceCreateCalibratedRGB.
* Calibrated gray is a device-independent grayscale color space that represents colors relative to a reference white point that is based on the whitest light that can be generated by the output device. Use the function CGColorSpaceCreateCalibratedGray.

####Creating Generic Color Spaces
Generic color spaces leave color matching to the system. For most cases, the result is acceptable. Although the name may imply otherwise, each “generic” color space—generic gray, generic RGB, and generic CMYK—is a specific device-independent color space.

Generic color spaces are easy to use; you don’t need to supply any reference point information. You create a generic color space by using the function CGColorSpaceCreateWithName along with one of the following constants:

* kCGColorSpaceGenericGray, which specifies generic gray, a monochromatic color space that permits the specification of a single value ranging from absolute black (value 0.0) to absolute white (value 1.0).
* kCGColorSpaceGenericRGB, which specifies generic RGB, a three-component color space (red, green, and blue) that models the way an individual pixel is composed on a color monitor. Each component of the RGB color space ranges in value from 0.0 (zero intensity) to 1.0 (full intensity).
* kCGColorSpaceGenericCMYK, which specifies generic CMYK, a four-component color space (cyan, magenta, yellow, and black) that models the way ink builds up during printing. Each component of the CMYK color space ranges in value from 0.0 (does not absorb the color) to 1.0 (fully absorbs the color).


####Creating Device Color Spaces
Device color spaces are primarily used by iOS applications because other options are not available. In most cases, a Mac OS X application should use a generic color space instead of creating a device color space. However, some Quartz routines expect images with a device color space. For example, if you call CGImageCreateWithMask and specify an image as the mask, the image must be defined with the device gray color space.

You create a device color space by using one of the following functions:

* CGColorSpaceCreateDeviceGray for a device-dependent grayscale color space.
* CGColorSpaceCreateDeviceRGB for a device-dependent RGB color space.
* CGColorSpaceCreateDeviceCMYK for a device-dependent CMYK color space.

####Creating Indexed and Pattern Color Spaces
Indexed color spaces contain a color table with up to 256 entries, and a base color space to which the color table entries are mapped. Each entry in the color table specifies one color in the base color space. Use the function CGColorSpaceCreateIndexed.

Pattern color spaces, discussed in Patterns, are used when painting with patterns. Use the function CGColorSpaceCreatePattern.

###Setting and Creating Colors

Quartz provides a suite of functions for setting fill color, stroke color, color spaces, and alpha. Each of these color parameters apply to the graphics state, which means that once set, that setting remains in effect until set to another value.

A color must have an associated color space. Otherwise, Quartz won’t know how to interpret color values. Further, you need to supply an appropriate color space for the drawing destination. Compare the blue fill color on the left side of Figure 4-4, which is a CMYK fill color, with the blue color shown on the right side, which is an RGB fill color. If you view the onscreen version of this document, you’ll see a large difference between the fill colors. The colors are theoretically identical, but appear identical only if the RGB color is used for an RGB device and the CMYK color is used for a CMYK device.

######Figure 4-4  A CMYK fill color and an RGB fill color
![Smaller icon](https://developer.apple.com/library/content/documentation/GraphicsImaging/Conceptual/drawingwithquartz2d/Art/cmyk_fill.gif)


You can use the functions CGContextSetFillColorSpace and CGContextSetStrokeColorSpace to set the fill and stroke color spaces, or you can use one of the convenience functions (listed in Table 4-2) that set color for a device color space.

######Table 4-2  Color-setting functions
Function                                  | Use to set color for
----------------------------------------- | -----------------------------------------
CGContextSetRGBStrokeColor CGContextSetRGBFillColor | Device RGB. At PDF-generation time, Quartz writes the colors as if they were in the corresponding generic color space.
CGContextSetCMYKStrokeColor CGContextSetCMYKFillColor | Device CMYK. (Remains device CMYK at PDF-generation time.)
CGContextSetGrayStrokeColor CGContextSetGrayFillColor | Device Gray. At PDF-generation time, Quartz writes the colors as if they were in the corresponding generic color space.
CGContextSetStrokeColorWithColor CGContextSetFillColorWithColor | Any color space; you supply a CGColor object that specifies the color space. Use these functions for colors you need repeatedly.
CGContextSetStrokeColor CGContextSetFillColor |  The current color space. Not recommended. Instead, set color using a CGColor object and the functions CGContextSetStrokeColorWithColor and CGContextSetFillColorWithColor.

You specify the fill and stroke colors as values located within the fill and stroke color spaces. For example, a fully saturated red color in the RGB color space is specified as an array of four numbers: (1.0, 0.0, 0.0, 1.0). The first three numbers specify full red intensity and no green or blue intensity. The fourth number is the alpha value, which is used to specify the opacity of the color.

If you reuse colors in your application, the most efficient way to set fill and stroke colors is to create a CGColor object, which you then pass as a parameter to the functions CGContextSetFillColorWithColor and CGContextSetStrokeColorWithColor. You can keep the CGColor object around as long as you need it. You can improve your application’s performance by using CGColor objects directly.

You create a CGColor object by calling the function CGColorCreate, passing a CGColorspace object and an array of floating-point values that specify the intensity values for the color. The last component in the array specifies the alpha value.

###Setting Rendering Intent

The rendering intent specifies how Quartz maps colors from the source color space to those that are within the gamut of the destination color space of a graphics context. If you don’t explicitly set the rendering intent, Quartz uses relative colorimetric rendering intent for all drawing except bitmap (sampled) images. Quartz uses perceptual rendering intent for those.

To set the rendering intent, call the function CGContextSetRenderingIntent, passing a graphics context and one of the following constants:

* kCGRenderingIntentDefault. Uses the default rendering intent for the context.
* kCGRenderingIntentAbsoluteColorimetric. Maps colors outside of the gamut of the output device to the closest possible match inside the gamut of the output device. This can produce a clipping effect, where two different color values in the gamut of the graphics context are mapped to the same color value in the output device’s gamut. This is the best choice when the colors used in the graphics are within the gamut of both the source and the destination, as is often the case with logos or when spot colors are used.
* kCGRenderingIntentRelativeColorimetric. The relative colorimetric shifts all colors (including those within the gamut) to account for the difference between the white point of the graphics context and the white point of the output device.
* kCGRenderingIntentPerceptual. Preserves the visual relationship between colors by compressing the gamut of the graphics context to fit inside the gamut of the output device. Perceptual intent is good for photographs and other complex, detailed images.
* kCGRenderingIntentSaturation. Preserves the relative saturation value of the colors when converting into the gamut of the output device. The result is an image with bright, saturated colors. Saturation intent is good for reproducing images with low detail, such as presentation charts and graphs.






