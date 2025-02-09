#include <lean/lean.h>
#include <flecs.h>
#include <flecs.lean/types.h>

#define LEAN_FLECS_AppDesc_LAYOUT 0, 2, 0, 0, 2, 1, 2
#define LEAN_FLECS_AppDesc_targetFps F32, 0, LEAN_FLECS_AppDesc_LAYOUT
#define LEAN_FLECS_AppDesc_deltaTime F32, 1, LEAN_FLECS_AppDesc_LAYOUT
#define LEAN_FLECS_AppDesc_threads BOX, 0, LEAN_FLECS_AppDesc_LAYOUT
#define LEAN_FLECS_AppDesc_frames BOX, 1, LEAN_FLECS_AppDesc_LAYOUT
#define LEAN_FLECS_AppDesc_enableRest U8, 0, LEAN_FLECS_AppDesc_LAYOUT
#define LEAN_FLECS_AppDesc_enableStats U8, 1, LEAN_FLECS_AppDesc_LAYOUT
#define LEAN_FLECS_AppDesc_port U16, 0, LEAN_FLECS_AppDesc_LAYOUT

#define LEAN_FLECS_AppDescX_LAYOUT 0, 5, 0, 0, 2, 1, 2
#define LEAN_FLECS_AppDescX_targetFps F32, 0, LEAN_FLECS_AppDescX_LAYOUT
#define LEAN_FLECS_AppDescX_deltaTime F32, 1, LEAN_FLECS_AppDescX_LAYOUT
#define LEAN_FLECS_AppDescX_threads BOX, 0, LEAN_FLECS_AppDescX_LAYOUT
#define LEAN_FLECS_AppDescX_frames BOX, 1, LEAN_FLECS_AppDescX_LAYOUT
#define LEAN_FLECS_AppDescX_enableRest U8, 0, LEAN_FLECS_AppDescX_LAYOUT
#define LEAN_FLECS_AppDescX_enableStats U8, 1, LEAN_FLECS_AppDescX_LAYOUT
#define LEAN_FLECS_AppDescX_port U16, 0, LEAN_FLECS_AppDescX_LAYOUT
#define LEAN_FLECS_AppDescX_init BOX, 2, LEAN_FLECS_AppDescX_LAYOUT
#define LEAN_FLECS_AppDescX_run BOX, 3, LEAN_FLECS_AppDescX_LAYOUT
#define LEAN_FLECS_AppDescX_frame BOX, 4, LEAN_FLECS_AppDescX_LAYOUT

static int lean_flecs_AppRunAction_wrapper(ecs_world_t* world, ecs_app_desc_t* desc) {
    lean_object* optInit = LEAN_POD_CTOR_GET(desc->ctx, LEAN_FLECS_AppDescX_init);
    lean_object* world_box = lean_flecs_World_box(world);
    if (lean_option_is_some(optInit)) {
        lean_object* init = lean_ctor_get(optInit, 0);
        lean_inc_ref(init);
        lean_inc_ref(world_box);
        lean_dec_ref(lean_apply_2(init, world_box, lean_box(0)));
    }
    lean_object* optRun = LEAN_POD_CTOR_GET(desc->ctx, LEAN_FLECS_AppDescX_run);
    if (lean_option_is_some(optRun)) {
        lean_object* run = lean_ctor_get(optRun, 0);
        lean_inc_ref(run);
        lean_object* res_box = lean_apply_2(run, world_box, lean_box(0));
        int32_t res = lean_pod_Int32_unbox(lean_ctor_get(res_box, 0));
        lean_dec_ref(res_box);
        return res;
    }
    else {
        lean_dec_ref_cold(world_box);
        return ecs_app_run(world, desc);
    }
}

static int lean_flecs_AppFrameAction_wrapper(ecs_world_t* world, const ecs_app_desc_t* desc) {
    lean_object* frame = lean_ctor_get(LEAN_POD_CTOR_GET(desc->ctx, LEAN_FLECS_AppDescX_frame), 0);
    lean_inc_ref(frame);
    lean_object* res_box = lean_apply_2(frame, lean_flecs_World_box(world), lean_box(0));
    int32_t res = lean_pod_Int32_unbox(lean_ctor_get(res_box, 0));
    lean_dec_ref(res_box);
    return res;
}

LEAN_EXPORT lean_obj_res lean_flecs_World_appRun(lean_flecs_World world, lean_obj_arg desc, lean_obj_arg io_) {
    ecs_app_desc_t desc_c = {};
    desc_c.target_fps = LEAN_POD_CTOR_GET(desc, LEAN_FLECS_AppDescX_targetFps);
    desc_c.delta_time = LEAN_POD_CTOR_GET(desc, LEAN_FLECS_AppDescX_deltaTime);
    desc_c.threads = lean_pod_Int32_unbox(LEAN_POD_CTOR_GET(desc, LEAN_FLECS_AppDescX_threads));
    desc_c.frames = lean_pod_Int32_unbox(LEAN_POD_CTOR_GET(desc, LEAN_FLECS_AppDescX_frames));
    desc_c.enable_rest = 0 != LEAN_POD_CTOR_GET(desc, LEAN_FLECS_AppDescX_enableRest);
    desc_c.enable_stats = 0 != LEAN_POD_CTOR_GET(desc, LEAN_FLECS_AppDescX_enableStats);
    desc_c.port = LEAN_POD_CTOR_GET(desc, LEAN_FLECS_AppDescX_port);
    ecs_app_set_run_action(lean_flecs_AppRunAction_wrapper);
    if (lean_option_is_some(LEAN_POD_CTOR_GET(desc, LEAN_FLECS_AppDescX_frame))) {
        ecs_app_set_frame_action(lean_flecs_AppFrameAction_wrapper);
    }
    desc_c.ctx = desc;
    int res = ecs_app_run(lean_flecs_World_fromRepr(world), &desc_c);
    lean_dec_ref(desc);
    return lean_io_result_mk_ok(lean_pod_Int32_box(res));
}

LEAN_EXPORT lean_obj_res lean_flecs_World_appRunFrame(lean_flecs_World world, b_lean_obj_arg desc, lean_obj_arg io_) {
    ecs_app_desc_t desc_c = {};
    desc_c.target_fps = LEAN_POD_CTOR_GET(desc, LEAN_FLECS_AppDesc_targetFps);
    desc_c.delta_time = LEAN_POD_CTOR_GET(desc, LEAN_FLECS_AppDesc_deltaTime);
    desc_c.threads = lean_pod_Int32_unbox(LEAN_POD_CTOR_GET(desc, LEAN_FLECS_AppDesc_threads));
    desc_c.frames = lean_pod_Int32_unbox(LEAN_POD_CTOR_GET(desc, LEAN_FLECS_AppDesc_frames));
    desc_c.enable_rest = 0 != LEAN_POD_CTOR_GET(desc, LEAN_FLECS_AppDesc_enableRest);
    desc_c.enable_stats = 0 != LEAN_POD_CTOR_GET(desc, LEAN_FLECS_AppDesc_enableStats);
    desc_c.port = LEAN_POD_CTOR_GET(desc, LEAN_FLECS_AppDesc_port);
    return lean_io_result_mk_ok(lean_pod_Int32_box(ecs_app_run_frame(lean_flecs_World_fromRepr(world), &desc_c)));
}
