
#include "bcos_sdk_c_common.h"
#include "bcos_sdk_c_event_sub.h"
#include <bcos-cpp-sdk/event/EventSubInterface.h>
#include <stdint.h>
#include <stdio.h>
#include <tuple>

// ------------------------------event interface begin ----------------------

void bcos_event_sub_subscribe_event(void *event, const char *group,
                                    const char *params, rpc_callback callback,
                                    void *context) {
  auto eventPointer = (bcos::cppsdk::event::EventSubInterface *)event;
  eventPointer->subscribeEvent(
      group, params,
      [callback, context](bcos::Error::Ptr error,
                          std::shared_ptr<bcos::bytes> resp) {
        bcos_rpc_handle_response(error ? error.get() : NULL,
                                 resp ? resp.get() : NULL, callback, context);
      });
}

void bcos_event_sub_unsubscribe_event(void *event, const char *event_id,
                                      rpc_callback callback, void *context) {
  auto eventPointer = (bcos::cppsdk::event::EventSubInterface *)event;
  eventPointer->unsubscribeEvent(
      event_id, [callback, context](bcos::Error::Ptr error,
                                    std::shared_ptr<bcos::bytes> resp) {
        bcos_rpc_handle_response(error ? error.get() : NULL,
                                 resp ? resp.get() : NULL, callback, context);
      });
}

// ------------------------------event interface end -------------------------
