##函数(Functions)

####0、前言

1、函数: 是一段完成特定任务的独立代码片段
2、函数类型: 每个函数都有一个由函数的参数类型和返回值类型组成的类型
3、嵌套函数: 函数的定义可以写在其他函数定义中, 这样可以在嵌套函数范围内实现功能封装。

####1、函数的定义与调用 (Defining and Calling Functions)
```
func greet(person: String) -> String {
	let greeting = "Hello, " + person + "!"
	return greeting
}
```




####2、函数参数与返回值 (Function Parameters and Return Values)




####3、函数参数标签和参数名称 (Function Argument Labels and Parameter Names)




####4、函数类型 (Function Types)
`函数类型`: 函数的类型由函数的*参数类型*和*返回值类型*组成。

######1. 函数类型

```
// 有参数和返回值的函数:
func addTwoInts(_a: Int, _b: Int) -> Int {
	return a + b;
}

func multiplyTwoInts(_a: Int, _b: Int) -> Int {
	return a * b;
}

```

这两个函数的类型都是  `(Int, Int) -> Int`



```
// 没有参数也没有返回值的函数:
func printHelloWorld() {
	print("Hello, world!");
}
```
这个函数的类型是: `()->void`


######2. 使用函数类型
在Swift中, 使用函数类型就像使用其他类型一样。
```
/// 声明:
var mathFunction:(Int, Int) -> Int = addTwoInts

/// 调用

```






####5、嵌套函数 (Nested Functions)



##闭包(Closures)


