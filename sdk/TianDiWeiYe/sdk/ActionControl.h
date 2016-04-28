				  //0x00-0x63 general  function
//0x00-0x2f decoder control
#define     REGISTER                0         //register  function
#define     MOVE_UP                 1         //ptz up
#define     MOVE_UP_STOP            2         //stop ptz up
#define     MOVE_DOWN               3         //ptz down
#define     MOVE_DOWN_STOP          4         //stop ptz down
#define     MOVE_LEFT               5         //ptz left
#define     MOVE_LEFT_STOP          6         //stop ptz left
#define     MOVE_RIGHT              7         //ptz right
#define     MOVE_RIGHT_STOP         8         //stop ptz right
#define     MOVE_UP_LEFT            9         //ptz top left
#define     MOVE_UP_LEFT_STOP       10        //stop ptz top left
#define     MOVE_UP_RIGHT           11        //ptz top right
#define     MOVE_UP_RIGHT_STOP      12        //stop ptz top right
#define     MOVE_DOWN_LEFT          13        //ptz down left
#define     MOVE_DOWN_LEFT_STOP     14        //stop ptz down left
#define     MOVE_DOWN_RIGHT         15        //ptz down right
#define     MOVE_DOWN_RIGHT_STOP    16        //stop ptz down right
/************************************************************************/
/* PTZ协议控制                                                                     */
/************************************************************************/
#define     PROTOCOL_MOVE_UP                 		1        //向上
#define     PROTOCOL_MOVE_DOWN               		2        //向下
#define     PROTOCOL_MOVE_LEFT               		3        //向左
#define     PROTOCOL_MOVE_RIGHT              		4        //向右
#define     PROTOCOL_MOVE_UP_RIGHT           		5        //右上
#define     PROTOCOL_MOVE_UP_LEFT            		6        //左上
#define     PROTOCOL_MOVE_DOWN_RIGHT         		7        //右下
#define     PROTOCOL_MOVE_DOWN_LEFT          		8        //左下
#define     PROTOCOL_MOVE_STOP               		9        //停止
#define     PROTOCOL_ZOOMIN                  		10       //放大
#define     PROTOCOL_ZOOMOUT                 		11       //缩小
#define		PROTOCOL_IST					 		12		//变化停止
#define		PROTOCOL_FOCUS_ON						13		//焦点调近
#define		PROTOCOL_FOCUS_OFF						14		//焦点调远
#define		PROTOCOL_PTZ_FST				 		15		//焦点变化停止
#define		PROTOCOL_IA_ON					 		16		//光圈自动调整(光圈运动停)
#define		PROTOCOL_IRIS_OPEN						17 	    //光圈增大
#define		PROTOCOL_IRIS_CLOSE					    18		//光圈缩小
#define		PROTOCOL_RAIN_ON						19		//擦拭启动
#define		PROTOCOL_RAIN_OFF						20		//擦拭停止
#define		PROTOCOL_LIGHT_ON						21		//灯光开启
#define		PROTOCOL_LIGHT_OFF						22		//灯光停止
#define		PROTOCOL_CRUISE_START					23		//巡航开始
#define		PROTOCOL_CRUISE_STOP					24		//巡航停止
#define		PROTOCOL_PRESET							25		//转到预设点
#define		PROTOCOL_START_TRACK_CRUISE		 		26		//开始轨迹巡航
#define		PROTOCOL_STOP_TRACK_CRUISE		 		27		//停止轨迹巡航
#define		PROTOCOL_SET_PRESET				 		28       //设置预置位
#define		PROTOCOL_POWER_ON				 		29		//电源开启
#define		PROTOCOL_POWER_OFF				 		30		//电源关闭
#define		PROTOCOL_3D_POSITION			 		31		//PTZ 3D定位
#define		PROTOCOL_3D_ROCKER				 		32		//对3维摇杆的响应
#define		PROTOCOL_ASSISTANT_ON			 		33		//辅助开关开
#define		PROTOCOL_ASSISTANT_OFF			 		34		//辅助开关关


#define     SET_LEFT_BORDER         17        //set  left border
#define     SET_RIGHT_BORDER        18        //set  right border 
#define     SET_UP_BORDER           19        //set  up border
#define     SET_DOWN_BORDER         20        //set  down border
#define     HOR_AUTO                21        //horizontal auto        
#define     HOR_AUTO_STOP           22        //stop horizontal auto
#define     SET_HOR_AUTO_BEGIN      23        //set  horizontal auto start
#define     SET_HOR_AUTO_END        24        //set  horizontal auto end
#define     SET_HOR_AUTO_SPEED      25        //set  horizontal auto speed
#define     VER_AUTO                26        //vertical auto
#define     SET_VER_AUTO_BEGIN      27        //set  vertical auto start
#define     SET_VER_AUTO_END        28        //set  verticall auto end
#define     SET_VER_AUTO_SPEED      29        //set  verticall auto speed
#define     VER_AUTO_STOP           30        //stop vertical auto

#define     ZOOM_BIG                31        //zoom big
#define     ZOOM_BIG_STOP           32        //stop zoom big
#define     ZOOM_SMALL              33        //zoom small
#define     ZOOM_SMALL_STOP         34        //stop zoom small
#define     FOCUS_FAR               35        //focus far
#define     FOCUS_FAR_STOP          36        //stop focus far
#define     FOCUS_NEAR              37        //focus near
#define     FOCUS_NEAR_STOP         38        //stop focus near
#define     IRIS_OPEN               39        //open iris 
#define     IRIS_OPEN_STOP          40        //stop open iris
#define     IRIS_CLOSE              41        //close iris
#define     IRIS_CLOSE_STOP         42        //stop close iris

#define     LIGHT_ON                43        //light on
#define     LIGHT_OFF               44        //light off
#define     POWER_ON                45        //power on
#define     POWER_OFF               46        //power off
#define     RAIN_ON                 47        //rain on
#define     RAIN_OFF                48        //rain off
#define     TALK_ON                 49        //talk on 
#define     TALK_OFF                50        //talk off
#define     DEF_ON                  51        //arm 
#define     DEF_OFF                 52        //disarm

#define     BROWSE                  53        //inquiry
#define     ALARM_ANSWER            54        //alarm response
#define     STATE_ASK               55        //ask for upload control state


//0x30-0x4f dome control
#define     MOVE                    60        //dome move
#define     MOVE_STOP               61        //stop dome move
#define     CALL_VIEW               62        //call camera
#define     SET_VIEW                63        //set preset
#define     DELETE_VIEW             64        //delete preset
#define     SEQUENCE_BEGIN          65        //start cruise
#define     SEQUENCE_END            66        //stop cruise
#define     ADD_PRESET              67        //add  cruise
#define     DELETE_PRESET           68        //delete cruise
#define     CLEAR_SEQUENCE          69        //clear cruise setup
#define     TIME_SEQUENCE           70        //set cruise time
#define     SET_GUARD               71        //set guard
#define     DELETE_GUARD            72        //delete guard
#define     GET_HOR_AUTO_SPEED      73        //get horizontal auto speed
#define     GET_TRACK_TIME          74        //get  cruise time
#define     GET_TRACK_SEQUENCE      75        //get  cruise sequence
#define     GUARD_TIME              76        //set  guard time
#define     GET_VIEW_LIST           77        //get  cameras' sequence

//0x64-0xc7 special function
#define     SWITCH                  101        //manually switch matrix
#define     SWITCH_MONITOR          102		   //switch monitor     
#define     SWITCH_VIDICON          103        //switch camera
#define     SWITCH_ORDER            104        //sequential switch  
#define     SWITCH_ORDER_STOP       105        //stop sequential switch                                       
#define     SWITCH_GROUP            106        //group switch
#define     SWITCH_GROUP_STOP       107        //stop group switch

