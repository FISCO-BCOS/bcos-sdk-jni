#ifndef __INCLUDE_BCOS_SDK_CONFIG__
#define __INCLUDE_BCOS_SDK_CONFIG__

#include <stdint.h>
#include <stdio.h>

//--------------- config items begin ----------------

// connect endpoint
struct EndPoint {
  char *host; // c-style string，end with '\0'
  uint16_t port;
};

// ssl config
struct CertConfig {
  char *ca_cert; // Note: buffer of cert should be in der format

  char *node_key;
  char *node_cert;
};

// sm ssl config
struct SMCertConfig {
  char *ca_cert;

  char *node_key;
  char *node_cert;

  char *en_node_key;
  char *en_node_cert;
};

// config for bcos-c-sdk
struct Config {

  // common config
  int thread_pool_size;
  int reconnect_period_ms;
  int heartbeat_period_ms;
  int message_timeout_ms;

  // ssl type: ssl or sm
  int ssl_type;
  struct CertConfig cert_config;
  struct SMCertConfig sm_cert_config;

  // connected peers info
  struct EndPoint *peers;
  size_t peers_count;
};
//--------------- config items end ----------------

//--------------- callback define begin------------
// response
struct rpcResponse {
  int error;       // error code
  char *error_msg; // error message

  void *msg;
  size_t size;

  void *context; // callback context
};

typedef void (*rpc_callback)(struct rpcResponse *);
//--------------- callback define end------------

// handle callback
void bcos_rpc_handle_response(void *error, void *resp, rpc_callback callback,
                              void *context);
// release rpcResponse object
void bcos_rpc_destroy_response(void *p);

#endif
