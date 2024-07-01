#include <lean/lean.h>
#include <lean_pod.h>
#include <flecs.h>
#include <flecs.lean/types.h>
#include "../util.h"

// Assumes `termRef_c` is zero-initialized.
static void lean_flecs_Option_TermRef_unbox(b_lean_obj_arg optTermRef, ecs_term_ref_t* termRef_c) {
    if (lean_option_is_some(optTermRef)) {
        lean_object* termRef = lean_ctor_get(optTermRef, 0);
        termRef_c->id = LEAN_POD_CTOR_GET(termRef, LEAN_FLECS_TermRef_id);
        termRef_c->name = lean_string_cstr(LEAN_POD_CTOR_GET(termRef, LEAN_FLECS_TermRef_name));
    }
}

// Assumes `term_c` is zero-initialized.
static void lean_flecs_Term_unbox(b_lean_obj_arg term, ecs_term_t* term_c) {
    term_c->id = LEAN_POD_CTOR_GET(term, LEAN_FLECS_Term_id);
    lean_flecs_Option_TermRef_unbox(LEAN_POD_CTOR_GET(term, LEAN_FLECS_Term_src), &term_c->src);
    lean_flecs_Option_TermRef_unbox(LEAN_POD_CTOR_GET(term, LEAN_FLECS_Term_first), &term_c->first);
    lean_flecs_Option_TermRef_unbox(LEAN_POD_CTOR_GET(term, LEAN_FLECS_Term_second), &term_c->second);
    term_c->inout = LEAN_POD_CTOR_GET(term, LEAN_FLECS_Term_inout);
    term_c->oper = LEAN_POD_CTOR_GET(term, LEAN_FLECS_Term_oper);
    term_c->field_index = lean_pod_Int16_unbox(LEAN_POD_CTOR_GET(term, LEAN_FLECS_Term_fieldIndex));
}

static int lean_flecs_OrderByAction_wrapper(ecs_entity_t e1, const void* p1, ecs_entity_t e2, const void* p2) {
    // TODO: how to get lean_object*, and optionally, ReadBytes instance here?
    return 0;
}

static uint64_t lean_flecs_GroupByAction_wrapper(ecs_world_t* world, ecs_table_t* table, ecs_id_t group_id, void* ctx) {
    lean_object* callback = lean_ctor_get(ctx, 0);
    lean_inc_ref(callback);
    lean_object* res_box = lean_apply_4(callback, lean_flecs_World_box(world), lean_flecs_Table_box(table), lean_flecs_Id_box(group_id), lean_box(0));
    uint64_t res = lean_unbox_uint64(lean_io_result_get_value(res_box));
    lean_dec_ref(res_box);
    return res;
}

static void* lean_flecs_GroupCreateAction_wrapper(ecs_world_t* world, uint64_t group_id, void* group_by_ctx) {
    lean_object* callback = lean_ctor_get(group_by_ctx, 1);
    lean_inc_ref(callback);
    lean_object* res_box = lean_apply_3(callback, lean_flecs_World_box(world), lean_box_uint64(group_id), lean_box(0));
    void* res = lean_io_result_get_value(res_box);
    lean_dec_ref(res_box);
    return res;
}

static void lean_flecs_GroupDeleteAction_wrapper(ecs_world_t* world, uint64_t group_id, void* group_ctx, void* group_by_ctx) {
    lean_object* callback = lean_ctor_get(group_by_ctx, 2);
    lean_inc_ref(callback);
    lean_dec_ref(lean_apply_4(callback, lean_flecs_World_box(world), lean_box_uint64(group_id), group_by_ctx, lean_box(0)));
}

LEAN_EXPORT lean_obj_res lean_flecs_Query_init (lean_flecs_World world, lean_obj_arg desc, lean_obj_arg io_) {
    ecs_query_desc_t desc_c = {};
    desc_c.binding_ctx = desc; // to keep strings alive
    desc_c.binding_ctx_free = lean_flecs_obj_ctx_free;
    lean_object* terms = LEAN_POD_CTOR_GET(desc, LEAN_FLECS_QueryDesc_terms);
    size_t term_count = lean_array_size(terms);
    for (size_t i = 0; i < term_count; ++i) {
        lean_flecs_Term_unbox(lean_array_get_core(terms, i), &desc_c.terms[i]);
    }
    lean_object* expr = LEAN_POD_CTOR_GET(desc, LEAN_FLECS_QueryDesc_expr);
    if (lean_option_is_some(expr)) {
        desc_c.expr = lean_string_cstr(lean_ctor_get(expr, 0));
    }
    desc_c.cache_kind = LEAN_POD_CTOR_GET(desc, LEAN_FLECS_QueryDesc_cacheKind);
    desc_c.flags = lean_unbox_uint32(LEAN_POD_CTOR_GET(desc, LEAN_FLECS_QueryDesc_flags));
    lean_object* orderBy = LEAN_POD_CTOR_GET(desc, LEAN_FLECS_QueryDesc_orderBy);
    unsigned int orderBy_tag = lean_obj_tag(orderBy);
    switch (orderBy_tag) {
        case 0: break;
        case 1: {
            desc_c.order_by = lean_ctor_get_uint64(orderBy, 1);
            desc_c.order_by_callback = lean_flecs_OrderByAction_wrapper;
            break;
        }
        case 2: {
            desc_c.order_by = lean_ctor_get_uint64(orderBy, 3);
            desc_c.order_by_callback = lean_flecs_OrderByAction_wrapper;
            break;
        }
    }
    lean_object* groupBy = LEAN_POD_CTOR_GET(desc, LEAN_FLECS_QueryDesc_groupBy);
    unsigned int groupBy_tag = lean_obj_tag(orderBy);
    switch (orderBy_tag) {
        case 0: break;
        case 1: {
            desc_c.group_by = lean_ctor_get_uint64(groupBy, sizeof(lean_object*) * 1);
            lean_inc_ref(groupBy);
            desc_c.group_by_ctx = groupBy;
            desc_c.group_by_ctx_free = lean_flecs_obj_ctx_free;
            desc_c.group_by_callback = lean_flecs_GroupByAction_wrapper;
            break;
        }
        case 2: {
            desc_c.group_by = lean_ctor_get_uint64(groupBy, sizeof(lean_object*) * 3);
            lean_inc_ref(groupBy);
            desc_c.group_by_ctx = groupBy;
            desc_c.group_by_ctx_free = lean_flecs_obj_ctx_free;
            desc_c.group_by_callback = lean_flecs_GroupByAction_wrapper;
            desc_c.on_group_create = lean_flecs_GroupCreateAction_wrapper;
            desc_c.on_group_delete = lean_flecs_GroupDeleteAction_wrapper;
            break;
        }
    }
    desc_c.entity = lean_flecs_Entity_fromRepr(LEAN_POD_CTOR_GET(desc, LEAN_FLECS_QueryDesc_entity));
    return lean_io_result_mk_ok(lean_flecs_Query_box(
        ecs_query_init(lean_flecs_World_fromRepr(world), &desc_c)
    ));
}

LEAN_EXPORT lean_obj_res lean_flecs_Query_fini (lean_flecs_Query query, lean_obj_arg io_) {
    ecs_query_fini(lean_flecs_Query_fromRepr(query));
    return lean_io_result_mk_ok(lean_box(0));
}
