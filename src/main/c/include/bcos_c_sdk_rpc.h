#ifndef __INCLUDE_BCOS_SDK_RPC__
#define __INCLUDE_BCOS_SDK_RPC__

#include "bcos_c_sdk_common.h"

#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

// ------------------------common send message interface begin----------------
// send message to rpc server
void bcos_rpc_send_msg(void *rpc, const char *data, rpc_callback callback,
                       void *context);

// send message to group
void bcos_rpc_send_msg_to_group(void *rpc, const char *group, const char *data,
                                rpc_callback callback, void *context);

// send message to group of node
void bcos_rpc_send_msg_to_group_node(void *rpc, const char *group,
                                     const char *node, const char *data,
                                     rpc_callback callback, void *context);
// ------------------------common send message interface end----------------

// ------------------------------rpc interface begin -------------------------
// call
void bcos_rpc_call(void *rpc, const char *group, const char *to,
                   const char *data, rpc_callback callback, void *context);

// sendTransaction
void bcos_rpc_send_transaction(void *rpc, const char *group, const char *data,
                               bool proof, rpc_callback callback,
                               void *context);

// getTransaction
void bcos_rpc_get_transaction(void *rpc, const char *group, const char *tx_hash,
                              bool proof, rpc_callback callback, void *context);

// getTransactionReceipt
void bcos_rpc_get_transaction_receipt(void *rpc, const char *group,
                                      const char *tx_hash, bool proof,
                                      rpc_callback callback, void *context);

// getBlockByHash
void bcos_rpc_get_block_by_hash(void *rpc, const char *group,
                                const char *block_hash, bool only_header,
                                bool only_tx_hash, rpc_callback callback,
                                void *context);

// getBlockByNumber
void bcos_rpc_get_block_by_number(void *rpc, const char *group,
                                  int64_t block_number, bool only_header,
                                  bool only_tx_hash, rpc_callback callback,
                                  void *context);

// getBlockHashByNumber
void bcos_rpc_get_block_hash_by_number(void *rpc, const char *group,
                                       int64_t block_number,
                                       rpc_callback callback, void *context);
// getBlockNumber
void bcos_rpc_get_block_number(void *rpc, const char *group,
                               rpc_callback callback, void *context);

// getCode
void bcos_rpc_get_code(void *rpc, const char *group, const char *address,
                       rpc_callback callback, void *context);

// getSealerList
void bcos_rpc_get_sealer_list(void *rpc, const char *group,
                              rpc_callback callback, void *context);

// getObserverList
void bcos_rpc_get_observer_list(void *rpc, const char *group,
                                rpc_callback callback, void *context);

// getPbftView
void bcos_rpc_get_pbft_view(void *rpc, const char *group, rpc_callback callback,
                            void *context);

// getPendingTxSize
void bcos_rpc_get_pending_tx_size(void *rpc, const char *group,
                                  rpc_callback callback, void *context);

// getSyncStatus
void bcos_rpc_get_sync_status(void *rpc, const char *group,
                              rpc_callback callback, void *context);

// getConsensusStatus
void bcos_rpc_get_consensus_status(void *rpc, const char *group,
                                   rpc_callback callback, void *context);

// getSystemConfigByKey
void bcos_rpc_get_system_config_by_key(void *rpc, const char *group,
                                       const char *key, rpc_callback callback,
                                       void *context);

// getTotalTransactionCount
void bcos_rpc_get_total_transaction_count(void *rpc, const char *group,
                                          rpc_callback callback, void *context);

// getPeers
void bcos_rpc_get_peers(void *rpc, rpc_callback callback, void *context);

// createGroup
void bcos_rpc_create_group(void *rpc, const char *group_info,
                           rpc_callback callback, void *context);

// expandGroupNode
void bcos_rpc_expand_group_node(void *rpc, const char *group,
                                const char *node_info, rpc_callback callback,
                                void *context);

// removeGroup
void bcos_rpc_remove_group(void *rpc, const char *group, rpc_callback callback,
                           void *context);

// recoverGroupNode
void bcos_rpc_recover_group_node(void *rpc, const char *group, const char *node,
                                 rpc_callback callback, void *context);

// startNode
void bcos_rpc_start_node(void *rpc, const char *group, const char *node,
                         rpc_callback callback, void *context);

// stopNode
void bcos_rpc_stop_node(void *rpc, const char *group, const char *node,
                        rpc_callback callback, void *context);

// getGroupList
void bcos_rpc_get_group_list(void *rpc, rpc_callback callback, void *context);

// getGroupInfoList
void bcos_rpc_get_group_info_list(void *rpc, rpc_callback callback,
                                  void *context);

// getGroupInfo
void bcos_rpc_get_group_info(void *rpc, const char *group,
                             rpc_callback callback, void *context);

// getGroupInfo
void bcos_rpc_get_group_info(void *rpc, const char *group,
                             rpc_callback callback, void *context);

// getGroupNodeInfo
void bcos_rpc_get_group_node_info(void *rpc, const char *group,
                                  const char *node, rpc_callback callback,
                                  void *context);

// getNodeInfo // TODO: Temporary interface, should be removed in the end
void bcos_rpc_get_node_info(void *rpc, rpc_callback callback, void *context);

// ------------------------------rpc interface end -------------------------

#ifdef __cplusplus
}
#endif
#endif
