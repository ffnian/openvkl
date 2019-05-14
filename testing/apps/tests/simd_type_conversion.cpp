// ======================================================================== //
// Copyright 2009-2019 Intel Corporation                                    //
//                                                                          //
// Licensed under the Apache License, Version 2.0 (the "License");          //
// you may not use this file except in compliance with the License.         //
// You may obtain a copy of the License at                                  //
//                                                                          //
//     http://www.apache.org/licenses/LICENSE-2.0                           //
//                                                                          //
// Unless required by applicable law or agreed to in writing, software      //
// distributed under the License is distributed on an "AS IS" BASIS,        //
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. //
// See the License for the specific language governing permissions and      //
// limitations under the License.                                           //
// ======================================================================== //

#include <array>
#include "../../external/catch.hpp"
#include "common/simd.h"
#include "volley_testing.h"

using namespace ospcommon;
using namespace volley::testing;
using namespace volley;

template <int sourceWidth, int destWidth>
void vvec3fn_upconversion_test()
{
  vvec3fn<sourceWidth> source;

  for (int i = 0; i < sourceWidth; i++) {
    source.x[i] = i * 3 + 0;
    source.y[i] = i * 3 + 1;
    source.z[i] = i * 3 + 2;
  }

  vvec3fn<destWidth> dest = static_cast<vvec3fn<destWidth>>(source);

  INFO("source width = " << sourceWidth << ", dest width = " << destWidth);

  for (int i = 0; i < sourceWidth; i++) {
    REQUIRE(source.x[i] == dest.x[i]);
    REQUIRE(source.y[i] == dest.y[i]);
    REQUIRE(source.z[i] == dest.z[i]);
  }
};

TEST_CASE("SIMD type conversion")
{
  vlyLoadModule("ispc_driver");

  VLYDriver driver = vlyNewDriver("ispc_driver");
  vlyCommitDriver(driver);
  vlySetCurrentDriver(driver);

  SECTION("vvec3fn")
  {
    vvec3fn_upconversion_test<4, 4>();
    vvec3fn_upconversion_test<4, 8>();
    vvec3fn_upconversion_test<4, 16>();

    vvec3fn_upconversion_test<8, 8>();
    vvec3fn_upconversion_test<8, 16>();

    vvec3fn_upconversion_test<16, 16>();
  }
}