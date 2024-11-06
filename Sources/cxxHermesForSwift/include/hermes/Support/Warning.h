/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#ifndef HERMES_SUPPORT_WARNINGS_H
#define HERMES_SUPPORT_WARNINGS_H

#include "llvh/ADT/DenseMapInfo.h"

#include <type_traits>

namespace hermes {

/// Categories of warnings the compiler might emit, that can be turned on or
/// off.
enum class Warning {
#define WARNING_CATEGORY_HIDDEN(name, specifier, description) name,
  #ifndef WARNING_CATEGORY_HIDDEN
  /// Usage within this file: Defines a warning that should NOT have its own
  /// -Wspecifier and -Wno-specifier flags, but may be specified in
  /// -Werror=specifier and -Wno-error=specifier.
  /// Usage outside of this file: Provide only this macro to expand to ALL
  /// warning categories, both hidden and non-hidden, or provide WARNING_CATEGORY
  /// separately to distinguish between them.
  #define WARNING_CATEGORY_HIDDEN(name, specifier, description)
  #endif

  #ifndef WARNING_CATEGORY
  /// Usage within this file: Defines a warning that should have its own
  /// -Wspecifier and -Wno-specifier flags, and may be specified in
  /// -Werror=specifier and -Wno-error=specifier.
  /// Usage outside of this file: Provide only this macro to expand only to
  /// non-hidden warning categories.
  #define WARNING_CATEGORY(name, specifier, description) WARNING_CATEGORY_HIDDEN(name, specifier, description)
  #endif

  // List of warning categories.
  // NoWarning is special and must be first. Its description is only used in the context of -Werror and -Wno-error.
  WARNING_CATEGORY_HIDDEN(NoWarning, "", "All warnings")
  WARNING_CATEGORY(UndefinedVariable, "undefined-variable", "Warning when an undefined variable is referenced")
  WARNING_CATEGORY(DirectEval, "direct-eval", "Warning when attempting a direct (local) eval")
  WARNING_CATEGORY(UnresolvedStaticRequire, "unresolved-static-require", "Warning when require calls cannot be resolved statically")
  WARNING_CATEGORY_HIDDEN(Misc, "misc", "Miscellaneous warnings")

  #undef WARNING_CATEGORY
  #undef WARNING_CATEGORY_HIDDEN
  _NumWarnings,
};

} // namespace hermes

namespace llvh {

using hermes::Warning;

/// Information to store a \p Warning as the key of a \p DenseMap or \p
/// DensetSet
template <>
struct DenseMapInfo<Warning> {
  using Underlying = std::underlying_type<Warning>::type;
  using UnderlyingInfo = DenseMapInfo<Underlying>;

  static inline Warning getEmptyKey() {
    return static_cast<Warning>(UnderlyingInfo::getEmptyKey());
  }

  static inline Warning getTombstoneKey() {
    return static_cast<Warning>(UnderlyingInfo::getTombstoneKey());
  }

  static unsigned getHashValue(Warning warning) {
    return UnderlyingInfo::getHashValue(static_cast<Underlying>(warning));
  }

  static bool isEqual(Warning lhs, Warning rhs) {
    return lhs == rhs;
  }
};

} // namespace llvh

#endif // HERMES_SUPPORT_SOURCEERRORMANAGER_H
