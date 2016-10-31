// =============================================================================
@interface UIResponder : NSObject

- (nullable UIResponder*)nextResponder;			// 获取下一个响应者
- (BOOL)canBecomeFirstResponder;				// 是否可以变成第一响应者
- (BOOL)becomeFirstResponder;					// 变为第一响应者
- (BOOL)canResignFirstResponder;				// 是否可以放弃第一响应者
- (BOOL)resignFirstResponder;					// 放弃第一响应者
- (BOOL)isFirstResponder;						// 是否是第一响应者

// 触摸事件
- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(nullable UIEvent *)event;
- (void)touchesMoved:(NSSet<UITouch *> *)touches withEvent:(nullable UIEvent *)event;
- (void)touchesEnded:(NSSet<UITouch *> *)touches withEvent:(nullable UIEvent *)event;
- (void)touchesCancelled:(nullable NSSet<UITouch *> *)touches withEvent:(nullable UIEvent *)event;
- (void)touchesEstimatedPropertiesUpdated:(NSSet * _Nonnull)touches NS_AVAILABLE_IOS(9_1);
// 按压事件
- (void)pressesBegan:(NSSet<UIPress *> *)presses withEvent:(nullable UIPressesEvent *)event NS_AVAILABLE_IOS(9_0);
- (void)pressesChanged:(NSSet<UIPress *> *)presses withEvent:(nullable UIPressesEvent *)event NS_AVAILABLE_IOS(9_0);
- (void)pressesEnded:(NSSet<UIPress *> *)presses withEvent:(nullable UIPressesEvent *)event NS_AVAILABLE_IOS(9_0);
- (void)pressesCancelled:(NSSet<UIPress *> *)presses withEvent:(nullable UIPressesEvent *)event NS_AVAILABLE_IOS(9_0);
// 陀螺仪
- (void)motionBegan:(UIEventSubtype)motion withEvent:(nullable UIEvent *)event NS_AVAILABLE_IOS(3_0);
- (void)motionEnded:(UIEventSubtype)motion withEvent:(nullable UIEvent *)event NS_AVAILABLE_IOS(3_0);
- (void)motionCancelled:(UIEventSubtype)motion withEvent:(nullable UIEvent *)event NS_AVAILABLE_IOS(3_0);

- (void)remoteControlReceivedWithEvent:(nullable UIEvent *)event NS_AVAILABLE_IOS(4_0);

- (BOOL)canPerformAction:(SEL)action withSender:(nullable id)sender NS_AVAILABLE_IOS(3_0);

- (nullable id)targetForAction:(SEL)action withSender:(nullable id)sender NS_AVAILABLE_IOS(7_0);

@property(nullable, nonatomic,readonly) NSUndoManager *undoManager NS_AVAILABLE_IOS(3_0);

@end

// =============================================================================
@interface UIResponder (UIResponderKeyCommands)
@property (nullable,nonatomic,readonly) NSArray<UIKeyCommand *> *keyCommands NS_AVAILABLE_IOS(7_0); // returns an array of UIKeyCommand objects<
@end

// =============================================================================
@interface UIResponder (UIResponderInputViewAdditions)

// Called and presented when object becomes first responder.  Goes up the responder chain.
@property (nullable, nonatomic, readonly, strong) __kindof UIView *inputView NS_AVAILABLE_IOS(3_2);
@property (nullable, nonatomic, readonly, strong) __kindof UIView *inputAccessoryView NS_AVAILABLE_IOS(3_2);

/// This method is for clients that wish to put buttons on the Shortcuts Bar, shown on top of the keyboard.
/// You may modify the returned inputAssistantItem to add to or replace the existing items on the bar.
/// Modifications made to the returned UITextInputAssistantItem are reflected automatically.
/// This method should not be overriden. Goes up the responder chain.
@property (nonnull, nonatomic, readonly, strong) UITextInputAssistantItem *inputAssistantItem NS_AVAILABLE_IOS(9_0) __TVOS_PROHIBITED __WATCHOS_PROHIBITED;

// For viewController equivalents of -inputView and -inputAccessoryView
// Called and presented when object becomes first responder.  Goes up the responder chain.
@property (nullable, nonatomic, readonly, strong) UIInputViewController *inputViewController NS_AVAILABLE_IOS(8_0);
@property (nullable, nonatomic, readonly, strong) UIInputViewController *inputAccessoryViewController NS_AVAILABLE_IOS(8_0);

/* When queried, returns the current UITextInputMode, from which the keyboard language can be determined.
 * When overridden it should return a previously-queried UITextInputMode object, which will attempt to be
 * set inside that app, but not persistently affect the user's system-wide keyboard settings. */
@property (nullable, nonatomic, readonly, strong) UITextInputMode *textInputMode NS_AVAILABLE_IOS(7_0);
/* When the first responder changes and an identifier is queried, the system will establish a context to
 * track the textInputMode automatically. The system will save and restore the state of that context to
 * the user defaults via the app identifier. Use of -textInputMode above will supercede use of -textInputContextIdentifier. */
@property (nullable, nonatomic, readonly, strong) NSString *textInputContextIdentifier NS_AVAILABLE_IOS(7_0);
// This call is to remove stored app identifier state that is no longer needed.
+ (void)clearTextInputContextIdentifier:(NSString *)identifier NS_AVAILABLE_IOS(7_0);

// If called while object is first responder, reloads inputView, inputAccessoryView, and textInputMode.  Otherwise ignored.
- (void)reloadInputViews NS_AVAILABLE_IOS(3_2);

@end

// =============================================================================
@interface UIResponder (ActivityContinuation)
@property (nullable, nonatomic, strong) NSUserActivity *userActivity NS_AVAILABLE_IOS(8_0);
- (void)updateUserActivityState:(NSUserActivity *)activity NS_AVAILABLE_IOS(8_0);
- (void)restoreUserActivityState:(NSUserActivity *)activity NS_AVAILABLE_IOS(8_0);
@end


