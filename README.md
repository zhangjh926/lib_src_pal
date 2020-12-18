# lib_src_sal
实现硬件抽象层HAL 和 跨系统的抽象层SAL

doc				: 文档等资料放置的目录
HAL				: 硬件抽象层模块代码目录，每个模块生成单独的库文件。可以进行配置, 提供通用的模块接口
Platform.env	: 平台配置, 编译环境，模块配置	
SAL				: 对系统接口的抽象，兼容Linux和Rtos
third-party		: 第三方开源库文件的放置目录
unitest			: 模块单元测试目录
vendor			: 不同平台差异性的模块代码所在目录
driver			: 提供私有实现的驱动程序模块，可以通用的驱动程序



硬件抽象层开发方法步骤：
	1.先判断模块是否可以做到所有linux平台通用，如果可以，直接用模块下面的接口实现开发, 如果做不到，拷贝实现文件到vendor厂商下面对应的目录进行差异性开发
	2.修改编译脚本，根据平台选择性编译，可以参考video模块

举例说明:[以video开发为例]
	1.判读发现不同平台的video接口封装不同，所以不能在liblds_hal_video_encode/linux/下面直接开发功能.
	2.创建vendor/amba/linux/video/encode/目录，amba目录代表平台，linux / rtos 代表不同的操作系统。其他目录深度和HAL模块深度一致，命名稍有区别。然后在创建liblds_hal_video_encode_amba.c, 用来区分平台的差异化代码实现
	3.针对不同的平台开发视频库，对外开发xxx_interface.h接口，接口内容和liblds_hal_video_encode_base.h保持一致，liblds_hal_video_encode_amba.c 里面只针对xxx_interface.h接口进行调用即可。
	4.平台的视频接口库文件和头文件，拷贝到vendor/amba/linux/platform/include 或 vendor/amba/linux/platform/lib/ 下面，进行编译即可。或者把代码实现放到platform/src里面也可以。
