##Lower Level Text-Handling Technologies

Most apps can use the high-level text display classes and Text Kit for all their text handling. You might have an app, however, that requires the lower level programmatic interfaces from the Core Text, Core Graphics, and Core Animation frameworks as well as other APIs in UIKit itself.

###Simple Text Drawing

In addition to the UIKit classes for displaying and editing text, iOS also includes several ways to draw text directly on the screen. The easiest and most efficient way to draw simple strings is using the UIKit additions to the NSString class, which is in a category named UIStringDrawing. These extensions include methods for drawing strings using a variety of attributes wherever you want them on the screen. There are also methods for computing the size of a rendered string before you actually draw it, which can help you lay out your app content more precisely.

```
Important: There are some good reasons to avoid drawing text directly in favor of using the text objects of the UIKit framework. One is performance. Although, a UILabel object also draws its static text, it draws it only once whereas a text-drawing routine is typically called repeatedly. Text objects also afford more interaction; for example, they are selectable.
```

The methods of UIStringDrawing draw strings at a given point (for single lines of text) or within a specified rectangle (for multiple lines). You can pass in attributes used in drawing—for example, font, line-break mode, and baseline adjustment. The methods of UIStringDrawing allow you to adjust the position of the rendered text precisely and blend it with the rest of your view’s content. They also let you compute the bounding rectangle for your text in advance based on the desired font and style attributes.

You can also use the CATextLayer class of Core Animation to do simple text drawing. An object of this class stores a plain string or attributed string as its content and offers a set of attributes that affect that content, such as font, font size, text color, and truncation behavior. The advantage of CATextLayer is that (being a subclass of CALayer) its properties are inherently capable of animation. Core Animation is associated with the QuartzCore framework. Because instances of CATextLayer know how to draw themselves in the current graphics context, you don’t need to issue any explicit drawing commands when using those instances.

For information about the string-drawing extensions to NSString, see NSString UIKit Additions Reference. To learn more about CATextLayer, CALayer, and the other classes of Core Animation, read Core Animation Programming Guide.

###Core Text

Core Text is a technology for custom text layout and font management. App developers typically have no need to use Core Text directly. Text Kit is built on top of Core Text, giving it the same advantages, such as speed and sophisticated typographic capability. In addition, Text Kit provides a great deal of infrastructure that you must build for yourself if you use Core Text.

However, the Core Text API is accessible to developers who must use it directly. It is intended to be used by apps that have their own layout engines—for example, a word processor that has its own page layout engine can use Core Text to generate the glyphs and position them relative to each other.

Core Text is implemented as a framework that publishes an API similar to that of Core Foundation—similar in that it is procedural (ANSI C) but is based on object-like opaque types. This API is integrated with both Core Foundation and Core Graphics. For example, Core Text uses Core Foundation and Core Graphics objects in many input and output parameters. Moreover, because many Core Foundation objects are “toll-free bridged” with their counterparts in the Foundation framework, you may use some Foundation objects in the parameters of Core Text functions.

```
Note: If you use Core Text or Core Graphics to draw text, remember that you must apply a flip transform to the current text matrix to have text displayed in its proper orientation—that is, with the drawing origin at the upper-left corner of the string’s bounding box.
```

Core Text has two major parts: a layout engine and font technology, each backed by its own collection of opaque types.

####Core Text Layout Opaque Types

Core Text requires two objects whose opaque types are not native to it: an attributed string (CFAttributedStringRef) and a graphics path (CGPathRef). An attributed-string object encapsulates a string backing the displayed text and includes properties (or, “attributes”) that define stylistic aspects of the characters in the string—for example, font and color. The graphics path defines the shape of a frame of text, which is equivalent to a paragraph.

Core Text objects at runtime form a hierarchy that is reflective of the level of the text being processed (see Figure 9-1). At the top of this hierarchy is the framesetter object (CTFramesetterRef). With an attributed string and a graphics path as input, a framesetter generates one or more frames of text (CTFrameRef). As the text is laid out in a frame, the framesetter applies paragraph styles to it, including such attributes as alignment, tab stops, line spacing, indentation, and line-breaking mode.

To generate frames, the framesetter calls a typesetter object (CTTypesetterRef). The typesetter converts the characters in the attributed string to glyphs and fits those glyphs into the lines that fill a text frame. (A glyph is a graphic shape used to represent a character.) A line in a frame is represented by a CTLine object (CTLineRef). A CTFrame object contains an array of CTLine objects.

A CTLine object, in turn, contains an array of glyph runs, represented by objects of the CTRunRef type. A glyph run is a series of consecutive glyphs that have the same attributes and direction. Although a typesetter object returns CTLine objects, it composes those lines from arrays of glyph runs.

######Figure 9-1  Core Text layout objects
![Smaller icon](https://developer.apple.com/library/content/documentation/StringsTextFonts/Conceptual/TextAndWebiPhoneOS/Art/core_text_arch_2x.png)

Using functions of the CTLine opaque type, you can draw a line of text from an attributed string without having to go through the CTFramesetter object. You simply position the origin of the text on the text baseline and request the line object to draw itself.

####Core Text Font Opaque Types
Fonts are essential to text processing in Core Text. The typesetter object uses fonts (along with the source attributed string) to convert glyphs from characters and then position those glyphs relative to one another. A graphics context is central to fonts in Core Text. You can use graphics-context functions to set the current font and draw glyphs; or you can create a CTLine object from an attributed string and use its functions to draw into the graphics context. The Core Text font system handles Unicode fonts natively.

The font system includes objects of three opaque types: CTFont, CTFontDescriptor, and CTFontCollection:

* Font objects (CTFontRef) are initialized with a point size and specific characteristics (from a transformation matrix). You can query the font object for its character-to-glyph mapping, its encoding, glyph data, and metrics such as ascent, leading, and so on. Core Text also offers an automatic font-substitution mechanism called font cascading.
* Font descriptor objects (CTFontDescriptorRef) are typically used to create font objects. Instead of dealing with a complex transformation matrix, they allow you to specify a dictionary of font attributes that include such properties as PostScript name, font family and style, and traits (for example, bold or italic).
* Font collection objects (CTFontCollectionRef) are groups of font descriptors that provide services such as font enumeration and access to global and custom font collections.
It’s possible to convert UIFont objects to CTFont objects by calling CTFontCreateWithName, passing the font name and point size encapsulated by the UIFont object.

###Core Graphics Text Drawing

Core Graphics (or Quartz) is the system framework that handles two-dimensional imaging at the lowest level. Text drawing is one of its capabilities. Generally, because Core Graphics is so low-level, it is recommended that you use one of the system’s other technologies for drawing text. However, if circumstances require it, you can draw text with Core Graphics.

You select fonts, set text attributes, and draw text using functions of the CGContext opaque type. For example, you can call CGContextSelectFont to set the font used, and then call CGContextSetFillColor to set the text color. You then set the text matrix (CGContextSetTextMatrix) and draw the text using CGContextShowGlyphsAtPoint.

For more information about these functions and their use, see Quartz 2D Programming Guide and Core Graphics Framework Reference.

###Foundation-Level Regular Expressions

The NSString class of the Foundation framework includes a simple programmatic interface for regular expressions. You call one of three methods that return a range, passing in a specific option constant and a regular-expression string. If there is a match, the method returns the range of the substring. The option is the NSRegularExpressionSearch constant, which is of bit-mask type NSStringCompareOptions; this constant tells the method to expect a regular-expression pattern rather than a literal string as the search value. The supported regular expression syntax is that defined by ICU (International Components for Unicode).

```
Note: In addition to the NSString regular-expression feature described here, iOS provides more complete support for regular expressions with the NSRegularExpression class. The ICU User Guide describes how to construct ICU regular expressions (http://userguide.icu-project.org/strings/regexp).
```

The NSString methods for regular expressions are the following:

* rangeOfString:options:
* rangeOfString:options:range:
* rangeOfString:options:range:locale:

If you specify the NSRegularExpressionSearch option in these methods, the only other NSStringCompareOptions options you may specify are NSCaseInsensitiveSearch and NSAnchoredSearch. If a regular-expression search does not find a match or the regular-expression syntax is malformed, these methods return an NSRange structure with a value of {NSNotFound, 0}.

Listing 9-1 gives an example of using the NSString regular-expression API.

######Listing 9-1  Finding a substring using a regular expression

```
    // finds phone number in format nnn-nnn-nnnn
    NSRange r;
    NSString *regEx = @"[0-9]{3}-[0-9]{3}-[0-9]{4}";
    r = [textView.text rangeOfString:regEx options:NSRegularExpressionSearch];
    if (r.location != NSNotFound) {
        NSLog(@"Phone number is %@", [textView.text substringWithRange:r]);
    } else {
        NSLog(@"Not found.");
    }
```
Because these methods return a single range value for the substring matching the pattern, certain regular-expression capabilities of the ICU library are either not available or have to be programmatically added. In addition, NSStringCompareOptions options such as backward search, numeric search, and diacritic-insensitive search are not available and capture groups are not supported.

When testing the returned range, you should be aware of certain behavioral differences between searches based on literal strings and searches based on regular-expression patterns. Some patterns can successfully match and return an NSRange structure with a length of 0 (in which case the location field is of interest). Other patterns can successfully match against an empty string or, in those methods with a range parameter, with a zero-length search range.


###ICU Regular-Expression Support
In case the NSString support for regular expressions is not sufficient for your needs, a modified version of the libraries from ICU 4.2.1 is included in iOS at the BSD (nonframework) level of the system. ICU (International Components for Unicode) is an open-source project for Unicode support and software internationalization. The installed version of ICU includes those header files necessary to support regular expressions, along with some modifications related to those interfaces, namely:

* parseerr.h
* platform.h
* putil.h
* uconfig.h
* udraft.h
* uintrnal.h
* uiter.h
* umachine.h
* uregex.h
* urename.h
* ustring.h
* utf_old.h
* utf.h
* utf16.h
* utf8.h 
* utypes.h
* uversion.h

You can read the ICU 4.2 API documentation and user guide at http://icu-project.org/apiref/icu4c/index.html.

###Simple Text Input

An app that wants to display and process text is not limited to the text and web objects of the UIKit framework. It can implement custom views that are capable of anything from simple text entry to complex text processing and custom input. Through the available programming interfaces, these apps can acquire features such as custom text layout, multistage input, autocorrection, custom keyboards, and spell-checking.

You can implement custom views that allow users to enter text at an insertion point and delete characters before that insertion point when they tap the Delete key. An instant-messaging app, for example, could have a view that allows users to enter their part of a conversation.

You can acquire this capability for simple text entry by subclassing UIView, or any other view class that inherits from UIResponder, and adopting the UIKeyInput protocol. When an instance of your view class becomes the first responder, UIKit displays the system keyboard. UIKeyInput itself adopts the UITextInputTraits protocol, so you can set keyboard type, return-key type, and other attributes of the keyboard.

```
Note: Only a subset of the available keyboards and languages are available to classes that adopt only the UIKeyInput protocol. For example, any multi-stage input method, such Chinese, Japanese, Korean, and Thai is excluded. If a class also adopts the UITextInput protocol, those input methods are then available.
```

To adopt UIKeyInput, you must implement the three methods it declares: hasText, insertText:, and deleteBackward. To do the actual drawing of the text, you may use any of the technologies summarized in this chapter. However, for simple text input, such as for a single line of text in a custom control, the UIStringDrawing and CATextLayer APIs are most appropriate.

Listing 9-2 illustrates the UIKeyInput implementation of a custom view class. The textStore property in this example is an NSMutableString object that serves as the backing store of text. The implementation either appends or removes the last character in the string (depending on whether an alphanumeric key or the Delete key is pressed) and then redraws textStore.

######Listing 9-2  Implementing simple text entry

```
- (BOOL)hasText {
    if (textStore.length > 0) {
        return YES;
    }
    return NO;
}
 
- (void)insertText:(NSString *)theText {
    [self.textStore appendString:theText];
    [self setNeedsDisplay];
}
 
- (void)deleteBackward {
    NSRange theRange = NSMakeRange(self.textStore.length-1, 1);
    [self.textStore deleteCharactersInRange:theRange];
    [self setNeedsDisplay];
}
 
- (void)drawRect:(CGRect)rect {
    CGRect rectForText = [self rectForTextWithInset:2.0]; // custom method
    [self.theColor set];
    UIRectFrame(rect);
    [self.textStore drawInRect:rectForText withFont:self.theFont];
}

```

To actually draw the text in the view, this code uses the drawInRect:withFont: from the UIStringDrawing category on NSString.


###Communicating with the Text Input System

The text input system of iOS manages the keyboard. It interprets taps as presses of specific keys in specific keyboards suitable for certain languages. It then sends the associated character to the target view for insertion. As explained in Simple Text Input, view classes must adopt the UIKeyInputprotocol to insert and delete characters at the caret (insertion point).

However, the text input system does more than simple text entry. For example, it manages autocorrection and multistage input, which are all based upon the current selection and context. Multistage text input is required for ideographic languages such as Kanji (Japanese) and Hanzi (Chinese), which take input from phonetic keyboards. To acquire these features, a custom text view must communicate with the text input system by adopting the UITextInput protocol and implementing the related client-side classes and protocols.

The following section describes the general responsibilities of a custom text view that communicates with the text input system. A Guided Tour of a UITextInput Implementation examines the most important classes and methods of a typical implementation of UITextInput.

####Overview of the Client Side of Text Input

A class that wants to communicate with the text input system must adopt the UITextInput protocol. The class needs to inherit from UIResponder and is in most cases a custom view.

```
Note: The responder class that adopts UITextInput does not have to be the view that draws and manages text (as is the case in the sample code analyzed in A Guided Tour of a UITextInput Implementation). However, if it isn’t the view that draws and manages text, the class that does adopt UITextInput should be able to communicate directly with the view that does. For simplicity’s sake, the following discussion refers to the responder class that adopts UITextInput as the text view.
```

The text view must do its own text layout and font management; for this purpose, the Core Text framework is recommended. (Core Text gives an overview of Core Text.) The class should also adopt and implement the UIKeyInput protocol and should set the necessary properties of the UITextInputTraits protocol.

The general architecture of the client and system sides of the text input system are diagrammed in Figure 9-2.

######Figure 9-2  Paths of communication with the text input system

![Smaller icon](https://developer.apple.com/library/content/documentation/StringsTextFonts/Conceptual/TextAndWebiPhoneOS/Art/text_input_arch_2x.png)

The text input system calls the UITextInput methods that the text view implements. Many of these methods request information about specific text positions and text ranges from the text view and pass the same information back to the class in other method calls. The reasons for these exchanges of text positions and text ranges are summarized in Tasks of a UITextInput Object.

Text positions and text ranges in the text input system are represented by instances of custom classes. Text Positions and Text Ranges discusses these objects in more detail.

The text view also maintains references to a tokenizer and an input delegate. The text view calls methods declared by the UITextInputDelegate protocol to notify a system-provided input delegate about external changes in text and selection. The text input system communicates with a tokenizer object to determine the granularity of text units—for example, character, word, and paragraph. The tokenizer is an object that adopts the UITextInputTokenizer protocol. The text view includes a property (declared by UITextInput) that holds a reference to the tokenizer.

#####Text Positions and Text Ranges

The client app must create two classes whose instances represent positions and ranges of text in a text view. These classes must be subclasses of UITextPosition and UITextRange.

Although UITextPosition itself declares no methods or properties, it is an essential part of the information exchanged between a text document and the text input system. The text input system requires an object to represent a location in the text instead of, say, an integer or a structure. Moreover, a UITextPosition object can serve a practical purpose by representing a position in the visible text when the string backing the text has a different offset to that position. This happens when the string contains invisible formatting characters, such as with RTF and HTML documents, or embedded objects, such as an attachment. The custom UITextPosition class can account for these invisible characters when locating the string offsets of visible characters. In the simplest case—a plain text document with no embedded objects—a custom UITextPosition object can encapsulate a single offset or index integer.

UITextRange declares a simple interface in which two of its properties are starting and ending custom UITextPosition objects. The third property holds a Boolean value that indicates whether the range is empty (that is, has no length).

#####Tasks of a UITextInput Object

A class adopting the UITextInput protocol is required to implement most of the protocol’s methods and properties. With a few exceptions, these methods take custom UITextPosition or UITextRange objects as parameters or return one of these objects. At runtime the text system invokes these methods and, again in almost all cases, expects some object or value back.

The text view must assign text positions to properties marking the beginning and end of the displayed text. In addition, it must also maintain the range of the currently selected text and the range of the currently marked text, if any. Marked text, which is part of multistage text input, represents provisionally inserted text the user has yet to confirm. It is styled in a distinctive way. The range of marked text always contains within it a range of selected text, which might be a range of characters or the caret.

The methods implemented by a UITextInput object can be divided into distinctive tasks:



