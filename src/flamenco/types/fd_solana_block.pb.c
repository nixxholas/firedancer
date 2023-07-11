/* Automatically generated nanopb constant definitions */
/* Generated by nanopb-0.4.8-dev */

#include "fd_solana_block.pb.h"
#if PB_PROTO_HEADER_VERSION != 40
#error Regenerate this file with the current version of nanopb generator.
#endif

PB_BIND(fd_solblock_MessageHeader, fd_solblock_MessageHeader, AUTO)


PB_BIND(fd_solblock_Instruction, fd_solblock_Instruction, AUTO)


PB_BIND(fd_solblock_MessageAddressTableLookup, fd_solblock_MessageAddressTableLookup, AUTO)


PB_BIND(fd_solblock_Message, fd_solblock_Message, AUTO)


PB_BIND(fd_solblock_Transaction, fd_solblock_Transaction, AUTO)


PB_BIND(fd_solblock_ConfirmedTransaction, fd_solblock_ConfirmedTransaction, 2)


PB_BIND(fd_solblock_InnerInstruction, fd_solblock_InnerInstruction, AUTO)


PB_BIND(fd_solblock_InnerInstructions, fd_solblock_InnerInstructions, AUTO)


PB_BIND(fd_solblock_TransactionError, fd_solblock_TransactionError, AUTO)


PB_BIND(fd_solblock_UiTokenAmount, fd_solblock_UiTokenAmount, AUTO)


PB_BIND(fd_solblock_TokenBalance, fd_solblock_TokenBalance, AUTO)


PB_BIND(fd_solblock_Reward, fd_solblock_Reward, AUTO)


PB_BIND(fd_solblock_ReturnData, fd_solblock_ReturnData, AUTO)


PB_BIND(fd_solblock_TransactionStatusMeta, fd_solblock_TransactionStatusMeta, 2)




#ifndef PB_CONVERT_DOUBLE_FLOAT
/* On some platforms (such as AVR), double is really float.
 * To be able to encode/decode double on these platforms, you need.
 * to define PB_CONVERT_DOUBLE_FLOAT in pb.h or compiler command line.
 */
PB_STATIC_ASSERT(sizeof(double) == 8, DOUBLE_MUST_BE_8_BYTES)
#endif

