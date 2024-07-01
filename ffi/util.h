#pragma once

#include <lean/lean.h>

static inline void lean_flecs_obj_ctx_free(void* obj) {
    lean_dec((lean_object*)obj);
}
