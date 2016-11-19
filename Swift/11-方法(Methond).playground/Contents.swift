//: Playground - noun: a place where people can play

//
//	什么是方法:
//
//	实例方法:
//
//	类型方法:

// 1. 实例方法
class Counter {
	var count = 0
	
	func increment() {
		count += 1
	}
	
	func incrementBy(_ amount: Int) {
		count += amount
	}
	
	func reset() {
		count = 0
	}
}

let counter = Counter()
print(counter)
print(counter.count)
counter.increment()
print(counter.count)
counter.incrementBy(11)
print(counter.count)



/* ----------- */
/*
	类型装换
*/

class Fateher {
	var name : String
	init(name:String) {
		self.name = name
	}
}

class Son: Fateher {
	var age : Int
	init(name:String, age:Int) {
		self.age = age
		super.init(name: name)
	}
	
	init(age: Int) {
		self.age = age
		super.init(name: "")
	}
}


let persons = [
			Son(name: "zhangsan", age: 12),
			Fateher(name: "123"),
			Son(name: "lisi", age: 22)
			]







