#include "bcos_sdk_c.h"
#include "bcos_sdk_c_error.h"
#include <bcos-boostssl/context/ContextBuilder.h>
#include <bcos-boostssl/utilities/BoostLog.h>
#include <bcos-boostssl/websocket/WsService.h>
#include <bcos-cpp-sdk/SdkFactory.h>
#include <cstdio>
#include <exception>
#include <memory>
#include <mutex>

// c-style sdk obj
struct Sdk
{
    std::shared_ptr<bcos::cppsdk::service::Service> service;
    void* rpc;
    void* amop;
    void* event;
};

// construct WsConfig obj by struct Config
static std::shared_ptr<bcos::boostssl::ws::WsConfig> initWsConfig(struct bcos_sdk_c_config* config)
{
    // init WsConfig by c Config
    auto wsConfig = std::make_shared<bcos::boostssl::ws::WsConfig>();
    wsConfig->setModel(bcos::boostssl::ws::WsModel::Client);

    auto peers = std::make_shared<bcos::boostssl::ws::EndPoints>();
    for (size_t i = 0; i < config->peers_count; i++)
    {
        bcos::boostssl::ws::EndPoint ep;
        ep.host = config->peers[i].host;
        ep.port = config->peers[i].port;
        peers->push_back(ep);
    }

    wsConfig->setConnectedPeers(peers);
    wsConfig->setDisableSsl(config->disableSsl);
    wsConfig->setThreadPoolSize(config->thread_pool_size);
    wsConfig->setReconnectPeriod(config->reconnect_period_ms);
    wsConfig->setHeartbeatPeriod(config->heartbeat_period_ms);
    wsConfig->setSendMsgTimeout(config->message_timeout_ms);

    if (!config->disableSsl)
    {
        auto contextConfig = std::make_shared<bcos::boostssl::context::ContextConfig>();
        contextConfig->setSslType(config->ssl_type);
        contextConfig->setIsCertPath(false);

        if (contextConfig->sslType() != "sm_ssl")
        {
            bcos::boostssl::context::ContextConfig::CertConfig certConfig;
            certConfig.caCert = config->cert_config->ca_cert;
            certConfig.nodeCert = config->cert_config->node_cert;
            certConfig.nodeKey = config->cert_config->node_key;
            contextConfig->setCertConfig(certConfig);
        }
        else
        {
            bcos::boostssl::context::ContextConfig::SMCertConfig smCertConfig;
            smCertConfig.caCert = config->sm_cert_config->ca_cert;
            smCertConfig.nodeKey = config->sm_cert_config->node_key;
            smCertConfig.nodeCert = config->sm_cert_config->node_cert;
            smCertConfig.enNodeCert = config->sm_cert_config->en_node_cert;
            smCertConfig.enNodeKey = config->sm_cert_config->en_node_key;
            contextConfig->setSmCertConfig(smCertConfig);
        }
        wsConfig->setContextConfig(contextConfig);
    }

    return wsConfig;
}

// create bcos sdk object by config
void* bcos_sdk_create(struct bcos_sdk_c_config* config)
{
    bcos_sdk_clear_last_error();
    try
    {
        // construct sdk object
        auto factory = std::make_shared<bcos::cppsdk::SdkFactory>();
        factory->setConfig(initWsConfig(config));

        auto sdk = new Sdk();
        auto service = factory->buildService();
        sdk->service = service;

        auto rpc = factory->buildJsonRpc(service);
        auto rpcPointer = rpc.release();

        auto amop = factory->buildAMOP(service);
        auto amopPointer = amop.release();

        auto event = factory->buildEventSub(service);
        auto eventPointer = event.release();

        sdk->rpc = (void*)rpcPointer;
        sdk->amop = (void*)amopPointer;
        sdk->event = (void*)eventPointer;

        return sdk;
    }
    catch (const std::exception& e)
    {
        auto&& msg = boost::diagnostic_information(e);
        BCOS_LOG(ERROR) << LOG_BADGE("bcos_sdk_create") << LOG_KV("error msg", msg);
        bcos_sdk_set_last_error_msg(-1, msg.c_str());
    }

    return NULL;
}

// destroy the bcos sdk object
void bcos_sdk_destroy(void* sdk)
{
    if (sdk)
    {
        auto rpcPointer = (bcos::cppsdk::jsonrpc::JsonRpcInterface*)(((Sdk*)sdk)->rpc);
        auto amopPointer = (bcos::cppsdk::amop::AMOPInterface*)(((Sdk*)sdk)->amop);
        auto eventPointer = (bcos::cppsdk::event::EventSubInterface*)(((Sdk*)sdk)->event);

        delete rpcPointer;
        delete amopPointer;
        delete eventPointer;

        // delete Sdk object
        delete (Sdk*)sdk;
    }
}

// create bcos sdk rpc object by sdk
void* bcos_sdk_get_rpc(void* sdk)
{
    if (sdk)
    {
        return ((Sdk*)sdk)->rpc;
    }

    return NULL;
}

// create bcos sdk event sub object by sdk
void* bcos_sdk_get_event_sub(void* sdk)
{
    if (sdk)
    {
        return ((Sdk*)sdk)->event;
    }

    return NULL;
}

// create bcos sdk amop object by sdk
void* bcos_sdk_get_amop(void* sdk)
{
    if (sdk)
    {
        return ((Sdk*)sdk)->amop;
    }

    return NULL;
}

void* bcos_sdk_create_rpc_by_config(struct bcos_sdk_c_config* config)
{
    bcos_sdk_clear_last_error();
    try
    {
        auto wsConfig = initWsConfig(config);

        // construct sdk object
        auto factory = std::make_shared<bcos::cppsdk::SdkFactory>();
        factory->setConfig(wsConfig);

        auto wsService = factory->buildService();
        auto rpc = factory->buildJsonRpc(wsService);

        auto rpcPointer = rpc.release();
        return rpcPointer;
    }
    catch (const std::exception& e)
    {
        auto&& msg = boost::diagnostic_information(e);
        BCOS_LOG(ERROR) << LOG_BADGE("bcos_sdk_create_rpc_by_config") << LOG_KV("error msg", msg);
        bcos_sdk_set_last_error_msg(-1, msg.c_str());
    }

    return NULL;
}

// destroy the bcos sdk rpc sdk object
void bcos_sdk_destroy_rpc(void* rpc)
{
    // stop rpc service and delete rpc object
    if (rpc)
    {
        auto rpcPointer = (bcos::cppsdk::jsonrpc::JsonRpcInterface*)rpc;
        rpcPointer->stop();
        delete rpcPointer;
        rpc = NULL;
    }
}

// start the rpc service
void bcos_sdk_start_rpc(void* rpc)
{
    bcos_sdk_clear_last_error();
    try
    {
        auto rpcPointer = (bcos::cppsdk::jsonrpc::JsonRpcInterface*)rpc;
        rpcPointer->start();
    }
    catch (const std::exception& e)
    {
        auto&& msg = boost::diagnostic_information(e);
        BCOS_LOG(ERROR) << LOG_BADGE("bcos_sdk_start_rpc") << LOG_KV("error msg", msg);
        bcos_sdk_set_last_error_msg(-1, msg.c_str());
    }
}

// stop the rpc service
void bcos_sdk_stop_rpc(void* rpc)
{
    if (rpc)
    {
        auto rpcPointer = (bcos::cppsdk::jsonrpc::JsonRpcInterface*)rpc;
        rpcPointer->stop();
    }
}

// create bcos sdk amop object by config
void* bcos_sdk_create_amop_by_config(struct bcos_sdk_c_config* config)
{
    bcos_sdk_clear_last_error();
    try
    {
        auto wsConfig = initWsConfig(config);

        // construct sdk object
        auto factory = std::make_shared<bcos::cppsdk::SdkFactory>();
        factory->setConfig(wsConfig);

        auto wsService = factory->buildService();
        auto amop = factory->buildAMOP(wsService);

        auto amopPointer = amop.release();
        return amopPointer;
    }
    catch (const std::exception& e)
    {
        auto&& msg = boost::diagnostic_information(e);
        BCOS_LOG(ERROR) << LOG_BADGE("bcos_sdk_create_amop_by_config") << LOG_KV("error msg", msg);
        bcos_sdk_set_last_error_msg(-1, msg.c_str());
    }

    return NULL;
}

// destroy the bcos sdk amop object
void bcos_sdk_destroy_amop(void* amop)
{
    // stop amop service and delete amop object
    if (amop)
    {
        auto amopPointer = (bcos::cppsdk::amop::AMOPInterface*)amop;
        amopPointer->stop();
        delete amopPointer;
        amop = NULL;
    }
}

// start the amop service
void bcos_sdk_start_amop(void* amop)
{
    bcos_sdk_clear_last_error();
    try
    {
        auto amopPointer = (bcos::cppsdk::amop::AMOPInterface*)amop;
        amopPointer->start();
    }
    catch (const std::exception& e)
    {
        auto&& msg = boost::diagnostic_information(e);
        BCOS_LOG(ERROR) << LOG_BADGE("bcos_sdk_start_amop") << LOG_KV("error msg", msg);
        bcos_sdk_set_last_error_msg(-1, msg.c_str());
    }
}

// stop the amop service
void bcos_sdk_stop_amop(void* amop)
{
    if (amop)
    {
        auto amopPointer = (bcos::cppsdk::amop::AMOPInterface*)amop;
        amopPointer->stop();
    }
}

// create bcos sdk event sub object by config
void* bcos_sdk_create_event_sub_by_config(struct bcos_sdk_c_config* config)
{
    bcos_sdk_clear_last_error();
    try
    {
        auto wsConfig = initWsConfig(config);

        // construct sdk object
        auto factory = std::make_shared<bcos::cppsdk::SdkFactory>();
        factory->setConfig(wsConfig);

        auto wsService = factory->buildService();
        auto event = factory->buildEventSub(wsService);

        auto eventPointer = event.release();
        return eventPointer;
    }
    catch (const std::exception& e)
    {
        auto&& msg = boost::diagnostic_information(e);
        BCOS_LOG(ERROR) << LOG_BADGE("bcos_sdk_create_event_sub_by_config")
                        << LOG_KV("error msg", msg);
        bcos_sdk_set_last_error_msg(-1, msg.c_str());
    }

    return NULL;
}


// destroy the bcos sdk event sub object
void bcos_sdk_destroy_event_sub(void* event)
{
    // stop event sub service and delete event sub object
    if (event)
    {
        auto eventPointer = (bcos::cppsdk::event::EventSubInterface*)event;
        eventPointer->stop();
        delete eventPointer;
        event = NULL;
    }
}

// start the event sub service
void bcos_sdk_start_event_sub(void* event)
{
    bcos_sdk_clear_last_error();
    try
    {
        auto eventPointer = (bcos::cppsdk::event::EventSubInterface*)event;
        eventPointer->start();
    }
    catch (const std::exception& e)
    {
        auto&& msg = boost::diagnostic_information(e);
        BCOS_LOG(ERROR) << LOG_BADGE("bcos_sdk_start_event_sub") << LOG_KV("error msg", msg);
        bcos_sdk_set_last_error_msg(-1, msg.c_str());
    }
}

// stop the event sub service
void bcos_sdk_stop_event_sub(void* event)
{
    if (event)
    {
        auto eventPointer = (bcos::cppsdk::event::EventSubInterface*)event;
        eventPointer->stop();
    }
}