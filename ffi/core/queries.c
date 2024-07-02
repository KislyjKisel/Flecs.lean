#include <lean/lean.h>
#include <lean_pod.h>
#include <flecs.h>
#include <flecs.lean/types.h>
#include "../util.h"

LEAN_EXPORT lean_obj_res lean_flecs_Query_str(lean_flecs_Query query, lean_obj_arg io_) {
    char* expr_c = ecs_query_str(lean_flecs_Query_fromRepr(query));
    lean_object* expr = lean_mk_string(expr_c);
    ecs_os_free(expr_c);
    return lean_io_result_mk_ok(expr);
}

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
    // Always `Option.some`, checked on query creation.
    lean_object* callback = lean_ctor_get(LEAN_POD_CTOR_GET(ctx, LEAN_FLECS_GroupBy_callback), 0);
    lean_inc_ref(callback);
    lean_object* res_box = lean_apply_4(callback, lean_flecs_World_box(world), lean_flecs_Table_box(table), lean_flecs_Id_box(group_id), lean_box(0));
    uint64_t res = lean_unbox_uint64(lean_io_result_get_value(res_box));
    lean_dec_ref(res_box);
    return res;
}

static void* lean_flecs_GroupCreateAction_wrapper(ecs_world_t* world, uint64_t group_id, void* group_by_ctx) {
    lean_object* callback = LEAN_POD_CTOR_GET(group_by_ctx, LEAN_FLECS_GroupBy_onCreate);
    lean_inc_ref(callback);
    lean_object* res_box = lean_apply_3(callback, lean_flecs_World_box(world), lean_box_uint64(group_id), lean_box(0));
    void* res = lean_io_result_get_value(res_box);
    lean_inc(res);
    lean_dec_ref(res_box);
    return res;
}

static void lean_flecs_GroupDeleteAction_wrapper(ecs_world_t* world, uint64_t group_id, void* group_ctx, void* group_by_ctx) {
    lean_object* callback = LEAN_POD_CTOR_GET(group_by_ctx, LEAN_FLECS_GroupBy_onDelete);
    lean_inc_ref(callback);
    lean_dec_ref(lean_apply_4(callback, lean_flecs_World_box(world), lean_box_uint64(group_id), group_by_ctx, lean_box(0)));
}

LEAN_EXPORT lean_obj_res lean_flecs_World_queryInit(lean_flecs_World world, lean_obj_arg desc, lean_obj_arg io_) {
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
    lean_object* optGroupBy = LEAN_POD_CTOR_GET(desc, LEAN_FLECS_QueryDesc_groupBy);
    if (lean_option_is_some(optGroupBy)) {
        lean_object* groupBy = lean_ctor_get(optGroupBy, 0);
        lean_inc_ref(groupBy);
        desc_c.group_by_ctx = groupBy;
        desc_c.group_by_ctx_free = lean_flecs_obj_ctx_free;
        desc_c.group_by = LEAN_POD_CTOR_GET(groupBy, LEAN_FLECS_GroupBy_component);
        if (lean_option_is_some(LEAN_POD_CTOR_GET(groupBy, LEAN_FLECS_GroupBy_callback))) {
            desc_c.group_by_callback = lean_flecs_GroupByAction_wrapper;
        }
        // Mandatory because the value must be created somehow,
        // and its simpler to always provide a cb than to use indexed types with a default case for `Unit`
        desc_c.on_group_create = lean_flecs_GroupCreateAction_wrapper;
        desc_c.on_group_delete = lean_flecs_GroupDeleteAction_wrapper;
    }
    desc_c.entity = lean_flecs_Entity_fromRepr(LEAN_POD_CTOR_GET(desc, LEAN_FLECS_QueryDesc_entity));
    return lean_io_result_mk_ok(lean_flecs_Query_box(
        ecs_query_init(lean_flecs_World_fromRepr(world), &desc_c)
    ));
}

LEAN_EXPORT lean_obj_res lean_flecs_Query_fini(lean_flecs_Query query, lean_obj_arg io_) {
    ecs_query_fini(lean_flecs_Query_fromRepr(query));
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_Query_findVar (lean_flecs_Query query, b_lean_obj_arg name, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_pod_Int32_box(
        ecs_query_find_var(lean_flecs_Query_fromRepr(query), lean_string_cstr(name))
    ));
}

LEAN_EXPORT lean_obj_res lean_flecs_Query_varName (lean_flecs_Query query, lean_pod_Int32 varId, lean_obj_arg io_) {
    ecs_query_t* query_c = lean_flecs_Query_fromRepr(query);
    int32_t varId_c = lean_pod_Int32_fromRepr(varId);
    if (varId_c >= 0 && varId_c < query_c->var_count) {
        return lean_io_result_mk_ok(lean_mk_option_some(lean_mk_string(
            ecs_query_var_name(query_c, varId_c)
        )));
    }
    return lean_io_result_mk_ok(lean_mk_option_none());
}

LEAN_EXPORT lean_obj_res lean_flecs_Query_varIsEntity (lean_flecs_Query query, lean_pod_Int32 varId, lean_obj_arg io_) {
    ecs_query_t* query_c = lean_flecs_Query_fromRepr(query);
    int32_t varId_c = lean_pod_Int32_fromRepr(varId);
    bool res = false;
    if (varId_c >= 0 && varId_c < query_c->var_count) {
        res = ecs_query_var_is_entity(query_c, varId_c);
    }
    return lean_io_result_mk_ok(lean_box(res));
}

LEAN_EXPORT lean_obj_res lean_flecs_Query_iter (lean_flecs_World world, lean_flecs_Query query, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_Iter_box(
        ecs_query_iter(lean_flecs_World_fromRepr(world), lean_flecs_Query_fromRepr(query))
    ));
}

LEAN_EXPORT lean_obj_res lean_flecs_Iter_queryNext (lean_flecs_Iter it, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box(ecs_query_next(lean_flecs_Iter_fromRepr(it))));
}

LEAN_EXPORT lean_obj_res lean_flecs_Query_has(lean_flecs_Query query, lean_flecs_Entity entity, lean_obj_arg io_) {
    ecs_iter_t it = {};
    if (ecs_query_has(lean_flecs_Query_fromRepr(query), lean_flecs_Entity_fromRepr(entity), &it)) {
        return lean_io_result_mk_ok(lean_mk_option_some(lean_flecs_Iter_box(it)));
    }
    return lean_io_result_mk_ok(lean_mk_option_none());
}

LEAN_EXPORT lean_obj_res lean_flecs_Query_hasTable(lean_flecs_Query query, lean_flecs_Table table, lean_obj_arg io_) {
    ecs_iter_t it = {};
    if (ecs_query_has_table(lean_flecs_Query_fromRepr(query), lean_flecs_Table_fromRepr(table), &it)) {
        return lean_io_result_mk_ok(lean_mk_option_some(lean_flecs_Iter_box(it)));
    }
    return lean_io_result_mk_ok(lean_mk_option_none());
}

LEAN_EXPORT lean_obj_res lean_flecs_Query_hasRange(lean_flecs_Query query, b_lean_obj_arg range, lean_obj_arg io_) {
    ecs_iter_t it = {};
    ecs_table_range_t range_c = lean_flecs_TableRange_fromRepr(range);
    if (ecs_query_has_range(lean_flecs_Query_fromRepr(query), &range_c, &it)) {
        return lean_io_result_mk_ok(lean_mk_option_some(lean_flecs_Iter_box(it)));
    }
    return lean_io_result_mk_ok(lean_mk_option_none());
}

LEAN_EXPORT lean_obj_res lean_flecs_Query_matchCount(lean_flecs_Query query, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_pod_Int32_box(ecs_query_match_count(lean_flecs_Query_fromRepr(query))));
}

LEAN_EXPORT lean_obj_res lean_flecs_Query_plan(lean_flecs_Query query, lean_obj_arg io_) {
    char* s_c = ecs_query_plan(lean_flecs_Query_fromRepr(query));
    lean_object* s = lean_mk_string(s_c);
    ecs_os_free(s_c);
    return lean_io_result_mk_ok(s);
}

LEAN_EXPORT lean_obj_res lean_flecs_Query_planWithProfile(lean_flecs_Query query, lean_flecs_Iter it, lean_obj_arg io_) {
    char* s_c = ecs_query_plan_w_profile(lean_flecs_Query_fromRepr(query), lean_flecs_Iter_fromRepr(it));
    lean_object* s = lean_mk_string(s_c);
    ecs_os_free(s_c);
    return lean_io_result_mk_ok(s);
}

// TODO: Query.argsParse "This function uses the script addon."
// LEAN_EXPORT lean_obj_res lean_flecs_Query_argsParse(lean_flecs_Query query, lean_flecs_Iter it, b_lean_obj_arg expr, lean_obj_arg io_) {
//     const char* expr_c = lean_string_cstr(expr);
//     const char* end = ecs_query_args_parse(lean_flecs_Query_fromRepr(query), lean_flecs_Iter_fromRepr(it), expr_c);
//     return lean_io_result_mk_ok(lean_usize_to_nat(end - expr_c));
// }

LEAN_EXPORT lean_obj_res lean_flecs_Query_changed(lean_flecs_Query query, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box(ecs_query_changed(lean_flecs_Query_fromRepr(query))));
}

LEAN_EXPORT lean_obj_res lean_flecs_Iter_skip(lean_flecs_Iter it, lean_obj_arg io_) {
    ecs_iter_skip(lean_flecs_Iter_fromRepr(it));
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_Iter_setGroup(lean_flecs_Iter it, uint64_t groupId, lean_obj_arg io_) {
    ecs_iter_set_group(lean_flecs_Iter_fromRepr(it), groupId);
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_Query_getGroupCtx(lean_flecs_Query query, uint64_t groupId, lean_obj_arg io_) {
    void* ctx = ecs_query_get_group_ctx(lean_flecs_Query_fromRepr(query), groupId);
    if (ctx != NULL) {
        lean_inc(ctx);
        return lean_io_result_mk_ok(lean_mk_option_some(ctx));
    }
    else {
        return lean_io_result_mk_ok(lean_mk_option_none());
    }
}

LEAN_EXPORT lean_obj_res lean_flecs_Query_getGroupInfo(lean_flecs_Query query, uint64_t groupId, lean_obj_arg io_) {
    const ecs_query_group_info_t* info = ecs_query_get_group_info(lean_flecs_Query_fromRepr(query), groupId);
    if (info != NULL) {
        return lean_io_result_mk_ok(lean_mk_option_some(lean_flecs_QueryGroupInfo_box(info)));
    }
    else {
        return lean_io_result_mk_ok(lean_mk_option_none());
    }
}

LEAN_EXPORT lean_obj_res lean_flecs_Query_count(lean_flecs_Query query, lean_obj_arg io_) {
    ecs_query_count_t count = ecs_query_count(lean_flecs_Query_fromRepr(query));
    lean_object* res = LEAN_POD_ALLOC_CTOR(LEAN_FLECS_QueryCount_LAYOUT);
    LEAN_POD_CTOR_SET(res, lean_pod_Int32_box(count.results), LEAN_FLECS_QueryCount_results);
    LEAN_POD_CTOR_SET(res, lean_pod_Int32_box(count.entities), LEAN_FLECS_QueryCount_entities);
    LEAN_POD_CTOR_SET(res, lean_pod_Int32_box(count.tables), LEAN_FLECS_QueryCount_tables);
    LEAN_POD_CTOR_SET(res, lean_pod_Int32_box(count.empty_tables), LEAN_FLECS_QueryCount_emptyTables);
    return lean_io_result_mk_ok(res);
}

LEAN_EXPORT lean_obj_res lean_flecs_Query_isTrue(lean_flecs_Query query, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box(ecs_query_is_true(lean_flecs_Query_fromRepr(query))));
}
