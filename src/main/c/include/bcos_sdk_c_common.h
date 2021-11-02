#ifndef __INCLUDE_BCOS_SDK_CONFIG__
#define __INCLUDE_BCOS_SDK_CONFIG__

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define _BCOS_SDK_JNI_DEBUG_

#ifdef __cplusplus
extern "C" {
#endif
/*
// sample: bcos_c_sdk.ini

[common]
    ; thread pool size for network send/receive/handle message
    thread_pool_size = 8
    ; timeout for send message(ms)
    message_timeout_ms = 10000

; ssl
[ssl]
    ; if ssl connection is disabled
    disable = false
    ; type: ssl or sm_ssl
    type = ssl
    ; directory the certificates located in
    ca_path=./conf
    ; the ca certificate file
    ca_cert=ca.crt
    ; the node private key file
    sdk_key=sdk.key
    ; the node certificate file
    sdk_cert=sdk.crt

; sm ssl
[ssl]
    ; if ssl connection is disabled
    disable = false
    ; type: ssl or sm_ssl
    type = sm_ssl
    ; directory the certificates located in
    ca_path=./conf
    ; the ca certificate file
    ca_cert=sm_ca.crt
    ; the node private key file
    sdk_key=sm_sdk.key
    ; the node certificate file
    sdk_cert=sm_sdk.crt
    ; the encrypt node private key file
    en_sdk_key=sm_en_sdk.key
    ; the encrypt node certificate file
    en_sdk_cert=sm_en_sdk.crt

; ipv4
[peers]
# ipv4
    node.0=127.0.0.1:30300
    node.1=127.0.0.1:30304
    node.2=127.0.0.1:30308
    node.3=127.0.0.1:30312

; ipv6
[peers]
    node.0=[::1]:30300
    node.1=[::1]:30304
    node.2=[::1]:30308
    node.3=[::1]:30312
*/

//--------------- config items begin ----------------

// connect endpoint
struct bcos_sdk_c_endpoint
{
    char* host;  // c-style string，end with '\0'
    uint16_t port;
};

// ssl config
struct bcos_sdk_c_cert_config
{
    char* ca_cert;  // Note: buffer of cert should be in pem format
    char* node_key;
    char* node_cert;
};

// sm ssl config
struct bcos_sdk_c_sm_cert_config
{
    char* ca_cert;
    char* node_key;
    char* node_cert;
    char* en_node_key;
    char* en_node_cert;
};

// config for bcos-c-sdk
struct bcos_sdk_c_config
{
    // common config
    int thread_pool_size;
    int message_timeout_ms;
    // int reconnect_period_ms;
    // int heartbeat_period_ms;

    // connected peers
    struct bcos_sdk_c_endpoint* peers;
    size_t peers_count;

    // the switch for disable ssl connection
    int disableSsl;

    // ssl type: ssl or sm_ssl
    int ssl_type;
    struct bcos_sdk_c_cert_config* cert_config;
    struct bcos_sdk_c_sm_cert_config* sm_cert_config;
};

struct bcos_sdk_c_config* bcos_sdk_c_config_create();
void bcos_sdk_c_config_destroy(void* p);

void bcos_sdk_c_cert_config_destroy(void* p);
void bcos_sdk_c_sm_cert_config_destroy(void* p);

//--------------- config items end ----------------

//--------------- callback begin------------
// response
struct bcos_sdk_c_struct_response
{
    int error;   // code
    char* desc;  // code describe message

    void* data;   // response data pointer
    size_t size;  // response data size

    void* context;  // callback context
};

typedef void (*bcos_sdk_c_struct_response_cb)(struct bcos_sdk_c_struct_response*);
//--------------- callback end------------

// handle callback
void bcos_sdk_c_handle_response(
    void* error, void* data, size_t size, bcos_sdk_c_struct_response_cb callback, void* context);

#ifdef __cplusplus
}
#endif
#endif
