#include "bcos_sdk_c_rpc.h"
#include <bcos-cpp-sdk/rpc/JsonRpcImpl.h>

#include <memory>
#include <tuple>

// ------------------------common send message interface begin----------------
// send message to rpc server
void bcos_rpc_generic_method_call(
    void* rpc, const char* data, bcos_sdk_c_struct_response_cb callback, void* context)
{
    auto rpcPointer = (bcos::cppsdk::jsonrpc::JsonRpcInterface*)rpc;

    rpcPointer->genericMethod(
        data, [callback, context](bcos::Error::Ptr error, std::shared_ptr<bcos::bytes> resp) {
            bcos_sdk_c_handle_response(error ? error.get() : NULL,
                resp ? (void*)resp->data() : NULL, resp ? resp->size() : 0, callback, context);
        });
}

// send message to group
void bcos_rpc_generic_method_call_to_group(void* rpc, const char* group, const char* data,
    bcos_sdk_c_struct_response_cb callback, void* context)
{
    auto rpcPointer = (bcos::cppsdk::jsonrpc::JsonRpcInterface*)rpc;

    rpcPointer->genericMethod(group, data,
        [callback, context](bcos::Error::Ptr error, std::shared_ptr<bcos::bytes> resp) {
            bcos_sdk_c_handle_response(error ? error.get() : NULL,
                resp ? (void*)resp->data() : NULL, resp ? resp->size() : 0, callback, context);
        });
}

// send message to group of node
void bcos_rpc_generic_method_call_to_group_node(void* rpc, const char* group, const char* node,
    const char* data, bcos_sdk_c_struct_response_cb callback, void* context)
{
    auto rpcPointer = (bcos::cppsdk::jsonrpc::JsonRpcInterface*)rpc;

    rpcPointer->genericMethod(group, node ? node : "", data,
        [callback, context](bcos::Error::Ptr error, std::shared_ptr<bcos::bytes> resp) {
            bcos_sdk_c_handle_response(error ? error.get() : NULL,
                resp ? (void*)resp->data() : NULL, resp ? resp->size() : 0, callback, context);
        });
}
// ------------------------common send message interface end----------------

// ------------------------------rpc interface begin -------------------------
// call
void bcos_rpc_call(void* rpc, const char* group, const char* node, const char* to, const char* data,
    bcos_sdk_c_struct_response_cb callback, void* context)
{
    auto rpcPointer = (bcos::cppsdk::jsonrpc::JsonRpcInterface*)rpc;

    rpcPointer->call(group, node ? node : "", to, data,
        [callback, context](bcos::Error::Ptr error, std::shared_ptr<bcos::bytes> resp) {
            bcos_sdk_c_handle_response(error ? error.get() : NULL,
                resp ? (void*)resp->data() : NULL, resp ? resp->size() : 0, callback, context);
        });
}

// sendTransaction
void bcos_rpc_send_transaction(void* rpc, const char* group, const char* node, const char* data,
    int proof, bcos_sdk_c_struct_response_cb callback, void* context)
{
    auto rpcPointer = (bcos::cppsdk::jsonrpc::JsonRpcInterface*)rpc;

    rpcPointer->sendTransaction(group, node ? node : "", data, proof,
        [callback, context](bcos::Error::Ptr error, std::shared_ptr<bcos::bytes> resp) {
            bcos_sdk_c_handle_response(error ? error.get() : NULL,
                resp ? (void*)resp->data() : NULL, resp ? resp->size() : 0, callback, context);
        });
}

// getTransaction
void bcos_rpc_get_transaction(void* rpc, const char* group, const char* node, const char* tx_hash,
    int proof, bcos_sdk_c_struct_response_cb callback, void* context)
{
    auto rpcPointer = (bcos::cppsdk::jsonrpc::JsonRpcInterface*)rpc;

    rpcPointer->getTransaction(group, node ? node : "", tx_hash, proof,
        [callback, context](bcos::Error::Ptr error, std::shared_ptr<bcos::bytes> resp) {
            bcos_sdk_c_handle_response(error ? error.get() : NULL,
                resp ? (void*)resp->data() : NULL, resp ? resp->size() : 0, callback, context);
        });
}

// getTransactionReceipt
void bcos_rpc_get_transaction_receipt(void* rpc, const char* group, const char* node,
    const char* tx_hash, int proof, bcos_sdk_c_struct_response_cb callback, void* context)
{
    auto rpcPointer = (bcos::cppsdk::jsonrpc::JsonRpcInterface*)rpc;

    rpcPointer->getTransactionReceipt(group, node ? node : "", tx_hash, proof,
        [callback, context](bcos::Error::Ptr error, std::shared_ptr<bcos::bytes> resp) {
            bcos_sdk_c_handle_response(error ? error.get() : NULL,
                resp ? (void*)resp->data() : NULL, resp ? resp->size() : 0, callback, context);
        });
}

// getBlockByHash
void bcos_rpc_get_block_by_hash(void* rpc, const char* group, const char* node,
    const char* block_hash, int only_header, int only_tx_hash,
    bcos_sdk_c_struct_response_cb callback, void* context)
{
    auto rpcPointer = (bcos::cppsdk::jsonrpc::JsonRpcInterface*)rpc;

    rpcPointer->getBlockByHash(group, node ? node : "", block_hash, only_header, only_tx_hash,
        [callback, context](bcos::Error::Ptr error, std::shared_ptr<bcos::bytes> resp) {
            bcos_sdk_c_handle_response(error ? error.get() : NULL,
                resp ? (void*)resp->data() : NULL, resp ? resp->size() : 0, callback, context);
        });
}

// getBlockByNumber
void bcos_rpc_get_block_by_number(void* rpc, const char* group, const char* node,
    int64_t block_number, int only_header, int only_tx_hash, bcos_sdk_c_struct_response_cb callback,
    void* context)
{
    auto rpcPointer = (bcos::cppsdk::jsonrpc::JsonRpcInterface*)rpc;

    rpcPointer->getBlockByNumber(group, node ? node : "", block_number, only_header, only_tx_hash,
        [callback, context](bcos::Error::Ptr error, std::shared_ptr<bcos::bytes> resp) {
            bcos_sdk_c_handle_response(error ? error.get() : NULL,
                resp ? (void*)resp->data() : NULL, resp ? resp->size() : 0, callback, context);
        });
}

// getBlockHashByNumber
void bcos_rpc_get_block_hash_by_number(void* rpc, const char* group, const char* node,
    int64_t block_number, bcos_sdk_c_struct_response_cb callback, void* context)
{
    auto rpcPointer = (bcos::cppsdk::jsonrpc::JsonRpcInterface*)rpc;

    rpcPointer->getBlockHashByNumber(group, node ? node : "", block_number,
        [callback, context](bcos::Error::Ptr error, std::shared_ptr<bcos::bytes> resp) {
            bcos_sdk_c_handle_response(error ? error.get() : NULL,
                resp ? (void*)resp->data() : NULL, resp ? resp->size() : 0, callback, context);
        });
}
// getBlockNumber
void bcos_rpc_get_block_number(void* rpc, const char* group, const char* node,
    bcos_sdk_c_struct_response_cb callback, void* context)
{
    auto rpcPointer = (bcos::cppsdk::jsonrpc::JsonRpcInterface*)rpc;

    rpcPointer->getBlockNumber(group, node ? node : "",
        [callback, context](bcos::Error::Ptr error, std::shared_ptr<bcos::bytes> resp) {
            bcos_sdk_c_handle_response(error ? error.get() : NULL,
                resp ? (void*)resp->data() : NULL, resp ? resp->size() : 0, callback, context);
        });
}

// getCode
void bcos_rpc_get_code(void* rpc, const char* group, const char* node, const char* address,
    bcos_sdk_c_struct_response_cb callback, void* context)
{
    auto rpcPointer = (bcos::cppsdk::jsonrpc::JsonRpcInterface*)rpc;

    rpcPointer->getCode(group, node ? node : "", address,
        [callback, context](bcos::Error::Ptr error, std::shared_ptr<bcos::bytes> resp) {
            bcos_sdk_c_handle_response(error ? error.get() : NULL,
                resp ? (void*)resp->data() : NULL, resp ? resp->size() : 0, callback, context);
        });
}

// getSealerList
void bcos_rpc_get_sealer_list(void* rpc, const char* group, const char* node,
    bcos_sdk_c_struct_response_cb callback, void* context)
{
    auto rpcPointer = (bcos::cppsdk::jsonrpc::JsonRpcInterface*)rpc;

    rpcPointer->getSealerList(group, node ? node : "",
        [callback, context](bcos::Error::Ptr error, std::shared_ptr<bcos::bytes> resp) {
            bcos_sdk_c_handle_response(error ? error.get() : NULL,
                resp ? (void*)resp->data() : NULL, resp ? resp->size() : 0, callback, context);
        });
}

// getObserverList
void bcos_rpc_get_observer_list(void* rpc, const char* group, const char* node,
    bcos_sdk_c_struct_response_cb callback, void* context)
{
    auto rpcPointer = (bcos::cppsdk::jsonrpc::JsonRpcInterface*)rpc;

    rpcPointer->getObserverList(group, node ? node : "",
        [callback, context](bcos::Error::Ptr error, std::shared_ptr<bcos::bytes> resp) {
            bcos_sdk_c_handle_response(error ? error.get() : NULL,
                resp ? (void*)resp->data() : NULL, resp ? resp->size() : 0, callback, context);
        });
}

// getPbftView
void bcos_rpc_get_pbft_view(void* rpc, const char* group, const char* node,
    bcos_sdk_c_struct_response_cb callback, void* context)
{
    auto rpcPointer = (bcos::cppsdk::jsonrpc::JsonRpcInterface*)rpc;

    rpcPointer->getPbftView(group, node ? node : "",
        [callback, context](bcos::Error::Ptr error, std::shared_ptr<bcos::bytes> resp) {
            bcos_sdk_c_handle_response(error ? error.get() : NULL,
                resp ? (void*)resp->data() : NULL, resp ? resp->size() : 0, callback, context);
        });
}

// getPendingTxSize
void bcos_rpc_get_pending_tx_size(void* rpc, const char* group, const char* node,
    bcos_sdk_c_struct_response_cb callback, void* context)
{
    auto rpcPointer = (bcos::cppsdk::jsonrpc::JsonRpcInterface*)rpc;

    rpcPointer->getPendingTxSize(group, node ? node : "",
        [callback, context](bcos::Error::Ptr error, std::shared_ptr<bcos::bytes> resp) {
            bcos_sdk_c_handle_response(error ? error.get() : NULL,
                resp ? (void*)resp->data() : NULL, resp ? resp->size() : 0, callback, context);
        });
}

// getSyncStatus
void bcos_rpc_get_sync_status(void* rpc, const char* group, const char* node,
    bcos_sdk_c_struct_response_cb callback, void* context)
{
    auto rpcPointer = (bcos::cppsdk::jsonrpc::JsonRpcInterface*)rpc;

    rpcPointer->getSyncStatus(group, node ? node : "",
        [callback, context](bcos::Error::Ptr error, std::shared_ptr<bcos::bytes> resp) {
            bcos_sdk_c_handle_response(error ? error.get() : NULL,
                resp ? (void*)resp->data() : NULL, resp ? resp->size() : 0, callback, context);
        });
}

// getConsensusStatus
void bcos_rpc_get_consensus_status(void* rpc, const char* group, const char* node,
    bcos_sdk_c_struct_response_cb callback, void* context)
{
    auto rpcPointer = (bcos::cppsdk::jsonrpc::JsonRpcInterface*)rpc;

    rpcPointer->getConsensusStatus(group, node ? node : "",
        [callback, context](bcos::Error::Ptr error, std::shared_ptr<bcos::bytes> resp) {
            bcos_sdk_c_handle_response(error ? error.get() : NULL,
                resp ? (void*)resp->data() : NULL, resp ? resp->size() : 0, callback, context);
        });
}

// getSystemConfigByKey
void bcos_rpc_get_system_config_by_key(void* rpc, const char* group, const char* node,
    const char* key, bcos_sdk_c_struct_response_cb callback, void* context)
{
    auto rpcPointer = (bcos::cppsdk::jsonrpc::JsonRpcInterface*)rpc;

    rpcPointer->getSystemConfigByKey(group, node ? node : "", key,
        [callback, context](bcos::Error::Ptr error, std::shared_ptr<bcos::bytes> resp) {
            bcos_sdk_c_handle_response(error ? error.get() : NULL,
                resp ? (void*)resp->data() : NULL, resp ? resp->size() : 0, callback, context);
        });
}

// getTotalTransactionCount
void bcos_rpc_get_total_transaction_count(void* rpc, const char* group, const char* node,
    bcos_sdk_c_struct_response_cb callback, void* context)
{
    auto rpcPointer = (bcos::cppsdk::jsonrpc::JsonRpcInterface*)rpc;

    rpcPointer->getTotalTransactionCount(group, node ? node : "",
        [callback, context](bcos::Error::Ptr error, std::shared_ptr<bcos::bytes> resp) {
            bcos_sdk_c_handle_response(error ? error.get() : NULL,
                resp ? (void*)resp->data() : NULL, resp ? resp->size() : 0, callback, context);
        });
}

// getPeers
void bcos_rpc_get_peers(void* rpc, bcos_sdk_c_struct_response_cb callback, void* context)
{
    auto rpcPointer = (bcos::cppsdk::jsonrpc::JsonRpcInterface*)rpc;

    rpcPointer->getPeers(
        [callback, context](bcos::Error::Ptr error, std::shared_ptr<bcos::bytes> resp) {
            bcos_sdk_c_handle_response(error ? error.get() : NULL,
                resp ? (void*)resp->data() : NULL, resp ? resp->size() : 0, callback, context);
        });
}

// getGroupList
void bcos_rpc_get_group_list(void* rpc, bcos_sdk_c_struct_response_cb callback, void* context)
{
    auto rpcPointer = (bcos::cppsdk::jsonrpc::JsonRpcInterface*)rpc;

    rpcPointer->getGroupList(
        [callback, context](bcos::Error::Ptr error, std::shared_ptr<bcos::bytes> resp) {
            bcos_sdk_c_handle_response(error ? error.get() : NULL,
                resp ? (void*)resp->data() : NULL, resp ? resp->size() : 0, callback, context);
        });
}

// getGroupInfo
void bcos_rpc_get_group_info(
    void* rpc, const char* group, bcos_sdk_c_struct_response_cb callback, void* context)
{
    auto rpcPointer = (bcos::cppsdk::jsonrpc::JsonRpcInterface*)rpc;

    rpcPointer->getGroupInfo(
        group, [callback, context](bcos::Error::Ptr error, std::shared_ptr<bcos::bytes> resp) {
            bcos_sdk_c_handle_response(error ? error.get() : NULL,
                resp ? (void*)resp->data() : NULL, resp ? resp->size() : 0, callback, context);
        });
}

// getGroupInfoList
void bcos_rpc_get_group_info_list(void* rpc, bcos_sdk_c_struct_response_cb callback, void* context)
{
    auto rpcPointer = (bcos::cppsdk::jsonrpc::JsonRpcInterface*)rpc;

    rpcPointer->getGroupInfoList(
        [callback, context](bcos::Error::Ptr error, std::shared_ptr<bcos::bytes> resp) {
            bcos_sdk_c_handle_response(error ? error.get() : NULL,
                resp ? (void*)resp->data() : NULL, resp ? resp->size() : 0, callback, context);
        });
}

// getGroupNodeInfo
void bcos_rpc_get_group_node_info(void* rpc, const char* group, const char* node,
    bcos_sdk_c_struct_response_cb callback, void* context)
{
    auto rpcPointer = (bcos::cppsdk::jsonrpc::JsonRpcInterface*)rpc;

    rpcPointer->getGroupNodeInfo(group, node,
        [callback, context](bcos::Error::Ptr error, std::shared_ptr<bcos::bytes> resp) {
            bcos_sdk_c_handle_response(error ? error.get() : NULL,
                resp ? (void*)resp->data() : NULL, resp ? resp->size() : 0, callback, context);
        });
}

// ------------------------------rpc interface end -------------------------

void* bcos_rpc_get_ws(void* rpc)
{
    if (rpc)
    {
        auto rpcPointer = (bcos::cppsdk::jsonrpc::JsonRpcImpl*)rpc;
        auto ws = rpcPointer->service();
        return ws ? ws.get() : NULL;
    }

    return NULL;
}