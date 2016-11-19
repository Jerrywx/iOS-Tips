##继承(Inheritance)

####0、前言
`继承:`一个类可以继承另一个类的方法，属性和其它特性。

`子类:`当一个类继承其它类时, 继承类叫子类。

`父类:`被继承的类叫超类或父类。

* 类可以调用和访问超类的方法,属性和下标(subscripts),并且可以重写(override)这些方 法,属性和下标来优化或修改它们的行为。
* 可以为类中继承来的属性添加属性观察器
* 可以为任何属性添加属性观察器,无论它原本被定义为存储型属性(stored property)还是计算型属性

####1、定义一个基类
`基类` 不继承于其它类的类, 称之为基类。
>Swift 中的类并不是从一个通用的基类继承而来。如果你不为你定义的类指定一个超类的话,这个类就自动成为 基类。

定义一个基类 Vehicle

```
class Vehicle {
	var currentSpeed = 0.0
	var description:String {
		return "traveling at \(currentSpeed) miles per hour"
	}
	func makeNise() {
		// ....
	}
}
```
创建类的实力

```
let someVehicle = Vehicle()
```
访问实例的方法

```
print("Vehicle: \(someVehicle.description)")
```

####2、子类生成

`子类生成:` 子类生成(Subclassing)指的是在一个已有类的基础上创建一个新的类。子类继承超类的特性,并且可以进一步 完善。你还可以为子类添加新的特性。

定义子类语法

```
class SomeClass: SomeSuperclass { 
	// 这里是子类的定义}
```

实例

```
class Bicycle: Vehicle {    var hasBasket = false}
```


####2、子类生成








