/*
 * Copyright (C) 2017 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ANDROID_ML_NN_COMMON_UTILS_H
#define ANDROID_ML_NN_COMMON_UTILS_H

#ifdef EMSCRIPTEN
#define __wur
#include <stdint.h>
#include "tensorflow/core/platform/default/logging.h"
enum class FusedActivationFunc : int32_t {
    NONE = 0,
    RELU = 1,
    RELU1 = 2,
    RELU6 = 3,
};
enum class OperandType : int32_t {
    FLOAT32 = 0,
    INT32 = 1,
    UINT32 = 2,
    TENSOR_FLOAT32 = 3,
    TENSOR_INT32 = 4,
    TENSOR_QUANT8_ASYMM = 5,
    OEM = 10000,
    TENSOR_OEM_BYTE = 10001,
};
enum class OperationType : int32_t {
    ADD = 0,
    AVERAGE_POOL_2D = 1,
    CONCATENATION = 2,
    CONV_2D = 3,
    DEPTHWISE_CONV_2D = 4,
    DEPTH_TO_SPACE = 5,
    DEQUANTIZE = 6,
    EMBEDDING_LOOKUP = 7,
    FLOOR = 8,
    FULLY_CONNECTED = 9,
    HASHTABLE_LOOKUP = 10,
    L2_NORMALIZATION = 11,
    L2_POOL_2D = 12,
    LOCAL_RESPONSE_NORMALIZATION = 13,
    LOGISTIC = 14,
    LSH_PROJECTION = 15,
    LSTM = 16,
    MAX_POOL_2D = 17,
    MUL = 18,
    RELU = 19,
    RELU1 = 20,
    RELU6 = 21,
    RESHAPE = 22,
    RESIZE_BILINEAR = 23,
    RNN = 24,
    SOFTMAX = 25,
    SPACE_TO_DEPTH = 26,
    SVDF = 27,
    TANH = 28,
    OEM_OPERATION = 10000,
};
#define ERROR 1
#include <iostream>
#define LOG(x) std::cout
#endif

#ifndef EMSCRIPTEN
#include "HalInterfaces.h"
//#endif
#include "NeuralNetworks.h"
//#ifndef EMSCRIPTEN
#include "ValidateHal.h"
#endif

#ifndef EMSCRIPTEN
#include <android-base/logging.h>
#endif
#include <vector>

namespace android {
namespace nn {

// The number of data types (OperandCode) defined in NeuralNetworks.h.
const int kNumberOfDataTypes = 9;

// The number of operation types (OperationCode) defined in NeuralNetworks.h.
const int kNumberOfOperationTypes = 90;

// The number of execution preferences defined in NeuralNetworks.h.
const int kNumberOfPreferences = 3;

// The number of data types (OperandCode) defined in NeuralNetworksOEM.h.
const int kNumberOfDataTypesOEM = 2;

// The number of operation types (OperationCode) defined in NeuralNetworksOEM.h.
const int kNumberOfOperationTypesOEM = 1;

// The lowest number assigned to any OEM Code in NeuralNetworksOEM.h.
const int kOEMCodeBase = 10000;

/* IMPORTANT: if you change the following list, don't
 * forget to update the corresponding 'tags' table in
 * the initVlogMask() function implemented in Utils.cpp.
 */
enum VLogFlags {
    MODEL = 0,
    COMPILATION,
    EXECUTION,
    CPUEXE,
    MANAGER,
    DRIVER
};

#define VLOG_IS_ON(TAG) \
    ((vLogMask & (1 << (TAG))) != 0)

#define VLOG(TAG)         \
    if (LIKELY(!VLOG_IS_ON(TAG))) \
        ;                 \
    else                  \
        LOG(INFO)

extern int vLogMask;
void initVLogMask();

#ifdef NN_DEBUGGABLE
#define SHOW_IF_DEBUG(msg) msg
#else
#define SHOW_IF_DEBUG(msg) ""
#endif

// DEPRECATED(b/118737105). Use CHECK.
#define nnAssert(v) CHECK(v)

// Returns the amount of space needed to store a value of the specified
// dimensions and type.
uint32_t sizeOfData(OperandType type, const std::vector<uint32_t>& dimensions);

#ifndef EMSCRIPTEN
// Returns the amount of space needed to store a value of the dimensions and
// type of this operand.
inline uint32_t sizeOfData(const Operand& operand) {
    return sizeOfData(operand.type, operand.dimensions);
}
#endif
// Returns the name of the operation type in ASCII.
const char* getOperationName(OperationType opCode);

// Returns the name of the operand type in ASCII.
const char* getOperandTypeName(OperandType type);

#ifndef EMSCRIPTEN
// Memory is unmapped.
// Memory is reference counted by hidl_memory instances, and is deallocated
// once there are no more references.
hidl_memory allocateSharedMemory(int64_t size);
#endif

// Returns the number of padding bytes needed to align data of the
// specified length.  It aligns object of length:
// 2, 3 on a 2 byte boundary,
// 4+ on a 4 byte boundary.
// We may want to have different alignments for tensors.
// TODO: This is arbitrary, more a proof of concept.  We need
// to determine what this should be.
uint32_t alignBytesNeeded(uint32_t index, size_t length);

#ifndef EMSCRIPTEN
// Does a detailed LOG(INFO) of the model
void logModelToInfo(const V1_0::Model& model);
void logModelToInfo(const V1_1::Model& model);
void logModelToInfo(const V1_2::Model& model);
#endif

inline std::string toString(uint32_t obj) {
    return std::to_string(obj);
}

template <typename Type>
std::string toString(const std::vector<Type>& range) {
    std::string os = "[";
    for (size_t i = 0; i < range.size(); ++i) {
        os += (i == 0 ? "" : ", ") + toString(range[i]);
    }
    return os += "]";
}

inline bool validCode(uint32_t codeCount, uint32_t codeCountOEM, uint32_t code) {
    return (code < codeCount) || (code >= kOEMCodeBase && (code - kOEMCodeBase) < codeCountOEM);
}
#ifndef EMSCRIPTEN
int validateOperandType(const ANeuralNetworksOperandType& type, const char* tag, bool allowPartial);
#endif
int validateOperandList(uint32_t count, const uint32_t* list, uint32_t operandCount,
                        const char* tag);

#ifndef EMSCRIPTEN
// Typename substitutes are contained in the cpp file.
int validateOperation(ANeuralNetworksOperationType opType, uint32_t inputCount,
                      const uint32_t* inputIndexes, uint32_t outputCount,
                      const uint32_t* outputIndexes, const std::vector<Operand>& operands,
                      HalVersion* minSupportedHalVersion);

inline int validateOperation(ANeuralNetworksOperationType opType, uint32_t inputCount,
                             const uint32_t* inputIndexes, uint32_t outputCount,
                             const uint32_t* outputIndexes, const std::vector<Operand>& operands) {
    HalVersion minSupportedHalVersion;
    return validateOperation(opType, inputCount, inputIndexes, outputCount, outputIndexes, operands,
                             &minSupportedHalVersion);
}
#endif
inline size_t getSizeFromInts(int lower, int higher) {
    return (uint32_t)(lower) + ((uint64_t)(uint32_t)(higher) << 32);
}

#ifndef EMSCRIPTEN
// Convert ANEURALNETWORKS_* result code to ErrorStatus.
// Not guaranteed to be a 1-to-1 mapping.
ErrorStatus convertResultCodeToErrorStatus(int resultCode);

// Convert ErrorStatus to ANEURALNETWORKS_* result code.
// Not guaranteed to be a 1-to-1 mapping.
int convertErrorStatusToResultCode(ErrorStatus status);

// Versioning

bool compliantWithV1_0(const V1_0::Capabilities& capabilities);
bool compliantWithV1_0(const V1_1::Capabilities& capabilities);
bool compliantWithV1_1(const V1_0::Capabilities& capabilities);
bool compliantWithV1_1(const V1_1::Capabilities& capabilities);

bool compliantWithV1_0(const V1_0::Model& model);
bool compliantWithV1_0(const V1_1::Model& model);
bool compliantWithV1_0(const V1_2::Model& model);
bool compliantWithV1_1(const V1_0::Model& model);
bool compliantWithV1_1(const V1_1::Model& model);
bool compliantWithV1_1(const V1_2::Model& model);

V1_0::Capabilities convertToV1_0(const V1_0::Capabilities& capabilities);
V1_0::Capabilities convertToV1_0(const V1_1::Capabilities& capabilities);
V1_1::Capabilities convertToV1_1(const V1_0::Capabilities& capabilities);
V1_1::Capabilities convertToV1_1(const V1_1::Capabilities& capabilities);

V1_0::Model convertToV1_0(const V1_0::Model& model);
V1_0::Model convertToV1_0(const V1_1::Model& model);
V1_0::Model convertToV1_0(const V1_2::Model& model);
V1_1::Model convertToV1_1(const V1_0::Model& model);
V1_1::Model convertToV1_1(const V1_1::Model& model);
V1_1::Model convertToV1_1(const V1_2::Model& model);
V1_2::Model convertToV1_2(const V1_0::Model& model);
V1_2::Model convertToV1_2(const V1_1::Model& model);

V1_2::Operand convertToV1_2(const V1_0::Operand& operand);
V1_2::Operand convertToV1_2(const V1_2::Operand& operand);

hidl_vec<V1_2::Operand> convertToV1_2(const hidl_vec<V1_0::Operand>& operands);
hidl_vec<V1_2::Operand> convertToV1_2(const hidl_vec<V1_2::Operand>& operands);
#endif

#ifdef NN_DEBUGGABLE
uint32_t getProp(const char* str, uint32_t defaultValue = 0);
#endif  // NN_DEBUGGABLE

}  // namespace nn
}  // namespace android

#endif  // ANDROID_ML_NN_COMMON_UTILS_H
