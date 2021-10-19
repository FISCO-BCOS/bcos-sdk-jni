#include "bcos_sdk_c_common.h"
#include <bcos-framework/interfaces/protocol/CommonError.h>
#include <bcos-framework/libutilities/Common.h>
#include <bcos-framework/libutilities/Error.h>


void bcos_sdk_c_cert_config_release(void* p)
{
    struct bcos_sdk_c_cert_config* config = (struct bcos_sdk_c_cert_config*)p;
    if (config && config->ca_cert)
    {
        free(config->ca_cert);
    }

    if (config && config->node_cert)
    {
        free(config->node_cert);
    }

    if (config && config->node_key)
    {
        free(config->node_key);
    }

    free(config);
}

void bcos_sdk_c_sm_cert_config_release(void* p)
{
    (void)p;
    // TODO:
}

struct bcos_sdk_c_config* bcos_sdk_c_config_new()
{
    struct bcos_sdk_c_config* config =
        (struct bcos_sdk_c_config*)malloc(sizeof(struct bcos_sdk_c_config));
    config->thread_pool_size = -1;
    config->message_timeout_ms = -1;
    config->heartbeat_period_ms = -1;
    config->reconnect_period_ms = -1;

    // TODO: init bcos_sdk_c_cert_config and bcos_sdk_c_sm_cert_config

    config->peers = NULL;
    config->peers_count = 0;

    return config;
}

void bcos_sdk_c_config_destroy(void* p)
{
    if (p)
    {
        return;
    }

    struct bcos_sdk_c_config* config = (struct bcos_sdk_c_config*)p;

    // TODO:  free bcos_sdk_c_cert_config and bcos_sdk_c_sm_cert_config
    if (config->peers && config->peers_count > 0)
    {
        for (size_t i = 0; i < config->peers_count; i++)
        {
            free((void*)config->peers[i].host);
        }
    }

    free((void*)config->peers);
    free((void*)config);
}


void bcos_sdk_c_handle_response(
    void* error, void* data, size_t size, bcos_sdk_struct_response_cb callback, void* context)
{
    // auto resp = new bcos_sdk_struct_response();
    bcos_sdk_struct_response temp_resp;
    auto resp = &temp_resp;
    resp->context = context;

    auto errorPtr = (bcos::Error*)error;
    if (errorPtr && errorPtr->errorCode() != bcos::protocol::CommonError::SUCCESS)
    {
        resp->error = errorPtr->errorCode();
        resp->desc = (char*)errorPtr->errorMessage().data();
    }
    else
    {
        resp->error = bcos::protocol::CommonError::SUCCESS;
        resp->data = (bcos::byte*)data;
        resp->size = size;
    }

    callback(resp);
}

// release bcos_sdk_struct_response object
void bcos_sdk_c_release_response(void* p)
{
    (void)p;
    return;
    // delete (bcos_sdk_struct_response *)p;
}
