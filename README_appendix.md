vector特色：
const_iterator/iterator基于下标实现。这意味着vector倍增的时候不会发生迭代器失效的情况。
const_iterator/iterator的取值运算会自动检测当前迭代器是否失效。如果失效则会抛出index_out_of_bound（与at(), []保持一致）
const_iterator与iterator互相可以作为拷贝构造的原值。可以进行赋值操作。
额外添加了reserve这个成员方法。与翁阿姨的教材上描述保持一致。如果保留的空间小于当前至少所需，则会抛出std :: out_of_range
额外添加了space_doubles这个成员方法。手动调用可以倍增当前占用的空间。

iterator的私有数据成员的一些说明：
index	下标	一个整数，表明当前迭代器所指的是哪一个元素。
context	"语境"	一个指向vector<T>的指针，表明当前迭代器依赖于哪一个vector而生存。
