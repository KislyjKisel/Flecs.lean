#include <lean/lean.h>
#include <flecs.h>
#include <flecs.lean/types.h>
#include "../util.h"

LEAN_EXPORT lean_obj_res lean_flecs_World_pipelineInit(lean_flecs_World world, b_lean_obj_arg desc, lean_obj_arg io_) {
    ecs_pipeline_desc_t desc_c = {0};
    desc_c.entity = lean_ctor_get_uint64(desc, sizeof(lean_object*));
    lean_object* queryDesc = lean_ctor_get(desc, 0);
    lean_inc_ref(queryDesc);
    desc_c.query = lean_flecs_QueryDesc_fromRepr(queryDesc);
    return lean_io_result_mk_ok(lean_flecs_Entity_box(ecs_pipeline_init(lean_flecs_World_fromRepr(world), &desc_c)));
}

LEAN_EXPORT lean_obj_res lean_flecs_World_setPipeline(lean_flecs_World world, lean_flecs_Entity pipeline, lean_obj_arg io_) {
    ecs_set_pipeline(lean_flecs_World_fromRepr(world), lean_flecs_Entity_fromRepr(pipeline));
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_World_getPipeline(lean_flecs_World world, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_Entity_box(ecs_get_pipeline(lean_flecs_World_fromRepr(world))));
}

LEAN_EXPORT lean_obj_res lean_flecs_World_progress(lean_flecs_World world, lean_flecs_FTime deltaTime, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box(ecs_progress(lean_flecs_World_fromRepr(world), lean_flecs_FTime_fromRepr(deltaTime))));
}

LEAN_EXPORT lean_obj_res lean_flecs_World_setTimeScale(lean_flecs_World world, lean_flecs_FTime timeScale, lean_obj_arg io_) {
    ecs_set_time_scale(lean_flecs_World_fromRepr(world), lean_flecs_FTime_fromRepr(timeScale));
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_World_resetClock(lean_flecs_World world, lean_obj_arg io_) {
    ecs_reset_clock(lean_flecs_World_fromRepr(world));
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_World_runPipeline(
    lean_flecs_World world, lean_flecs_Entity pipeline, lean_flecs_FTime deltaTime, lean_obj_arg io_
) {
    ecs_run_pipeline(
        lean_flecs_World_fromRepr(world),
        lean_flecs_Entity_fromRepr(pipeline),
        lean_flecs_FTime_fromRepr(deltaTime)
    );
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_World_setThreads(lean_flecs_World world, lean_pod_Int32 threads, lean_obj_arg io_) {
    ecs_set_threads(lean_flecs_World_fromRepr(world), lean_pod_Int32_fromRepr(threads));
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_World_setTaskThreads(lean_flecs_World world, lean_pod_Int32 taskThreads, lean_obj_arg io_) {
    ecs_set_threads(lean_flecs_World_fromRepr(world), lean_pod_Int32_fromRepr(taskThreads));
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_World_usingTaskThreads(lean_flecs_World world, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box(ecs_using_task_threads(lean_flecs_World_fromRepr(world))));
}
