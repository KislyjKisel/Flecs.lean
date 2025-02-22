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
LEAN_POD_PTR_ALIAS(flecs_Observer, const ecs_observer_t*)

typedef struct {
    bool owned;
    union {
        ecs_iter_t* pointer;
        ecs_iter_t value;
    };
} lean_flecs_Iter_data;

typedef lean_object* lean_flecs_Iter;
extern lean_external_class* lean_flecs_Iter_class;

static inline ecs_iter_t* lean_flecs_Iter_fromRepr(b_lean_obj_arg obj) {
    lean_flecs_Iter_data* data = lean_get_external_data(obj);
    if (data->owned) {
        return &data->value;
    }
    else {
        return data->pointer;
    }
}

static inline lean_object* lean_flecs_Iter_alloc_value(ecs_iter_t it) {
    lean_flecs_Iter_data* it_box = lean_pod_alloc(sizeof(lean_flecs_Iter_data));
    it_box->value = it;
    it_box->owned = true;
    return lean_alloc_external(lean_flecs_Iter_class, it_box);
}

static inline lean_object* lean_flecs_Iter_alloc_pointer(ecs_iter_t* it) {
    lean_flecs_Iter_data* it_box = lean_pod_alloc(sizeof(lean_flecs_Iter_data));
    it_box->pointer = it;
    it_box->owned = false;
    return lean_alloc_external(lean_flecs_Iter_class, it_box);
}


LEAN_POD_DECLARE_EXTERNAL_CLASS(flecs_Ref, ecs_ref_t*)

static inline lean_object* lean_flecs_Ref_box(ecs_ref_t ref) {
    ecs_ref_t* ref_p = lean_pod_alloc(sizeof(ecs_ref_t));
    return lean_alloc_external(lean_flecs_Ref_class, ref_p);
}

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

#define LEAN_FLECS_Term_LAYOUT 0, 3, 0, 2, 0, 0, 2
#define LEAN_FLECS_Term_id U64, 0, LEAN_FLECS_Term_LAYOUT
#define LEAN_FLECS_Term_src BOX, 0, LEAN_FLECS_Term_LAYOUT
#define LEAN_FLECS_Term_first BOX, 1, LEAN_FLECS_Term_LAYOUT
#define LEAN_FLECS_Term_second BOX, 2, LEAN_FLECS_Term_LAYOUT
#define LEAN_FLECS_Term_trav U64, 1, LEAN_FLECS_Term_LAYOUT
#define LEAN_FLECS_Term_inout U8, 0, LEAN_FLECS_Term_LAYOUT
#define LEAN_FLECS_Term_oper U8, 1, LEAN_FLECS_Term_LAYOUT

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

#define LEAN_FLECS_EventTarget_entity_LAYOUT 0, 0, 0, 1, 0, 0, 0
#define LEAN_FLECS_EventTarget_entity_entity U64, 0, LEAN_FLECS_EventTarget_entity_LAYOUT
#define LEAN_FLECS_EventTarget_table_LAYOUT 1, 3, 0, 0, 0, 0, 0
#define LEAN_FLECS_EventTarget_table_table BOX, 0, LEAN_FLECS_EventTarget_table_LAYOUT
#define LEAN_FLECS_EventTarget_table_offset BOX, 1, LEAN_FLECS_EventTarget_table_LAYOUT
#define LEAN_FLECS_EventTarget_table_count BOX, 2, LEAN_FLECS_EventTarget_table_LAYOUT

#define LEAN_FLECS_EventDesc_LAYOUT 0, 4, 0, 1, 1, 0, 0
#define LEAN_FLECS_EventDesc_event U64, 0, LEAN_FLECS_EventDesc_LAYOUT
#define LEAN_FLECS_EventDesc_ids BOX, 0, LEAN_FLECS_EventDesc_LAYOUT
#define LEAN_FLECS_EventDesc_param BOX, 1, LEAN_FLECS_EventDesc_LAYOUT
#define LEAN_FLECS_EventDesc_observable BOX, 2, LEAN_FLECS_EventDesc_LAYOUT
#define LEAN_FLECS_EventDesc_flags U32, 0, LEAN_FLECS_EventDesc_LAYOUT
#define LEAN_FLECS_EventDesc_target BOX, 3, LEAN_FLECS_EventDesc_LAYOUT

#define LEAN_FLECS_ObserverDesc_LAYOUT 0, 4, 0, 1, 0, 0, 1
#define LEAN_FLECS_ObserverDesc_entity U64, 0, LEAN_FLECS_ObserverDesc_LAYOUT
#define LEAN_FLECS_ObserverDesc_query BOX, 0, LEAN_FLECS_ObserverDesc_LAYOUT
#define LEAN_FLECS_ObserverDesc_events BOX, 1, LEAN_FLECS_ObserverDesc_LAYOUT
#define LEAN_FLECS_ObserverDesc_yieldExisting U8, 0, LEAN_FLECS_ObserverDesc_LAYOUT
#define LEAN_FLECS_ObserverDesc_callback BOX, 2, LEAN_FLECS_ObserverDesc_LAYOUT
#define LEAN_FLECS_ObserverDesc_observable BOX, 3, LEAN_FLECS_ObserverDesc_LAYOUT


// Miscellaneous types

#define LEAN_FLECS_EntityDesc_LAYOUT 0, 6, 0, 2, 0, 0, 1
#define LEAN_FLECS_EntityDesc_id U64, 0, LEAN_FLECS_EntityDesc_LAYOUT
#define LEAN_FLECS_EntityDesc_parent U64, 1, LEAN_FLECS_EntityDesc_LAYOUT
#define LEAN_FLECS_EntityDesc_name BOX, 0, LEAN_FLECS_EntityDesc_LAYOUT
#define LEAN_FLECS_EntityDesc_sep BOX, 1, LEAN_FLECS_EntityDesc_LAYOUT
#define LEAN_FLECS_EntityDesc_rootSep BOX, 2, LEAN_FLECS_EntityDesc_LAYOUT
#define LEAN_FLECS_EntityDesc_symbol BOX, 3, LEAN_FLECS_EntityDesc_LAYOUT
#define LEAN_FLECS_EntityDesc_useLowId U8, 0, LEAN_FLECS_EntityDesc_LAYOUT
#define LEAN_FLECS_EntityDesc_add BOX, 4, LEAN_FLECS_EntityDesc_LAYOUT
#define LEAN_FLECS_EntityDesc_addExpr BOX, 5, LEAN_FLECS_EntityDesc_LAYOUT

// `.add` must be freed; `.name` assumed to be freed by flecs;
// `symbol` is ignored (appears to be unused by `ecs_entity_init`);
// some contained string pointers' lifetimes are tied to the `desc` argument.
static inline ecs_entity_desc_t lean_flecs_EntityDesc_fromRepr(b_lean_obj_arg desc) {
    ecs_entity_desc_t desc_c = {0};
    desc_c.id = LEAN_POD_CTOR_GET(desc, LEAN_FLECS_EntityDesc_id);
    desc_c.parent = LEAN_POD_CTOR_GET(desc, LEAN_FLECS_EntityDesc_parent);
    // Mutated and stored by `ecs_entity_init`; empty = none.
    // TODO: not freed?
    lean_object* name = LEAN_POD_CTOR_GET(desc, LEAN_FLECS_EntityDesc_name);
    if (lean_option_is_some(name)) {
        lean_object* name_v = lean_ctor_get(name, 0);
        if (lean_string_byte_size(name_v) > 0) {
            desc_c.name = ecs_os_strdup(lean_string_cstr(name_v));
        }
    }
    lean_object* sep = LEAN_POD_CTOR_GET(desc, LEAN_FLECS_EntityDesc_sep);
    if (lean_option_is_some(sep)) {
        desc_c.sep = lean_string_cstr(lean_ctor_get(sep, 0));
    }
    lean_object* rootSep = LEAN_POD_CTOR_GET(desc, LEAN_FLECS_EntityDesc_rootSep);
    if (lean_option_is_some(rootSep)) {
        desc_c.root_sep = lean_string_cstr(lean_ctor_get(rootSep, 0));
    }
    // TODO: ecs_entity_init: `symbol` unused?
    // lean_object* symbol = LEAN_POD_CTOR_GET(desc, LEAN_FLECS_EntityDesc_symbol);
    // if (lean_option_is_some(symbol)) {
    //     desc_c.symbol = lean_string_cstr(lean_ctor_get(symbol, 0));
    // }
    desc_c.use_low_id = 0 != LEAN_POD_CTOR_GET(desc, LEAN_FLECS_EntityDesc_useLowId);
    lean_object* add = LEAN_POD_CTOR_GET(desc, LEAN_FLECS_EntityDesc_add);
    size_t add_size = lean_array_size(add);
    if (add_size > 0) {
        ecs_id_t* add_c = malloc(sizeof(ecs_id_t) * (add_size + 1));
        for (size_t i = 0; i < add_size; ++i) {
            add_c[i] = lean_flecs_Id_unbox(lean_array_get_core(add, i));
        }
        add_c[add_size] = 0;
        desc_c.add = add_c;
    }
    lean_object* addExpr = LEAN_POD_CTOR_GET(desc, LEAN_FLECS_EntityDesc_addExpr);
    if (lean_option_is_some(addExpr)) {
        desc_c.add_expr = lean_string_cstr(lean_ctor_get(addExpr, 0));
    }
    return desc_c;
}

LEAN_POD_PTR_ALIAS(flecs_BuildInfo, const ecs_build_info_t*)
LEAN_POD_PTR_ALIAS(flecs_WorldInfo, const ecs_world_info_t*)
LEAN_POD_PTR_ALIAS(flecs_QueryGroupInfo, const ecs_query_group_info_t*)

#define LEAN_FLECS_QueryCount_LAYOUT 0, 4, 0, 0, 0, 0, 0
#define LEAN_FLECS_QueryCount_results BOX, 0, LEAN_FLECS_QueryCount_LAYOUT
#define LEAN_FLECS_QueryCount_entities BOX, 1, LEAN_FLECS_QueryCount_LAYOUT
#define LEAN_FLECS_QueryCount_tables BOX, 2, LEAN_FLECS_QueryCount_LAYOUT
#define LEAN_FLECS_QueryCount_emptyTables BOX, 3, LEAN_FLECS_QueryCount_LAYOUT

#define LEAN_FLECS_DeleteEmptyTablesDesc_LAYOUT 0, 0, 0, 2, 1, 2, 0
#define LEAN_FLECS_DeleteEmptyTablesDesc_id U64, 0, LEAN_FLECS_DeleteEmptyTablesDesc_LAYOUT
#define LEAN_FLECS_DeleteEmptyTablesDesc_clearGeneration U16, 0, LEAN_FLECS_DeleteEmptyTablesDesc_LAYOUT
#define LEAN_FLECS_DeleteEmptyTablesDesc_deleteGeneration U16, 1, LEAN_FLECS_DeleteEmptyTablesDesc_LAYOUT
#define LEAN_FLECS_DeleteEmptyTablesDesc_minIdCount U32, 0, LEAN_FLECS_DeleteEmptyTablesDesc_LAYOUT
#define LEAN_FLECS_DeleteEmptyTablesDesc_timeBudgetSeconds F64, 1, LEAN_FLECS_DeleteEmptyTablesDesc_LAYOUT

static inline ecs_delete_empty_tables_desc_t lean_flecs_DeleteEmptyTablesDesc_fromRepr(b_lean_obj_arg obj) {
    ecs_delete_empty_tables_desc_t desc = {0};
    desc.id = LEAN_POD_CTOR_GET(obj, LEAN_FLECS_DeleteEmptyTablesDesc_id);
    desc.clear_generation = LEAN_POD_CTOR_GET(obj, LEAN_FLECS_DeleteEmptyTablesDesc_clearGeneration);
    desc.delete_generation = LEAN_POD_CTOR_GET(obj, LEAN_FLECS_DeleteEmptyTablesDesc_deleteGeneration);
    desc.min_id_count = LEAN_POD_CTOR_GET(obj, LEAN_FLECS_DeleteEmptyTablesDesc_minIdCount);
    desc.time_budget_seconds = LEAN_POD_CTOR_GET(obj, LEAN_FLECS_DeleteEmptyTablesDesc_timeBudgetSeconds);
    return desc;
}
