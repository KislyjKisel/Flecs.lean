#include <assert.h>
#include <lean/lean.h>
#include <flecs.h>
#include <flecs.lean/types.h>
#include "../util.h"

#ifdef static_assert
static_assert(sizeof(EcsTickSource) == 8 && ECS_ALIGNOF(EcsTickSource) == 4); // Storable TickSource
#endif

static inline lean_obj_res lean_flecs_TickSource_box(EcsTickSource tickSource) {
    lean_object* obj = lean_alloc_ctor(0, 0, 4 + 1);
    lean_ctor_set_uint8(obj, 4, tickSource.tick);
    lean_ctor_set_float32(obj, 0, tickSource.time_elapsed);
    return obj;
}

static inline EcsTickSource lean_flecs_TickSource_fromRepr(b_lean_obj_arg obj) {
    return (EcsTickSource){
        .tick = lean_ctor_get_uint8(obj, 4),
        .time_elapsed = lean_ctor_get_float32(obj, 0),
    };
}

LEAN_POD_RWBYTES_INST(Flecs_TickSource, EcsTickSource, lean_object*, lean_flecs_TickSource_box, lean_flecs_TickSource_box, lean_flecs_TickSource_fromRepr) 

#define LEAN_FLECS_SystemDesc_LAYOUT 0, 3, 0, 2, 1, 0, 2
#define LEAN_FLECS_SystemDesc_entity U64, 0, LEAN_FLECS_SystemDesc_LAYOUT
#define LEAN_FLECS_SystemDesc_query BOX, 0, LEAN_FLECS_SystemDesc_LAYOUT
#define LEAN_FLECS_SystemDesc_callback BOX, 1, LEAN_FLECS_SystemDesc_LAYOUT
#define LEAN_FLECS_SystemDesc_interval F32, 0, LEAN_FLECS_SystemDesc_LAYOUT
#define LEAN_FLECS_SystemDesc_rate BOX, 2, LEAN_FLECS_SystemDesc_LAYOUT
#define LEAN_FLECS_SystemDesc_tickSource U64, 1, LEAN_FLECS_SystemDesc_LAYOUT
#define LEAN_FLECS_SystemDesc_multiThreaded U8, 0, LEAN_FLECS_SystemDesc_LAYOUT
#define LEAN_FLECS_SystemDesc_immediate U8, 1, LEAN_FLECS_SystemDesc_LAYOUT

lean_object* lean_flecs_Dynamic_mk_empty(lean_obj_arg unit_);

static void lean_flecs_system_callback(ecs_iter_t* it) {
    lean_object* callback = it->callback_ctx;
    lean_inc_ref(callback);
    lean_object* param = it->param;
    // Param won't be passed when the system runs automatically
    if (it->param == NULL) {
        param = lean_flecs_Dynamic_mk_empty(lean_box(0));
    }
    else {
        lean_inc(param);
    }
    // Iterator can't be copied because changes to it (e.g. setInterruptedBy) must be visible to the caller.
    lean_dec_ref(lean_apply_3(callback, lean_flecs_Iter_alloc_pointer(it), param, lean_box(0)));
}

LEAN_EXPORT lean_obj_res lean_flecs_World_systemInit(lean_flecs_World world, b_lean_obj_arg desc, lean_obj_arg io_) {
    ecs_system_desc_t desc_c = {0};
    desc_c.entity = LEAN_POD_CTOR_GET(desc, LEAN_FLECS_SystemDesc_entity);
    lean_object* queryDesc = LEAN_POD_CTOR_GET(desc, LEAN_FLECS_SystemDesc_query);
    lean_inc_ref(queryDesc);
    desc_c.query = lean_flecs_QueryDesc_fromRepr(queryDesc);
    lean_object* callback = LEAN_POD_CTOR_GET(desc, LEAN_FLECS_SystemDesc_callback);
    lean_inc_ref(callback);
    desc_c.callback = lean_flecs_system_callback;
    desc_c.callback_ctx = callback;
    desc_c.callback_ctx_free = lean_flecs_obj_ctx_free;
    desc_c.interval = LEAN_POD_CTOR_GET(desc, LEAN_FLECS_SystemDesc_interval);
    desc_c.rate = lean_pod_Int32_unbox(LEAN_POD_CTOR_GET(desc, LEAN_FLECS_SystemDesc_rate));
    desc_c.tick_source = LEAN_POD_CTOR_GET(desc, LEAN_FLECS_SystemDesc_tickSource);
    desc_c.multi_threaded = LEAN_POD_CTOR_GET(desc, LEAN_FLECS_SystemDesc_multiThreaded);
    desc_c.immediate = LEAN_POD_CTOR_GET(desc, LEAN_FLECS_SystemDesc_immediate);
    return lean_io_result_mk_ok(lean_flecs_Entity_box(ecs_system_init(lean_flecs_World_fromRepr(world), &desc_c)));
}

LEAN_POD_PTR_ALIAS(flecs_System, const ecs_system_t*);

LEAN_EXPORT lean_obj_res lean_flecs_System_query(lean_flecs_System system, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_Query_box(lean_flecs_System_fromRepr(system)->query));
}

LEAN_EXPORT lean_obj_res lean_flecs_System_queryEntity(lean_flecs_System system, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_Entity_box(lean_flecs_System_fromRepr(system)->query_entity));
}

LEAN_EXPORT lean_obj_res lean_flecs_System_tickSource(lean_flecs_System system, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_Entity_box(lean_flecs_System_fromRepr(system)->tick_source));
}

LEAN_EXPORT lean_obj_res lean_flecs_System_multiThreaded(lean_flecs_System system, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box(0 != lean_flecs_System_fromRepr(system)->multi_threaded));
}

LEAN_EXPORT lean_obj_res lean_flecs_System_immediate(lean_flecs_System system, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box(0 != lean_flecs_System_fromRepr(system)->immediate));
}

LEAN_EXPORT lean_obj_res lean_flecs_System_timeSpent(lean_flecs_System system, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_FTime_box(lean_flecs_System_fromRepr(system)->time_spent));
}

LEAN_EXPORT lean_obj_res lean_flecs_System_timePassed(lean_flecs_System system, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_FTime_box(lean_flecs_System_fromRepr(system)->time_passed));
}

LEAN_EXPORT lean_obj_res lean_flecs_System_lastFrame(lean_flecs_System system, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_pod_Int64_box(lean_flecs_System_fromRepr(system)->last_frame));
}

LEAN_EXPORT lean_obj_res lean_flecs_System_world(lean_flecs_System system, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_World_box(lean_flecs_System_fromRepr(system)->world));
}

LEAN_EXPORT lean_obj_res lean_flecs_System_entity(lean_flecs_System system, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_Entity_box(lean_flecs_System_fromRepr(system)->entity));
}

LEAN_EXPORT lean_obj_res lean_flecs_World_systemGet(lean_flecs_World world, lean_flecs_Entity system, lean_obj_arg io_) {
    const ecs_system_t* system_ptr = ecs_system_get(lean_flecs_World_fromRepr(world), lean_flecs_Entity_fromRepr(system));
    if (system_ptr == NULL) {
        return lean_io_result_mk_ok(lean_mk_option_none());
    }
    return lean_io_result_mk_ok(lean_mk_option_some(lean_flecs_System_box(system_ptr)));
}

LEAN_EXPORT lean_obj_res lean_flecs_World_run(
    lean_flecs_World world, lean_flecs_Entity system,
    lean_flecs_FTime deltaTime, b_lean_obj_arg param, lean_obj_arg io_
) {
    return lean_io_result_mk_ok(lean_flecs_Entity_box(ecs_run(
        lean_flecs_World_fromRepr(world),
        lean_flecs_Entity_fromRepr(system),
        lean_flecs_FTime_fromRepr(deltaTime),
        param
    )));
}

LEAN_EXPORT lean_obj_res lean_flecs_World_runWorker(
    lean_flecs_World world, lean_flecs_Entity system, lean_pod_Int32 stageCurrent,
    lean_pod_Int32 stageCount, lean_flecs_FTime deltaTime, b_lean_obj_arg param, lean_obj_arg io_
) {
    return lean_io_result_mk_ok(lean_flecs_Entity_box(ecs_run_worker(
        lean_flecs_World_fromRepr(world),
        lean_flecs_Entity_fromRepr(system),
        lean_pod_Int32_fromRepr(stageCurrent),
        lean_pod_Int32_fromRepr(stageCount),
        lean_flecs_FTime_fromRepr(deltaTime),
        param
    )));
}

LEAN_EXPORT lean_obj_res lean_flecs_World_systemImport(lean_flecs_World world, lean_obj_arg io_) {
    FlecsSystemImport(lean_flecs_World_fromRepr(world));
    return lean_io_result_mk_ok(lean_box(0));
}
