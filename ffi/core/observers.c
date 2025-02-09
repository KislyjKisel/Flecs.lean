#include <lean/lean.h>
#include <lean_pod.h>
#include <flecs.h>
#include <flecs.lean/types.h>
#include "../util.h"

static lean_obj_res lean_flecs_World_emit_impl(lean_flecs_World world, b_lean_obj_arg desc, void (*f)(ecs_world_t* w, ecs_event_desc_t* d)) {
    ecs_type_t type = {};
    ecs_event_desc_t desc_c = { .ids = &type };
    desc_c.event = LEAN_POD_CTOR_GET(desc, LEAN_FLECS_EventDesc_event);
    {
        lean_object* ids = LEAN_POD_CTOR_GET(desc, LEAN_FLECS_EventDesc_ids);
        size_t ids_size = lean_array_size(ids);
        if (ids_size > 0) {
            type.array = ecs_os_malloc_n(ecs_id_t, ids_size);
            type.count = ids_size;
            for (size_t i = 0; i < ids_size; ++i) {
                type.array[i] = lean_flecs_Id_unbox(lean_array_get_core(ids, i));
            }
        }
    }
    desc_c.param = LEAN_POD_CTOR_GET(desc, LEAN_FLECS_EventDesc_param); // UFixnum - Unboxed - skip lean_inc
    {
        lean_object* obsa = LEAN_POD_CTOR_GET(desc, LEAN_FLECS_EventDesc_observable);
        if (lean_option_is_some(obsa)) {
            desc_c.observable = lean_flecs_Poly_unbox(lean_ctor_get(obsa, 0));
        }
    }
    desc_c.flags = LEAN_POD_CTOR_GET(desc, LEAN_FLECS_EventDesc_flags);
    {
        lean_object* target = LEAN_POD_CTOR_GET(desc, LEAN_FLECS_EventDesc_target);
        if (LEAN_POD_IS(target, LEAN_FLECS_EventTarget_entity_LAYOUT)) {
            desc_c.entity = LEAN_POD_CTOR_GET(target, LEAN_FLECS_EventTarget_entity_entity);
        }
        else if (LEAN_POD_IS(target, LEAN_FLECS_EventTarget_table_LAYOUT)) {
            desc_c.table = lean_flecs_Table_unbox(LEAN_POD_CTOR_GET(target, LEAN_FLECS_EventTarget_table_table));
            desc_c.offset = lean_pod_Int32_unbox(LEAN_POD_CTOR_GET(target, LEAN_FLECS_EventTarget_table_offset));
            desc_c.count = lean_pod_Int32_unbox(LEAN_POD_CTOR_GET(target, LEAN_FLECS_EventTarget_table_count));
        }
        else {
            lean_internal_panic_unreachable();
        }
    }
    f(lean_flecs_World_fromRepr(world), &desc_c);
    if (type.array != NULL) {
        ecs_os_free(type.array);
    }
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_World_emit(lean_flecs_World world, b_lean_obj_arg desc, lean_obj_arg io_) {
    return lean_flecs_World_emit_impl(world, desc, ecs_emit);
}

LEAN_EXPORT lean_obj_res lean_flecs_World_enqueue(lean_flecs_World world, b_lean_obj_arg desc, lean_obj_arg io_) {
    return lean_flecs_World_emit_impl(world, desc, ecs_enqueue);
}

static void lean_flecs_observer_callback(ecs_iter_t *it) {
    lean_object* callback = it->callback_ctx;
    lean_inc_ref(callback);
    lean_object* param = it->param; // UFixnum = unboxed
    lean_dec_ref(lean_apply_3(callback, lean_flecs_Iter_alloc_pointer(it), param, lean_box(0)));
}

LEAN_EXPORT lean_obj_res lean_flecs_World_observerInit(lean_flecs_World world, b_lean_obj_arg desc, lean_obj_arg io_) {
    ecs_observer_desc_t desc_c = {};
    desc_c.entity = LEAN_POD_CTOR_GET(desc, LEAN_FLECS_ObserverDesc_entity);
    {
        lean_object* queryDesc = LEAN_POD_CTOR_GET(desc, LEAN_FLECS_ObserverDesc_query);
        lean_inc_ref(queryDesc);
        desc_c.query = lean_flecs_QueryDesc_fromRepr(queryDesc);
    }
    {
        lean_object* events = LEAN_POD_CTOR_GET(desc, LEAN_FLECS_ObserverDesc_events);
        size_t events_size = lean_array_size(events);
        for (size_t i = 0; i < events_size; ++i) {
            desc_c.events[i] = lean_flecs_Entity_unbox(lean_array_get_core(events, i));
        }
        if (events_size < FLECS_EVENT_DESC_MAX) {
            desc_c.events[events_size] = 0;
        }
    }
    desc_c.yield_existing = LEAN_POD_CTOR_GET(desc, LEAN_FLECS_ObserverDesc_yieldExisting);
    {
        desc_c.callback = lean_flecs_observer_callback;
        lean_object* callback = LEAN_POD_CTOR_GET(desc, LEAN_FLECS_ObserverDesc_callback);
        lean_inc_ref(callback);
        desc_c.callback_ctx = callback;
        desc_c.callback_ctx_free = lean_flecs_obj_ctx_free;
    }
    {
        lean_object* obsa = LEAN_POD_CTOR_GET(desc, LEAN_FLECS_ObserverDesc_observable);
        if (lean_option_is_some(obsa)) {
            desc_c.observable = lean_flecs_Poly_unbox(lean_ctor_get(obsa, 0));
        }
    }
    return lean_io_result_mk_ok(lean_flecs_Entity_box(
        ecs_observer_init(lean_flecs_World_fromRepr(world), &desc_c)
    ));
}

LEAN_EXPORT lean_obj_res lean_flecs_World_observerGet(lean_flecs_World world, lean_flecs_Entity observer, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_Observer_box(
        ecs_observer_get(lean_flecs_World_fromRepr(world), lean_flecs_Entity_fromRepr(observer))
    ));
}
