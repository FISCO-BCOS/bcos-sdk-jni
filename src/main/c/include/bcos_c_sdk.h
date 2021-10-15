#ifndef __INCLUDE_BCOS_SDK__
#define __INCLUDE_BCOS_SDK__

#include "bcos_c_sdk_common.h"

#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------------------------------
// bcos sdk function start
//--------------------------------------------------------
// create bcos sdk object by config object
void *create_bcos_sdk(struct Config *config);
// destroy the bcos sdk object
void destroy_bcos_sdk(void *sdk);
// start bcos sdk
void start_bcos_sdk(void *sdk);
// stop bcos sdk
void stop_bcos_sdk(void *sdk);

// get rpc module from sdk object
void *get_rpc_obj(void *sdk, const char *group);
// get event sub module from sdk object
void *get_event_sub_obj(void *sdk, const char *group);
// get amop module from sdk object
void *get_amop_obj(void *sdk);
//--------------------------------------------------------
// bcos sdk function end
//--------------------------------------------------------

//--------------------------------------------------------
// bcos rpc function start
//--------------------------------------------------------
// create bcos sdk rpc object by config object
void *create_bcos_sdk_rpc_obj(struct Config *config);
// destroy the bcos sdk rpc sdk object
void destroy_bcos_sdk_rpc_obj(void *rpc);
// start the rpc service
void start_bcos_sdk_rpc_obj(void *rpc);
// stop the rpc service
void stop_bcos_sdk_rpc_obj(void *rpc);
//--------------------------------------------------------
// bcos rpc function end
//--------------------------------------------------------

//--------------------------------------------------------
// bcos amop function start
//--------------------------------------------------------
// create bcos sdk amop object by config object
void *create_bcos_sdk_amop_obj(struct Config *config);
// destroy the bcos sdk amop object
void destroy_bcos_sdk_amop_obj(void *amop);
// start the amop service
void start_bcos_sdk_amop_obj(void *amop);
// stop the amop service
void stop_bcos_sdk_amop_obj(void *amop);
//--------------------------------------------------------
// bcos amop function end
//--------------------------------------------------------

//--------------------------------------------------------
// bcos event sub function start
//--------------------------------------------------------
// create bcos sdk event sub object by config object
void *create_bcos_sdk_event_sub_obj(struct Config *config);
// destroy the bcos sdk event sub object
void destroy_bcos_sdk_event_sub_obj(void *event);
// start the bcos sdk event sub service
void start_bcos_sdk_event_sub_obj(void *event);
// stop the bcos sdk event sub service
void stop_bcos_sdk_event_sub_obj(void *event);
//--------------------------------------------------------
// bcos event sub function end
//--------------------------------------------------------

#ifdef __cplusplus
}
#endif
#endif
