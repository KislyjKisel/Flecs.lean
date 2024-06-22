#pragma once

#include <lean/lean.h>
#include <flecs.h>

#define LEAN_FLECS_DECLARE_TYPE(name, cty)\
extern lean_external_class* lean_flecs_##name##_class;\
static inline lean_object* lean_flecs_##name##_box(cty cvalue) {\
    return lean_alloc_external(lean_flecs_##name##_class, cvalue);\
}\
static inline cty lean_flecs_##name##_unbox(b_lean_obj_arg lean_value) {\
  return (cty) lean_get_external_data(lean_value);\
}\
static inline cty lean_flecs_##name##_fromRepr(b_lean_obj_arg lean_value) {\
  return (cty) lean_get_external_data(lean_value);\
}

// TODO: understand why USize can't be used for opaque types
// #define LEAN_FLECS_DECLARE_TYPE_USIZE(name, cty)\
// extern lean_external_class* lean_flecs_##name##_class;\
// static inline lean_object* lean_flecs_##name##_box(cty cvalue) {\
//     return lean_box_usize((size_t)cvalue);\
// }\
// static inline cty lean_flecs_##name##_unbox(b_lean_obj_arg lean_value) {\
//   return (cty) lean_unbox_usize(lean_value);\
// }\
// static inline cty lean_flecs_##name##_fromRepr(size_t unboxed) {\
//   return (cty) unboxed;\
// }

LEAN_FLECS_DECLARE_TYPE(World, ecs_world_t*);
