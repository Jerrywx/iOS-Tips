/*
 *  CFHTTPMessageCreateRequest()
 *
 *  Discussion:
 *	Create an HTTPMessage from an HTTP method, url and version.
 *
 *  Mac OS X threading:
 *	Thread safe
 *
 *  Parameters:
 *
 *	alloc:
 *	  A pointer to the CFAllocator which should be used to allocate
 *	  memory for the CF read stream and its storage for values. If
 *	  this reference is not a valid CFAllocator, the behavior is
 *	  undefined.
 *
 *	requestMethod:
 *	  A pointer to a CFString indicating the method of request. For a
 *	  "GET" request, for example, the value would be CFSTR("GET").
 *
 *	url:
 *	  A pointer to a CFURL structure created any of the several
 *	  CFURLCreate... functions.  If this parameter is not a pointer
 *	  to a valid CFURL structure, the behavior is undefined.
 *
 *	httpVersion:
 *	  A pointer to a CFString indicating the version of request.
 *
 *  Result:
 *	A pointer to the CFHTTPMessage created, or NULL if failed. It is
 *	caller's responsibilty to release the memory allocated for the
 *	message.
 *
 */

// 1. ---------------------- 描述
Creates and returns a CFHTTPMessage object for an HTTP request.
//为HTTP请求创建并返回一个 CFHTTPMessage 对象


// 2. ---------------------- Parameters
// 2.1 allocator
The allocator to use to allocate memory for the new object.
// 内存分配器用来为新对象分配内存。
Pass NULL or kCFAllocatorDefault to use the current default allocator.
// 传递NULL或kCFAllocatorDefault使用当前默认的分配。

// 2.2 requestMethod
The request method for the request.
// 请求方式 GET、POST...
Use any of the request methods allowed by the HTTP version specified by httpVersion.
//

// 2.3 url
The URL to which the request will be sent.
// 请求的 URL

// 2.4 httpVersion
The HTTP version for this message. Pass kCFHTTPVersion1_0 or kCFHTTPVersion1_1.
// HTTP 版本, 传入 kCFHTTPVersion1_0 或 kCFHTTPVersion1_1.

// 3. ---------------------- Return Value
A new CFHTTPMessage object, or NULL if there was a problem creating the object.
// 返回一个新的 CFHTTPMessage 对象 或者 NULL
Ownership follows the The Create Rule.
// 所有权遵循创建规则。

// 4. ---------------------- Discussion
This function returns a CFHTTPMessage object that you can use to build an HTTP request. Continue building the request by callingCFHTTPMessageSetBody to set the message’s body. Call CFHTTPMessageCopyHeaderFieldValue to set the message’s headers.

If you are using a CFReadStream object to send the message, call CFReadStreamCreateForHTTPRequest to create a read stream for the request. If you are not using CFReadStream, call CFHTTPMessageCopySerializedMessage to make the message ready for transmission by serializing it.

// 5. Availability
Available in iOS 2.0 and later.







