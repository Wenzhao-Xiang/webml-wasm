// clang-format off
// Generated file (from: strided_slice_float_3_relaxed.mod.py). Do not edit
#include "../../TestGenerated.h"

namespace strided_slice_float_3_relaxed {
// Generated strided_slice_float_3_relaxed test
#include "generated/examples/strided_slice_float_3_relaxed.example.cpp"
// Generated model constructor
#include "generated/models/strided_slice_float_3_relaxed.model.cpp"
} // namespace strided_slice_float_3_relaxed

TEST_F(GeneratedTests, strided_slice_float_3_relaxed) {
    execute(strided_slice_float_3_relaxed::CreateModel,
            strided_slice_float_3_relaxed::is_ignored,
            strided_slice_float_3_relaxed::examples);
}

