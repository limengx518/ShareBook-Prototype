sequence_diagram_before中存放的是没有进行版本控制之前的相关截图

2022年5月25日
主要更改：添加了界面类和界面相关的控制类 
问题：
    1.界面控制类和之前的JottingSocialControl是不是一种控制类，还是说一个是客户端的，一个是服务器端的
    2.查看笔记详情中需要几个界面控制类，一个还是说三个（materialListControl,JottingListControl,CommentListControl）



2022年5月27日

主要更改：去掉了UI界面的控制类，只留一个控制类，完善了UI界面的顺序图

问题：

	1. 观察者模式怎么实现
	2. 界面的Control 和 业务逻辑的 Control 如何区分


2022年5月28日
主要更改： 添加关于cache的类图

问题：
    1.cache中的6个缓存指的是实现为6个类，还是6个状态
      如果是6个类，那么inMemory(objectid)判断如果在缓存中，对于每个类的实例来说，返回的类型都不一样，那么还需要再次往下继承吗？
      如果是6个状态，那么缓存中的删除策略如何保证newCleanCache中的东西不被删除呢？


2022年5月31日
主要更改：代码中添加类cache，cache主要实现的函数为inCache(string key)和storeObject（unoredered_map<string,string>）,incache函数判断所传入的键是否在内存中,storeObject是把从数据库中拿出来的数据存放到缓存中去
问题：
    1.不用6个cache,主要负责从cache中读取数据，当数据需要更新时，先删除缓存，再更新数据库。此时涉及到数据同步问题，需要加锁解决
    2.netizen中所有Jotting的id,Jotting中所有material的id,进行序列化后存储到hash这个结构中去，这个思路在很多地方会用，代码有很多相似的地方
    3.关于cache做缓存时，缓存大小的设置，以及当缓存即将满时，采用什么策略将缓存中的键进行删除
    4.更新数据（先更新数据库，再删除缓存）要加锁的问题
