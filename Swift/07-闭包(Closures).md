##闭包(Closures)

####0、前言


####1、闭包表达式(Closure Expressions)



######sorted 方法(The Sorted Method)
`sorted(by:)`: 它会根据你所提供的用于排序的闭包函数将已知类型数组中的 值进行排序。一旦排序完成,sorted(by:) 方法会返回一个与原数组大小相同,包含同类型元素且元素已正确排 序的新数组。原数组不会被 sorted(by:) 方法修改。

`sorted(by:)参数`:方法接受一个闭包,该闭包函数需要传入与数组元素类型相同的两个值,并返回一个布尔类型值来 表明当排序结束后传入的第一个参数排在第二个参数前面还是后面。如果第一个参数值出现在第二个参数值前 面,排序闭包函数需要返回 true ,反之返回 false 。


######闭包表达式语法(Closure Expression Syntax)

1. 闭包表达式语法有如下的一般形式:

```
{ (parameters) -> returnType in     statements}
```

2. s  


######根据上下文推断类型(Inferring Type From Context)




######单表达式闭包隐式返回(Implicit Returns From Single-Expression Closures)


######参数名称缩写(Shorthand Argument Names)




####2、尾随闭包(Trailing Closures)



####3、值捕获(Capturing Values)









