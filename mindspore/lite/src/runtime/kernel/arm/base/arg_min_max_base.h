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

#ifndef MINDSPORE_LITE_SRC_RUNTIME_KERNEL_ARM_BASE_ARG_MIN_MAX_BASE_H_
#define MINDSPORE_LITE_SRC_RUNTIME_KERNEL_ARM_BASE_ARG_MIN_MAX_BASE_H_

#include <vector>
#include "src/lite_kernel.h"

namespace mindspore::kernel {
class ArgMinMaxBaseCPUKernel : public LiteKernel {
 public:
  ArgMinMaxBaseCPUKernel(OpParameter *parameter, const std::vector<lite::tensor::Tensor *> &inputs,
                         const std::vector<lite::tensor::Tensor *> &outputs, const lite::Context *ctx)
      : LiteKernel(parameter, inputs, outputs), context_(ctx), data_from_allocator_(false) {
    opParameter->thread_num_ = ctx->threadNum;
  }

  virtual ~ArgMinMaxBaseCPUKernel() {
    FreeTmpMemory();
  }

  int Init() override;

  int ReSize() override { return 0; }

  int Run() override;

  void FreeTmpMemory();
 private:
  const lite::Context *context_;
  bool data_from_allocator_;
};
}  // namespace mindspore::kernel

#endif  // MINDSPORE_LITE_SRC_RUNTIME_KERNEL_ARM_BASE_ARG_MIN_MAX_BASE_H_
