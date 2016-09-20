//
// 1、NSString 操作
//

// 1. 字符串截取操作

/*
 1. 过滤字符串两端的特殊字符
 Returns a new string made by removing from both ends of the receiver 
 characters contained in a given character set.
 */
- (NSString *)stringByTrimmingCharactersInSet:(NSCharacterSet *)set;

/*
 1. 根据指定 字符串 将字符串拆分成多个字符串
 Returns an array containing substrings from the receiver that have 
 been divided by a given separator.
 */
- (NSArray<NSString *> *)componentsSeparatedByString:(NSString *)separator;

/*
 1. 根据指定 字符集 将字符串拆分成多个字符串
 Returns an array containing substrings from the receiver that have 
 been divided by characters in a given set.
 */
- (NSArray<NSString *> *)componentsSeparatedByCharactersInSet:(NSCharacterSet *)separator;



//==============================================================================
//			NSCharacterSet
//==============================================================================
















