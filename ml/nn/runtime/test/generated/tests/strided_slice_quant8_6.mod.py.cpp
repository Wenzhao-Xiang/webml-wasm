// clang-format off
// Generated file (from: strided_slice_quant8_6.mod.py). Do not edit
#include "../../TestGenerated.h"

namespace strided_slice_quant8_6 {
// Generated strided_slice_quant8_6 test
#include "generated/examples/strided_slice_quant8_6.example.cpp"
// Generated model constructor
#include "generated/models/strided_slice_quant8_6.model.cpp"
} // namespace strided_slice_quant8_6

TEST_F(GeneratedTests, strided_slice_quant8_6) {
    execute(strided_slice_quant8_6::CreateModel,
            strided_slice_quant8_6::is_ignored,
            strided_slice_quant8_6::examples);
}

