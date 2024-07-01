#pragma once

#include <lean/lean.h>
#include <lean_pod.h>
#include <flecs.h>

LEAN_POD_TYPE_ALIAS(flecs_Float, ecs_float_t, pod_Float32, float)
LEAN_POD_TYPE_ALIAS(flecs_FTime, ecs_ftime_t, flecs_Float, ecs_float_t)

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

LEAN_POD_TYPE_ALIAS(flecs_Entity, ecs_entity_t, flecs_Id, ecs_id_t);


// Core types

LEAN_POD_PTR_ALIAS(flecs_World, ecs_world_t*)
LEAN_POD_PTR_ALIAS(flecs_Poly, ecs_poly_t*)
LEAN_POD_PTR_ALIAS(flecs_Table, ecs_table_t*)
LEAN_POD_DECLARE_EXTERNAL_CLASS(flecs_Iter, ecs_iter_t*)

static inline lean_object* lean_flecs_Iter_box(ecs_iter_t it) {
    ecs_iter_t* it_box = lean_pod_alloc(sizeof(ecs_iter_t));
    *it_box = it;
    return lean_alloc_external(lean_flecs_Iter_class, it_box);
}

#define lean_flecs_Iter_toRepr lean_flecs_Iter_box

#define lean_flecs_TableRange_layout 3, 0, 0, 0, 0

static inline lean_object* lean_flecs_TableRange_box(const ecs_table_range_t* tr) {
    lean_object* obj = lean_alloc_ctor(0, 3, 0);
    LEAN_POD_CTOR_SET_BOX(lean_flecs_TableRange_layout, obj, 0, lean_flecs_Table_box(tr->table));
    LEAN_POD_CTOR_SET_BOX(lean_flecs_TableRange_layout, obj, 1, lean_box_uint32(tr->offset));
    LEAN_POD_CTOR_SET_BOX(lean_flecs_TableRange_layout, obj, 2, lean_box_uint32(tr->count));
    return obj;
}


// Miscellaneous types

LEAN_POD_PTR_ALIAS(flecs_BuildInfo, const ecs_build_info_t*)
LEAN_POD_PTR_ALIAS(flecs_WorldInfo, const ecs_world_info_t*)
LEAN_POD_PTR_ALIAS(flecs_QueryGroupInfo, const ecs_query_group_info_t*)
