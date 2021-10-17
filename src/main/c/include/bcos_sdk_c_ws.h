#ifndef __INCLUDE_BCOS_SDK_WS__
#define __INCLUDE_BCOS_SDK_WS__

#include "bcos_sdk_c_common.h"

#ifdef __cplusplus
extern "C" {
#endif

// ------------ websocket interface interface begin -------------------------

int32_t bcos_ws_connection_count(void *ws);

// ------------ websocket interface interface end ---------------------------

void *bcos_event_sub_get_ws(void *event);

#ifdef __cplusplus
}
#endif
#endif
