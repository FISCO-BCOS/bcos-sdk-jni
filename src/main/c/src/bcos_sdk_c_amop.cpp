#include "bcos_sdk_c_amop.h"
#include "bcos_sdk_c_common.h"
#include <bcos-boostssl/utilities/Common.h>
#include <bcos-cpp-sdk/amop/AMOP.h>
#include <set>
#include <string>

// ------------------------------amop interface begin ----------------------

using namespace bcos;
using namespace bcos::boostssl;
using namespace bcos::boostssl::utilities;
using namespace bcos::boostssl::utilities::protocol;

void bcos_amop_subscribe_topic(void* amop, char** topics, size_t topic_count)
{
    if (!topics || !topic_count)
    {
        return;
    }

    auto amopPointer = (bcos::cppsdk::amop::AMOPInterface*)amop;

    std::set<std::string> setTopics;
    for (size_t i = 0; i < topic_count; i++)
    {
        setTopics.insert(std::string(topics[i]));
    }

    amopPointer->subscribe(setTopics);
}

void bcos_amop_subscribe_topic_with_cb(
    void* amop, const char* topic, bcos_sdk_c_amop_subscribe_cb cb, void* context)
{
    if (!topic || !context || !cb)
    {
        return;
    }

    auto amopPointer = (bcos::cppsdk::amop::AMOPInterface*)amop;
    amopPointer->subscribe(std::string(topic),
        [context, cb](Error::Ptr error, const std::string& endpoint, const std::string& seq,
            bytesConstRef data, std::shared_ptr<bcos::boostssl::ws::WsSession> session) {
            std::ignore = session;
            // create resp obj
            bcos_sdk_c_struct_response resp;
            resp.context = context;
            if (error && error->errorCode() != CommonError::SUCCESS)
            {
                resp.error = error->errorCode();
                resp.desc = (char*)error->errorMessage().data();
            }
            else
            {
                resp.error = CommonError::SUCCESS;
                resp.data = (void*)data.data();
                resp.size = data.size();
            }

            // callback
            cb(endpoint.c_str(), seq.c_str(), &resp);
        });
}

void bcos_amop_unsubscribe_topic(void* amop, char** topics, size_t topic_count)
{
    if (!topics || !topic_count)
    {
        return;
    }

    auto amopPointer = (bcos::cppsdk::amop::AMOPInterface*)amop;

    std::set<std::string> setTopics;
    for (size_t i = 0; i < topic_count; i++)
    {
        setTopics.insert(std::string(topics[i]));
    }

    amopPointer->unsubscribe(setTopics);
}

void bcos_amop_publish(void* amop, const char* topic, void* data, size_t size, uint32_t timeout,
    bcos_sdk_c_amop_publish_cb cb, void* context)
{
    if (!data || !size || !cb)
    {
        return;
    }

    auto amopPointer = (bcos::cppsdk::amop::AMOPInterface*)amop;
    amopPointer->publish(std::string(topic), bytesConstRef((byte*)data, size), timeout,
        [cb, context](Error::Ptr error, std::shared_ptr<bcos::boostssl::ws::WsMessage> msg,
            std::shared_ptr<bcos::boostssl::ws::WsSession> session) {
            std::ignore = session;

            void* data = msg ? msg->data()->data() : NULL;
            size_t size = msg ? msg->data()->size() : 0;

            bcos_sdk_c_handle_response(error ? error.get() : NULL, data, size, cb, context);
        });
}

void bcos_amop_broadcast(void* amop, const char* topic, void* data, size_t size)
{
    if (!topic || !data || !size)
    {
        return;
    }

    auto amopPointer = (bcos::cppsdk::amop::AMOPInterface*)amop;
    amopPointer->broadcast(std::string(topic), bytesConstRef((byte*)data, size));
}

void bcos_amop_set_subscribe_topic_cb(void* amop, bcos_sdk_c_amop_subscribe_cb cb, void* context)
{
    if (!context || !cb)
    {
        return;
    }

    auto amopPointer = (bcos::cppsdk::amop::AMOPInterface*)amop;
    amopPointer->setSubCallback(
        [context, cb](Error::Ptr error, const std::string& endpoint, const std::string& seq,
            bytesConstRef data, std::shared_ptr<bcos::boostssl::ws::WsSession> session) {
            std::ignore = session;
            // create resp obj
            bcos_sdk_c_struct_response resp;
            resp.context = context;
            if (error && error->errorCode() != CommonError::SUCCESS)
            {
                resp.error = error->errorCode();
                resp.desc = (char*)error->errorMessage().data();
            }
            else
            {
                resp.error = CommonError::SUCCESS;
                resp.data = (void*)data.data();
                resp.size = data.size();
            }

            // callback
            cb(endpoint.c_str(), seq.c_str(), &resp);
        });
}

void bcos_amop_send_response(void* amop, const char* peer, const char* seq, void* data, size_t size)
{
    if (!seq || !peer || !data || !size)
    {
        return;
    }

    auto amopPointer = (bcos::cppsdk::amop::AMOPInterface*)amop;
    amopPointer->sendResponse(
        std::string(peer), std::string(seq), bytesConstRef((byte*)data, size));
}

void* bcos_amop_get_ws(void* amop)
{
    if (amop)
    {
        auto amopPointer = (bcos::cppsdk::amop::AMOP*)amop;
        auto ws = amopPointer->service();
        return ws ? ws.get() : NULL;
    }
    return NULL;
}

// ------------------------------amop interface end -------------------------