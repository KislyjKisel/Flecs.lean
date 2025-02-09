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

LEAN_EXPORT lean_obj_res lean_flecs_World_queryInit(lean_flecs_World world, lean_obj_arg desc, lean_obj_arg io_) {
    ecs_query_desc_t desc_c = lean_flecs_QueryDesc_fromRepr(desc);
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
    return lean_io_result_mk_ok(lean_flecs_Iter_alloc_value(
        ecs_query_iter(lean_flecs_World_fromRepr(world), lean_flecs_Query_fromRepr(query))
    ));
}

LEAN_EXPORT lean_obj_res lean_flecs_Iter_queryNext (lean_flecs_Iter it, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box(ecs_query_next(lean_flecs_Iter_fromRepr(it))));
}

LEAN_EXPORT lean_obj_res lean_flecs_Query_has(lean_flecs_Query query, lean_flecs_Entity entity, lean_obj_arg io_) {
    ecs_iter_t it = {};
    if (ecs_query_has(lean_flecs_Query_fromRepr(query), lean_flecs_Entity_fromRepr(entity), &it)) {
        return lean_io_result_mk_ok(lean_mk_option_some(lean_flecs_Iter_alloc_value(it)));
    }
    return lean_io_result_mk_ok(lean_mk_option_none());
}

LEAN_EXPORT lean_obj_res lean_flecs_Query_hasTable(lean_flecs_Query query, lean_flecs_Table table, lean_obj_arg io_) {
    ecs_iter_t it = {};
    if (ecs_query_has_table(lean_flecs_Query_fromRepr(query), lean_flecs_Table_fromRepr(table), &it)) {
        return lean_io_result_mk_ok(lean_mk_option_some(lean_flecs_Iter_alloc_value(it)));
    }
    return lean_io_result_mk_ok(lean_mk_option_none());
}

LEAN_EXPORT lean_obj_res lean_flecs_Query_hasRange(lean_flecs_Query query, b_lean_obj_arg range, lean_obj_arg io_) {
    ecs_iter_t it = {};
    ecs_table_range_t range_c = lean_flecs_TableRange_fromRepr(range);
    if (ecs_query_has_range(lean_flecs_Query_fromRepr(query), &range_c, &it)) {
        return lean_io_result_mk_ok(lean_mk_option_some(lean_flecs_Iter_alloc_value(it)));
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
