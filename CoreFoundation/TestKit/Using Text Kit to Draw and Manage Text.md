#Using Text Kit to Draw and Manage Text

The UIKit framework includes several classes whose purpose is to display text in an app’s user interface: UITextView, UITextField, and UILabel, as described in Displaying Text Content in iOS. Text views, created from the UITextView class, are meant to display large amounts of text. Underlying UITextView is a powerful layout engine called Text Kit. If you need to customize the layout process or you need to intervene in that behavior, you can use Text Kit. For smaller amounts of text and special needs requiring custom solutions, you can use alternative, lower-level technologies, as described in Lower Level Text-Handling Technologies.

Text Kit is a set of classes and protocols in the UIKit framework providing high-quality typographical services that enable apps to store, lay out, and display text with all the characteristics of fine typesetting, such as kerning, ligatures, line breaking, and justification. Text Kit is built on top of Core Text, so it provides the same speed and power. UITextView is fully integrated with Text Kit; it provides editing and display capabilities that enable users to input text, specify formatting attributes, and view the results. The other Text Kit classes provide text storage and layout capabilities. Figure 8-1 shows the position of Text Kit among other iOS text and graphics frameworks.

######Figure 8-1  Text Kit Framework Position
![MacDown logo](file:///Users/wangxiao/Library/Developer/Shared/Documentation/DocSets/com.apple.adc.documentation.docset/Contents/Resources/Documents/documentation/StringsTextFonts/Conceptual/TextAndWebiPhoneOS/Art/text_kit_arch_2x.png)

Text Kit gives you complete control over text rendering in user interface elements. In addition to UITextView, UITextField and UILabel are built on top of Text Kit, and it seamlessly integrates with animations, UICollectionView and UITableView. Text Kit is designed with a fully extensible object-oriented architecture that supports subclassing, delegation, and a thorough set of notifications enabling deep customization.


##1、Primary Text Kit Objects

The data flow paths among the primary Text Kit objects are shown in Figure 8-2. Text views are instances of UITextView class, text containers are instances of NSTextContainer class, the layout manager is an instance of NSLayoutManager class, and the text storage is an instance of NSTextStorage class. In Text Kit, an NSTextStorage object stores the text that is displayed by a UITextView object and laid out by an NSLayoutManager object into an area defined by NSTextContainer object.

######Figure 8-2  Primary Text Kit Objects
![MacDown logo](file:///Users/wangxiao/Library/Developer/Shared/Documentation/DocSets/com.apple.adc.documentation.docset/Contents/Resources/Documents/documentation/StringsTextFonts/Conceptual/TextAndWebiPhoneOS/Art/textkitarchitecture_2x.png)

An NSTextContainer object defines a region where text can be laid out. Typically, a text container defines a rectangular area, but by creating a subclass of NSTextContainer you can create other shapes: circles, pentagons, or irregular shapes, for example. Not only does a text container describe the outline of an area that can be filled with text, it maintains an array of Bezier paths that are exclusion zones within its area where text is not laid out. As it is laid out, text flows around the exclusion paths, providing a means to include graphics and other non-text layout elements.

NSTextStorage defines the fundamental storage mechanism of the Text Kit’s extended text-handling system. NSTextStorage is a subclass of NSMutableAttributedString that stores the characters and attributes manipulated by the text system. It ensures that text and attributes are maintained in a consistent state across editing operations. In addition to storing the text, an NSTextStorage object manages a set of client NSLayoutManager objects, notifying them of any changes to its characters or attributes so that they can relay and redisplay the text as needed.

An NSLayoutManager object orchestrates the operation of the other text handling objects. It intercedes in operations that convert the data in an NSTextStorage object to rendered text in a view’s display area. It maps Unicode character codes to glyphs and oversees the layout of the glyphs within the areas defined by NSTextContainer objects.

>Note: NLayoutManager, NSTextStorage, and NSTextContainer can be accessed from subthreads as long as the app guarantees the access from a single thread.

For reference information about UITextView, see UITextView Class Reference. NSTextContainer is described in NSTextContainer Class Reference for iOS, NSLayoutManager in NSLayoutManager Class Reference for iOS, and NSTextStorage in NSTextStorage Class Reference for iOS.


##2、Text Attributes

Text Kit handles three kinds of text attributes: character attributes, paragraph attributes, and document attributes. Character attributes include traits such as font, color, and subscript, which can be associated with an individual character or a range of characters. Paragraph attributes are traits such as indentation, tabs, and line spacing. Document attributes include documentwide traits such as paper size, margins, and view zoom percentage.


####1.Character Attributes
An attributed string stores character attributes as key-value pairs in NSDictionary objects. The key is an attribute name, represented by an identifier (an NSString constant) such as NSFontAttributeName. Figure 8-3 shows an attributed string with an attribute dictionary applied to a range within the string.

######Figure 8-3  Composition of an attributed string
![MacDown logo](https://developer.apple.com/library/content/documentation/StringsTextFonts/Conceptual/TextAndWebiPhoneOS/Art/ns_attributed_string_2x.png)

Conceptually, each character in an attributed string has an associated dictionary of attributes. Typically, however, an attribute dictionary applies to a longer range of characters, a run of text. The NSAttributedString class provides methods that take a character index and return the associated attribute dictionary and the range to which its attribute values apply, such as attributesAtIndex:effectiveRange:.

You can assign any attribute key-value pair you choose to a range of characters, in addition to working with predefined attributes. You add the attributes to the appropriate character range in the NSTextStorage object using the NSMutableAttributedString method addAttribute:value:range:. You can also create an NSDictionary object containing the names and values of a set of custom attributes and add them to the character range in a single step using the addAttributes:range: method. To make use of your custom attributes, you need a custom subclass of NSLayoutManager to work with them. Your subclass should override the drawGlyphsForGlyphRange:atPoint: method. Your override can first call the superclass to draw the glyph range and then draw your own attributes on top. Alternatively, your override can draw the glyphs entirely your own way.

####2.Paragraph Attributes
Paragraph attributes affect the way the layout manager arranges lines of text into paragraphs on a page. The text system encapsulates paragraph attributes in objects of the NSParagraphStyle class. The value of one of the predefined character attributes, NSParagraphStyleAttributeName, points to an NSParagraphStyle object containing the paragraph attributes for that character range. Attribute fixing ensures that only one NSParagraphStyle object pertains to the characters throughout each paragraph.

Paragraph attributes include traits such as alignment, tab stops, line-breaking mode, and line spacing (also known as leading).

####3.Document Attributes
Document attributes pertain to a document as a whole. Document attributes include traits such as paper size, margins, and view zoom percentage. Although the text system has no built-in mechanism to store document attributes, NSAttributedString initialization methods such as initWithRTF:documentAttributes: can populate an NSDictionary object that you provide with document attributes derived from a stream of RTF or HTML data. Conversely, methods that write RTF data, such as RTFFromRange:documentAttributes:, write document attributes if you pass a reference to an NSDictionary object containing them with the message.

####4.Attribute Fixing
Editing attributed strings can cause inconsistencies that must be cleaned up by attribute fixing. The UIKit extensions to NSMutableAttributedString define the fixAttributesInRange: method to fix inconsistencies among attachment, character, and paragraph attributes


##3、Changing Text Storage Programmatically

An NSTextStorage object serves as the character data repository for Text Kit. The format for this data is an attributed string, which is a sequence of characters (in Unicode encoding) and associated attributes (such as font, color, and paragraph style). The classes that represent attributed strings are NSAttributedString and NSMutableAttributedString, of which NSTextStorage is a subclass. As described in Character Attributes, each character in a block of text has a dictionary of keys and values associated with it. A key names an attribute (such as NSFontAttributeName), and the associated value specifies the characteristics of that attribute (such as Helvetica 12-point).

There are three stages to editing a text storage object programmatically. The first stage is to send it a beginEditing message to announce a group of changes.

In the second stage, you send it some editing messages, such as replaceCharactersInRange:withString: and setAttributes:range:, to effect the changes in characters or attributes. Each time you send such a message, the text storage object invokes edited:range:changeInLength: to track the range of its characters affected since it received the beginEditing message.

In the third stage, when you’re done changing the text storage object, you send it an endEditing message. This causes it to sends out the delegate message textStorage:willProcessEditing:range:changeInLength: and invoke its own processEditing method, fixing attributes within the recorded range of changed characters. See Attribute Fixing for information about attribute fixing.

After fixing its attributes, the text storage object sends the delegate method textStorage:didProcessEditing:range:changeInLength:, giving the delegate an opportunity to verify and possibly change the attributes. (Although the delegate can change the text storage object’s character attributes in this method, it cannot change the characters themselves without leaving the text storage in an inconsistent state.) Finally, the text storage object sends the processEditingForTextStorage:edited:range:changeInLength:invalidatedRange: message to each associated layout manager—indicating the range in the text storage object that has changed, along with the nature of those changes. The layout managers in turn use this information to recalculate their glyph locations and redisplay if necessary.

##4、Working with Font Objects
A computer font is a data file in a format such as OpenType or TrueType, containing information describing a set of glyphs, as described in Characters and Glyphs, and various supplementary information used in glyph rendering. The UIFont class provides the interface for getting and setting font information. A UIFont instance provides access to the font’s characteristics and glyphs. Text Kit combines character information with font information to choose the glyphs used during text layout. You use font objects by passing them to methods that accept them as a parameter. Font objects are immutable, so it is safe to use them from multiple threads in your app.

You don’t create UIFont objects using the alloc and init methods; instead, you use preferredFontForTextStyle: with a text style constant or fontWithName:size:. You can also use a font descriptor to create a font with fontWithDescriptor:size:. These methods check for an existing font object with the specified characteristics, returning it if there is one. Otherwise, they look up the font data requested and create the appropriate font object.





















> **Important:** This documentation contains preliminary information about an API or technology in development. This information is subject to change, and software implemented according to this documentation should be tested with final operating system software.


The iOS platform gives you many ways to display text in your apps and let users edit that text. It also lets you display formatted text and web content in your app’s views. The resources at your disposal range from [framework]() objects—such as text views, text fields, and web views—to text layout engines that you can use directly to draw, lay out, and otherwise manage text.

![MacDown logo](https://developer.apple.com/library/prerelease/content/documentation/StringsTextFonts/Conceptual/TextAndWebiPhoneOS/Art/textpg_intro_2x.png)


With the classes in the UIKit framework, you can manage the edit menu (including adding custom items to it), implement custom input views, and copy, cut, and paste data within and between apps.


	Note: This document was previously titled Text, Web, and Editing Programming Guide for iOS.
	


##At a Glance
	
Apps in iOS have a number of powerful technologies to handle text, both for editing text and for rendering high-quality typographically formatted text.



####The UIKit Framework Provides Your App with Text and Web Objects

You can add ready-made text views, text fields, and labels to your app’s user interface by using instances of the [UITextView](), [UITextField](), and [UILabel](). You can add and configure them programmatically or by using the Interface Builder editor in Xcode. You can also turn a view of your app into a miniature web browser capable of understanding and displaying HTML, CSS, and JavaScript content.


>Relevant Chapters: [Displaying Text Content in iOS](), [Typographical Concepts](), [Managing Text Fields and Text Views]()


####When Users Edit Text, Your App Must Manage the Keyboard

When a user taps a text field, text view, or form field in a web view, iOS animates a keyboard into view. An app can control which keyboard is presented; for example, for a numeric-value field, the app should select the numeric keypad. If the entered or edited text is obscured by the keyboard, the app should adjust the view displaying the text so that the text appears above the keyboard. The delegate of a text view, text field, or web view is responsible for validating edited text and for accessing and storing edited text when the user dismisses the keyboard.

>Relevant Chapters: [Managing the Keyboard]()


####Your App Can Draw and Manage Text Directly

Underlying the text views in UIKit is a powerful layout engine called Text Kit. If you need to customize the layout process or you need to intervene in that behavior, you can use Text Kit. Text Kit is a set of classes and protocols that provide high-quality typographical services which enable apps to store, lay out, and display text with all the characteristics of fine typesetting, such as kerning, ligatures, line breaking, and justification.

For most apps, you can use the high-level text display classes and Text Kit for all their text handling. For smaller amounts of text and special needs requiring custom solutions, you can use alternate, lower level technologies, such as the programmatic interfaces from the Core Text, Core Graphics, and Core Animation frameworks as well as other APIs in UIKit itself.

To communicate directly with the text-input system of iOS, implement the [UITextInput protocol]() and related protocols and classes. Your app can also make use of technologies for spell checking and regular expressions.

>Relevant Chapter: [Using Text Kit to Draw and Manage Text](), [Lower Level Text-Handling Technologies]()
	

####Your App Has a Range of Options for the Input and Editing of Data

The UIKit framework includes programmatic interfaces for editing the data in a view and for entering data into an app. Custom input views can replace the system keyboard to permit input of special data; input accessory views are a custom view above the system keyboard (or custom input view) that enables users to affect edited data in app-specific ways. Using UIPasteboard and related classes, an app can copy, cut, and paste data within different locations of itself or between itself and another app. As part of copy-cut-paste operations, the user taps a command on an contextual edit menu; your app manages this menu and can add custom commands to it.

>Relevant Chapters:: [Copy, Cut, and Paste Operations](), [Displaying and Managing the Edit Menu](), [Custom Views for Data Input]()



##See Also

The Core Graphics and Core Animation frameworks have some text-handling capabilities. Core Animation, for example, offers the[CATextLayer]() class. To learn more about these capabilities, read [Quartz 2D Programming Guide]() (Core Graphics) and [Core Animation Programming Guide]().

To find out more about the Core Text framework, which is appropriate for developing higher-level text-handling frameworks, read [Core Text Programming Guide]() and [Core Text Reference Collection]().