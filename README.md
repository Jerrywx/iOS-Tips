# iOS-Tips

###git 使用
####1、为项目添加远程仓库地址
```
git remote add origin git@github.com:djqiang（github帐号名）/gitdemo（项目名）.git 
```
如果报错:fatal: remote origin already exists.
说明已经存在远程仓库地址
####2、删除远程项目远程仓库地址
```
git remote rm origin
```
之后再输入 1 中的 添加远程仓库地址 

####3、查看远程仓库地址
```
git remote get-url --all origin
git remote get-url [--push] [--all] <name>
```


###4、Git忽略规则及.gitignore规则不生效的解决办法

在git中如果想忽略掉某个文件，不让这个文件提交到版本库中，可以使用修改根目录中 .gitignore 文件的方法（如无，则需自己手工建立此文件）。这个文件每一行保存了一个匹配的规则例如：

``` 
#此为注释 – 将被 Git 忽略
*.a       # 忽略所有 .a 结尾的文件
!lib.a    # 但 lib.a 除外
/TODO     # 仅仅忽略项目根目录下的 TODO 文件，不包括 subdir/TODO
build/    # 忽略 build/ 目录下的所有文件
doc/*.txt # 会忽略 doc/notes.txt 但不包括 doc/server/arch.txt
```

规则很简单，不做过多解释，但是有时候在项目开发过程中，突然心血来潮想把某些目录或文件加入忽略规则，按照上述方法定义后发现并未生效，原因是.gitignore只能忽略那些原来没有被track的文件，如果某些文件已经被纳入了版本管理中，则修改.gitignore是无效的。那么解决方法就是先把本地缓存删除（改变成未track状态），然后再提交：

```
git rm -r --cached .
git add .
git commit -m 'update .gitignore'
```

###5、Podfile.lock 文件
当你执行pod install之后，除了 Podfile 外，CocoaPods 还会生成一个名为Podfile.lock的文件，Podfile.lock 应该加入到版本控制里面，不应该把这个文件加入到.gitignore中。因为Podfile.lock会锁定当前各依赖库的版本，之后如果多次执行pod install 不会更改版本，要pod update才会改Podfile.lock了。这样多人协作的时候，可以防止第三方库升级时造成大家各自的第三方库版本不一致