#pragma once
#include <string>

// #include "llvh-c/DataTypes.h"
// #include "llvh-c/Error.h"
// #include "llvh-c/ErrorHandling.h"
// #include "llvh-c/Support.h"
// #include "llvh-c/Types.h"

// #include "llvh/Config/llvm-config.h"
// #include "llvh/Support/Compiler.h"
// #include "llvh/Support/DataTypes.h"
// #include "llvh/Support/SwapByteOrder.h"

// #include "hermes/Support/Compiler.h"

#include <cstdlib>
#include <system_error>
// #include <cassert>

class Greeter {
public:
  Greeter(const std::string& name);
  std::string greet() const;
private:
  std::string name_;
};