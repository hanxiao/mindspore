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
#include <iostream>
#include "src/common/log_adapter.h"
#include "common/common_test.h"
#include "mindspore/lite/nnacl/fp32/instance_norm.h"
#include "mindspore/lite/src/kernel_registry.h"
#include "mindspore/lite/src/lite_kernel.h"

namespace mindspore {
class TestInstanceNormFp32 : public mindspore::CommonTest {
 public:
  TestInstanceNormFp32() {}
};

TEST_F(TestInstanceNormFp32, INTest1) {
  std::vector<float> in_data = {-11.18675,  11.433986,  11.386012, 11.245945,   -2.7614849, 14.692399,
                                -1.1983503, -6.6790967, 6.383416,  -13.3213005, -8.693595,  9.476344};
  std::vector<float> in_data1 = {12.352293, 5.122387, 14.249514};
  std::vector<float> in_data2 = {14.632595, 0.70900035, 11.179003};

  InstanceNormParameter op_param;
  op_param.op_parameter_.type_ = schema::PrimitiveType_InstanceNorm;
  op_param.epsilon_ = 0.001f;

  lite::Tensor input0_tensor(kNumberTypeFloat32, {1, 2, 2, 3});
  lite::Tensor input1_tensor(kNumberTypeFloat32, {3});
  lite::Tensor input2_tensor(kNumberTypeFloat32, {3});
  input0_tensor.set_data(in_data.data());
  input1_tensor.set_data(in_data1.data());
  input2_tensor.set_data(in_data2.data());
  std::vector<lite::Tensor *> inputs_tensor = {&input0_tensor, &input1_tensor, &input2_tensor};

  std::vector<float> output(12);
  std::vector<float> corr_out = {-6.1533737, 7.4904885,  -0.8563998, -0.289212,  -9.356432,  0.13245535,
                                 -3.5422924, -14.005781, -2.3525476, -6.7113695, -16.396551, -1.4275324};

  lite::Tensor output0_tensor(kNumberTypeFloat32, {1, 2, 2, 3});
  output0_tensor.set_data(output.data());
  std::vector<lite::Tensor *> outputs_tensor = {&output0_tensor};

  kernel::KernelKey desc = {kernel::KERNEL_ARCH::kCPU, kNumberTypeFloat32, schema::PrimitiveType_InstanceNorm};
  auto creator = lite::KernelRegistry::GetInstance()->GetCreator(desc);
  ASSERT_NE(creator, nullptr);
  lite::InnerContext ctx;
  ctx.thread_num_ = 4;
  ASSERT_EQ(lite::RET_OK, ctx.Init());
  kernel::LiteKernel *kernel =
    creator(inputs_tensor, outputs_tensor, reinterpret_cast<OpParameter *>(&op_param), &ctx, desc, nullptr);
  ASSERT_NE(kernel, nullptr);
  auto output_tensor_shape = output0_tensor.shape();
  kernel->Run();

  printf("==================output data=================\n");
  for (int i = 0; i < output0_tensor.ElementsNum(); i++) {
    std::cout << output[i] << " ,";
  }
  std::cout << std::endl;
  CompareOutputData(output.data(), corr_out.data(), output0_tensor.ElementsNum(), 0.001);

  input0_tensor.set_data(nullptr);
  input1_tensor.set_data(nullptr);
  input2_tensor.set_data(nullptr);
  output0_tensor.set_data(nullptr);
}

TEST_F(TestInstanceNormFp32, INTest2) {
  std::vector<float> in_data = {-11.18675,  11.433986,  11.386012, 11.245945,   -2.7614849, 14.692399,
                                -1.1983503, -6.6790967, 6.383416,  -13.3213005, -8.693595,  9.476344,
                                -11.18675,  11.433986,  11.386012, 11.245945,   -2.7614849, 14.692399,
                                -1.1983503, -6.6790967, 6.383416,  -13.3213005, -8.693595,  9.476344};
  std::vector<float> in_data1 = {12.352293, 5.122387, 14.249514, 12.352293, 5.122387, 14.249514};
  std::vector<float> in_data2 = {14.632595, 0.70900035, 11.179003, 14.632595, 0.70900035, 11.179003};

  InstanceNormParameter op_param;
  op_param.op_parameter_.type_ = schema::PrimitiveType_InstanceNorm;
  op_param.epsilon_ = 0.001f;

  lite::Tensor input0_tensor(kNumberTypeFloat32, {2, 2, 2, 3});
  lite::Tensor input1_tensor(kNumberTypeFloat32, {6});
  lite::Tensor input2_tensor(kNumberTypeFloat32, {6});
  input0_tensor.set_data(in_data.data());
  input1_tensor.set_data(in_data1.data());
  input2_tensor.set_data(in_data2.data());
  std::vector<lite::Tensor *> inputs_tensor = {&input0_tensor, &input1_tensor, &input2_tensor};

  std::vector<float> output(24);
  std::vector<float> corr_out = {-6.1533737, 7.4904885,  -0.8563998, -0.289212,  -9.356432,  0.13245535,
                                 -3.5422924, -14.005781, -2.3525476, -6.7113695, -16.396551, -1.4275324,
                                 -6.1533737, 7.4904885,  -0.8563998, -0.289212,  -9.356432,  0.13245535,
                                 -3.5422924, -14.005781, -2.3525476, -6.7113695, -16.396551, -1.4275324};

  lite::Tensor output0_tensor(kNumberTypeFloat32, {2, 2, 2, 3});
  output0_tensor.set_data(output.data());
  std::vector<lite::Tensor *> outputs_tensor = {&output0_tensor};

  kernel::KernelKey desc = {kernel::KERNEL_ARCH::kCPU, kNumberTypeFloat32, schema::PrimitiveType_InstanceNorm};
  auto creator = lite::KernelRegistry::GetInstance()->GetCreator(desc);
  ASSERT_NE(creator, nullptr);
  lite::InnerContext ctx;
  ctx.thread_num_ = 4;
  ASSERT_EQ(lite::RET_OK, ctx.Init());
  kernel::LiteKernel *kernel =
    creator(inputs_tensor, outputs_tensor, reinterpret_cast<OpParameter *>(&op_param), &ctx, desc, nullptr);
  ASSERT_NE(kernel, nullptr);
  auto output_tensor_shape = output0_tensor.shape();
  kernel->Run();

  printf("==================output data=================\n");
  for (int i = 0; i < output0_tensor.ElementsNum(); i++) {
    std::cout << output[i] << " ,";
  }
  std::cout << std::endl;
  CompareOutputData(output.data(), corr_out.data(), output0_tensor.ElementsNum(), 0.001);

  input0_tensor.set_data(nullptr);
  input1_tensor.set_data(nullptr);
  input2_tensor.set_data(nullptr);
  output0_tensor.set_data(nullptr);
}
}  // namespace mindspore
