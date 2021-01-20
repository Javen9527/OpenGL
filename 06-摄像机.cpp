总结：
    1.观察矩阵将世界坐标转换成观察坐标，摄像机类是将世界坐标转换为观察者坐标
    2.定义摄像机需要定义它在世界坐标中的：位置、方向（Z）、指向它右侧的向量（X）、指向它上侧的向量(Y)

概述：
1.获得观察坐标系
{
    //世界坐标系
    X向右，Y向上，Z从屏幕向外

    //摄像机的位置
    即在世界坐标系中（原点）指向摄像机的向量

    //摄像机的方向（观察坐标系中的Z轴）
    指摄像机看向的方向的相反方向
    该方向作为观察坐标中的Z轴

    //指向它右侧的向量（观察坐标系的X轴）
    如何获得：通过世界坐标系中的Y轴和观察坐标的Z轴叉乘获得

    //指向它上侧的向量（观察者坐标系的Y轴）
    如何获得：通过观察坐标系的Z轴和X轴叉乘获得
}

2.LookAt矩阵
{
    //坐标系变换矩阵
    通过观察者坐标系 + 平移向量（摄像机的位置）创建的矩阵，乘以原空间（世界坐标）中任意向量可将其变换到观察空间
    LookAt矩阵是：
    |¯ Rx   Ry   Rz   0  ¯|  |¯ 1  0  0  -Px ¯| 
    |  Ux   Uy   Uz   0   |  |  0  1  0  -Py  |
    |  Dx   Dy   Dz   0   |  |  0  0  1  -Pz  |
    |_ 0    0    0    1  _|  |_ 0  0  0   1  _|
}

3.glm库实现LookAt矩阵
{
    //仔细分析上述LookAt实际必须的部分是：
    摄像机的位置
    目标位置
    世界空间的Y轴
}

4.视角移动
{
    //欧拉角
    俯仰角（pitch） 偏航角（Yaw） 滚转角（Roll）

    //通过俯仰角和偏航角获得摄像机的位置向量
}

5.创建摄像机类
{
    //基于欧拉角的摄像机类缺点
    万向节死锁

    //基于四元数的摄像机
}