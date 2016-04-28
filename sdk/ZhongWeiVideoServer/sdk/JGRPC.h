//---------------------------------------------------------------------------
// JGRPC.h
//---------------------------------------------------------------------------

#pragma once

#ifndef JCSDK_EXPORTS
	typedef int GBOOL;
#endif


//json/account.json
#if 1

//account_get_users
#  if 1

//--- account_get_users definition ----
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_account_get_users PARAM_REQ_sdk_account_get_users;
typedef PARAM_RESP_vms_account_get_users PARAM_RESP_sdk_account_get_users;
#    else

typedef struct{
	int idle;
} PARAM_REQ_sdk_account_get_users;

typedef struct{
	int users_cnt;
	struct{
		char *name; //username
		char *level; //admin,operator,user,anonymous,extended
		char *description; //This is Adiministrator
	} *users;
} PARAM_RESP_sdk_account_get_users;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_account_get_users(JCLink_t nLinkID, PARAM_REQ_sdk_account_get_users *req, PARAM_RESP_sdk_account_get_users *resp);
#  endif

//account_add_user
#  if 1

//--- account_add_user definition ----
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_account_add_user PARAM_REQ_sdk_account_add_user;
typedef PARAM_RESP_vms_account_add_user PARAM_RESP_sdk_account_add_user;
#    else

typedef struct{
	char *name; //username
	char *passwd; //123456
	char *level; //admin,operator,user,anonymous,extended
	char *description; //This is Adiministrator
} PARAM_REQ_sdk_account_add_user;

typedef struct{
	int idle;
} PARAM_RESP_sdk_account_add_user;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_account_add_user(JCLink_t nLinkID, PARAM_REQ_sdk_account_add_user *req, PARAM_RESP_sdk_account_add_user *resp);
#  endif

//account_del_user
#  if 1

//--- account_del_user definition ----
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_account_del_user PARAM_REQ_sdk_account_del_user;
typedef PARAM_RESP_vms_account_del_user PARAM_RESP_sdk_account_del_user;
#    else

typedef struct{
	char *name; //username
} PARAM_REQ_sdk_account_del_user;

typedef struct{
	int idle;
} PARAM_RESP_sdk_account_del_user;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_account_del_user(JCLink_t nLinkID, PARAM_REQ_sdk_account_del_user *req, PARAM_RESP_sdk_account_del_user *resp);
#  endif

//account_modify_user
#  if 1

//--- account_modify_user definition ----
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_account_modify_user PARAM_REQ_sdk_account_modify_user;
typedef PARAM_RESP_vms_account_modify_user PARAM_RESP_sdk_account_modify_user;
#    else

typedef struct{
	char *name; //username
	char *passwd; //123456
	char *level; //admin,operator,user,anonymous,extended
	char *description; //This is Adiministrator
} PARAM_REQ_sdk_account_modify_user;

typedef struct{
	int idle;
} PARAM_RESP_sdk_account_modify_user;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_account_modify_user(JCLink_t nLinkID, PARAM_REQ_sdk_account_modify_user *req, PARAM_RESP_sdk_account_modify_user *resp);
#  endif

//account_login
#  if 1

//--- account_login definition ----
/*
grpc supply login ,but some device may need login cmd.
*/
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_account_login PARAM_REQ_sdk_account_login;
typedef PARAM_RESP_vms_account_login PARAM_RESP_sdk_account_login;
#    else

typedef struct{
	char *username; //abc
	char *password; //123
} PARAM_REQ_sdk_account_login;

typedef struct{
	int idle;
} PARAM_RESP_sdk_account_login;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_account_login(JCLink_t nLinkID, PARAM_REQ_sdk_account_login *req, PARAM_RESP_sdk_account_login *resp);
#  endif

//account_login_force
#  if 1

//--- account_login_force definition ----
/*
if client force login, server must disconnect other clients.
*/
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_account_login_force PARAM_REQ_sdk_account_login_force;
typedef PARAM_RESP_vms_account_login_force PARAM_RESP_sdk_account_login_force;
#    else

typedef struct{
	char *username; //abc
	char *password; //123
} PARAM_REQ_sdk_account_login_force;

typedef struct{
	int idle;
} PARAM_RESP_sdk_account_login_force;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_account_login_force(JCLink_t nLinkID, PARAM_REQ_sdk_account_login_force *req, PARAM_RESP_sdk_account_login_force *resp);
#  endif

#endif


//json/alarm.json
#if 1

//alarmin_start
#  if 1

//--- alarmin_start definition ----
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_alarmin_start PARAM_REQ_sdk_alarmin_start;
typedef PARAM_RESP_vms_alarmin_start PARAM_RESP_sdk_alarmin_start;
#    else

typedef struct{
	int channelid;
} PARAM_REQ_sdk_alarmin_start;

typedef struct{
	int idle;
} PARAM_RESP_sdk_alarmin_start;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_alarmin_start(JCLink_t nLinkID, PARAM_REQ_sdk_alarmin_start *req, PARAM_RESP_sdk_alarmin_start *resp);
#  endif

//alarmin_stop
#  if 1

//--- alarmin_stop definition ----
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_alarmin_stop PARAM_REQ_sdk_alarmin_stop;
typedef PARAM_RESP_vms_alarmin_stop PARAM_RESP_sdk_alarmin_stop;
#    else

typedef struct{
	int channelid;
} PARAM_REQ_sdk_alarmin_stop;

typedef struct{
	int idle;
} PARAM_RESP_sdk_alarmin_stop;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_alarmin_stop(JCLink_t nLinkID, PARAM_REQ_sdk_alarmin_stop *req, PARAM_RESP_sdk_alarmin_stop *resp);
#  endif

//alarmin_get_param
#  if 1

//--- alarmin_get_param definition ----
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_alarmin_get_param PARAM_REQ_sdk_alarmin_get_param;
typedef PARAM_RESP_vms_alarmin_get_param PARAM_RESP_sdk_alarmin_get_param;
#    else

typedef struct{
	int channelid;
} PARAM_REQ_sdk_alarmin_get_param;

typedef struct{
	GBOOL bEnable;
	GBOOL bNormallyClosed;
	GBOOL bEnableRecord;
	GBOOL bStarting;
	GBOOL bBuzzing;
	GBOOL bSendtoClient;
	GBOOL bSendEmail;
	int u8AlarmNum;
	int nDelay;
} PARAM_RESP_sdk_alarmin_get_param;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_alarmin_get_param(JCLink_t nLinkID, PARAM_REQ_sdk_alarmin_get_param *req, PARAM_RESP_sdk_alarmin_get_param *resp);
#  endif

//alarmin_set_param
#  if 1

//--- alarmin_set_param definition ----
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_alarmin_set_param PARAM_REQ_sdk_alarmin_set_param;
typedef PARAM_RESP_vms_alarmin_set_param PARAM_RESP_sdk_alarmin_set_param;
#    else

typedef struct{
	int channelid;
	GBOOL bEnable;
	GBOOL bNormallyClosed;
	GBOOL bEnableRecord;
	GBOOL bStarting;
	GBOOL bBuzzing;
	GBOOL bSendtoClient;
	GBOOL bSendEmail;
	int u8AlarmNum;
	int nDelay;
} PARAM_REQ_sdk_alarmin_set_param;

typedef struct{
	int idle;
} PARAM_RESP_sdk_alarmin_set_param;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_alarmin_set_param(JCLink_t nLinkID, PARAM_REQ_sdk_alarmin_set_param *req, PARAM_RESP_sdk_alarmin_set_param *resp);
#  endif

//alarmin_b_onduty
#  if 1

//--- alarmin_b_onduty definition ----
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_alarmin_b_onduty PARAM_REQ_sdk_alarmin_b_onduty;
typedef PARAM_RESP_vms_alarmin_b_onduty PARAM_RESP_sdk_alarmin_b_onduty;
#    else

typedef struct{
	int channelid;
} PARAM_REQ_sdk_alarmin_b_onduty;

typedef struct{
	GBOOL bOnduty;
} PARAM_RESP_sdk_alarmin_b_onduty;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_alarmin_b_onduty(JCLink_t nLinkID, PARAM_REQ_sdk_alarmin_b_onduty *req, PARAM_RESP_sdk_alarmin_b_onduty *resp);
#  endif

//alarmin_b_alarming
#  if 1

//--- alarmin_b_alarming definition ----
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_alarmin_b_alarming PARAM_REQ_sdk_alarmin_b_alarming;
typedef PARAM_RESP_vms_alarmin_b_alarming PARAM_RESP_sdk_alarmin_b_alarming;
#    else

typedef struct{
	int channelid;
} PARAM_REQ_sdk_alarmin_b_alarming;

typedef struct{
	GBOOL bAlarming;
} PARAM_RESP_sdk_alarmin_b_alarming;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_alarmin_b_alarming(JCLink_t nLinkID, PARAM_REQ_sdk_alarmin_b_alarming *req, PARAM_RESP_sdk_alarmin_b_alarming *resp);
#  endif

//alarm_get_param
#  if 1

//--- alarm_get_param definition ----
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_alarm_get_param PARAM_REQ_sdk_alarm_get_param;
typedef PARAM_RESP_vms_alarm_get_param PARAM_RESP_sdk_alarm_get_param;
#    else

typedef struct{
	int idle;
} PARAM_REQ_sdk_alarm_get_param;

typedef struct{
	int delay;
	int port;
	char *sender; //lfx@jovision.com
	char *server; //lfx@jovision.com
	char *username; //lfx
	char *passwd; //123456
	int receiver_cnt;
	char **receiver; //qlc@jovision.com
} PARAM_RESP_sdk_alarm_get_param;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_alarm_get_param(JCLink_t nLinkID, PARAM_REQ_sdk_alarm_get_param *req, PARAM_RESP_sdk_alarm_get_param *resp);
#  endif

//alarm_set_param
#  if 1

//--- alarm_set_param definition ----
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_alarm_set_param PARAM_REQ_sdk_alarm_set_param;
typedef PARAM_RESP_vms_alarm_set_param PARAM_RESP_sdk_alarm_set_param;
#    else

typedef struct{
	int delay;
	int port;
	char *sender; //lfx@jovision.com
	char *server; //lfx@jovision.com
	char *username; //lfx
	char *passwd; //123456
	int receiver_cnt;
	char **receiver; //qlc@jovision.com
} PARAM_REQ_sdk_alarm_set_param;

typedef struct{
	int idle;
} PARAM_RESP_sdk_alarm_set_param;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_alarm_set_param(JCLink_t nLinkID, PARAM_REQ_sdk_alarm_set_param *req, PARAM_RESP_sdk_alarm_set_param *resp);
#  endif

//alarm_report
#  if 1

//--- alarm_report definition ----
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_alarm_report PARAM_REQ_sdk_alarm_report;
typedef PARAM_RESP_vms_alarm_report PARAM_RESP_sdk_alarm_report;
#    else

typedef struct{
	char *type; //video,io,analyse
	char *subtype; //videoLost,motionDetect,videoBlock,hardDriverLost,doorAlarm,smoke,pir,invasion
	char *content; //alarm details
	char *detectorId; //xxx
	char *ystID; //A402153844
	char *devType; //card,dvr,ipc,nvr
	int channel;
} PARAM_REQ_sdk_alarm_report;

typedef struct{
	int idle;
} PARAM_RESP_sdk_alarm_report;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_alarm_report(JCLink_t nLinkID, PARAM_REQ_sdk_alarm_report *req, PARAM_RESP_sdk_alarm_report *resp);
#  endif

//alarm_heartbeat
#  if 1

//--- alarm_heartbeat definition ----
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_alarm_heartbeat PARAM_REQ_sdk_alarm_heartbeat;
typedef PARAM_RESP_vms_alarm_heartbeat PARAM_RESP_sdk_alarm_heartbeat;
#    else

typedef struct{
	char *ystID; //A402153844
	char *devType; //card,dvr,ipc,nvr
	int channel;
} PARAM_REQ_sdk_alarm_heartbeat;

typedef struct{
	int idle;
} PARAM_RESP_sdk_alarm_heartbeat;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_alarm_heartbeat(JCLink_t nLinkID, PARAM_REQ_sdk_alarm_heartbeat *req, PARAM_RESP_sdk_alarm_heartbeat *resp);
#  endif

//alarm_deployment
#  if 1

//--- alarm_deployment definition ----
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_alarm_deployment PARAM_REQ_sdk_alarm_deployment;
typedef PARAM_RESP_vms_alarm_deployment PARAM_RESP_sdk_alarm_deployment;
#    else

typedef struct{
	GBOOL enable;
	int timeRange_cnt;
	struct{
		char *startTime; //00:00:00
		char *endTime; //23:59:59
	} *timeRange;
} PARAM_REQ_sdk_alarm_deployment;

typedef struct{
	GBOOL enable;
	int timeRange_cnt;
	struct{
		char *startTime; //00:00:00
		char *endTime; //23:59:59
	} *timeRange;
} PARAM_RESP_sdk_alarm_deployment;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_alarm_deployment(JCLink_t nLinkID, PARAM_REQ_sdk_alarm_deployment *req, PARAM_RESP_sdk_alarm_deployment *resp);
#  endif

//alarm_deployment_query
#  if 1

//--- alarm_deployment_query definition ----
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_alarm_deployment_query PARAM_REQ_sdk_alarm_deployment_query;
typedef PARAM_RESP_vms_alarm_deployment_query PARAM_RESP_sdk_alarm_deployment_query;
#    else

typedef struct{
	int cid;
} PARAM_REQ_sdk_alarm_deployment_query;

typedef struct{
	int cid;
	GBOOL enable;
	int timeRange_cnt;
	struct{
		char *startTime; //00:00:00
		char *endTime; //23:59:59
	} *timeRange;
} PARAM_RESP_sdk_alarm_deployment_query;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_alarm_deployment_query(JCLink_t nLinkID, PARAM_REQ_sdk_alarm_deployment_query *req, PARAM_RESP_sdk_alarm_deployment_query *resp);
#  endif

//alarm_deployment_push
#  if 1

//--- alarm_deployment_push definition ----
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_alarm_deployment_push PARAM_REQ_sdk_alarm_deployment_push;
typedef PARAM_RESP_vms_alarm_deployment_push PARAM_RESP_sdk_alarm_deployment_push;
#    else

typedef struct{
	GBOOL enable;
	int timeRange_cnt;
	struct{
		char *startTime; //00:00:00
		char *endTime; //23:59:59
	} *timeRange;
} PARAM_REQ_sdk_alarm_deployment_push;

typedef struct{
	int idle;
} PARAM_RESP_sdk_alarm_deployment_push;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_alarm_deployment_push(JCLink_t nLinkID, PARAM_REQ_sdk_alarm_deployment_push *req, PARAM_RESP_sdk_alarm_deployment_push *resp);
#  endif

#endif


//json/audio.json
#if 1

//ai_get_param
#  if 1

//--- ai_get_param definition ----
/*
sampleRate : 8000,11025,16000,22050,24000,32000,44100,48000;
bitWidth : 8,16,32
*/
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_ai_get_param PARAM_REQ_sdk_ai_get_param;
typedef PARAM_RESP_vms_ai_get_param PARAM_RESP_sdk_ai_get_param;
#    else

typedef struct{
	int channelid;
} PARAM_REQ_sdk_ai_get_param;

typedef struct{
	int sampleRate;
	int bitWidth;
	char *encType; //pcm,g711a,g711u,g726_16k,g726_24k,g726_32k,g726_40k,aac,adpcm
} PARAM_RESP_sdk_ai_get_param;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_ai_get_param(JCLink_t nLinkID, PARAM_REQ_sdk_ai_get_param *req, PARAM_RESP_sdk_ai_get_param *resp);
#  endif

//ai_set_param
#  if 1

//--- ai_set_param definition ----
/*
sampleRate : 8000,11025,16000,22050,24000,32000,44100,48000;
bitWidth : 8,16,32
*/
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_ai_set_param PARAM_REQ_sdk_ai_set_param;
typedef PARAM_RESP_vms_ai_set_param PARAM_RESP_sdk_ai_set_param;
#    else

typedef struct{
	int channelid;
	struct{
		int sampleRate;
		int bitWidth;
		char *encType; //pcm,g711a,g711u,g726_16k,g726_24k,g726_32k,g726_40k,aac,adpcm
	} audioAttr;
} PARAM_REQ_sdk_ai_set_param;

typedef struct{
	int idle;
} PARAM_RESP_sdk_ai_set_param;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_ai_set_param(JCLink_t nLinkID, PARAM_REQ_sdk_ai_set_param *req, PARAM_RESP_sdk_ai_set_param *resp);
#  endif

//ao_get_param
#  if 1

//--- ao_get_param definition ----
/*
sampleRate : 8000,11025,16000,22050,24000,32000,44100,48000;
bitWidth : 8,16,32
*/
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_ao_get_param PARAM_REQ_sdk_ao_get_param;
typedef PARAM_RESP_vms_ao_get_param PARAM_RESP_sdk_ao_get_param;
#    else

typedef struct{
	int channelid;
} PARAM_REQ_sdk_ao_get_param;

typedef struct{
	int sampleRate;
	int bitWidth;
	char *encType; //pcm,g711a,g711u,g726_16k,g726_24k,g726_32k,g726_40k,aac,adpcm
} PARAM_RESP_sdk_ao_get_param;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_ao_get_param(JCLink_t nLinkID, PARAM_REQ_sdk_ao_get_param *req, PARAM_RESP_sdk_ao_get_param *resp);
#  endif

//ao_set_param
#  if 1

//--- ao_set_param definition ----
/*
sampleRate : 8000,11025,16000,22050,24000,32000,44100,48000;
bitWidth : 8,16,32
*/
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_ao_set_param PARAM_REQ_sdk_ao_set_param;
typedef PARAM_RESP_vms_ao_set_param PARAM_RESP_sdk_ao_set_param;
#    else

typedef struct{
	int channelid;
	struct{
		int sampleRate;
		int bitWidth;
		char *encType; //pcm,g711a,g711u,g726_16k,g726_24k,g726_32k,g726_40k,aac,adpcm
	} audioAttr;
} PARAM_REQ_sdk_ao_set_param;

typedef struct{
	int idle;
} PARAM_RESP_sdk_ao_set_param;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_ao_set_param(JCLink_t nLinkID, PARAM_REQ_sdk_ao_set_param *req, PARAM_RESP_sdk_ao_set_param *resp);
#  endif

#endif


//json/connect.json
#if 1

//connection_get_list
#  if 1

//--- connection_get_list definition ----
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_connection_get_list PARAM_REQ_sdk_connection_get_list;
typedef PARAM_RESP_vms_connection_get_list PARAM_RESP_sdk_connection_get_list;
#    else

typedef struct{
	char *conType; //all,jovision,rtsp,gb28181,psia,other
} PARAM_REQ_sdk_connection_get_list;

typedef struct{
	int connectionList_cnt;
	struct{
		char *conType; //jovision
		int key;
		char *addr; //192.168.7.160
		char *user; //admin
	} *connectionList;
} PARAM_RESP_sdk_connection_get_list;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_connection_get_list(JCLink_t nLinkID, PARAM_REQ_sdk_connection_get_list *req, PARAM_RESP_sdk_connection_get_list *resp);
#  endif

//connection_breakoff
#  if 1

//--- connection_breakoff definition ----
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_connection_breakoff PARAM_REQ_sdk_connection_breakoff;
typedef PARAM_RESP_vms_connection_breakoff PARAM_RESP_sdk_connection_breakoff;
#    else

typedef struct{
	int connectionList_cnt;
	struct{
		char *conType; //jovision
		int key;
	} *connectionList;
} PARAM_REQ_sdk_connection_breakoff;

typedef struct{
	int idle;
} PARAM_RESP_sdk_connection_breakoff;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_connection_breakoff(JCLink_t nLinkID, PARAM_REQ_sdk_connection_breakoff *req, PARAM_RESP_sdk_connection_breakoff *resp);
#  endif

#endif


//json/devinfo.json
#if 1

//dev_get_hwinfo
#  if 1

//--- dev_get_hwinfo definition ----
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_dev_get_hwinfo PARAM_REQ_sdk_dev_get_hwinfo;
typedef PARAM_RESP_vms_dev_get_hwinfo PARAM_RESP_sdk_dev_get_hwinfo;
#    else

typedef struct{
	int idle;
} PARAM_REQ_sdk_dev_get_hwinfo;

typedef struct{
	char *type; //IPC
	char *hardware; //V1.0
	char *sn; //112233
	char *firmware; //V1.0
	char *manufacture; //JOVISION
	char *model; //JVS-N71-HD
	GBOOL bPtzSupport;
	GBOOL bWifiSupport;
	int channelCnt;
	int streamCnt;
	char *ystID; //A402153844
} PARAM_RESP_sdk_dev_get_hwinfo;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_dev_get_hwinfo(JCLink_t nLinkID, PARAM_REQ_sdk_dev_get_hwinfo *req, PARAM_RESP_sdk_dev_get_hwinfo *resp);
#  endif

//dev_get_info
#  if 1

//--- dev_get_info definition ----
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_dev_get_info PARAM_REQ_sdk_dev_get_info;
typedef PARAM_RESP_vms_dev_get_info PARAM_RESP_sdk_dev_get_info;
#    else

typedef struct{
	int idle;
} PARAM_REQ_sdk_dev_get_info;

typedef struct{
	GBOOL bDiscoverable;
	char *hostname; //HD IPC
	char *name; //HD IPC
	char *rebootDay; //never,everyday,everysunday,everymonday,everytuesday,everywednesday,everythursday,everyfriday,everysaturday
	int rebootHour;
} PARAM_RESP_sdk_dev_get_info;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_dev_get_info(JCLink_t nLinkID, PARAM_REQ_sdk_dev_get_info *req, PARAM_RESP_sdk_dev_get_info *resp);
#  endif

//dev_set_info
#  if 1

//--- dev_set_info definition ----
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_dev_set_info PARAM_REQ_sdk_dev_set_info;
typedef PARAM_RESP_vms_dev_set_info PARAM_RESP_sdk_dev_set_info;
#    else

typedef struct{
	GBOOL bDiscoverable;
	char *hostname; //HD IPC
	char *name; //HD IPC
	char *rebootDay; //never,everyday,everysunday,everymonday,everytuesday,everywednesday,everythursday,everyfriday,everysaturday
	int rebootHour;
} PARAM_REQ_sdk_dev_set_info;

typedef struct{
	int idle;
} PARAM_RESP_sdk_dev_set_info;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_dev_set_info(JCLink_t nLinkID, PARAM_REQ_sdk_dev_set_info *req, PARAM_RESP_sdk_dev_set_info *resp);
#  endif

//dev_stime
#  if 1

//--- dev_stime definition ----
/*
Param tmsec means the seconds elapsed since 1970.
*/
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_dev_stime PARAM_REQ_sdk_dev_stime;
typedef PARAM_RESP_vms_dev_stime PARAM_RESP_sdk_dev_stime;
#    else

typedef struct{
	int tmsec;
	char *tz; //8.5
} PARAM_REQ_sdk_dev_stime;

typedef struct{
	int idle;
} PARAM_RESP_sdk_dev_stime;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_dev_stime(JCLink_t nLinkID, PARAM_REQ_sdk_dev_stime *req, PARAM_RESP_sdk_dev_stime *resp);
#  endif

//dev_gtime
#  if 1

//--- dev_gtime definition ----
/*
Param tmsec means the seconds elapsed since 1970.
*/
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_dev_gtime PARAM_REQ_sdk_dev_gtime;
typedef PARAM_RESP_vms_dev_gtime PARAM_RESP_sdk_dev_gtime;
#    else

typedef struct{
	int idle;
} PARAM_REQ_sdk_dev_gtime;

typedef struct{
	int tmsec;
	char *tz; //8.5
} PARAM_RESP_sdk_dev_gtime;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_dev_gtime(JCLink_t nLinkID, PARAM_REQ_sdk_dev_gtime *req, PARAM_RESP_sdk_dev_gtime *resp);
#  endif

//dev_ntp_set
#  if 1

//--- dev_ntp_set definition ----
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_dev_ntp_set PARAM_REQ_sdk_dev_ntp_set;
typedef PARAM_RESP_vms_dev_ntp_set PARAM_RESP_sdk_dev_ntp_set;
#    else

typedef struct{
	GBOOL bEnableNtp;
	int sntpInterval;
	int servers_cnt;
	char **servers; //ntp.fudan.edu.cn
} PARAM_REQ_sdk_dev_ntp_set;

typedef struct{
	int idle;
} PARAM_RESP_sdk_dev_ntp_set;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_dev_ntp_set(JCLink_t nLinkID, PARAM_REQ_sdk_dev_ntp_set *req, PARAM_RESP_sdk_dev_ntp_set *resp);
#  endif

//dev_ntp_get
#  if 1

//--- dev_ntp_get definition ----
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_dev_ntp_get PARAM_REQ_sdk_dev_ntp_get;
typedef PARAM_RESP_vms_dev_ntp_get PARAM_RESP_sdk_dev_ntp_get;
#    else

typedef struct{
	int idle;
} PARAM_REQ_sdk_dev_ntp_get;

typedef struct{
	GBOOL bEnableNtp;
	int sntpInterval;
	int servers_cnt;
	char **servers; //ntp.fudan.edu.cn
} PARAM_RESP_sdk_dev_ntp_get;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_dev_ntp_get(JCLink_t nLinkID, PARAM_REQ_sdk_dev_ntp_get *req, PARAM_RESP_sdk_dev_ntp_get *resp);
#  endif

//dev_reboot
#  if 1

//--- dev_reboot definition ----
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_dev_reboot PARAM_REQ_sdk_dev_reboot;
typedef PARAM_RESP_vms_dev_reboot PARAM_RESP_sdk_dev_reboot;
#    else

typedef struct{
	int delaymSec;
} PARAM_REQ_sdk_dev_reboot;

typedef struct{
	int idle;
} PARAM_RESP_sdk_dev_reboot;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_dev_reboot(JCLink_t nLinkID, PARAM_REQ_sdk_dev_reboot *req, PARAM_RESP_sdk_dev_reboot *resp);
#  endif

//dev_factory_default
#  if 1

//--- dev_factory_default definition ----
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_dev_factory_default PARAM_REQ_sdk_dev_factory_default;
typedef PARAM_RESP_vms_dev_factory_default PARAM_RESP_sdk_dev_factory_default;
#    else

typedef struct{
	GBOOL bHard;
} PARAM_REQ_sdk_dev_factory_default;

typedef struct{
	int idle;
} PARAM_RESP_sdk_dev_factory_default;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_dev_factory_default(JCLink_t nLinkID, PARAM_REQ_sdk_dev_factory_default *req, PARAM_RESP_sdk_dev_factory_default *resp);
#  endif

#endif


//json/ifconfig.json
#if 1

//ifconfig_get_inet
#  if 1

//--- ifconfig_get_inet definition ----
/*
The value of quality ranges from 0 to 100.
*/
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_ifconfig_get_inet PARAM_REQ_sdk_ifconfig_get_inet;
typedef PARAM_RESP_vms_ifconfig_get_inet PARAM_RESP_sdk_ifconfig_get_inet;
#    else

typedef struct{
	int idle;
} PARAM_REQ_sdk_ifconfig_get_inet;

typedef struct{
	char *iface; //eth,ppp,wifi
	struct{
		char *name; //eth0
		GBOOL bDHCP;
		char *addr; //192.168.7.160
		char *mask; //255.255.255.0
		char *gateway; //192.168.7.1
		char *mac; //E0:62:90:33:58:C7
		char *dns; //202.102.128.68
	} eth;
	struct{
		char *name; //adsl
		char *username; //qlc
		char *passwd; //123456
	} ppp;
	struct{
		char *name; //hehe
		int quality;
		int keystat;
		char *iestat; //wpa,wpa2,wep,plain
		GBOOL bDHCP;
		char *addr; //192.168.7.160
		char *mask; //255.255.255.0
		char *gateway; //192.168.7.1
		char *mac; //E0:62:90:33:58:C7
		char *dns; //202.102.128.68
	} wifi;
} PARAM_RESP_sdk_ifconfig_get_inet;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_ifconfig_get_inet(JCLink_t nLinkID, PARAM_REQ_sdk_ifconfig_get_inet *req, PARAM_RESP_sdk_ifconfig_get_inet *resp);
#  endif

//ifconfig_eth_set
#  if 1

//--- ifconfig_eth_set definition ----
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_ifconfig_eth_set PARAM_REQ_sdk_ifconfig_eth_set;
typedef PARAM_RESP_vms_ifconfig_eth_set PARAM_RESP_sdk_ifconfig_eth_set;
#    else

typedef struct{
	char *name; //eth0
	GBOOL bDHCP;
	char *addr; //192.168.7.160
	char *mask; //255.255.255.0
	char *gateway; //192.168.7.1
	char *dns; //202.102.128.68
} PARAM_REQ_sdk_ifconfig_eth_set;

typedef struct{
	int idle;
} PARAM_RESP_sdk_ifconfig_eth_set;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_ifconfig_eth_set(JCLink_t nLinkID, PARAM_REQ_sdk_ifconfig_eth_set *req, PARAM_RESP_sdk_ifconfig_eth_set *resp);
#  endif

//ifconfig_ppp_set
#  if 1

//--- ifconfig_ppp_set definition ----
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_ifconfig_ppp_set PARAM_REQ_sdk_ifconfig_ppp_set;
typedef PARAM_RESP_vms_ifconfig_ppp_set PARAM_RESP_sdk_ifconfig_ppp_set;
#    else

typedef struct{
	char *name; //adsl
	char *username; //qlc
	char *passwd; //123456
} PARAM_REQ_sdk_ifconfig_ppp_set;

typedef struct{
	int idle;
} PARAM_RESP_sdk_ifconfig_ppp_set;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_ifconfig_ppp_set(JCLink_t nLinkID, PARAM_REQ_sdk_ifconfig_ppp_set *req, PARAM_RESP_sdk_ifconfig_ppp_set *resp);
#  endif

//ifconfig_wifi_connect
#  if 1

//--- ifconfig_wifi_connect definition ----
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_ifconfig_wifi_connect PARAM_REQ_sdk_ifconfig_wifi_connect;
typedef PARAM_RESP_vms_ifconfig_wifi_connect PARAM_RESP_sdk_ifconfig_wifi_connect;
#    else

typedef struct{
	char *name; //hehe
	char *passwd; //hehe12345
} PARAM_REQ_sdk_ifconfig_wifi_connect;

typedef struct{
	int idle;
} PARAM_RESP_sdk_ifconfig_wifi_connect;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_ifconfig_wifi_connect(JCLink_t nLinkID, PARAM_REQ_sdk_ifconfig_wifi_connect *req, PARAM_RESP_sdk_ifconfig_wifi_connect *resp);
#  endif

//ifconfig_wifi_list_ap
#  if 1

//--- ifconfig_wifi_list_ap definition ----
/*
The value of quality ranges from 0 to 100.
*/
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_ifconfig_wifi_list_ap PARAM_REQ_sdk_ifconfig_wifi_list_ap;
typedef PARAM_RESP_vms_ifconfig_wifi_list_ap PARAM_RESP_sdk_ifconfig_wifi_list_ap;
#    else

typedef struct{
	GBOOL bResearch;
} PARAM_REQ_sdk_ifconfig_wifi_list_ap;

typedef struct{
	int apList_cnt;
	struct{
		char *name; //hehe
		char *passwd; //hehe12345
		int quality;
		int keystat;
		char *iestat; //wpa,wpa2,wep,plain
	} *apList;
} PARAM_RESP_sdk_ifconfig_wifi_list_ap;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_ifconfig_wifi_list_ap(JCLink_t nLinkID, PARAM_REQ_sdk_ifconfig_wifi_list_ap *req, PARAM_RESP_sdk_ifconfig_wifi_list_ap *resp);
#  endif

//ifconfig_server_set
#  if 1

//--- ifconfig_server_set definition ----
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_ifconfig_server_set PARAM_REQ_sdk_ifconfig_server_set;
typedef PARAM_RESP_vms_ifconfig_server_set PARAM_RESP_sdk_ifconfig_server_set;
#    else

typedef struct{
	struct{
		char *ipaddr; //192.168.7.160
		int port;
	} vmsServer;
	struct{
		GBOOL bEnable;
		int channel;
		char *serverURL; //rtmp://192.168.100.10:1935/a381_1
	} rtmpServer;
} PARAM_REQ_sdk_ifconfig_server_set;

typedef struct{
	int idle;
} PARAM_RESP_sdk_ifconfig_server_set;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_ifconfig_server_set(JCLink_t nLinkID, PARAM_REQ_sdk_ifconfig_server_set *req, PARAM_RESP_sdk_ifconfig_server_set *resp);
#  endif

//ifconfig_server_get
#  if 1

//--- ifconfig_server_get definition ----
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_ifconfig_server_get PARAM_REQ_sdk_ifconfig_server_get;
typedef PARAM_RESP_vms_ifconfig_server_get PARAM_RESP_sdk_ifconfig_server_get;
#    else

typedef struct{
	int idle;
} PARAM_REQ_sdk_ifconfig_server_get;

typedef struct{
	struct{
		char *ipaddr; //192.168.7.160
		int port;
	} vmsServer;
	struct{
		GBOOL bEnable;
		int channel;
		char *serverURL; //rtmp://192.168.100.10:1935/a381_1
	} rtmpServer;
} PARAM_RESP_sdk_ifconfig_server_get;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_ifconfig_server_get(JCLink_t nLinkID, PARAM_REQ_sdk_ifconfig_server_get *req, PARAM_RESP_sdk_ifconfig_server_get *resp);
#  endif

#endif


//json/image.json
#if 1

//image_get_param
#  if 1

//--- image_get_param definition ----
/*
The value of contrast, brightness, saturation and sharpen ranges from 0 to 255.
*/
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_image_get_param PARAM_REQ_sdk_image_get_param;
typedef PARAM_RESP_vms_image_get_param PARAM_RESP_sdk_image_get_param;
#    else

typedef struct{
	int idle;
} PARAM_REQ_sdk_image_get_param;

typedef struct{
	int contrast;
	int brightness;
	int saturation;
	int sharpen;
	int exposureMax;
	int exposureMin;
	char *scene; //indoor,outdoor,default,soft
	char *daynightMode; //auto,alwaysDay,alwaysNight,timer
	struct{
		int hour;
		int minute;
	} dayStart;
	struct{
		int hour;
		int minute;
	} dayEnd;
	GBOOL bEnableAWB;
	GBOOL bEnableMI;
	GBOOL bEnableST;
	GBOOL bEnableNoC;
	GBOOL bEnableWDynamic;
	GBOOL bAutoLowFrameEn;
	GBOOL bNightOptimization;
} PARAM_RESP_sdk_image_get_param;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_image_get_param(JCLink_t nLinkID, PARAM_REQ_sdk_image_get_param *req, PARAM_RESP_sdk_image_get_param *resp);
#  endif

//image_set_param
#  if 1

//--- image_set_param definition ----
/*
The value of contrast, brightness, saturation and sharpen ranges from 0 to 255.
*/
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_image_set_param PARAM_REQ_sdk_image_set_param;
typedef PARAM_RESP_vms_image_set_param PARAM_RESP_sdk_image_set_param;
#    else

typedef struct{
	int contrast;
	int brightness;
	int saturation;
	int sharpen;
	int exposureMax;
	int exposureMin;
	char *scene; //indoor,outdoor,default,soft
	char *daynightMode; //auto,alwaysDay,alwaysNight,timer
	struct{
		int hour;
		int minute;
	} dayStart;
	struct{
		int hour;
		int minute;
	} dayEnd;
	GBOOL bEnableAWB;
	GBOOL bEnableMI;
	GBOOL bEnableST;
	GBOOL bEnableNoC;
	GBOOL bEnableWDynamic;
	GBOOL bAutoLowFrameEn;
	GBOOL bNightOptimization;
} PARAM_REQ_sdk_image_set_param;

typedef struct{
	int idle;
} PARAM_RESP_sdk_image_set_param;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_image_set_param(JCLink_t nLinkID, PARAM_REQ_sdk_image_set_param *req, PARAM_RESP_sdk_image_set_param *resp);
#  endif

#endif


//json/log.json
#if 1

//log_get
#  if 1

//--- log_get definition ----
/*
type: enum{SYSTEM,CONFIG,DATA_MANGE,ALARM,RECORD,USER,FILE_OPER,ALL}.
nSub: affiliated log counts
*/
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_log_get PARAM_REQ_sdk_log_get;
typedef PARAM_RESP_vms_log_get PARAM_RESP_sdk_log_get;
#    else

typedef struct{
	char *date; //2014-11-18
	char *type; //SYSTEM
} PARAM_REQ_sdk_log_get;

typedef struct{
	int log_items_cnt;
	struct{
		char *time; //2014-11-18 08:43:57
		char *strlog; //the happened events
		GBOOL bNetuser;
		GBOOL bmain;
		int nSub;
		char *type; //SYSTEM
		char *username; //system
	} *log_items;
} PARAM_RESP_sdk_log_get;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_log_get(JCLink_t nLinkID, PARAM_REQ_sdk_log_get *req, PARAM_RESP_sdk_log_get *resp);
#  endif

//log_clear
#  if 1

//--- log_clear definition ----
/*
type: enum{SYSTEM,CONFIG,DATA_MANGE,ALARM,RECORD,USER,FILE_OPER,ALL}.
*/
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_log_clear PARAM_REQ_sdk_log_clear;
typedef PARAM_RESP_vms_log_clear PARAM_RESP_sdk_log_clear;
#    else

typedef struct{
	int idle;
} PARAM_REQ_sdk_log_clear;

typedef struct{
	int idle;
} PARAM_RESP_sdk_log_clear;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_log_clear(JCLink_t nLinkID, PARAM_REQ_sdk_log_clear *req, PARAM_RESP_sdk_log_clear *resp);
#  endif

#endif


//json/matrix.json
#if 1

//matrix_set_work_mode
#  if 1

//--- matrix_set_work_mode definition ----
/*
设置级联工作模式，machineDevID是设备物理ID的基数，默认0。DevMode是主设备工作模式:mix(转发数据+解码)/data(只转发数据)，默认mix
*/
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_matrix_set_work_mode PARAM_REQ_sdk_matrix_set_work_mode;
typedef PARAM_RESP_vms_matrix_set_work_mode PARAM_RESP_sdk_matrix_set_work_mode;
#    else

typedef struct{
	int machineDevID;
	char *workMode; //mix,data
} PARAM_REQ_sdk_matrix_set_work_mode;

typedef struct{
	int idle;
} PARAM_RESP_sdk_matrix_set_work_mode;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_matrix_set_work_mode(JCLink_t nLinkID, PARAM_REQ_sdk_matrix_set_work_mode *req, PARAM_RESP_sdk_matrix_set_work_mode *resp);
#  endif

//matrix_update
#  if 1

//--- matrix_update definition ----
/*
url对usb方式无效，格式: http://www.jovetech.com ftp://192.168.8.118
*/
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_matrix_update PARAM_REQ_sdk_matrix_update;
typedef PARAM_RESP_vms_matrix_update PARAM_RESP_sdk_matrix_update;
#    else

typedef struct{
	char *method; //usb,ftp,http
	char *url; //ftp://192.168.8.118/
} PARAM_REQ_sdk_matrix_update;

typedef struct{
	int idle;
} PARAM_RESP_sdk_matrix_update;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_matrix_update(JCLink_t nLinkID, PARAM_REQ_sdk_matrix_update *req, PARAM_RESP_sdk_matrix_update *resp);
#  endif

//matrix_get_matrix
#  if 1

//--- matrix_get_matrix definition ----
/*
获取矩阵排列方式
*/
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_matrix_get_matrix PARAM_REQ_sdk_matrix_get_matrix;
typedef PARAM_RESP_vms_matrix_get_matrix PARAM_RESP_sdk_matrix_get_matrix;
#    else

typedef struct{
	int idle;
} PARAM_REQ_sdk_matrix_get_matrix;

typedef struct{
	int row;
	int column;
} PARAM_RESP_sdk_matrix_get_matrix;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_matrix_get_matrix(JCLink_t nLinkID, PARAM_REQ_sdk_matrix_get_matrix *req, PARAM_RESP_sdk_matrix_get_matrix *resp);
#  endif

//matrix_set_matrix
#  if 1

//--- matrix_set_matrix definition ----
/*
设置矩阵排列方式
*/
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_matrix_set_matrix PARAM_REQ_sdk_matrix_set_matrix;
typedef PARAM_RESP_vms_matrix_set_matrix PARAM_RESP_sdk_matrix_set_matrix;
#    else

typedef struct{
	int row;
	int column;
} PARAM_REQ_sdk_matrix_set_matrix;

typedef struct{
	int idle;
} PARAM_RESP_sdk_matrix_set_matrix;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_matrix_set_matrix(JCLink_t nLinkID, PARAM_REQ_sdk_matrix_set_matrix *req, PARAM_RESP_sdk_matrix_set_matrix *resp);
#  endif

//matrix_get_physical_screen_info
#  if 1

//--- matrix_get_physical_screen_info definition ----
/*
获取物理屏信息。bSupportMerge是否支持融合，bSupportCellOverlap是否支持矩阵单元叠加
*/
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_matrix_get_physical_screen_info PARAM_REQ_sdk_matrix_get_physical_screen_info;
typedef PARAM_RESP_vms_matrix_get_physical_screen_info PARAM_RESP_sdk_matrix_get_physical_screen_info;
#    else

typedef struct{
	int idle;
} PARAM_REQ_sdk_matrix_get_physical_screen_info;

typedef struct{
	struct{
		int bSupportMerge;
		int bSupportCellOverlap;
	} abality;
	struct{
		int width;
		int height;
	} resolution;
	int resolutionList_cnt;
	struct{
		int width;
		int height;
	} *resolutionList;
	int cntScreen;
} PARAM_RESP_sdk_matrix_get_physical_screen_info;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_matrix_get_physical_screen_info(JCLink_t nLinkID, PARAM_REQ_sdk_matrix_get_physical_screen_info *req, PARAM_RESP_sdk_matrix_get_physical_screen_info *resp);
#  endif

//matrix_get_image_parm
#  if 1

//--- matrix_get_image_parm definition ----
/*
获取逻辑屏图像调节参数
*/
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_matrix_get_image_parm PARAM_REQ_sdk_matrix_get_image_parm;
typedef PARAM_RESP_vms_matrix_get_image_parm PARAM_RESP_sdk_matrix_get_image_parm;
#    else

typedef struct{
	int logicID;
} PARAM_REQ_sdk_matrix_get_image_parm;

typedef struct{
	int nBright;
	int nContrast;
	int nSaturation;
} PARAM_RESP_sdk_matrix_get_image_parm;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_matrix_get_image_parm(JCLink_t nLinkID, PARAM_REQ_sdk_matrix_get_image_parm *req, PARAM_RESP_sdk_matrix_get_image_parm *resp);
#  endif

//matrix_set_image_parm
#  if 1

//--- matrix_set_image_parm definition ----
/*
设置逻辑屏图像调节参数
*/
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_matrix_set_image_parm PARAM_REQ_sdk_matrix_set_image_parm;
typedef PARAM_RESP_vms_matrix_set_image_parm PARAM_RESP_sdk_matrix_set_image_parm;
#    else

typedef struct{
	int logicID;
	int nBright;
	int nContrast;
	int nSaturation;
} PARAM_REQ_sdk_matrix_set_image_parm;

typedef struct{
	int idle;
} PARAM_RESP_sdk_matrix_set_image_parm;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_matrix_set_image_parm(JCLink_t nLinkID, PARAM_REQ_sdk_matrix_set_image_parm *req, PARAM_RESP_sdk_matrix_set_image_parm *resp);
#  endif

//matrix_get_resolution
#  if 1

//--- matrix_get_resolution definition ----
/*
获取物理屏的分辨率
*/
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_matrix_get_resolution PARAM_REQ_sdk_matrix_get_resolution;
typedef PARAM_RESP_vms_matrix_get_resolution PARAM_RESP_sdk_matrix_get_resolution;
#    else

typedef struct{
	int idle;
} PARAM_REQ_sdk_matrix_get_resolution;

typedef struct{
	struct{
		int width;
		int height;
	} resolution;
} PARAM_RESP_sdk_matrix_get_resolution;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_matrix_get_resolution(JCLink_t nLinkID, PARAM_REQ_sdk_matrix_get_resolution *req, PARAM_RESP_sdk_matrix_get_resolution *resp);
#  endif

//matrix_set_resolution
#  if 1

//--- matrix_set_resolution definition ----
/*
设置物理屏的分辨率
*/
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_matrix_set_resolution PARAM_REQ_sdk_matrix_set_resolution;
typedef PARAM_RESP_vms_matrix_set_resolution PARAM_RESP_sdk_matrix_set_resolution;
#    else

typedef struct{
	struct{
		int width;
		int height;
	} resolution;
} PARAM_REQ_sdk_matrix_set_resolution;

typedef struct{
	int idle;
} PARAM_RESP_sdk_matrix_set_resolution;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_matrix_set_resolution(JCLink_t nLinkID, PARAM_REQ_sdk_matrix_set_resolution *req, PARAM_RESP_sdk_matrix_set_resolution *resp);
#  endif

//matrix_display_physical_screen_ID
#  if 1

//--- matrix_display_physical_screen_ID definition ----
/*
显示物理屏ID，帮助用户做逻辑屏和物理屏的映射
*/
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_matrix_display_physical_screen_ID PARAM_REQ_sdk_matrix_display_physical_screen_ID;
typedef PARAM_RESP_vms_matrix_display_physical_screen_ID PARAM_RESP_sdk_matrix_display_physical_screen_ID;
#    else

typedef struct{
	int bDisplay;
} PARAM_REQ_sdk_matrix_display_physical_screen_ID;

typedef struct{
	int idle;
} PARAM_RESP_sdk_matrix_display_physical_screen_ID;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_matrix_display_physical_screen_ID(JCLink_t nLinkID, PARAM_REQ_sdk_matrix_display_physical_screen_ID *req, PARAM_RESP_sdk_matrix_display_physical_screen_ID *resp);
#  endif

//matrix_get_logic_screen_map
#  if 1

//--- matrix_get_logic_screen_map definition ----
/*
获取逻辑屏到物理屏的映射
*/
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_matrix_get_logic_screen_map PARAM_REQ_sdk_matrix_get_logic_screen_map;
typedef PARAM_RESP_vms_matrix_get_logic_screen_map PARAM_RESP_sdk_matrix_get_logic_screen_map;
#    else

typedef struct{
	int idle;
} PARAM_REQ_sdk_matrix_get_logic_screen_map;

typedef struct{
	int map_cnt;
	int *map;
} PARAM_RESP_sdk_matrix_get_logic_screen_map;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_matrix_get_logic_screen_map(JCLink_t nLinkID, PARAM_REQ_sdk_matrix_get_logic_screen_map *req, PARAM_RESP_sdk_matrix_get_logic_screen_map *resp);
#  endif

//matrix_set_logic_screen_map
#  if 1

//--- matrix_set_logic_screen_map definition ----
/*
设置逻辑屏到物理屏的映射
*/
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_matrix_set_logic_screen_map PARAM_REQ_sdk_matrix_set_logic_screen_map;
typedef PARAM_RESP_vms_matrix_set_logic_screen_map PARAM_RESP_sdk_matrix_set_logic_screen_map;
#    else

typedef struct{
	int map_cnt;
	int *map;
} PARAM_REQ_sdk_matrix_set_logic_screen_map;

typedef struct{
	int idle;
} PARAM_RESP_sdk_matrix_set_logic_screen_map;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_matrix_set_logic_screen_map(JCLink_t nLinkID, PARAM_REQ_sdk_matrix_set_logic_screen_map *req, PARAM_RESP_sdk_matrix_set_logic_screen_map *resp);
#  endif

//matrix_get_cell
#  if 1

//--- matrix_get_cell definition ----
/*
矩阵单元(cell): 可以是一块逻辑屏，也可以是多个逻辑屏融合而成。坐标单位：单块物理屏的宽和高是1000000
*/
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_matrix_get_cell PARAM_REQ_sdk_matrix_get_cell;
typedef PARAM_RESP_vms_matrix_get_cell PARAM_RESP_sdk_matrix_get_cell;
#    else

typedef struct{
	int idle;
} PARAM_REQ_sdk_matrix_get_cell;

typedef struct{
	int cell_cnt;
	struct{
		int cellID;
		int x;
		int y;
		int w;
		int h;
		int maxResource;
		int modeList_cnt;
		int *modeList;
	} *cell;
} PARAM_RESP_sdk_matrix_get_cell;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_matrix_get_cell(JCLink_t nLinkID, PARAM_REQ_sdk_matrix_get_cell *req, PARAM_RESP_sdk_matrix_get_cell *resp);
#  endif

//matrix_set_cell
#  if 1

//--- matrix_set_cell definition ----
/*
设置矩阵单元，原有的单元会被删除。矩阵单元包含多块逻辑屏时就是融合。坐标单位：单块物理屏的宽和高是1000000
*/
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_matrix_set_cell PARAM_REQ_sdk_matrix_set_cell;
typedef PARAM_RESP_vms_matrix_set_cell PARAM_RESP_sdk_matrix_set_cell;
#    else

typedef struct{
	int cell_cnt;
	struct{
		int cellID;
		int x;
		int y;
		int w;
		int h;
	} *cell;
} PARAM_REQ_sdk_matrix_set_cell;

typedef struct{
	int idle;
} PARAM_RESP_sdk_matrix_set_cell;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_matrix_set_cell(JCLink_t nLinkID, PARAM_REQ_sdk_matrix_set_cell *req, PARAM_RESP_sdk_matrix_set_cell *resp);
#  endif

//matrix_modify_cell
#  if 1

//--- matrix_modify_cell definition ----
/*
修改矩阵单元。矩阵单元包含多块逻辑屏时就是融合。坐标单位：单块物理屏的宽和高是1000000
*/
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_matrix_modify_cell PARAM_REQ_sdk_matrix_modify_cell;
typedef PARAM_RESP_vms_matrix_modify_cell PARAM_RESP_sdk_matrix_modify_cell;
#    else

typedef struct{
	int cellID;
	int x;
	int y;
	int w;
	int h;
} PARAM_REQ_sdk_matrix_modify_cell;

typedef struct{
	int idle;
} PARAM_RESP_sdk_matrix_modify_cell;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_matrix_modify_cell(JCLink_t nLinkID, PARAM_REQ_sdk_matrix_modify_cell *req, PARAM_RESP_sdk_matrix_modify_cell *resp);
#  endif

//matrix_add_cell
#  if 1

//--- matrix_add_cell definition ----
/*
添加矩阵单元。矩阵单元包含多块逻辑屏时就是融合。坐标单位：单块物理屏的宽和高是1000000
*/
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_matrix_add_cell PARAM_REQ_sdk_matrix_add_cell;
typedef PARAM_RESP_vms_matrix_add_cell PARAM_RESP_sdk_matrix_add_cell;
#    else

typedef struct{
	int cellID;
	int x;
	int y;
	int w;
	int h;
} PARAM_REQ_sdk_matrix_add_cell;

typedef struct{
	int idle;
} PARAM_RESP_sdk_matrix_add_cell;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_matrix_add_cell(JCLink_t nLinkID, PARAM_REQ_sdk_matrix_add_cell *req, PARAM_RESP_sdk_matrix_add_cell *resp);
#  endif

//matrix_del_cell
#  if 1

//--- matrix_del_cell definition ----
/*
删除矩阵单元
*/
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_matrix_del_cell PARAM_REQ_sdk_matrix_del_cell;
typedef PARAM_RESP_vms_matrix_del_cell PARAM_RESP_sdk_matrix_del_cell;
#    else

typedef struct{
	int cellID;
} PARAM_REQ_sdk_matrix_del_cell;

typedef struct{
	int idle;
} PARAM_RESP_sdk_matrix_del_cell;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_matrix_del_cell(JCLink_t nLinkID, PARAM_REQ_sdk_matrix_del_cell *req, PARAM_RESP_sdk_matrix_del_cell *resp);
#  endif

//matrix_set_cell_video
#  if 1

//--- matrix_set_cell_video definition ----
/*
设置矩阵单元的视频源，原有的视频源会被删除
*/
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_matrix_set_cell_video PARAM_REQ_sdk_matrix_set_cell_video;
typedef PARAM_RESP_vms_matrix_set_cell_video PARAM_RESP_sdk_matrix_set_cell_video;
#    else

typedef struct{
	int cellID;
	int spiltnum;
	int resource_cnt;
	struct{
		int indexResource;
		char *cloudnum; //A361
		char *name; //演示点1
		char *ip; //192.168.6.141
		int port;
		int chnindex;
		char *netuser; //abc
		char *netpwd; //123
		char *type; //yst,onvif
		char *serviceAddr; //
	} *resource;
} PARAM_REQ_sdk_matrix_set_cell_video;

typedef struct{
	int idle;
} PARAM_RESP_sdk_matrix_set_cell_video;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_matrix_set_cell_video(JCLink_t nLinkID, PARAM_REQ_sdk_matrix_set_cell_video *req, PARAM_RESP_sdk_matrix_set_cell_video *resp);
#  endif

//matrix_modify_cell_video
#  if 1

//--- matrix_modify_cell_video definition ----
/*
修改矩阵单元的视频源
*/
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_matrix_modify_cell_video PARAM_REQ_sdk_matrix_modify_cell_video;
typedef PARAM_RESP_vms_matrix_modify_cell_video PARAM_RESP_sdk_matrix_modify_cell_video;
#    else

typedef struct{
	int cellID;
	int indexResource;
	struct{
		char *cloudnum; //A361
		char *name; //演示点1
		char *ip; //192.168.6.141
		int port;
		int chnindex;
		char *netuser; //abc
		char *netpwd; //123
		char *type; //yst,onvif
		char *serviceAddr; //
	} resource;
} PARAM_REQ_sdk_matrix_modify_cell_video;

typedef struct{
	int idle;
} PARAM_RESP_sdk_matrix_modify_cell_video;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_matrix_modify_cell_video(JCLink_t nLinkID, PARAM_REQ_sdk_matrix_modify_cell_video *req, PARAM_RESP_sdk_matrix_modify_cell_video *resp);
#  endif

//matrix_add_cell_video
#  if 1

//--- matrix_add_cell_video definition ----
/*
添加矩阵单元的视频源
*/
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_matrix_add_cell_video PARAM_REQ_sdk_matrix_add_cell_video;
typedef PARAM_RESP_vms_matrix_add_cell_video PARAM_RESP_sdk_matrix_add_cell_video;
#    else

typedef struct{
	int cellID;
	int indexResource;
	struct{
		char *cloudnum; //A361
		char *name; //演示点1
		char *ip; //192.168.6.141
		int port;
		int chnindex;
		char *netuser; //abc
		char *netpwd; //123
		char *type; //yst,onvif
		char *serviceAddr; //
	} resource;
} PARAM_REQ_sdk_matrix_add_cell_video;

typedef struct{
	int idle;
} PARAM_RESP_sdk_matrix_add_cell_video;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_matrix_add_cell_video(JCLink_t nLinkID, PARAM_REQ_sdk_matrix_add_cell_video *req, PARAM_RESP_sdk_matrix_add_cell_video *resp);
#  endif

//matrix_del_cell_video
#  if 1

//--- matrix_del_cell_video definition ----
/*
删除矩阵单元的视频源
*/
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_matrix_del_cell_video PARAM_REQ_sdk_matrix_del_cell_video;
typedef PARAM_RESP_vms_matrix_del_cell_video PARAM_RESP_sdk_matrix_del_cell_video;
#    else

typedef struct{
	int cellID;
	int indexResource;
} PARAM_REQ_sdk_matrix_del_cell_video;

typedef struct{
	int idle;
} PARAM_RESP_sdk_matrix_del_cell_video;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_matrix_del_cell_video(JCLink_t nLinkID, PARAM_REQ_sdk_matrix_del_cell_video *req, PARAM_RESP_sdk_matrix_del_cell_video *resp);
#  endif

//matrix_get_cell_video
#  if 1

//--- matrix_get_cell_video definition ----
/*
获取矩阵单元的视频源
*/
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_matrix_get_cell_video PARAM_REQ_sdk_matrix_get_cell_video;
typedef PARAM_RESP_vms_matrix_get_cell_video PARAM_RESP_sdk_matrix_get_cell_video;
#    else

typedef struct{
	int cellID;
} PARAM_REQ_sdk_matrix_get_cell_video;

typedef struct{
	int spiltnum;
	int resource_cnt;
	struct{
		int indexResource;
		char *cloudnum; //A361
		char *name; //演示点1
		char *ip; //
		int port;
		int chnindex;
		char *netuser; //abc
		char *netpwd; //123
		char *type; //yst,onvif
		char *serviceAddr; //
		char *status; //no video,disconnect,connecting,connected,password error,connect timeout,server stop,connect break,decoder failed,decoder over range,over link count,IP conflict
	} *resource;
} PARAM_RESP_sdk_matrix_get_cell_video;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_matrix_get_cell_video(JCLink_t nLinkID, PARAM_REQ_sdk_matrix_get_cell_video *req, PARAM_RESP_sdk_matrix_get_cell_video *resp);
#  endif

//matrix_set_cell_video_pos
#  if 1

//--- matrix_set_cell_video_pos definition ----
/*
reset the video position
*/
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_matrix_set_cell_video_pos PARAM_REQ_sdk_matrix_set_cell_video_pos;
typedef PARAM_RESP_vms_matrix_set_cell_video_pos PARAM_RESP_sdk_matrix_set_cell_video_pos;
#    else

typedef struct{
	int newPosResource_cnt;
	int *newPosResource;
} PARAM_REQ_sdk_matrix_set_cell_video_pos;

typedef struct{
	int idle;
} PARAM_RESP_sdk_matrix_set_cell_video_pos;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_matrix_set_cell_video_pos(JCLink_t nLinkID, PARAM_REQ_sdk_matrix_set_cell_video_pos *req, PARAM_RESP_sdk_matrix_set_cell_video_pos *resp);
#  endif

//matrix_set_cell_cycle
#  if 1

//--- matrix_set_cell_cycle definition ----
/*
设置矩阵单元的轮显视频源，indexResource 指参与轮显的视频源，如果为空，则在现有的视频源中轮显
*/
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_matrix_set_cell_cycle PARAM_REQ_sdk_matrix_set_cell_cycle;
typedef PARAM_RESP_vms_matrix_set_cell_cycle PARAM_RESP_sdk_matrix_set_cell_cycle;
#    else

typedef struct{
	int cellID;
	int elapse;
	char *state; //start,pause,stop
	int indexResource_cnt;
	int *indexResource;
} PARAM_REQ_sdk_matrix_set_cell_cycle;

typedef struct{
	int idle;
} PARAM_RESP_sdk_matrix_set_cell_cycle;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_matrix_set_cell_cycle(JCLink_t nLinkID, PARAM_REQ_sdk_matrix_set_cell_cycle *req, PARAM_RESP_sdk_matrix_set_cell_cycle *resp);
#  endif

//matrix_get_cell_cycle
#  if 1

//--- matrix_get_cell_cycle definition ----
/*
获取矩阵单元的轮显视频源
*/
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_matrix_get_cell_cycle PARAM_REQ_sdk_matrix_get_cell_cycle;
typedef PARAM_RESP_vms_matrix_get_cell_cycle PARAM_RESP_sdk_matrix_get_cell_cycle;
#    else

typedef struct{
	int cellID;
} PARAM_REQ_sdk_matrix_get_cell_cycle;

typedef struct{
	int elapse;
	char *state; //start,pause,stop
	int indexResource_cnt;
	int *indexResource;
} PARAM_RESP_sdk_matrix_get_cell_cycle;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_matrix_get_cell_cycle(JCLink_t nLinkID, PARAM_REQ_sdk_matrix_get_cell_cycle *req, PARAM_RESP_sdk_matrix_get_cell_cycle *resp);
#  endif

//matrix_set_cell_cycle_state
#  if 1

//--- matrix_set_cell_cycle_state definition ----
/*
开始/暂停/停止轮显
*/
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_matrix_set_cell_cycle_state PARAM_REQ_sdk_matrix_set_cell_cycle_state;
typedef PARAM_RESP_vms_matrix_set_cell_cycle_state PARAM_RESP_sdk_matrix_set_cell_cycle_state;
#    else

typedef struct{
	int cellID;
	char *state; //start,pause,stop
} PARAM_REQ_sdk_matrix_set_cell_cycle_state;

typedef struct{
	int idle;
} PARAM_RESP_sdk_matrix_set_cell_cycle_state;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_matrix_set_cell_cycle_state(JCLink_t nLinkID, PARAM_REQ_sdk_matrix_set_cell_cycle_state *req, PARAM_RESP_sdk_matrix_set_cell_cycle_state *resp);
#  endif

//matrix_set_cell_single
#  if 1

//--- matrix_set_cell_single definition ----
/*
在多画面显示时，临时放大某一画面或者恢复（实现双击放大、缩小功能）
*/
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_matrix_set_cell_single PARAM_REQ_sdk_matrix_set_cell_single;
typedef PARAM_RESP_vms_matrix_set_cell_single PARAM_RESP_sdk_matrix_set_cell_single;
#    else

typedef struct{
	GBOOL single;
	int cellID;
	int show_index;
} PARAM_REQ_sdk_matrix_set_cell_single;

typedef struct{
	int idle;
} PARAM_RESP_sdk_matrix_set_cell_single;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_matrix_set_cell_single(JCLink_t nLinkID, PARAM_REQ_sdk_matrix_set_cell_single *req, PARAM_RESP_sdk_matrix_set_cell_single *resp);
#  endif

//matrix_get_cell_single
#  if 1

//--- matrix_get_cell_single definition ----
/*
获取当前状态是临时放大某一画面，还是正常显示
*/
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_matrix_get_cell_single PARAM_REQ_sdk_matrix_get_cell_single;
typedef PARAM_RESP_vms_matrix_get_cell_single PARAM_RESP_sdk_matrix_get_cell_single;
#    else

typedef struct{
	int cellID;
} PARAM_REQ_sdk_matrix_get_cell_single;

typedef struct{
	GBOOL single;
	int show_index;
} PARAM_RESP_sdk_matrix_get_cell_single;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_matrix_get_cell_single(JCLink_t nLinkID, PARAM_REQ_sdk_matrix_get_cell_single *req, PARAM_RESP_sdk_matrix_get_cell_single *resp);
#  endif

//matrix_set_cell_multi
#  if 1

//--- matrix_set_cell_multi definition ----
/*
设置多画面显示的起始画面和分屏数。start_index指当视频源超过分屏数时，可以指定从某一个开始显示
*/
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_matrix_set_cell_multi PARAM_REQ_sdk_matrix_set_cell_multi;
typedef PARAM_RESP_vms_matrix_set_cell_multi PARAM_RESP_sdk_matrix_set_cell_multi;
#    else

typedef struct{
	int cellID;
	int spiltnum;
	int start_index;
} PARAM_REQ_sdk_matrix_set_cell_multi;

typedef struct{
	int idle;
} PARAM_RESP_sdk_matrix_set_cell_multi;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_matrix_set_cell_multi(JCLink_t nLinkID, PARAM_REQ_sdk_matrix_set_cell_multi *req, PARAM_RESP_sdk_matrix_set_cell_multi *resp);
#  endif

//matrix_get_cell_multi
#  if 1

//--- matrix_get_cell_multi definition ----
/*
多画面显示的状态。主要获取分屏数和从哪个视频源开始显示
*/
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_matrix_get_cell_multi PARAM_REQ_sdk_matrix_get_cell_multi;
typedef PARAM_RESP_vms_matrix_get_cell_multi PARAM_RESP_sdk_matrix_get_cell_multi;
#    else

typedef struct{
	int cellID;
} PARAM_REQ_sdk_matrix_get_cell_multi;

typedef struct{
	int spiltnum;
	int start_index;
} PARAM_RESP_sdk_matrix_get_cell_multi;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_matrix_get_cell_multi(JCLink_t nLinkID, PARAM_REQ_sdk_matrix_get_cell_multi *req, PARAM_RESP_sdk_matrix_get_cell_multi *resp);
#  endif

#endif


//json/mdetect.json
#if 1

//mdetect_set_param
#  if 1

//--- mdetect_set_param definition ----
/*
The max number of rects is 4, 0 means full screen motion detect.
Param nSensitivity ranges from 0 to 255.
Param x,y,w,h is measured in pixels.
*/
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_mdetect_set_param PARAM_REQ_sdk_mdetect_set_param;
typedef PARAM_RESP_vms_mdetect_set_param PARAM_RESP_sdk_mdetect_set_param;
#    else

typedef struct{
	int channelid;
	struct{
		GBOOL bEnable;
		GBOOL bEnableRecord;
		int sensitivity;
		int delay;
		GBOOL bOutClient;
		GBOOL bOutEmail;
		int rects_cnt;
		struct{
			int x;
			int y;
			int w;
			int h;
		} *rects;
	} md;
} PARAM_REQ_sdk_mdetect_set_param;

typedef struct{
	int idle;
} PARAM_RESP_sdk_mdetect_set_param;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_mdetect_set_param(JCLink_t nLinkID, PARAM_REQ_sdk_mdetect_set_param *req, PARAM_RESP_sdk_mdetect_set_param *resp);
#  endif

//mdetect_get_param
#  if 1

//--- mdetect_get_param definition ----
/*
The max number of rects is 4, 0 means full screen motion detect.
Param nSensitivity ranges from 0 to 255.
Param x,y,w,h is measured in pixels.
*/
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_mdetect_get_param PARAM_REQ_sdk_mdetect_get_param;
typedef PARAM_RESP_vms_mdetect_get_param PARAM_RESP_sdk_mdetect_get_param;
#    else

typedef struct{
	int channelid;
} PARAM_REQ_sdk_mdetect_get_param;

typedef struct{
	GBOOL bEnable;
	GBOOL bEnableRecord;
	int sensitivity;
	int delay;
	GBOOL bOutClient;
	GBOOL bOutEmail;
	int rects_cnt;
	struct{
		int x;
		int y;
		int w;
		int h;
	} *rects;
} PARAM_RESP_sdk_mdetect_get_param;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_mdetect_get_param(JCLink_t nLinkID, PARAM_REQ_sdk_mdetect_get_param *req, PARAM_RESP_sdk_mdetect_get_param *resp);
#  endif

//mdetect_balarming
#  if 1

//--- mdetect_balarming definition ----
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_mdetect_balarming PARAM_REQ_sdk_mdetect_balarming;
typedef PARAM_RESP_vms_mdetect_balarming PARAM_RESP_sdk_mdetect_balarming;
#    else

typedef struct{
	int channelid;
} PARAM_REQ_sdk_mdetect_balarming;

typedef struct{
	GBOOL bMdetectAlarming;
} PARAM_RESP_sdk_mdetect_balarming;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_mdetect_balarming(JCLink_t nLinkID, PARAM_REQ_sdk_mdetect_balarming *req, PARAM_RESP_sdk_mdetect_balarming *resp);
#  endif

#endif


//json/osd.json
#if 1

//chnosd_get_param
#  if 1

//--- chnosd_get_param definition ----
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_chnosd_get_param PARAM_REQ_sdk_chnosd_get_param;
typedef PARAM_RESP_vms_chnosd_get_param PARAM_RESP_sdk_chnosd_get_param;
#    else

typedef struct{
	int channelid;
} PARAM_REQ_sdk_chnosd_get_param;

typedef struct{
	GBOOL bShowOSD;
	char *timeFormat; //YYYY-MM-DD hh:mm:ss
	char *position; //left_top,left_bottom,right_top,right_bottom
	char *timePos; //left_top,left_bottom,right_top,right_bottom
	char *channelName; //HD IPC
	GBOOL bOsdInvColEn;
	GBOOL bLargeOSD;
} PARAM_RESP_sdk_chnosd_get_param;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_chnosd_get_param(JCLink_t nLinkID, PARAM_REQ_sdk_chnosd_get_param *req, PARAM_RESP_sdk_chnosd_get_param *resp);
#  endif

//chnosd_set_param
#  if 1

//--- chnosd_set_param definition ----
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_chnosd_set_param PARAM_REQ_sdk_chnosd_set_param;
typedef PARAM_RESP_vms_chnosd_set_param PARAM_RESP_sdk_chnosd_set_param;
#    else

typedef struct{
	int channelid;
	struct{
		GBOOL bShowOSD;
		char *timeFormat; //YYYY-MM-DD hh:mm:ss
		char *position; //left_top,left_bottom,right_top,right_bottom
		char *timePos; //left_top,left_bottom,right_top,right_bottom
		char *channelName; //HD IPC
		GBOOL bOsdInvColEn;
		GBOOL bLargeOSD;
	} attr;
} PARAM_REQ_sdk_chnosd_set_param;

typedef struct{
	int idle;
} PARAM_RESP_sdk_chnosd_set_param;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_chnosd_set_param(JCLink_t nLinkID, PARAM_REQ_sdk_chnosd_set_param *req, PARAM_RESP_sdk_chnosd_set_param *resp);
#  endif

#endif


//json/privacy.json
#if 1

//privacy_get_param
#  if 1

//--- privacy_get_param definition ----
/*
The max number of rects is 4.
Param x,y,w,h is measured in pixels.
*/
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_privacy_get_param PARAM_REQ_sdk_privacy_get_param;
typedef PARAM_RESP_vms_privacy_get_param PARAM_RESP_sdk_privacy_get_param;
#    else

typedef struct{
	int channelid;
} PARAM_REQ_sdk_privacy_get_param;

typedef struct{
	GBOOL bEnable;
	int rects_cnt;
	struct{
		int x;
		int y;
		int w;
		int h;
	} *rects;
} PARAM_RESP_sdk_privacy_get_param;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_privacy_get_param(JCLink_t nLinkID, PARAM_REQ_sdk_privacy_get_param *req, PARAM_RESP_sdk_privacy_get_param *resp);
#  endif

//privacy_set_param
#  if 1

//--- privacy_set_param definition ----
/*
The max number of rects is 4.
Param x,y,w,h is measured in pixels.
*/
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_privacy_set_param PARAM_REQ_sdk_privacy_set_param;
typedef PARAM_RESP_vms_privacy_set_param PARAM_RESP_sdk_privacy_set_param;
#    else

typedef struct{
	int channelid;
	struct{
		GBOOL bEnable;
		int rects_cnt;
		struct{
			int x;
			int y;
			int w;
			int h;
		} *rects;
	} region;
} PARAM_REQ_sdk_privacy_set_param;

typedef struct{
	int idle;
} PARAM_RESP_sdk_privacy_set_param;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_privacy_set_param(JCLink_t nLinkID, PARAM_REQ_sdk_privacy_set_param *req, PARAM_RESP_sdk_privacy_set_param *resp);
#  endif

#endif


//json/ptz.json
#if 1

//ptz_move_start
#  if 1

//--- ptz_move_start definition ----
/*
ptz speed ranges from -254 to 254;
 > 0, pan left or tilt up or zoom in, otherwise the opposite direction.
*/
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_ptz_move_start PARAM_REQ_sdk_ptz_move_start;
typedef PARAM_RESP_vms_ptz_move_start PARAM_RESP_sdk_ptz_move_start;
#    else

typedef struct{
	int channelid;
	int panLeft;
	int tiltUp;
	int zoomIn;
} PARAM_REQ_sdk_ptz_move_start;

typedef struct{
	int idle;
} PARAM_RESP_sdk_ptz_move_start;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_ptz_move_start(JCLink_t nLinkID, PARAM_REQ_sdk_ptz_move_start *req, PARAM_RESP_sdk_ptz_move_start *resp);
#  endif

//ptz_move_stop
#  if 1

//--- ptz_move_stop definition ----
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_ptz_move_stop PARAM_REQ_sdk_ptz_move_stop;
typedef PARAM_RESP_vms_ptz_move_stop PARAM_RESP_sdk_ptz_move_stop;
#    else

typedef struct{
	int channelid;
} PARAM_REQ_sdk_ptz_move_stop;

typedef struct{
	int idle;
} PARAM_RESP_sdk_ptz_move_stop;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_ptz_move_stop(JCLink_t nLinkID, PARAM_REQ_sdk_ptz_move_stop *req, PARAM_RESP_sdk_ptz_move_stop *resp);
#  endif

//ptz_fi_start
#  if 1

//--- ptz_fi_start definition ----
/*
fi speed ranges from -254 to 254;
 > 0, focus far or iris open, otherwise the opposite direction.
*/
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_ptz_fi_start PARAM_REQ_sdk_ptz_fi_start;
typedef PARAM_RESP_vms_ptz_fi_start PARAM_RESP_sdk_ptz_fi_start;
#    else

typedef struct{
	int channelid;
	int focusFar;
	int irisOpen;
} PARAM_REQ_sdk_ptz_fi_start;

typedef struct{
	int idle;
} PARAM_RESP_sdk_ptz_fi_start;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_ptz_fi_start(JCLink_t nLinkID, PARAM_REQ_sdk_ptz_fi_start *req, PARAM_RESP_sdk_ptz_fi_start *resp);
#  endif

//ptz_fi_stop
#  if 1

//--- ptz_fi_stop definition ----
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_ptz_fi_stop PARAM_REQ_sdk_ptz_fi_stop;
typedef PARAM_RESP_vms_ptz_fi_stop PARAM_RESP_sdk_ptz_fi_stop;
#    else

typedef struct{
	int channelid;
} PARAM_REQ_sdk_ptz_fi_stop;

typedef struct{
	int idle;
} PARAM_RESP_sdk_ptz_fi_stop;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_ptz_fi_stop(JCLink_t nLinkID, PARAM_REQ_sdk_ptz_fi_stop *req, PARAM_RESP_sdk_ptz_fi_stop *resp);
#  endif

//ptz_preset_set
#  if 1

//--- ptz_preset_set definition ----
/*
errcode : 
 0 : success;
 -1 : illegal preset number;
 -2 : preset already exists;
 -3 : no enough preset number.
*/
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_ptz_preset_set PARAM_REQ_sdk_ptz_preset_set;
typedef PARAM_RESP_vms_ptz_preset_set PARAM_RESP_sdk_ptz_preset_set;
#    else

typedef struct{
	int channelid;
	int presetno;
	char *name; //preset1
} PARAM_REQ_sdk_ptz_preset_set;

typedef struct{
	int idle;
} PARAM_RESP_sdk_ptz_preset_set;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_ptz_preset_set(JCLink_t nLinkID, PARAM_REQ_sdk_ptz_preset_set *req, PARAM_RESP_sdk_ptz_preset_set *resp);
#  endif

//ptz_preset_locate
#  if 1

//--- ptz_preset_locate definition ----
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_ptz_preset_locate PARAM_REQ_sdk_ptz_preset_locate;
typedef PARAM_RESP_vms_ptz_preset_locate PARAM_RESP_sdk_ptz_preset_locate;
#    else

typedef struct{
	int channelid;
	int presetno;
} PARAM_REQ_sdk_ptz_preset_locate;

typedef struct{
	int idle;
} PARAM_RESP_sdk_ptz_preset_locate;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_ptz_preset_locate(JCLink_t nLinkID, PARAM_REQ_sdk_ptz_preset_locate *req, PARAM_RESP_sdk_ptz_preset_locate *resp);
#  endif

//ptz_preset_delete
#  if 1

//--- ptz_preset_delete definition ----
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_ptz_preset_delete PARAM_REQ_sdk_ptz_preset_delete;
typedef PARAM_RESP_vms_ptz_preset_delete PARAM_RESP_sdk_ptz_preset_delete;
#    else

typedef struct{
	int channelid;
	int presetno;
} PARAM_REQ_sdk_ptz_preset_delete;

typedef struct{
	int idle;
} PARAM_RESP_sdk_ptz_preset_delete;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_ptz_preset_delete(JCLink_t nLinkID, PARAM_REQ_sdk_ptz_preset_delete *req, PARAM_RESP_sdk_ptz_preset_delete *resp);
#  endif

//ptz_presets_get
#  if 1

//--- ptz_presets_get definition ----
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_ptz_presets_get PARAM_REQ_sdk_ptz_presets_get;
typedef PARAM_RESP_vms_ptz_presets_get PARAM_RESP_sdk_ptz_presets_get;
#    else

typedef struct{
	int channelid;
} PARAM_REQ_sdk_ptz_presets_get;

typedef struct{
	int presetsList_cnt;
	struct{
		int presetno;
		char *name; //preset1
	} *presetsList;
} PARAM_RESP_sdk_ptz_presets_get;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_ptz_presets_get(JCLink_t nLinkID, PARAM_REQ_sdk_ptz_presets_get *req, PARAM_RESP_sdk_ptz_presets_get *resp);
#  endif

//ptz_patrol_create
#  if 1

//--- ptz_patrol_create definition ----
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_ptz_patrol_create PARAM_REQ_sdk_ptz_patrol_create;
typedef PARAM_RESP_vms_ptz_patrol_create PARAM_RESP_sdk_ptz_patrol_create;
#    else

typedef struct{
	int channelid;
} PARAM_REQ_sdk_ptz_patrol_create;

typedef struct{
	int index;
} PARAM_RESP_sdk_ptz_patrol_create;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_ptz_patrol_create(JCLink_t nLinkID, PARAM_REQ_sdk_ptz_patrol_create *req, PARAM_RESP_sdk_ptz_patrol_create *resp);
#  endif

//ptz_patrol_delete
#  if 1

//--- ptz_patrol_delete definition ----
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_ptz_patrol_delete PARAM_REQ_sdk_ptz_patrol_delete;
typedef PARAM_RESP_vms_ptz_patrol_delete PARAM_RESP_sdk_ptz_patrol_delete;
#    else

typedef struct{
	int channelid;
	int index;
} PARAM_REQ_sdk_ptz_patrol_delete;

typedef struct{
	int idle;
} PARAM_RESP_sdk_ptz_patrol_delete;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_ptz_patrol_delete(JCLink_t nLinkID, PARAM_REQ_sdk_ptz_patrol_delete *req, PARAM_RESP_sdk_ptz_patrol_delete *resp);
#  endif

//ptz_patrols_get
#  if 1

//--- ptz_patrols_get definition ----
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_ptz_patrols_get PARAM_REQ_sdk_ptz_patrols_get;
typedef PARAM_RESP_vms_ptz_patrols_get PARAM_RESP_sdk_ptz_patrols_get;
#    else

typedef struct{
	int channelid;
} PARAM_REQ_sdk_ptz_patrols_get;

typedef struct{
	int patrolsList_cnt;
	struct{
		int patrolid;
	} *patrolsList;
} PARAM_RESP_sdk_ptz_patrols_get;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_ptz_patrols_get(JCLink_t nLinkID, PARAM_REQ_sdk_ptz_patrols_get *req, PARAM_RESP_sdk_ptz_patrols_get *resp);
#  endif

//ptz_patrol_get_nodes
#  if 1

//--- ptz_patrol_get_nodes definition ----
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_ptz_patrol_get_nodes PARAM_REQ_sdk_ptz_patrol_get_nodes;
typedef PARAM_RESP_vms_ptz_patrol_get_nodes PARAM_RESP_sdk_ptz_patrol_get_nodes;
#    else

typedef struct{
	int channelid;
	int patrolid;
} PARAM_REQ_sdk_ptz_patrol_get_nodes;

typedef struct{
	int patrolNodesList_cnt;
	struct{
		struct{
			int presetno;
			char *name; //preset1
		} preset;
		int staySeconds;
	} *patrolNodesList;
} PARAM_RESP_sdk_ptz_patrol_get_nodes;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_ptz_patrol_get_nodes(JCLink_t nLinkID, PARAM_REQ_sdk_ptz_patrol_get_nodes *req, PARAM_RESP_sdk_ptz_patrol_get_nodes *resp);
#  endif

//ptz_patrol_add_node
#  if 1

//--- ptz_patrol_add_node definition ----
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_ptz_patrol_add_node PARAM_REQ_sdk_ptz_patrol_add_node;
typedef PARAM_RESP_vms_ptz_patrol_add_node PARAM_RESP_sdk_ptz_patrol_add_node;
#    else

typedef struct{
	int channelid;
	int patrolid;
	int presetno;
	int staySeconds;
} PARAM_REQ_sdk_ptz_patrol_add_node;

typedef struct{
	int idle;
} PARAM_RESP_sdk_ptz_patrol_add_node;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_ptz_patrol_add_node(JCLink_t nLinkID, PARAM_REQ_sdk_ptz_patrol_add_node *req, PARAM_RESP_sdk_ptz_patrol_add_node *resp);
#  endif

//ptz_patrol_del_node
#  if 1

//--- ptz_patrol_del_node definition ----
/*
presetindex: the index of this node in patrol, start from 0. if -1, delete all the nodes in patrol.
*/
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_ptz_patrol_del_node PARAM_REQ_sdk_ptz_patrol_del_node;
typedef PARAM_RESP_vms_ptz_patrol_del_node PARAM_RESP_sdk_ptz_patrol_del_node;
#    else

typedef struct{
	int channelid;
	int patrolid;
	int presetindex;
} PARAM_REQ_sdk_ptz_patrol_del_node;

typedef struct{
	int idle;
} PARAM_RESP_sdk_ptz_patrol_del_node;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_ptz_patrol_del_node(JCLink_t nLinkID, PARAM_REQ_sdk_ptz_patrol_del_node *req, PARAM_RESP_sdk_ptz_patrol_del_node *resp);
#  endif

//ptz_patrol_set_speed
#  if 1

//--- ptz_patrol_set_speed definition ----
/*
Speed ranges from 0 to 254.
*/
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_ptz_patrol_set_speed PARAM_REQ_sdk_ptz_patrol_set_speed;
typedef PARAM_RESP_vms_ptz_patrol_set_speed PARAM_RESP_sdk_ptz_patrol_set_speed;
#    else

typedef struct{
	int channelid;
	int patrolid;
	int speed;
} PARAM_REQ_sdk_ptz_patrol_set_speed;

typedef struct{
	int idle;
} PARAM_RESP_sdk_ptz_patrol_set_speed;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_ptz_patrol_set_speed(JCLink_t nLinkID, PARAM_REQ_sdk_ptz_patrol_set_speed *req, PARAM_RESP_sdk_ptz_patrol_set_speed *resp);
#  endif

//ptz_patrol_set_stay_seconds
#  if 1

//--- ptz_patrol_set_stay_seconds definition ----
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_ptz_patrol_set_stay_seconds PARAM_REQ_sdk_ptz_patrol_set_stay_seconds;
typedef PARAM_RESP_vms_ptz_patrol_set_stay_seconds PARAM_RESP_sdk_ptz_patrol_set_stay_seconds;
#    else

typedef struct{
	int channelid;
	int patrolid;
	int staySeconds;
} PARAM_REQ_sdk_ptz_patrol_set_stay_seconds;

typedef struct{
	int idle;
} PARAM_RESP_sdk_ptz_patrol_set_stay_seconds;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_ptz_patrol_set_stay_seconds(JCLink_t nLinkID, PARAM_REQ_sdk_ptz_patrol_set_stay_seconds *req, PARAM_RESP_sdk_ptz_patrol_set_stay_seconds *resp);
#  endif

//ptz_patrol_locate
#  if 1

//--- ptz_patrol_locate definition ----
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_ptz_patrol_locate PARAM_REQ_sdk_ptz_patrol_locate;
typedef PARAM_RESP_vms_ptz_patrol_locate PARAM_RESP_sdk_ptz_patrol_locate;
#    else

typedef struct{
	int channelid;
	int patrolid;
} PARAM_REQ_sdk_ptz_patrol_locate;

typedef struct{
	int idle;
} PARAM_RESP_sdk_ptz_patrol_locate;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_ptz_patrol_locate(JCLink_t nLinkID, PARAM_REQ_sdk_ptz_patrol_locate *req, PARAM_RESP_sdk_ptz_patrol_locate *resp);
#  endif

//ptz_patrol_stop
#  if 1

//--- ptz_patrol_stop definition ----
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_ptz_patrol_stop PARAM_REQ_sdk_ptz_patrol_stop;
typedef PARAM_RESP_vms_ptz_patrol_stop PARAM_RESP_sdk_ptz_patrol_stop;
#    else

typedef struct{
	int channelid;
	int patrolid;
} PARAM_REQ_sdk_ptz_patrol_stop;

typedef struct{
	int idle;
} PARAM_RESP_sdk_ptz_patrol_stop;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_ptz_patrol_stop(JCLink_t nLinkID, PARAM_REQ_sdk_ptz_patrol_stop *req, PARAM_RESP_sdk_ptz_patrol_stop *resp);
#  endif

//ptz_scan_set_left
#  if 1

//--- ptz_scan_set_left definition ----
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_ptz_scan_set_left PARAM_REQ_sdk_ptz_scan_set_left;
typedef PARAM_RESP_vms_ptz_scan_set_left PARAM_RESP_sdk_ptz_scan_set_left;
#    else

typedef struct{
	int channelid;
	int groupid;
} PARAM_REQ_sdk_ptz_scan_set_left;

typedef struct{
	int idle;
} PARAM_RESP_sdk_ptz_scan_set_left;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_ptz_scan_set_left(JCLink_t nLinkID, PARAM_REQ_sdk_ptz_scan_set_left *req, PARAM_RESP_sdk_ptz_scan_set_left *resp);
#  endif

//ptz_scan_set_right
#  if 1

//--- ptz_scan_set_right definition ----
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_ptz_scan_set_right PARAM_REQ_sdk_ptz_scan_set_right;
typedef PARAM_RESP_vms_ptz_scan_set_right PARAM_RESP_sdk_ptz_scan_set_right;
#    else

typedef struct{
	int channelid;
	int groupid;
} PARAM_REQ_sdk_ptz_scan_set_right;

typedef struct{
	int idle;
} PARAM_RESP_sdk_ptz_scan_set_right;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_ptz_scan_set_right(JCLink_t nLinkID, PARAM_REQ_sdk_ptz_scan_set_right *req, PARAM_RESP_sdk_ptz_scan_set_right *resp);
#  endif

//ptz_scan_start
#  if 1

//--- ptz_scan_start definition ----
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_ptz_scan_start PARAM_REQ_sdk_ptz_scan_start;
typedef PARAM_RESP_vms_ptz_scan_start PARAM_RESP_sdk_ptz_scan_start;
#    else

typedef struct{
	int channelid;
	int groupid;
} PARAM_REQ_sdk_ptz_scan_start;

typedef struct{
	int idle;
} PARAM_RESP_sdk_ptz_scan_start;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_ptz_scan_start(JCLink_t nLinkID, PARAM_REQ_sdk_ptz_scan_start *req, PARAM_RESP_sdk_ptz_scan_start *resp);
#  endif

//ptz_scan_stop
#  if 1

//--- ptz_scan_stop definition ----
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_ptz_scan_stop PARAM_REQ_sdk_ptz_scan_stop;
typedef PARAM_RESP_vms_ptz_scan_stop PARAM_RESP_sdk_ptz_scan_stop;
#    else

typedef struct{
	int channelid;
	int groupid;
} PARAM_REQ_sdk_ptz_scan_stop;

typedef struct{
	int idle;
} PARAM_RESP_sdk_ptz_scan_stop;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_ptz_scan_stop(JCLink_t nLinkID, PARAM_REQ_sdk_ptz_scan_stop *req, PARAM_RESP_sdk_ptz_scan_stop *resp);
#  endif

//ptz_scan_set_speed
#  if 1

//--- ptz_scan_set_speed definition ----
/*
Speed ranges from 0 to 254.
*/
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_ptz_scan_set_speed PARAM_REQ_sdk_ptz_scan_set_speed;
typedef PARAM_RESP_vms_ptz_scan_set_speed PARAM_RESP_sdk_ptz_scan_set_speed;
#    else

typedef struct{
	int channelid;
	int groupid;
	int speed;
} PARAM_REQ_sdk_ptz_scan_set_speed;

typedef struct{
	int idle;
} PARAM_RESP_sdk_ptz_scan_set_speed;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_ptz_scan_set_speed(JCLink_t nLinkID, PARAM_REQ_sdk_ptz_scan_set_speed *req, PARAM_RESP_sdk_ptz_scan_set_speed *resp);
#  endif

#endif


//json/record.json
#if 1

//record_get
#  if 1

//--- record_get definition ----
/*
enum{ALL,Mon,Tues,Wed,Thur,Fri,Sat,Sun}
*/
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_record_get PARAM_REQ_sdk_record_get;
typedef PARAM_RESP_vms_record_get PARAM_RESP_sdk_record_get;
#    else

typedef struct{
	int channelid;
} PARAM_REQ_sdk_record_get;

typedef struct{
	int record_params_cnt;
	struct{
		GBOOL brecording;
		GBOOL normal_record;
		GBOOL time_record;
		int date_cnt;
		struct{
			char *week; //Mon
			int time_cnt;
			struct{
				int begin_hour;
				int begin_min;
				int end_hour;
				int end_min;
			} *time;
		} *date;
	} *record_params;
} PARAM_RESP_sdk_record_get;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_record_get(JCLink_t nLinkID, PARAM_REQ_sdk_record_get *req, PARAM_RESP_sdk_record_get *resp);
#  endif

//record_set
#  if 1

//--- record_set definition ----
/*
enum{ALL,Mon,Tues,Wed,Thur,Fri,Sat,Sun}
*/
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_record_set PARAM_REQ_sdk_record_set;
typedef PARAM_RESP_vms_record_set PARAM_RESP_sdk_record_set;
#    else

typedef struct{
	int record_params_cnt;
	struct{
		int channelid;
		GBOOL normal_record;
		GBOOL time_record;
		int date_cnt;
		struct{
			char *week; //Mon
			int time_cnt;
			struct{
				int begin_hour;
				int begin_min;
				int end_hour;
				int end_min;
			} *time;
		} *date;
	} *record_params;
} PARAM_REQ_sdk_record_set;

typedef struct{
	int idle;
} PARAM_RESP_sdk_record_set;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_record_set(JCLink_t nLinkID, PARAM_REQ_sdk_record_set *req, PARAM_RESP_sdk_record_set *resp);
#  endif

#endif


//json/storage.json
#if 1

//storage_get_info
#  if 1

//--- storage_get_info definition ----
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_storage_get_info PARAM_REQ_sdk_storage_get_info;
typedef PARAM_RESP_vms_storage_get_info PARAM_RESP_sdk_storage_get_info;
#    else

typedef struct{
	int idle;
} PARAM_REQ_sdk_storage_get_info;

typedef struct{
	int size;
	int cylinder;
	int partSize;
	int partition;
	int entryCount;
	int status;
	int curPart;
	GBOOL bNocard;
	GBOOL bMounted;
	int partSpace_cnt;
	int *partSpace;
	int freeSpace_cnt;
	int *freeSpace;
} PARAM_RESP_sdk_storage_get_info;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_storage_get_info(JCLink_t nLinkID, PARAM_REQ_sdk_storage_get_info *req, PARAM_RESP_sdk_storage_get_info *resp);
#  endif

//storage_format
#  if 1

//--- storage_format definition ----
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_storage_format PARAM_REQ_sdk_storage_format;
typedef PARAM_RESP_vms_storage_format PARAM_RESP_sdk_storage_format;
#    else

typedef struct{
	int diskNum;
} PARAM_REQ_sdk_storage_format;

typedef struct{
	int idle;
} PARAM_RESP_sdk_storage_format;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_storage_format(JCLink_t nLinkID, PARAM_REQ_sdk_storage_format *req, PARAM_RESP_sdk_storage_format *resp);
#  endif

#endif


//json/stream.json
#if 1

//stream_get_param
#  if 1

//--- stream_get_param definition ----
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_stream_get_param PARAM_REQ_sdk_stream_get_param;
typedef PARAM_RESP_vms_stream_get_param PARAM_RESP_sdk_stream_get_param;
#    else

typedef struct{
	int channelid;
	int streamid;
} PARAM_REQ_sdk_stream_get_param;

typedef struct{
	int width;
	int height;
	int frameRate;
	int bitRate;
	int ngop_s;
	int quality;
	char *rcMode; //cbr,vbr,fixQP
} PARAM_RESP_sdk_stream_get_param;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_stream_get_param(JCLink_t nLinkID, PARAM_REQ_sdk_stream_get_param *req, PARAM_RESP_sdk_stream_get_param *resp);
#  endif

//stream_get_params
#  if 1

//--- stream_get_params definition ----
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_stream_get_params PARAM_REQ_sdk_stream_get_params;
typedef PARAM_RESP_vms_stream_get_params PARAM_RESP_sdk_stream_get_params;
#    else

typedef struct{
	int idle;
} PARAM_REQ_sdk_stream_get_params;

typedef struct{
	int streams_cnt;
	struct{
		int channelid;
		int streamid;
		int width;
		int height;
		int frameRate;
		int bitRate;
		int ngop_s;
		int quality;
		char *rcMode; //cbr,vbr,fixQP
	} *streams;
} PARAM_RESP_sdk_stream_get_params;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_stream_get_params(JCLink_t nLinkID, PARAM_REQ_sdk_stream_get_params *req, PARAM_RESP_sdk_stream_get_params *resp);
#  endif

//stream_set_param
#  if 1

//--- stream_set_param definition ----
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_stream_set_param PARAM_REQ_sdk_stream_set_param;
typedef PARAM_RESP_vms_stream_set_param PARAM_RESP_sdk_stream_set_param;
#    else

typedef struct{
	int channelid;
	int streamid;
	int width;
	int height;
	int frameRate;
	int bitRate;
	int ngop_s;
	int quality;
	char *rcMode; //cbr,vbr,fixQP
} PARAM_REQ_sdk_stream_set_param;

typedef struct{
	int idle;
} PARAM_RESP_sdk_stream_set_param;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_stream_set_param(JCLink_t nLinkID, PARAM_REQ_sdk_stream_set_param *req, PARAM_RESP_sdk_stream_set_param *resp);
#  endif

//stream_get_ability
#  if 1

//--- stream_get_ability definition ----
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_stream_get_ability PARAM_REQ_sdk_stream_get_ability;
typedef PARAM_RESP_vms_stream_get_ability PARAM_RESP_sdk_stream_get_ability;
#    else

typedef struct{
	int channelid;
	int streamid;
} PARAM_REQ_sdk_stream_get_ability;

typedef struct{
	int resolutions_cnt;
	struct{
		int width;
		int height;
	} *resolutions;
	struct{
		int width;
		int height;
	} inputRes;
	int maxFramerate;
	int minFramerate;
	int maxQuality;
	int minQuality;
	int maxNGOP;
	int minNGOP;
	int maxKBitrate;
	int minKBitrate;
} PARAM_RESP_sdk_stream_get_ability;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_stream_get_ability(JCLink_t nLinkID, PARAM_REQ_sdk_stream_get_ability *req, PARAM_RESP_sdk_stream_get_ability *resp);
#  endif

//stream_snapshot
#  if 1

//--- stream_snapshot definition ----
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_stream_snapshot PARAM_REQ_sdk_stream_snapshot;
typedef PARAM_RESP_vms_stream_snapshot PARAM_RESP_sdk_stream_snapshot;
#    else

typedef struct{
	int channelid;
	int streamid;
	int width;
	int height;
} PARAM_REQ_sdk_stream_snapshot;

typedef struct{
	char *snapshot; //url of snapshot
} PARAM_RESP_sdk_stream_snapshot;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_stream_snapshot(JCLink_t nLinkID, PARAM_REQ_sdk_stream_snapshot *req, PARAM_RESP_sdk_stream_snapshot *resp);
#  endif

//stream_request_idr
#  if 1

//--- stream_request_idr definition ----
#    ifdef JCSDK_EXPORTS

typedef PARAM_REQ_vms_stream_request_idr PARAM_REQ_sdk_stream_request_idr;
typedef PARAM_RESP_vms_stream_request_idr PARAM_RESP_sdk_stream_request_idr;
#    else

typedef struct{
	int channelid;
	int streamid;
} PARAM_REQ_sdk_stream_request_idr;

typedef struct{
	int idle;
} PARAM_RESP_sdk_stream_request_idr;
#    endif
JCSDK_API BOOL JCSDK_CALLTYPE JCSDK_GRPC_stream_request_idr(JCLink_t nLinkID, PARAM_REQ_sdk_stream_request_idr *req, PARAM_RESP_sdk_stream_request_idr *resp);
#  endif

#endif

