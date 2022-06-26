sequence_diagram_before中存放的是没有进行版本控制之前的相关截图

## 2022年5月25日
- 主要更改：添加了界面类和界面相关的控制类 
- 问题：
1. 界面控制类和之前的JottingSocialControl是不是一种控制类，还是说一个是客户端的，一个是服务器端的
2. 查看笔记详情中需要几个界面控制类，一个还是说三个（materialListControl,JottingListControl,CommentListControl）



## 2022年5月27日
- 主要更改：去掉了UI界面的控制类，只留一个控制类，完善了UI界面的顺序图
- 问题：
1. 观察者模式怎么实现
2. 界面的Control 和 业务逻辑的 Control 如何区分

## 2022年6月6日
- 主要更改：基于模型的一致性，统一了属性名和操作名，添加了scanJottings、publishJottings活动图

## 2022年6月7日
- 主要更改：基于模型的一致性，更新完善了类图、顺序图
- 问题：
1. 新增评论后，将新增的评论添加到数据库后，需要在Jotting、Netizen中添加，还是在Cache中,没有Jotting的实例 MVC

## 2022年6月8日
- 主要更改：明确实体类的职责、控制器类应该把业务逻辑的实现委托给实体类
1. 重新细致描述了用况、修改了login、pushJottings、checkOneJotting、commentJotting顺序图


## 2022年6月9日
- 主要更改：重新绘制commentJotting顺序图里面缓存更新、网民申请关注的部分
- 问题：
1. 对于一些消息的接收者明确(类的操作明确)，但发送者有些不太清楚

## 2022年6月11日
- 主要更改：补充完善6.9的内容


## 2022年6月26日
- 主要更改：去掉redis,自定义缓存，更新类图
