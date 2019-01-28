/// \file
/// \brief Test compilation unit.
///
/// \copyright
///   Copyright 2018 by Google Inc. All Rights Reserved.
///
/// \copyright
///   Licensed under the Apache License, Version 2.0 (the "License"); you may
///   not use this file except in compliance with the License. You may obtain a
///   copy of the License at
///
/// \copyright
///   http://www.apache.org/licenses/LICENSE-2.0
///
/// \copyright
///   Unless required by applicable law or agreed to in writing, software
///   distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
///   WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
///   License for the specific language governing permissions and limitations
///   under the License.

#include "module2.h"
#include <chrono>
#include <iostream>
#include "ash/io.h"

void run_module2() {
  ash::channel in(0);
  auto s =
      ash::select(in.read(), ash::timeout(std::chrono::milliseconds(3000)));
  std::cerr << s[0] << s[1] << std::endl;
  in.release();
}