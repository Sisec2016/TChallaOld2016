
#ifndef HSX_CONFIG_DEFINE_H
#define HSX_CONFIG_DEFINE_H


#include "./hsx_netclient.h"


////////////////////////////////////////////////////////////////////////////////
// 配置中的宏定义
////////////////////////////////////////////////////////////////////////////////

#define max_user_cnt				(10)				// 最大用户数，其中包含一个管理员用户
#define max_normal_user_cnt			(max_user_cnt -1)	// 最大的普通用户数，是除去管理员以外的用户数
#define max_user_name_len			(32)				// 最大用户名称长度
#define max_user_pwd_len			(32)				// 最大用户密码长度

#define max_name_len				(32)				// 最大的名称长度
#define max_address_len				(64)				// 最大地址长度
#define max_hdd_cnt					(8)					// 最大支持的硬盘个数
#define max_alarm_out_cnt			(4)					// 最大报警输出个数

#define motion_area_rect_row		(12)				// 整个视频区域被分割成12*16的块，以块为单位来设置移动侦测区域
#define motion_area_rect_column		(16)
#define max_mosaic_area_cnt			(4)					// 最大可以设置的马赛克区域的个数
#define day_per_week				(7)					// 每周的天数
#define hour_per_day				(24)				// 每天的小时数

#define max_ptz_protocol_cnt		(16)				// 最大支持的云台协议个数
#define max_preset_point_cnt		(255)				// 最大预置点个数
#define max_cruise_preset_cnt		(16)				// 巡航线路中的最大预置点个数

#define max_ddns_protocol_cnt		(32)				// 最大ddns协议个数

#define max_email_username_len		(64)				// 最大email用户名长度
#define max_email_userpass_len		(32)				// 最大email用户密码长度
#define max_email_receiver_cnt		(3)					// 最大支持的邮件接收者个数

#define max_wifi_search_cnt			(16)				// wifi最大搜索个数
#define max_spare_domain_cnt		(1)					// 最大备用域名数
#define max_usb_disk_cnt			(4)					// 最大支持的u盘个数

////////////////////////////////////////////////////////////////////////////////
// 配置命令id
////////////////////////////////////////////////////////////////////////////////
enum msg_dvr_ctrl_id
{
	msg_get_wifi_search_info = 908,						// 获取wifi搜索信息
	msg_get_usb_disk_info = 910,						// 获取U盘信息

	msg_get_device_cfg = 1000,							// 获取设备配置
	msg_set_device_cfg,									// 设置设备配置

	msg_get_dst_cfg,									// 获取DST配置
	msg_set_dst_cfg,									// 设置DST配置

	msg_get_ntp_cfg,									// 获取NTP配置
	msg_set_ntp_cfg,									// 设置NTP配置

	msg_get_disk_cfg,									// 获取硬盘配置
	msg_set_disk_cfg,									// 设置硬盘配置

	msg_get_user_cfg,									// 获取用户配置
	msg_set_user_cfg,									// 设置用户配置

	msg_get_channel_basic_cfg,							// 获取通道基本配置
	msg_set_channel_basic_cfg,							// 设置通道基本配置
	msg_get_channel_ptz_cfg,							// 获取通道PTZ配置
	msg_set_channel_ptz_cfg,							// 设置通道PTZ配置

	msg_get_record_schedule_cfg,						// 获取录像计划配置
	msg_set_record_schedule_cfg,						// 设置录像计划配置
	msg_get_record_quality_cfg,							// 获取录像画质配置
	msg_set_record_quality_cfg,							// 设置录像画质配置

	msg_get_alarm_in_cfg,								// 获取报警输入配置
	msg_set_alarm_in_cfg,								// 设置报警输入配置
		
	msg_get_network_basic_cfg,							// 获取网络基本配置
	msg_set_network_basic_cfg,							// 设置网络基本配置
	msg_get_network_advanced_cfg,						// 获取网络高级配置
	msg_set_network_advanced_cfg,						// 设置网络高级配置

	msg_get_channel_attr_cfg,							// 获取通道属性配置
	msg_set_channel_attr_cfg,							// 设置通道属性配置

	msg_get_ipc_cfg,									// 获取IPC配置									
	msg_set_ipc_cfg,									// 设置IPC配置

	msg_get_network_wireless_cfg,						// 获取网络无线配置
	msg_set_network_wireless_cfg,						// 设置网络无线配置

	msg_get_device_info = 1100,							// 获取设备信息
	msg_get_channel_info,								// 获取通道信息
	msg_get_alarm_in_info,								// 获取报警输入信息
	msg_get_network_info,								// 获取网络信息
	msg_get_wireless_info,								// 获取无线信息
};

////////////////////////////////////////////////////////////////////////////////
// 配置信息结构体定义
////////////////////////////////////////////////////////////////////////////////

#pragma pack(push)
#pragma pack(1) 


// 视频制式
typedef enum 
{
	VIDEO_STD_NTSC        = 0x00000001,					// NTSC
	VIDEO_STD_PAL         = 0x00000002,					// PAL
	VIDEO_STD_SECAM       = 0x00000004,					// SECAM
}video_stand_e;  


/*	
	设备配置
	获取设备配置的命令id为msg_get_device_cfg
	设置设备配置的命令id为msg_set_device_cfg
*/
typedef struct
{
	char dvr_name[max_name_len];						// dvr设备名称, 注意使用的是utf-8编码
	long dvr_id;										// dvr设备id（用于遥控器设置）
	long video_standard;								// 视频制式，请参考video_stand_e枚举类型定义

	float latitude;										// 设备所在纬度 [-90, 90] ，无效值：360
	float longitude;									// 设备所在经度 [-180, 180]，无效值：360

	// 设备时间
	DWORD year;											//	年，如2011
	DWORD month;										//	月，0-11
	DWORD day;											//	日，1-
	DWORD hour;											//	时，0-23
	DWORD minute;										//	分，0-59
	DWORD second;										//	秒，0-59
	
}dvr_device_cfg, *lpdvr_device_cfg;

// 硬盘状态
typedef enum
{
	DISK_STAT_ERROR	 	= -1,							// 错误
	DISK_STAT_NORMAL 	= 0,							// 正常
	DISK_STAT_WRITE 	= 1,							// 正在写入
	DISK_STAT_FORMAT 	= 2,							// 正在格式化
}disk_state_e;


// 网络能力定义
typedef enum
{
	SUPPORT_CH_ATTR			= (1 << 0),					// 是否支持通道属性
	SUPPORT_SYNC_PLAYBACK	= (1 << 1),					// 是否支持同步回放
	SUPPORT_ADVANCED_CFG	= (1 << 2),					/* 是否支持高级配置，对于您使用的网络库版本，一般情况下都是支持高级配置的;
														但对于比较老的网络库会不支持dst、ntp等配置，这种情况，建议您升级dvr设备*/
	SUPPORT_MULTI_STREAM    = (1 << 3),					// 是否支持多码流
	SUPPORT_WIFI			= (1 << 4),					// 是否支持wifi
	SUPPORT_3G				= (1 << 5),					// 是否支持3G
	SUPPORT_P2P				= (1 << 6),					// 是否支持P2P
	PN_REBOOT				= (1 << 7),					// 修改制式是否需要重启
}net_capability_e;


// 视频分辨率
typedef enum
{
	ENC_SIZE_NOT_CARE = 0,		//维持原来尺寸不变
	ENC_SIZE_CIF 	= 0x02,		//352*288
	ENC_SIZE_HD1	= 0x04,		//704*288
	ENC_SIZE_D1		= 0x08,		//704*576
	ENC_SIZE_720P	= 0x10,		//1280*720
	ENC_SIZE_1080P	= 0x20,		//1920*1080
	ENC_SIZE_SXGA	= 0x40,		//1280*1024
	ENC_SIZE_VGA	= 0x80,		//640*480
	ENC_SIZE_QVGA	= 0x100,	//320*240
	ENC_SIZE_QQVGA	= 0x200,	//176*128
	ENC_SIZE_1280x960 = 0x400,	//1280*960
}enc_size_e;

// 编解码资源受限类型
typedef enum
{
	AD_LIMIT_BY_ENC_PERFOR, // 受限于空闲编码资源
	AD_LIMIT_BY_ANALOGO,	// 受限于空闲模拟通道
	AD_LIMIT_BY_NONE,		// 不受限
}ad_ch_resource_type;


/*	
	设备信息（只读）
	获取设备信息的命令id为msg_get_device_info
*/
typedef struct
{
	char board_name[max_name_len];						// 板子名称（用于升级包的校验）
	DWORD board_id;										// 板型id
	DWORD serial_number;								// 序列号
	char mac[max_name_len];								// 设备mac地址，如：00:0b:74:9f:5f:33

	char software_version_base[max_name_len];			// 基础软件版本，用于升级包的校验，格式:主版本.次版本.修订版本，如1.0.0
	char software_version_main[max_name_len];			// 软件版本，如1.0.0
	char software_build_date[max_name_len];				// 软件生成日期
	char hardware_version[max_name_len];				// 硬件版本，如1.0.0
	char hardware_build_date[max_name_len];				// 硬件生成日期
	
	DWORD video_analog_cnt_max;							// 模拟通道最大个数
	DWORD video_digital_cnt_max;						// 数字通道最大个数

	DWORD spot_cnt;										// spot个数								
	DWORD audio_enc_cnt;								/* 音频通道个数, 表示前audio_enc_cnt个视频通道支持音频,
														   注意：对于hvr/nvr设备，该参数无效*/
	DWORD audio_talk_cnt;								// 语音对讲个数

	DWORD alarm_in_cnt;									// 报警输入个数	
	DWORD alarm_out_cnt;								// 报警输出个数	

	DWORD video_enc_resolution;							/* 视频编码能力（分辨率），enc_size_e类型的组合, 
														   注意：当net_capability支持通道属性时，以各通道属性内的分辨率能力为主*/
	DWORD video_analog_performance;						// 模拟视频编码性能
	DWORD video_analog_digital_performance;				// 模拟数字视频公用编码性能
	DWORD video_digital_performance;					// 数字视频编码性能

	DWORD disk_cnt;										// 硬盘个数
	DWORD capacity[max_hdd_cnt];						// 硬盘总容量，单位MB		
	DWORD useable[max_hdd_cnt];							// 硬盘可使用容量，单位MB		
	DWORD write_status[max_hdd_cnt];					// 硬盘状态，参见disk_state_e
	char disk_type[max_hdd_cnt][max_name_len];			// 硬盘类型

	DWORD is_support_ch_auth;							// 设备是否支持通道权限
	DWORD net_capability;								// 网络能力，net_capability_e类型的组合
	ad_ch_resource_type ad_ch_res_type;					// 编解码资源受限类型

}dvr_device_info, *lpdvr_device_info;


/*	
	U盘信息（只读）
	获取U盘信息的命令id为msg_get_usb_disk_info
*/
typedef struct
{
	long disk_cnt;										// u盘个数
	long capacity[max_usb_disk_cnt];					// u盘总容量，单位MB		
	long useable[max_usb_disk_cnt];						// u盘可使用容量，单位MB		
	long write_status[max_usb_disk_cnt];				// u盘状态，参见disk_state_e
	char disk_type[max_usb_disk_cnt][max_name_len];		// u盘类型

}dvr_usb_disk_info;


/*	
	DST配置
	获取DST配置的命令id为msg_get_dst_cfg
	设置DST配置的命令id为msg_set_dst_cfg
*/
typedef struct
{
	// 夏令时DST
	DWORD dst_enable;									// 是否开启夏令时，0--关闭 1--开启
	DWORD adjust_time_len_s;							// 调整的时间长度 (秒)

	// 夏令时起始时间
	int begin_month;									// [0,11]
	int begin_week_index;								// [1-5]
	int begin_week_day;									// [0-6]
	int begin_hour;										// [0-23]
	int begin_minute;									// [0-59]
	int begin_second;									// [0-59]

	// 夏令时结束时间
	int end_month;										// [0,11]
	int end_week_index;									// [1-5]
	int end_week_day;									// [0-6]
	int end_hour;										// [0-23]
	int end_minute;										// [0-59]
	int end_second;										// [0-59]	

}dvr_dst_cfg, *lpdvr_dst_cfg;



/*	
	NTP配置
	获取NTP配置的命令id为msg_get_ntp_cfg
	设置NTP配置的命令id为msg_set_ntp_cfg
*/
typedef struct
{
	int ntp_enable;										// 是否开启网络时间同步，0--关闭 1--开启
	int interval;										// 同步时间间隔 (24*3600 - 7*24*3600 秒)
	int timezone_hour;									// 时区，时(0-11)
	int timezone_min;									// 时区，分(0-59)

	char server[256];									// NTP服务器

}dvr_ntp_cfg, *lpdvr_ntp_cfg;	



/*	
	硬盘配置
	获取硬盘配置的命令id为msg_get_disk_cfg
	设置硬盘配置的命令id为msg_set_disk_cfg
*/
typedef struct
{
	int overwrite_enable;								// 是否开启硬盘覆盖

}dvr_disk_cfg, *lpdvr_disk_cfg;



// 用户权限
typedef enum
{	
	eAuthority_Undefined		= 0x00,
	eAuthority_Configuration	= 0x01,					// 系统配置权限
	eAuthority_PTZControl		= 0x02,					// 云台控制权限
	eAuthority_Playback			= 0x04,					// 回放权限
	eAuthority_Backup			= 0x08,					// 备份权限
	eAuthority_All				= eAuthority_Configuration | eAuthority_PTZControl | eAuthority_Playback | eAuthority_Backup,
}eAuthority;

/*	
	用户配置
	获取用户配置的命令id为msg_get_user_cfg
	设置用户配置的命令id为msg_set_user_cfg
*/
typedef struct
{
	int ch_auth_enable;									// 是否启用通道权限。只有设备有此能力时才能启用通道权限

	char admin_name[max_user_name_len];					// 管理员名称（只读），只能是"Admin"	
	char admin_pass[max_user_pwd_len];					// 管理员密码
	DWORD admin_auth;									// 管理员权限（只读），管理员拥有所有权限，参见eAuthority
	DWORD admin_ch_auth_mask;							// 通道权限掩码

	DWORD user_cnt;										// 普通用户的个数
	char user_name[max_normal_user_cnt][max_user_name_len];	// 普通用户的用户名称，用户名称不为空的用户即为有效用户
	char user_pass[max_normal_user_cnt][max_user_pwd_len];	// 普通用户的用户密码
	DWORD user_auth[max_normal_user_cnt];				// 普通用户的权限,参见eAuthority枚举类型的定义
	DWORD user_ch_auth_mask[max_normal_user_cnt];		// 普通用户的通道权限掩码
	
}dvr_user_cfg, *lpdvr_user_cfg;





/*	
	通道基本配置
	获取通道基本配置的命令id为msg_get_channel_basic_cfg
	设置通道基本配置的命令id为msg_set_channel_basic_cfg
*/
typedef struct
{	
	int video_channel;									// 通道号，从0开始
	char name[max_name_len];							// 通道名称, 注意使用的是utf-8编码

	// 色彩调节
	DWORD brightness;									// 亮度 0-255
	DWORD contrast;										// 对比度 0-255
	DWORD saturation;									// 饱和度 0-255
	DWORD hue;											// 色度 0-255	
	DWORD sharpness;									// 锐度（清晰度） 0-255

	// 信号丢失报警 
	DWORD vl_trigger_record_mask;						// 联动录像的通道掩码，如二进制0101表示触发第1、3通道的录像
	DWORD vl_trigger_alarm_out_mask;					// 联动报警输出的通道掩码，含义同上
	DWORD vl_trigger_live;								// 联动预览的通道号，从0开始，(DWORD)-1表示关闭联动预览
	DWORD vl_trigger_buzzer;							// 联动蜂鸣器报警
	DWORD vl_trigger_email;								// 联动邮件通告

	// 移动侦测 
	DWORD motion_en;									// 是否打开移动侦测，0--关闭 1--开启
	BYTE motion_area[motion_area_rect_row][motion_area_rect_column];// 移动侦测区域，以宏块为单位，0--撤防 1--布防
	DWORD motion_senstivity;							// 移动侦测灵敏度，0-4，数值越大灵敏度越高
	DWORD mt_trigger_record_mask;						// 联动录像的通道掩码，如二进制0101表示触发第1、3通道的录像
	DWORD mt_trigger_alarm_out_mask;					// 联动报警输出的通道掩码，含义同上
	DWORD mt_trigger_live;								// 联动预览的通道号，从0开始，(DWORD)-1表示关闭联动预览
	DWORD mt_trigger_buzzer;							// 联动蜂鸣器报警						
	DWORD mt_trigger_mail;								// 联动邮件通告

	//马赛克
	DWORD mosaic_cnt;									// 马赛克的个数
	DWORD mosaic_x[max_mosaic_area_cnt];				// 马赛克区域的x坐标, [比例，分母固定为16，这里是分子的值：0-16，下同]
	DWORD mosaic_y[max_mosaic_area_cnt];				// 马赛克区域的y坐标
	DWORD mosaic_w[max_mosaic_area_cnt];				// 马赛克区域的宽度
	DWORD mosaic_h[max_mosaic_area_cnt];				// 马赛克区域的高度

}dvr_channel_basic_cfg, *lpdvr_channel_basic_cfg;

/*	
	通道PTZ配置
	获取通道PTZ配置的命令id为msg_get_channel_ptz_cfg
	设置通道PTZ配置的命令id为msg_set_channel_ptz_cfg
*/
typedef struct
{
	int video_channel;									// 通道号，从0开始
	//	PTZ
	DWORD speed;										// 云台移动的速度，1-16
	DWORD baudrate;										// 波特率，1200, 2400, 4800, 9600
	DWORD databit;										// 数据位
	DWORD stopbit;										// 停止位
	DWORD parity;										// 校验位
	DWORD address;										// 云台地址
	DWORD flowcontrol;									// 流控

	DWORD protocol_index;								// 当前通道的云台协议索引	
	DWORD protocol_cnt;									// 云台协议个数
	char protocol_name[max_ptz_protocol_cnt][max_name_len]; // 支持的云台协议名称

	DWORD cruise_preset_cnt;							// 巡航预置点个数
	DWORD cruise_preset[max_cruise_preset_cnt];			// 巡航预置点id，从0开始
	DWORD delay_time[max_cruise_preset_cnt];			// 停留时间(秒), 1-(24*3600)

}dvr_channel_ptz_cfg, *lpdvr_channel_ptz_cfg;

// ipc类型
typedef enum eIPCType
{
	eIpcType_None,				// 不是IPC
	eIPCType_AutoAdapt = 1,		// 自动适匹IPC的类型,用户应该尽量使用确切的类型,否则会因为支持类型的增多影响成功连接的时间 (预留)
	eIPCType_AMTK_V5,			// A-MTK V5型,一般指MTK 1.3Mega的IPC,软件版板是5.0的 (预留)
	eIPCType_AMTK_V6,			// A-MTK V6型,一般指MTK 2.0Mega的IPC,软件版板是6.0的
	eIPCType_GK,				// GK
	eIPCType_ONVIF,				// onvif
	eIPCType_IPUX,				// IPUX厂家的,这个设备只支持一个码流.
	eIPCType_ONVIF_TST,			// 天视通ONVIF协议,不设置参数.因为设置参数会导致其不正常.
}eIPCType;


/*	
	通道属性配置
	获取通道属性配置的命令id为msg_get_channel_attr_cfg
	设置通道属性配置的命令id为msg_set_channel_attr_cfg
*/
typedef struct
{
	int video_channel;									// 通道号，从0开始
	int enable;											// 当前通道是否已经启用.
	int is_ipcam;										// 当前通道是本地通道还是IPCAM通道. 0--本地 1--IP通道（只读）
	int ipcam_port;										// IPCAM的信令端口.
	int ipcam_channel;									// IPCAM的通道号,一般为0.
	int ipcam_resolution;								// IPCAM的编码分辨率
	DWORD video_enc_resolution;							// 视频编码能力（分辨率），enc_size_e类型的组合

	DWORD ipcam_ipaddr;									// IPCAM的IP地址.
	char ipcam_username[max_user_name_len];				// 登陆IPCAM的用户名
	char ipcam_password[max_user_pwd_len];				// 登陆IPCAM的用户密码
	eIPCType ipcam_type;								// IPCAM类型

}dvr_channel_attr_cfg, *lpdvr_channel_attr_cfg;

// ipc工作模式
 typedef enum
 {
 	IPC_AE_INDOOR_MODE = 0, //室内模式
 	IPC_AE_OUTDOOR_MODE = 1, //室外模式
 }ipc_ae_work_mode;

 typedef enum
 {
	 ICR_WORK_BY_CHECK_LEVEL,	// 自动，根据灯板检测电压和相关配置来工作
	 ICR_WORK_FORCE_DAY,		// 强制彩色
	 ICR_WORK_FORCE_NIGHT,		// 强制黑白
 }icr_wrok_mode;

/*	
	IPC配置
	获取IPC配置的命令id为msg_get_ipc_cfg
	设置IPC配置的命令id为msg_set_ipc_cfg
*/
typedef struct
{
	// 自动曝光
	ipc_ae_work_mode work_mode;							// 工作模式
	long outdoor_day;									// 室内白天 1-100
	long outdoor_night;									// 室内黑夜	1-100
	long indoor_day;									// 户外白天1-100									
	long indoor_night;									// 户外黑夜1-100
	long frequence;										// 电源频率 50HZ/60HZ

	// 色彩模式
	char fixed_mode_start_hour;							// 起始小时，0-23,default 18
	char fixed_mode_start_min;							// 起始分钟，0-59,default 0
	char fixed_mode_end_hour;							// 结束小时，0-23,default 21
	char fixed_mode_end_min;							// 结束分钟，0-59,default 0
	long fixed_mode;									// 强制为何种模式, 参见icr_wrok_mode

}dvr_ipc_cfg, *lpdvr_ipc_cfg;

/*
	通道信息（只读）
	获取通道信息的命令id为msg_get_channel_info
*/
typedef struct
{
	int video_channel;									// 通道号，从0开始

	DWORD is_recording;									// 是否正在录像，0--未录像 1--正在录像
	DWORD record_type;									// 录像类型，参见record_type_e枚举类型定义
	DWORD record_resolution;							// 录像分辨率， 参见enc_size_e枚举类型的定义
	DWORD record_fps;									// 实际帧率，单位fps
	DWORD record_kpbs;									// 实际码率，单位kbps

	DWORD is_videolost;									// 信号是否丢失
	DWORD is_motion;									// 当前是否有移动事件
	
}dvr_channel_info, *lpdvr_channel_info;





// 录像流类型
typedef enum
{
	eRecordSourceType_VideoOnly,						// 视频流	
	eRecordSourceType_VideoAudio,						// 音视频复合流
	eRecordSourceType_Undefined							// 未定义
}eRecordSourceType;

/*	
	录像计划配置
	获取录像计划配置的命令id为msg_get_record_schedule_cfg
	设置录像计划配置的命令id为msg_set_record_schedule_cfg
*/
typedef struct 
{
	int video_channel;									// 通道号，从0开始

	DWORD stream_type;									// 录像的流类型，参见eRecordSourceType枚举类型定义
	DWORD prerecord_time;								// 预录时间	
	DWORD delayrecord_time;								// 延迟录像时间		
	BYTE schedule[day_per_week][hour_per_day];			// 一周的录像计划，以小时为单位进行设置，录像类型参见record_type_e

}dvr_record_schedule_cfg;

/*	
	录像画质配置
	获取录像画质配置的命令id为msg_get_record_quality_cfg
	设置录像画质配置的命令id为msg_set_record_quality_cfg
*/
typedef struct 
{
	int video_channel;									// 通道号，从0开始

	int bitrate;										/* 普通录像码率, 单位kbps，
														   取值范围：256, 384, 512, 640, 768, 1024, 1536, 2048, 2560, 3072, 4096, 5120, 6144 */
	int framerate;										// 普通录像帧率，1-30 （FPS）
	int resolution;										// 普通录像分辨率，参见enc_size_e

	int event_bitrate;									/* 事件录像码率, 单位kbps，
														   取值范围：256, 384, 512, 640, 768, 1024, 1536, 2048, 2560, 3072, 4096, 5120, 6144 */
	int event_framerate;								// 事件录像帧率，1-30 （FPS）
	int event_resolution;								// 事件录像分辨率，参见enc_size_e
						 
}dvr_record_quality_cfg; 





/*	
	报警输入配置
	获取报警输入配置的命令id为msg_get_alarm_in_cfg
	设置报警输入配置的命令id为msg_set_alarm_in_cfg
*/
typedef struct
{
	int alarm_in_channel;								// 报警输入通道号，从0开始
	DWORD device_type;									// 报警设备类型，0--常闭 1--常开
	BYTE schedule[day_per_week][hour_per_day];			// 一周的报警计划，以小时为单位进行设置，0--撤防 1--布防

	DWORD trigger_record_mask;							// 联动录像的通道掩码，如二进制0101表示触发第1、3通道的录像
	DWORD trigger_alarm_out_mask;						// 联动报警输出的通道掩码，含义同上
	DWORD trigger_live;									// 联动预览的通道号，从0开始，(DWORD)-1表示关闭联动预览
	DWORD trigger_preset;								// 联动的预置点索引，从0开始
	DWORD trigger_buzzer;								// 联动蜂鸣器报警
	DWORD trigger_mail;									// 联动邮件通告

}dvr_alarm_in_cfg, *lpdvr_alarm_in_cfg;

/*	
	报警输入信息（只读）
	获取报警输入信息的命令id为msg_get_alarm_in_info
*/
typedef struct
{
	int alarm_in_channel;								// 报警输入通道号，从0开始
	DWORD device_type;									// 报警设备类型，0--常闭 1--常开
	DWORD status;										// 设备状态，0--正常 1--报警
}dvr_alarm_in_info, *lpdvr_alarm_in_info;




/*	
	网络基本配置
	获取网络基本配置的命令id为msg_get_network_basic_cfg
	设置网络基本配置的命令id为msg_set_network_basic_cfg
*/
typedef struct 
{
	int ip;												// ip地址
	int submask;										// 子网掩码
	int gateway;										// 网关
	int dns1;											// DNS1
	int dns2;											// DNS2

	int http_port;										// http端口，默认80
	int cmd_port;										// 信令端口，默认6001
	int data_port;										// 媒体端口，默认6002
	int mobile_port;									// 手机端口，默认6003
	
	int upnp_enable;									// UPnP设置，0--关闭 1--开启
	int dhcp_enable;									// IP获取方式，0--静态配置 1--动态获取
	int p2p_enable;										// 是否启用P2P, 0--禁用，1--启用

}dvr_network_basic_cfg, *lpdvr_network_basic_cfg;

/*	
	网络高级配置
	获取网络高级配置的命令id为msg_get_network_advanced_cfg
	设置网络高级配置的命令id为msg_set_network_advanced_cfg
*/
typedef struct  
{
	DWORD pppoe_enable;									// 是否开启拨号，0--关闭 1--开启
	char pppoe_user[max_user_name_len];					// pppoe用户名
	char pppoe_pass[max_user_pwd_len];					// pppoe用户密码

	DWORD ddns_enable;									// 是否开启动态域名，0--关闭 1--开启
	DWORD server_index;									// 当前使用的ddns域名服务器索引
	char domain_name[max_name_len];						// 设备域名
	char ddns_user[max_user_name_len];					// ddns用户名
	char ddns_pass[max_user_pwd_len];					// ddns用户密码
	DWORD server_cnt;									// 域名服务器个数			
	char server_info[max_ddns_protocol_cnt][max_address_len]; // 域名服务器信息

	// email
	DWORD email_enable;									// 是否启用邮件，0--关闭 1--开启
	char email_server[max_address_len];					// 发送邮件服务器（SMTP）
	DWORD email_port;									// 服务器端口
	DWORD ssl_enable;									// 是否需要安全连接，0--关闭 1--开启
	char email_sender[max_address_len];					// 发件人邮箱
	char email_user[max_email_username_len];			// 用户名称
	char email_pass[max_email_userpass_len];			// 用户密码
	char email_receiver[max_email_receiver_cnt][max_address_len]; // 收件人邮箱
	int  need_snapshot;									// 附带抓图，0--关闭 1--开启

	// subcode
	DWORD subcode_enable;								// 是否开启子码流，0--关闭 1--开启
	DWORD framerate_by_fps;								// 子码流帧率，单位fps，范围1-30
	DWORD bitrate_by_kbps;								// 子码流码率，单位kbps，范围10-512

}dvr_network_advanced_cfg;

// 3G 服务提供商类型
typedef enum provider_type_s
{
	NET_3G_AUTO,
	NET_3G_TD_SCDMA,
	NET_3G_WCDMA,		// 中国联通
	NET_3G_CDMA_1x,		// 中国电信
	NET_3G_GPRS,		// 中国移动
	NET_3G_EVDO,
}provider_type_t;

/*	
	网络无线配置
	获取网络无线配置的命令id为msg_get_network_wireless_cfg
	设置网络无线配置的命令id为msg_set_network_wireless_cfg
*/
typedef struct
{
	// wifi
	long wifi_enable;									// 是否启用WIFI，0--关闭 1--开启
	char wifi_pass[32];									// 访问的wifi网络的密码
	char wifi_ssid[32];									// 访问的wifi网络的SSID
	long wifi_auto_join;								// 是否自动加入
	long wifi_enable_dhcp;								// wifi端口是否使能dhcp
	long wifi_static_ip;								// 如果使能dhcp，该项忽略
	long wifi_static_submask;							// 如果使能dhcp，该项忽略
	long wifi_static_gw;								// 如果使能dhcp，该项忽略
	long wifi_static_dns1;								// 如果使能dhcp，该项忽略
	long wifi_static_dns2;								// 如果使能dhcp，该项忽略

	// 3G功能
	long net3g_enable;									// 是否开启,1,开启,0,禁用.
	provider_type_t net3g_provider_type;				// 服务提供商类型
	char net3g_dial_number[32];							// 号码
	char net3g_username[32];							// 用户名
	char net3g_password[32];							// 密码
	char net3g_apn[32];									// APN

}dvr_network_wireless_cfg;


/*	
	网络信息（只读）
	获取网络信息的命令id为msg_get_network_info
*/
typedef struct
{
	int ip;												// ip地址
	int submask;										// 子网掩码
	int gateway;										// 网关
	int dns1;											// DNS1
	int dns2;											// DNS2
	char mac[max_name_len];								// 设备mac地址，如：00:0b:74:9f:5f:33

	// pppoe info
	int pppoe_status;									// 拨号状态，0--未连接 1--连接
	int pppoe_ip;										// 拨号ip
	int pppoe_submask;									// pppoe子网掩码
	int pppoe_gateway;									// pppoe网关

	// 自带域名
	char own_domain_name[64];							// 域名名称
	time_t last_update_time;							// 最后一个成功刷新ip的时间，启动的时候为0
	char spare_domain_name[max_spare_domain_cnt][64];	// 备用域名名称
	time_t spare_last_update_time[max_spare_domain_cnt];// 备用域名最后一次重新刷新ip的时间

}dvr_network_info, *lpdvr_network_info;


/*	
	无线信息（只读）
	获取无线信息的命令id为msg_get_wireless_info
*/
typedef struct
{
	// wifi
	char wifi_ssid[32];									// SSID
	long wifi_connect_status;							// 是否连接
	long wifi_ip;										// wifi ip地址								
	long wifi_submask;									// wifi 子网掩码
	long wifi_gw;										// wifi 网关
	long wifi_dns1;										// wifi DNS1
	long wifi_dns2;										// wifi DNS2

	// 3G
	long net3g_status;									// 是否连接上
	long net3g_ip;										// IP
	long net3g_submask;									// 子网掩码
	long net3g_gateway;									// 网关
	int net3g_reserved[128];							// 保留用

}dvr_network_wireless_info;


/*	
	wifi搜索信息（只读）
	获取wifi搜索信息的命令id为msg_get_wifi_search_info
*/
typedef struct
{
	long count;											// 查找到的wifi网络的总数
	char ssid[max_wifi_search_cnt][32];					// ssid
	long quality[max_wifi_search_cnt];					// 信号强度，0-100，0-最弱，100-最强
	long encryption[max_wifi_search_cnt];				// 是否加密，0-no，1-yes
	long is_join[max_wifi_search_cnt];					// 是否已加入，0-no 1-yes
	long state[max_wifi_search_cnt];					// 连接状态，0-no 1-yes
}wifi_search_info;


#pragma pack(pop)

#endif

