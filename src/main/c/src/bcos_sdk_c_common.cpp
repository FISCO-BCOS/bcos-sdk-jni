#include "bcos_sdk_c_common.h"
#include <bcos-framework/interfaces/protocol/CommonError.h>
#include <bcos-framework/libutilities/Common.h>
#include <bcos-framework/libutilities/Error.h>

void bcos_rpc_handle_response(void *error, void *resp, size_t resp_size,
                              rpc_callback callback, void *context) {
  auto rpcRespObj = new rpcResponse();
  rpcRespObj->context = context;

  auto errorPtr = (bcos::Error *)error;
  if (errorPtr &&
      errorPtr->errorCode() != bcos::protocol::CommonError::SUCCESS) {
    rpcRespObj->error = errorPtr->errorCode();
    rpcRespObj->error_msg = (char *)errorPtr->errorMessage().data();
  } else {
    rpcRespObj->error = bcos::protocol::CommonError::SUCCESS;
    rpcRespObj->msg = (bcos::byte *)resp;
    rpcRespObj->size = resp_size;
  }

  callback(rpcRespObj);
}

// release rpcResponse object
void bcos_rpc_destroy_response(void *p) { delete (rpcResponse *)p; }
