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
LEAN_POD_PTR_ALIAS(flecs_Query, ecs_query_t*)
LEAN_POD_DECLARE_EXTERNAL_CLASS(flecs_Iter, ecs_iter_t*)

static inline lean_object* lean_flecs_Iter_box(ecs_iter_t it) {
    ecs_iter_t* it_box = lean_pod_alloc(sizeof(ecs_iter_t));
    *it_box = it;
    return lean_alloc_external(lean_flecs_Iter_class, it_box);
}

#define lean_flecs_Iter_toRepr lean_flecs_Iter_box

#define LEAN_FLECS_TableRange_LAYOUT 0, 3, 0, 0, 0, 0, 0
#define LEAN_FLECS_TableRange_table BOX, 0, LEAN_FLECS_TableRange_LAYOUT
#define LEAN_FLECS_TableRange_offset BOX, 1, LEAN_FLECS_TableRange_LAYOUT
#define LEAN_FLECS_TableRange_count BOX, 2, LEAN_FLECS_TableRange_LAYOUT

typedef lean_object* lean_flecs_TableRange;

static inline lean_object* lean_flecs_TableRange_box(const ecs_table_range_t* tr) {
    lean_object* obj = LEAN_POD_ALLOC_CTOR(LEAN_FLECS_TableRange_LAYOUT);
    LEAN_POD_CTOR_SET(obj, lean_flecs_Table_box(tr->table), LEAN_FLECS_TableRange_table);
    LEAN_POD_CTOR_SET(obj, lean_box_uint32(tr->offset), LEAN_FLECS_TableRange_offset);
    LEAN_POD_CTOR_SET(obj, lean_box_uint32(tr->count), LEAN_FLECS_TableRange_count);
    return obj;
}

#define lean_flecs_TableRange_toRepr lean_flecs_TableRange_box

static inline ecs_table_range_t lean_flecs_TableRange_unbox(b_lean_obj_arg range) {
    ecs_table_range_t range_c;
    range_c.table = lean_flecs_Table_unbox(LEAN_POD_CTOR_GET(range, LEAN_FLECS_TableRange_table));
    range_c.offset = lean_pod_Int32_unbox(LEAN_POD_CTOR_GET(range, LEAN_FLECS_TableRange_offset));
    range_c.count = lean_pod_Int32_unbox(LEAN_POD_CTOR_GET(range, LEAN_FLECS_TableRange_count));
    return range_c;
}

#define lean_flecs_TableRange_fromRepr lean_flecs_TableRange_unbox

#define LEAN_FLECS_TermRef_LAYOUT 0, 1, 0, 1, 0, 0, 0
#define LEAN_FLECS_TermRef_id U64, 0, LEAN_FLECS_TermRef_LAYOUT
#define LEAN_FLECS_TermRef_name BOX, 0, LEAN_FLECS_TermRef_LAYOUT

#define LEAN_FLECS_Term_LAYOUT 0, 4, 0, 1, 0, 0, 2
#define LEAN_FLECS_Term_id U64, 0, LEAN_FLECS_Term_LAYOUT
#define LEAN_FLECS_Term_src BOX, 0, LEAN_FLECS_Term_LAYOUT
#define LEAN_FLECS_Term_first BOX, 1, LEAN_FLECS_Term_LAYOUT
#define LEAN_FLECS_Term_second BOX, 2, LEAN_FLECS_Term_LAYOUT
#define LEAN_FLECS_Term_inout U8, 0, LEAN_FLECS_Term_LAYOUT
#define LEAN_FLECS_Term_oper U8, 1, LEAN_FLECS_Term_LAYOUT
#define LEAN_FLECS_Term_fieldIndex BOX, 3, LEAN_FLECS_Term_LAYOUT

#define LEAN_FLECS_GroupBy_LAYOUT 0, 3, 0, 1, 0, 0, 0
#define LEAN_FLECS_GroupBy_component U64, 0, LEAN_FLECS_GroupBy_LAYOUT
#define LEAN_FLECS_GroupBy_callback BOX, 0, LEAN_FLECS_GroupBy_LAYOUT
#define LEAN_FLECS_GroupBy_onCreate BOX, 1, LEAN_FLECS_GroupBy_LAYOUT
#define LEAN_FLECS_GroupBy_onDelete BOX, 2, LEAN_FLECS_GroupBy_LAYOUT

#define LEAN_FLECS_QueryDesc_LAYOUT 0, 5, 0, 1, 0, 0, 1
#define LEAN_FLECS_QueryDesc_terms BOX, 0, LEAN_FLECS_QueryDesc_LAYOUT
#define LEAN_FLECS_QueryDesc_expr BOX, 1, LEAN_FLECS_QueryDesc_LAYOUT
#define LEAN_FLECS_QueryDesc_cacheKind U8, 0, LEAN_FLECS_QueryDesc_LAYOUT
#define LEAN_FLECS_QueryDesc_flags BOX, 2, LEAN_FLECS_QueryDesc_LAYOUT
#define LEAN_FLECS_QueryDesc_orderBy BOX, 3, LEAN_FLECS_QueryDesc_LAYOUT
#define LEAN_FLECS_QueryDesc_groupBy BOX, 4, LEAN_FLECS_QueryDesc_LAYOUT
#define LEAN_FLECS_QueryDesc_entity U64, 0, LEAN_FLECS_QueryDesc_LAYOUT


// Miscellaneous types

LEAN_POD_PTR_ALIAS(flecs_BuildInfo, const ecs_build_info_t*)
LEAN_POD_PTR_ALIAS(flecs_WorldInfo, const ecs_world_info_t*)
LEAN_POD_PTR_ALIAS(flecs_QueryGroupInfo, const ecs_query_group_info_t*)

#define LEAN_FLECS_QueryCount_LAYOUT 0, 4, 0, 0, 0, 0, 0
#define LEAN_FLECS_QueryCount_results BOX, 0, LEAN_FLECS_QueryCount_LAYOUT
#define LEAN_FLECS_QueryCount_entities BOX, 1, LEAN_FLECS_QueryCount_LAYOUT
#define LEAN_FLECS_QueryCount_tables BOX, 2, LEAN_FLECS_QueryCount_LAYOUT
#define LEAN_FLECS_QueryCount_emptyTables BOX, 3, LEAN_FLECS_QueryCount_LAYOUT
