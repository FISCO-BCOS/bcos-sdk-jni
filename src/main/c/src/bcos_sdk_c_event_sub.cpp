
#include "bcos_sdk_c_event_sub.h"
#include "bcos_sdk_c_common.h"
#include <bcos-cpp-sdk/event/EventSub.h>
#include <bcos-cpp-sdk/event/EventSubInterface.h>
#include <tuple>

using namespace bcos;
using namespace bcos::boostssl;
using namespace bcos::boostssl::utilities;
using namespace bcos::boostssl::utilities::protocol;

// ------------------------------event interface begin ----------------------

void bcos_event_sub_subscribe_event(void* event, const char* group, const char* params,
    bcos_sdk_c_struct_response_cb callback, void* context)
{
    auto eventPointer = (bcos::cppsdk::event::EventSubInterface*)event;
    eventPointer->subscribeEvent(
        group, params, [callback, context](Error::Ptr error, const std::string& resp) {
            bcos_sdk_c_handle_response(
                error ? error.get() : NULL, (void*)resp.data(), resp.size(), callback, context);
        });
}

void bcos_event_sub_unsubscribe_event(void* event, const char* event_sub_id)
{
    auto eventPointer = (bcos::cppsdk::event::EventSubInterface*)event;
    eventPointer->unsubscribeEvent(event_sub_id);
}

// ------------------------------event interface end -------------------------

void* bcos_event_sub_get_ws(void* event)
{
    if (event)
    {
        auto eventPointer = (bcos::cppsdk::event::EventSub*)event;
        auto ws = eventPointer->wsService();
        return ws ? ws.get() : NULL;
    }

    return NULL;
}
