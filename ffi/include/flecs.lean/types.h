#pragma once

#include <lean/lean.h>
#include <lean_pod.h>
#include <flecs.h>

#define lean_flecs_Float uint32_t
#define lean_flecs_Float_box lean_pod_Float32_box
#define lean_flecs_Float_unbox lean_pod_Float32_unbox
#define lean_flecs_Float_fromRepr lean_pod_Float32_fromBits
#define lean_flecs_Float_toRepr lean_pod_Float32_toBits

#define lean_flecs_FTime lean_flecs_Float
#define lean_flecs_FTime_box lean_flecs_Float_box
#define lean_flecs_FTime_unbox lean_flecs_Float_unbox
#define lean_flecs_FTime_fromRepr lean_flecs_Float_fromRepr
#define lean_flecs_FTime_toRepr lean_flecs_Float_toRepr

#define lean_flecs_Id uint64_t
static inline lean_object* lean_flecs_Id_box(ecs_entity_t cvalue) {\
    return lean_box_uint64(cvalue);
}
static inline ecs_id_t lean_flecs_Id_unbox(b_lean_obj_arg lean_value) {
    return lean_unbox_uint64(lean_value);
}
static inline ecs_id_t lean_flecs_Id_fromRepr(uint64_t lean_value) {
    return lean_value;
}
static inline uint64_t lean_flecs_Id_toRepr(ecs_entity_t cvalue) {
    return cvalue;
}

#define lean_flecs_Entity lean_flecs_Id
#define lean_flecs_Entity_box lean_flecs_Id_box
#define lean_flecs_Entity_unbox lean_flecs_Id_unbox
#define lean_flecs_Entity_fromRepr lean_flecs_Id_fromRepr
#define lean_flecs_Entity_toRepr lean_flecs_Id_toRepr

#define LEAN_FLECS_DECLARE_TYPE(name, cty)\
typedef lean_object* lean_flecs_##name;\
extern lean_external_class* lean_flecs_##name##_class;\
static inline lean_object* lean_flecs_##name##_box(cty cvalue) {\
    return lean_alloc_external(lean_flecs_##name##_class, cvalue);\
}\
static inline cty lean_flecs_##name##_unbox(b_lean_obj_arg lean_value) {\
    return (cty) lean_get_external_data(lean_value);\
}\
static inline cty lean_flecs_##name##_fromRepr(b_lean_obj_arg lean_value) {\
    return (cty) lean_get_external_data(lean_value);\
}\
static inline lean_object* lean_flecs_##name##_toRepr(cty cvalue) {\
    return lean_flecs_##name##_box(cvalue);\
}

LEAN_FLECS_DECLARE_TYPE(Ptr, void*);
#define LEAN_FLECS_DECLARE_TYPE_PTR(name, cty)\
typedef lean_flecs_Ptr lean_flecs_##name;\
static inline lean_object* lean_flecs_##name##_box(cty cvalue) { return lean_flecs_Ptr_box((void*)cvalue); }\
static inline cty lean_flecs_##name##_unbox(b_lean_obj_arg lean_value) { return (cty)lean_flecs_Ptr_unbox(lean_value); }\
static inline cty lean_flecs_##name##_fromRepr(b_lean_obj_arg lean_value) { return (cty)lean_flecs_Ptr_fromRepr(lean_value); }\
static inline lean_object* lean_flecs_##name##_toRepr(cty cvalue) { return lean_flecs_Ptr_toRepr((void*)cvalue); }

// Core types

LEAN_FLECS_DECLARE_TYPE_PTR(World, ecs_world_t*)
LEAN_FLECS_DECLARE_TYPE_PTR(Poly, ecs_poly_t*)

// Miscellaneous types

LEAN_FLECS_DECLARE_TYPE_PTR(BuildInfo, const ecs_build_info_t*)
LEAN_FLECS_DECLARE_TYPE_PTR(WorldInfo, const ecs_world_info_t*)
LEAN_FLECS_DECLARE_TYPE_PTR(QueryGroupInfo, const ecs_query_group_info_t*)
