##Transforms

The Quartz 2D drawing model defines two completely separate coordinate spaces: user space, which represents the document page, and device space, which represents the native resolution of a device. User space coordinates are floating-point numbers that are unrelated to the resolution of pixels in device space. When you want to print or display your document, Quartz maps user space coordinates to device space coordinates. Therefore, you never have to rewrite your application or write additional code to adjust the output from your application for optimum display on different devices.

You can modify the default user space by operating on the current transformation matrix, or CTM. After you create a graphics context, the CTM is the identity matrix. You can use Quartz transformation functions to modify the CTM and, as a result, modify drawing in user space.

This chapter:

 * Provides an overview of the functions you can use to perform transformations
 * Shows how to modify the CTM
 * Describes how to create an affine transform
 * Shows how to determine if two transforms are equivalent
 * Describes how to obtain the user-to-device-space transform
 * Discusses the math behind affine transforms

####About Quartz Transformation Functions

You can easily translate, scale, and rotate your drawing using the Quartz 2D built-in transformation functions. With just a few lines of code, you can apply these transformations in any order and in any combination. Figure 5-1 illustrates the effects of scaling and rotating an image. Each transformation you apply updates the CTM. The CTM always represents the current mapping between user space and device space. This mapping ensures that the output from your application looks great on any display screen or printer.

######Figure 5-1  Applying scaling and rotation

![Smaller icon](https://developer.apple.com/library/content/documentation/GraphicsImaging/Conceptual/drawingwithquartz2d/Art/spaces.gif)

The Quartz 2D API provides five functions that allow you to obtain and modify the CTM. You can rotate, translate, and scale the CTM, and you can concatenate an affine transformation matrix with the CTM. See Modifying the Current Transformation Matrix.

Quartz also allows you to create affine transforms that don’t operate on user space until you decide to apply the transform to the CTM. You use another set of functions to create affine transforms, which can then be concatenated with the CTM. See Creating Affine Transforms.

You can use either set of functions without understanding anything about matrix math. However if you want to understand what Quartz does when you call one of the transform functions, read The Math Behind the Matrices.

####Modifying the Current Transformation Matrix

You manipulate the CTM to rotate, scale, or translate the page before drawing an image, thereby transforming the object you are about to draw. Before you transform the CTM, you need to save the graphics state so that you can restore it after drawing. You can also concatenate the CTM with an affine transform (see Creating Affine Transforms). Each of these four operations—translation, rotation, scaling, and concatenation—is described in this section along with the CTM functions that perform each operation.

The following line of code draws an image, assuming that you provide a valid graphics context, a pointer to the rectangle to draw the image to, and a valid CGImage object. The code draws an image, such as the sample rooster image shown in Figure 5-2. As you read the rest of this section, you’ll see how the image changes as you apply transformations.

```
CGContextDrawImage (myContext, rect, myImage);

```

######Figure 5-2  An image that is not transformed

![Smaller icon](https://developer.apple.com/library/content/documentation/GraphicsImaging/Conceptual/drawingwithquartz2d/Art/normal_rooster.gif)

Translation moves the origin of the coordinate space by the amount you specify for the x and y axes. You call the function CGContextTranslateCTM to modify the x and y coordinates of each point by a specified amount. Figure 5-3 shows an image translated by 100 units in the x-axis and 50 units in the y-axis, using the following line of code:

######Figure 5-3  A translated image

![Smaller icon](https://developer.apple.com/library/content/documentation/GraphicsImaging/Conceptual/drawingwithquartz2d/Art/translated_rooster.gif)

Rotation moves the coordinate space by the angle you specify. You call the function CGContextRotateCTM to specify the rotation angle, in radians. Figure 5-4 shows an image rotated by –45 degrees about the origin, which is the lower left of the window, using the following line of code:

```
CGContextRotateCTM (myContext, radians(–45.));
```





