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
    // TODO: LEAN_FLECS_QueryDesc_orderBy
    // TODO: LEAN_FLECS_QueryDesc_groupBy
    desc_c.entity = lean_flecs_Entity_fromRepr(LEAN_POD_CTOR_GET(desc, LEAN_FLECS_QueryDesc_entity));
    return lean_io_result_mk_ok(lean_flecs_Query_box(
        ecs_query_init(lean_flecs_World_fromRepr(world), &desc_c)
    ));
}

LEAN_EXPORT lean_obj_res lean_flecs_Query_fini (lean_flecs_Query query, lean_obj_arg io_) {
    ecs_query_fini(lean_flecs_Query_fromRepr(query));
    return lean_io_result_mk_ok(lean_box(0));
}
