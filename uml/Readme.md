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
