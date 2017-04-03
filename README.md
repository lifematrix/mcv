
# Minimalism Computer Vision (MCV) Library
 
 '''M'''不是微型，而是简约主义的意思。
 
 目前的opencv库，存在几个问题：
 
 * 依赖的库太多，编译opencv 是一个噩梦。要填很多坑。
 
 * 需要很多jpeg, png的原生库支持，而按理说，这些都是视觉库应该自带的。
 
 * 错误处理不友好。比如，没有找到某个解码器时，只是简单地返回报错。
 
 * 功能过多，比如绘图、窗口显示等。
 

 我们这个库，致力于：
 
 * Self-dependent (自依赖)： 只依赖标准库，至多是C++11的标准库
 
 * 自带解码器(jpeg, png, gif)等。换言之，我们的开发者会自己开发解码器。这一方面加深了对算法的理解， 另方面保证了依赖的单纯。
 
 * 强调速度。会用各种办法，尽可能加速。
 
 * 对Python的友好性。这些库的最终目的，是方便在Python中使用和测试。
 
 
 mailto: [steven liu]<stevenliucx@gmail.com>