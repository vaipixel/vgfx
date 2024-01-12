# vgfx

## Device

抽象一个渲染设备。包括用于渲染的上下文锁定和解锁功能，存在资源争用的多线程环境中使用。

## Window

代表一个设备可以渲染的可显示窗口。它包括管理和呈现关联表面的方法。

## Context

代表渲染所需的状态，包括对设备、缓存和其他GPU资源的引用。它包括用于管理资源和将命令刷新到 GPU 的方法。

## Surface

代表一个绘图表面。它管理 Canvas 绘制进入的像素，并且始终具有非零尺寸。基于不同的参数如宽度、高度和上下文创建实例。

## Canvas

提供一个绘制接口

### Matrix

代表了一个 3x2 矩阵，用于坐标变换

- 坐标变换：Matrix 类保存了一个 3x2 矩阵，用于执行坐标变换。这包括平移（translation）、缩放（scaling）、倾斜（skewing）和旋转（rotation）。
- 仿射变换：这些变换类型统称为仿射变换（affine transformations），它们在变换过程中保持线条的直线性和平行性。这在图形渲染中非常重要。
- 行主序存储：矩阵元素按行主序排列。

### Paint

用于控制绘制时应用的各种选项

- 风格设置：Paint 类包含一个 setStyle 方法，用于设置绘制几何形状时的风格，比如填充（Fill）或描边（Stroke）。
- 颜色和透明度：提供 getColor、setColor、getAlpha 和 setAlpha 方法来管理绘制时使用的颜色和透明度。
- 笔触属性：包括设置笔触宽度（setStrokeWidth）、线帽（setLineCap）、线接合（setLineJoin）和斜接限制（setMiterLimit）的方法。
- 高级绘制选项：提供设置渐变（setShader）、遮罩滤镜（setMaskFilter）、颜色滤镜（setColorFilter）和图像滤镜（setImageFilter）的方法。
- 重置功能：reset 方法将 Paint 对象的所有内容重置为其初始值。

`Paint` 类的设计体现了图形编程中对于绘制属性的灵活管理的需求。通过提供这些方法，它允许用户以精细的方式控制绘制效果。

### Path

`Path` 类用于表示和操作几何路径。

- 几何形状的表示：Path 类包含几何形状，可以是空的，或者包含一个或多个轮廓勾勒动作（称为“verbs”）
- 路径的开始和构造：路径始终以移动（move）动作到笛卡尔坐标开始，后续可能会跟随其他动作（如添加线条或曲线）。
- 闭合路径：添加闭合（close）动作可以将几何形状变为连续的闭环，形成封闭轮廓。
- 包含多个轮廓：路径可以包含任意数量的轮廓，每个轮廓都以移动动作开始。

## GPU

### Proxies

#### ResourceProxy

用于所有代理派生对象的基类。它实现了资源的延迟加载，只在实际需要的时候才进行加载。

### Backend

抽象了 VGFX 会使用的后端 API

#### BackendTexture

用于传入和从VGFX接收有关后端纹理对象数据的包装类。

#### BackendRenderTarget

用于传入和从 VGFX 接收有关后端渲染目标对象数据的包装类。

#### BackendSemaphore

用于传入和从 VGFX 接收有关后端信号量对象数据的包装类。