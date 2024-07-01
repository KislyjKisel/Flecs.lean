#include <lean/lean.h>
#include <flecs.h>
#include <flecs.lean/types.h>

static void lean_flecs_ctx_free(void* ctx) {
    lean_dec((lean_object*)ctx);
}

LEAN_EXPORT lean_obj_res lean_flecs_init(lean_obj_arg ctx, lean_obj_arg io_) {
    ecs_world_t* world = ecs_init();
    ecs_set_ctx(world, ctx, lean_flecs_ctx_free);
    return lean_io_result_mk_ok(lean_flecs_World_box(world));
}

LEAN_EXPORT lean_obj_res lean_flecs_mini(lean_obj_arg ctx, lean_obj_arg io_) {
    ecs_world_t* world = ecs_mini();
    ecs_set_ctx(world, ctx, lean_flecs_ctx_free);
    return lean_io_result_mk_ok(lean_flecs_World_box(world));
}

LEAN_EXPORT lean_obj_res lean_flecs_initWithArgs(lean_obj_arg ctx, b_lean_obj_arg args, lean_obj_arg io_) {
    size_t size = lean_array_size(args);
    char** argv = malloc(size * sizeof(char*));
    for (size_t i = 0; i < size; ++i) {
        argv[i] = (char*)lean_string_cstr(lean_array_get_core(args, i));
    }
    ecs_world_t* world = ecs_init_w_args(size, argv);
    free(argv);
    ecs_set_ctx(world, ctx, lean_flecs_ctx_free);
    return lean_io_result_mk_ok(lean_flecs_World_box(world));
}

LEAN_EXPORT lean_obj_res lean_flecs_fini(lean_flecs_World world, lean_obj_arg io_) {
    ecs_fini(lean_flecs_World_fromRepr(world));
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_isFini(lean_flecs_World world, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box(
        ecs_is_fini(lean_flecs_World_fromRepr(world))
    ));
}

static void lean_flecs_FiniAction_wrapper(ecs_world_t* world, void* ctx) {
    // called only once before the world is destroyed or the action is unregistered
    lean_object* action = (lean_object*)ctx;
    lean_apply_2(action, lean_flecs_World_box(world), lean_io_mk_world());
}

LEAN_EXPORT lean_obj_res lean_flecs_atFini(lean_flecs_World world, lean_obj_arg action, lean_obj_arg io_) {
    ecs_atfini(lean_flecs_World_fromRepr(world), lean_flecs_FiniAction_wrapper, action);
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_entities(lean_flecs_World world, lean_obj_arg io_) {
    ecs_entities_t entities = ecs_get_entities(lean_flecs_World_fromRepr(world));
    lean_object* arr = lean_alloc_array(entities.alive_count, entities.alive_count);
    for (size_t i = 0; i < entities.alive_count; ++i) {
        lean_array_set_core(arr, i, lean_flecs_Entity_box(entities.ids[i]));
    }
    return lean_io_result_mk_ok(arr);
}

LEAN_EXPORT lean_obj_res lean_flecs_frameBegin(lean_flecs_World world, lean_flecs_FTime deltaTime, lean_obj_arg io_) {
    ecs_frame_begin(
        lean_flecs_World_fromRepr(world),
        lean_flecs_FTime_fromRepr(deltaTime)
    );
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_frameEnd(lean_flecs_World world, lean_obj_arg io_) {
    ecs_frame_end(lean_flecs_World_fromRepr(world));
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_measureFrameTime(lean_flecs_World world, uint8_t enable, lean_obj_arg io_) {
    ecs_measure_frame_time(lean_flecs_World_fromRepr(world), enable);
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_measureSystemTime(lean_flecs_World world, uint8_t enable, lean_obj_arg io_) {
    ecs_measure_system_time(lean_flecs_World_fromRepr(world), enable);
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_quit(lean_flecs_World world, lean_obj_arg io_) {
    ecs_quit(lean_flecs_World_fromRepr(world));
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_runPostFrame(lean_flecs_World world, lean_obj_arg action, lean_obj_arg io_) {
    ecs_run_post_frame(lean_flecs_World_fromRepr(world), lean_flecs_FiniAction_wrapper, action);
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_setTargetFps(lean_flecs_World world, lean_flecs_FTime targetFps, lean_obj_arg io_) {
    ecs_set_target_fps(
        lean_flecs_World_fromRepr(world),
        lean_flecs_FTime_fromRepr(targetFps)
    );
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_shouldQuit(lean_flecs_World world, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box(
        ecs_should_quit(lean_flecs_World_fromRepr(world))
    ));
}

LEAN_EXPORT lean_obj_res lean_flecs_readonlyBegin(lean_flecs_World world, uint8_t multiThreaded, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box(
        ecs_readonly_begin(lean_flecs_World_fromRepr(world), multiThreaded)
    ));
}

LEAN_EXPORT lean_obj_res lean_flecs_readonlyEnd(lean_flecs_World world, lean_obj_arg io_) {
    ecs_readonly_end(lean_flecs_World_fromRepr(world));
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_merge(lean_flecs_World world, lean_obj_arg io_) {
    ecs_merge(lean_flecs_World_fromRepr(world));
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_deferBegin(lean_flecs_World world, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box(
        ecs_defer_begin(lean_flecs_World_fromRepr(world))
    ));
}

LEAN_EXPORT lean_obj_res lean_flecs_isDeferred(lean_flecs_World world, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box(
        ecs_is_deferred(lean_flecs_World_fromRepr(world))
    ));
}

LEAN_EXPORT lean_obj_res lean_flecs_deferEnd(lean_flecs_World world, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box(
        ecs_defer_end(lean_flecs_World_fromRepr(world))
    ));
}

LEAN_EXPORT lean_obj_res lean_flecs_deferSuspend(lean_flecs_World world, lean_obj_arg io_) {
    ecs_defer_suspend(lean_flecs_World_fromRepr(world));
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_deferResume(lean_flecs_World world, lean_obj_arg io_) {
    ecs_defer_resume(lean_flecs_World_fromRepr(world));
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_setStageCount(lean_flecs_World world, uint32_t stages, lean_obj_arg io_) {
    ecs_set_stage_count(lean_flecs_World_fromRepr(world), (int32_t)stages);
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_getStageCount(lean_flecs_World world, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box_uint32(
        ecs_get_stage_count(lean_flecs_World_fromRepr(world))
    ));
}

LEAN_EXPORT lean_obj_res lean_flecs_stageGetId(lean_flecs_World world, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box_uint32(
        ecs_stage_get_id(lean_flecs_World_fromRepr(world))
    ));
}

LEAN_EXPORT lean_obj_res lean_flecs_getStage(lean_flecs_World world, uint32_t stageId, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_World_box(
        ecs_get_stage(lean_flecs_World_fromRepr(world), stageId)
    ));
}

LEAN_EXPORT lean_obj_res lean_flecs_stageIsReadonly(lean_flecs_World world, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box(
        ecs_stage_is_readonly(lean_flecs_World_fromRepr(world))
    ));
}

LEAN_EXPORT lean_obj_res lean_flecs_stageNew(lean_flecs_World world, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_World_box(
        ecs_stage_new(lean_flecs_World_fromRepr(world))
    ));
}

LEAN_EXPORT lean_obj_res lean_flecs_stageFree(lean_flecs_World world, lean_obj_arg io_) {
    ecs_stage_free(lean_flecs_World_fromRepr(world));
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_setCtx(lean_flecs_World world, lean_obj_arg value, lean_obj_arg io_) {
    ecs_set_ctx(lean_flecs_World_fromRepr(world), value, lean_flecs_ctx_free);
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_getCtx(lean_flecs_World world, lean_obj_arg io_) {
    return lean_io_result_mk_ok(
        (lean_object*)ecs_get_ctx(lean_flecs_World_fromRepr(world))
    );
}

LEAN_EXPORT lean_obj_res lean_flecs_getBuildInfo(lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_BuildInfo_box(ecs_get_build_info()));
}

LEAN_EXPORT lean_obj_res lean_flecs_getWorldInfo(lean_flecs_World world, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_WorldInfo_box(
        ecs_get_world_info(lean_flecs_World_fromRepr(world))
    ));
}

LEAN_EXPORT lean_obj_res lean_flecs_dim(lean_flecs_World world, uint32_t entityCount, lean_obj_arg io_) {
    ecs_dim(lean_flecs_World_fromRepr(world), (int32_t)entityCount);
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_setEntityRange(lean_flecs_World world, lean_flecs_Entity idStart, lean_flecs_Entity idEnd, lean_obj_arg io_) {
    ecs_set_entity_range(
        lean_flecs_World_fromRepr(world),
        lean_flecs_Entity_fromRepr(idStart),
        lean_flecs_Entity_fromRepr(idEnd)
    );
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_enableRangeCheck(lean_flecs_World world, uint8_t enable, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box(
        ecs_enable_range_check(lean_flecs_World_fromRepr(world), enable)
    ));
}

LEAN_EXPORT lean_obj_res lean_flecs_getMaxId(lean_flecs_World world, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_Entity_box(
        ecs_get_max_id(lean_flecs_World_fromRepr(world))
    ));
}

LEAN_EXPORT lean_obj_res lean_flecs_runAperiodic(lean_flecs_World world, uint32_t flags, lean_obj_arg io_) {
    ecs_run_aperiodic(
        lean_flecs_World_fromRepr(world),
        flags
    );
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_deleteEmptyTables(
    lean_flecs_World world, lean_flecs_Id id, uint16_t clearGeneration, uint16_t deleteGeneration,
    uint32_t minIdCount, double timeBudgetSeconds, lean_obj_arg io_
) {
    return lean_io_result_mk_ok(lean_box_uint32(ecs_delete_empty_tables(
        lean_flecs_World_fromRepr(world),
        lean_flecs_Id_fromRepr(id),
        clearGeneration,
        deleteGeneration,
        (int32_t)minIdCount,
        timeBudgetSeconds
    )));
}

// TODO: lean_flecs_getWorld (const pointer)
// LEAN_EXPORT lean_obj_res lean_flecs_getWorld(b_lean_obj_arg poly, lean_obj_arg io_) {
//     return lean_io_result_mk_ok(lean_flecs_World_box(
//         ecs_get_world(lean_flecs_Poly_fromRepr(poly))
//     ));
// }

LEAN_EXPORT lean_obj_res lean_flecs_getEntity(b_lean_obj_arg poly, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_Entity_box(
        ecs_get_entity(lean_flecs_Poly_fromRepr(poly))
    ));
}

LEAN_EXPORT lean_flecs_Id lean_flecs_makePair(lean_flecs_Entity first, lean_flecs_Entity second) {
    return lean_flecs_Id_toRepr(ecs_make_pair(
        lean_flecs_Entity_fromRepr(first),
        lean_flecs_Entity_fromRepr(second)
    ));
}

#define LEAN_FLECS_DEFINE_POLY_IS(leanty, cty)\
LEAN_EXPORT lean_obj_arg lean_flecs_Poly_as##leanty(lean_flecs_Poly poly, lean_obj_arg io_) {\
    lean_object* res;\
    if (flecs_poly_is(lean_flecs_Poly_fromRepr(poly), cty)) {\
        lean_inc_ref(poly);\
        res = lean_mk_option_some(poly);\
    }\
    else {\
        res = lean_mk_option_none();\
    }\
    return lean_io_result_mk_ok(res);\
}

LEAN_FLECS_DEFINE_POLY_IS(World, ecs_world_t)
LEAN_FLECS_DEFINE_POLY_IS(Query, ecs_query_t)
