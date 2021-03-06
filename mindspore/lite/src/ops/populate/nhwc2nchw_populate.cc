/**
 * Copyright 2020 Huawei Technologies Co., Ltd
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "src/ops/primitive_c.h"
#include "src/ops/populate/populate_register.h"
#include "src/common/common.h"
#include "nnacl/transpose.h"

namespace mindspore {
namespace lite {

OpParameter *PopulateNhwc2NchwParameter(const mindspore::lite::PrimitiveC *primitive) {
  TransposeParameter *parameter = reinterpret_cast<TransposeParameter *>(malloc(sizeof(TransposeParameter)));
  if (parameter == nullptr) {
    MS_LOG(ERROR) << "malloc OpParameter failed.";
    return nullptr;
  }
  memset(parameter, 0, sizeof(OpParameter));
  parameter->op_parameter_.type_ = primitive->Type();
  parameter->num_axes_ = 4;
  parameter->perm_[0] = 0;
  parameter->perm_[1] = 3;
  parameter->perm_[2] = 1;
  parameter->perm_[3] = 2;
  return reinterpret_cast<OpParameter *>(parameter);
}

Registry Nhwc2NchwParameterRegistry(schema::PrimitiveType_Nhwc2Nchw, PopulateNhwc2NchwParameter);

}  // namespace lite
}  // namespace mindspore
