// TyCart library
//
// Copyright (c) 2021-2021 TyCart Authors
// Distributed under the BSD 3-Clause license.
// (See accompanying file LICENSE or copy at
// https://opensource.org/licenses/BSD-3-Clause)
//
// Project home: https://github.com/tudasc/TyCart
//
// SPDX-License-Identifier: BSD-3-Clause
//

#ifndef TYCART_TYCARTASSERT_H
#define TYCART_TYCARTASSERT_H

#ifdef __cplusplus
#include <cstddef>
#else
#include <stddef.h>
#endif  // __cplusplus

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

// Assert functions
void tycart_assert_auto_(int checkpoint_id, const void* pointer, size_t type_size, int type_id);
void tycart_assert_(int checkpoint_id, const void* pointer, size_t count, size_t type_size, int type_id);
void tycart_register_FTI_t_(int type_id);

// Mock or "stub" functions of the corresponding assert functions. They ares replaced by the TyCart LLVM pass.
void tycart_assert_stub_(const void* pointer, void* tycart_stub_ptr, size_t count, int checkpoint_id);  // NOLINT
void tycart_assert_auto_stub_(const void* pointer, void* tycart_stub_ptr, int checkpoint_id);           // NOLINT
void tycart_register_FTI_t_stub_(const void* pointer);                                                  // NOLINT

#ifdef __cplusplus
}
#endif  // __cplusplus

/*
 * Define the used backend library based on the include in user code.
 */
#ifdef __VELOC_H
#define VELOC_PROTECT(id, pointer, count, type) VELOC_Mem_protect(id, pointer, count, sizeof(type));

#define FTI_PROTECT(id, pointer, count, type)
#define MCPR_PROTECT(id, pointer, count, type)
#endif

#ifdef __FTI_H__
#define FTI_PROTECT(id, pointer, count, type) // TODO add FTI support

#define VELOC_PROTECT(id, pointer, count, type)
#define MCPR_PROTECT(id, pointer, count, type)
#endif

#ifdef MINI_CPR_MINI_CPR_H
#define MCPR_PROTECT(id, pointer, count, type) mini_cpr_register(id, pointer, count, sizeof(type));

#define VELOC_PROTECT(id, pointer, count, type)
#define FTI_PROTECT(id, pointer, count, type)
#endif

// Taken from
// https://stackoverflow.com/questions/1597007/creating-c-macro-with-and-line-token-concatenation-with-positioning-macr
#define TOKENPASTE(x, y) x##y
#define PASTELINE(x, y) TOKENPASTE(x, y)

// clang-format off
//

// mark a pointer for checkpointing
#define TY_protect(id, pointer, count, type)                            \
{                                                                         \
type* PASTELINE(__stub_ptr_, __LINE__) = NULL; tycart_assert_stub_((void*)pointer, PASTELINE(__stub_ptr_, __LINE__), count, id); \
VELOC_PROTECT(id, pointer, count, type)                                 \
FTI_PROTECT(id, pointer, count, type)                                   \
MCPR_PROTECT(id, pointer, count, type)                                  \
}

#endif  // TYCART_TYCARTASSERT_H
