#include "bcos_sdk_c_common.h"
#include <bcos-framework/interfaces/protocol/CommonError.h>
#include <bcos-framework/libutilities/Common.h>
#include <bcos-framework/libutilities/Error.h>

void bcos_rpc_handle_response(void *error, void *resp, rpc_callback callback,
                              void *context) {
  auto rpcRespObj = new rpcResponse();
  rpcRespObj->context = context;

  auto errorPtr = (bcos::Error *)error;
  auto bytesPtr = (bcos::bytes *)resp;

  if (errorPtr &&
      errorPtr->errorCode() != bcos::protocol::CommonError::SUCCESS) {
    rpcRespObj->error = errorPtr->errorCode();
    rpcRespObj->error_msg = (char *)errorPtr->errorMessage().data();
  } else {
    rpcRespObj->error = bcos::protocol::CommonError::SUCCESS;
    rpcRespObj->msg = bytesPtr->data();
    rpcRespObj->size = bytesPtr->size();
  }

  callback(rpcRespObj);
}

// release rpcResponse object
void bcos_rpc_destroy_response(void *p) { delete (rpcResponse *)p; }
