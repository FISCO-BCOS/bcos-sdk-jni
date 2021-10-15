
#include "bcos_c_sdk_event_sub.h"
#include <bcos-cpp-sdk/event/EventSubInterface.h>
#include <stdint.h>
#include <stdio.h>
#include <tuple>

// ------------------------------event interface begin ----------------------

void bcos_event_sub_subscribe_event(void *event, const char *params,
                                    rpc_callback callback, void *context) {
  auto eventPointer = (bcos::cppsdk::event::EventSubInterface *)event;
  std::ignore = context;
  std::ignore = eventPointer;
  std::ignore = params;
  std::ignore = callback;
  std::ignore = context;

  /*
auto eventPointer = (bcos::cppsdk::event::EventSubInterface *)event;

eventPointer->subscribeEvent(
group, [callback, context](bcos::Error::Ptr error,
std::shared_ptr<bcos::bytes> resp) {
bcos_rpc_handle_response(error, resp, callback, context);
});
*/
}

void bcos_event_sub_unsubscribe_event(void *event, const char *event_id,
                                      rpc_callback callback, void *context) {
  auto eventPointer = (bcos::cppsdk::event::EventSubInterface *)event;
  std::ignore = context;
  std::ignore = eventPointer;
  std::ignore = event_id;
  std::ignore = callback;
  std::ignore = context;
}

// ------------------------------event interface end -------------------------
