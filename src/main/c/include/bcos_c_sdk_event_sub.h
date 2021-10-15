#ifndef __INCLUDE_BCOS_SDK_EVENT__
#define __INCLUDE_BCOS_SDK_EVENT__

#include <stdint.h>
#include <stdio.h>

#include "bcos_c_sdk_common.h"

#ifdef __cplusplus
extern "C" {
#endif

// ------------------------------event interface begin ----------------------

void bcos_event_sub_subscribe_event(void *event, const char *params,
                                    rpc_callback callback, void *context);

void bcos_event_sub_unsubscribe_event(void *event, const char *event_id,
                                      rpc_callback callback, void *context);

// ------------------------------event interface end -------------------------
#ifdef __cplusplus
}
#endif
#endif
