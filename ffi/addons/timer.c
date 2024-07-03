#include <lean/lean.h>
#include <flecs.h>
#include <flecs.lean/types.h>

#define LEAN_FLECS_Timer_LAYOUT 0, 4, 0, 0, 0, 0, 2
#define LEAN_FLECS_Timer_timeout BOX, 0, LEAN_FLECS_Timer_LAYOUT
#define LEAN_FLECS_Timer_time BOX, 1, LEAN_FLECS_Timer_LAYOUT
#define LEAN_FLECS_Timer_overshoot BOX, 2, LEAN_FLECS_Timer_LAYOUT
#define LEAN_FLECS_Timer_firedCount BOX, 3, LEAN_FLECS_Timer_LAYOUT
#define LEAN_FLECS_Timer_active U8, 0, LEAN_FLECS_Timer_LAYOUT
#define LEAN_FLECS_Timer_singleShot U8, 1, LEAN_FLECS_Timer_LAYOUT

#ifdef static_assert
static_assert(sizeof(EcsTimer) == 20 && ECS_ALIGNOF(EcsTimer) == 4); // Storable Timer
#endif

static inline lean_obj_res lean_flecs_Timer_box(EcsTimer timer) {
    lean_object* obj = LEAN_POD_ALLOC_CTOR(LEAN_FLECS_Timer_LAYOUT);
    LEAN_POD_CTOR_SET(obj, lean_flecs_FTime_box(timer.timeout), LEAN_FLECS_Timer_timeout);
    LEAN_POD_CTOR_SET(obj, lean_flecs_FTime_box(timer.time), LEAN_FLECS_Timer_time);
    LEAN_POD_CTOR_SET(obj, lean_flecs_FTime_box(timer.overshoot), LEAN_FLECS_Timer_overshoot);
    LEAN_POD_CTOR_SET(obj, lean_pod_Int32_box(timer.fired_count), LEAN_FLECS_Timer_firedCount);
    LEAN_POD_CTOR_SET(obj, timer.active, LEAN_FLECS_Timer_active);
    LEAN_POD_CTOR_SET(obj, timer.single_shot, LEAN_FLECS_Timer_singleShot);
    return obj;
}

static inline EcsTimer lean_flecs_Timer_fromRepr(b_lean_obj_arg obj) {
    return (EcsTimer){
        .timeout = lean_flecs_FTime_unbox(LEAN_POD_CTOR_GET(obj, LEAN_FLECS_Timer_timeout)),
        .time = lean_flecs_FTime_unbox(LEAN_POD_CTOR_GET(obj, LEAN_FLECS_Timer_time)),
        .overshoot = lean_flecs_FTime_unbox(LEAN_POD_CTOR_GET(obj, LEAN_FLECS_Timer_overshoot)),
        .fired_count = lean_pod_Int32_unbox(LEAN_POD_CTOR_GET(obj, LEAN_FLECS_Timer_firedCount)),
        .active = LEAN_POD_CTOR_GET(obj, LEAN_FLECS_Timer_active),
        .single_shot = LEAN_POD_CTOR_GET(obj, LEAN_FLECS_Timer_singleShot),
    };
}

LEAN_POD_RWBYTES_INST(Flecs_Timer, EcsTimer, lean_object*, lean_flecs_Timer_box, lean_flecs_Timer_box, lean_flecs_Timer_fromRepr)

#define LEAN_FLECS_RateFilter_LAYOUT 0, 3, 0, 1, 0, 0, 0
#define LEAN_FLECS_RateFilter_src U64, 0, LEAN_FLECS_RateFilter_LAYOUT
#define LEAN_FLECS_RateFilter_rate BOX, 0, LEAN_FLECS_RateFilter_LAYOUT
#define LEAN_FLECS_RateFilter_tickCount BOX, 1, LEAN_FLECS_RateFilter_LAYOUT
#define LEAN_FLECS_RateFilter_timeElapsed BOX, 2, LEAN_FLECS_RateFilter_LAYOUT

#ifdef static_assert
static_assert(sizeof(EcsRateFilter) == 24 && ECS_ALIGNOF(EcsRateFilter) == 8); // Storable RateFilter
#endif

static inline lean_obj_res lean_flecs_RateFilter_box(EcsRateFilter rateFilter) {
    lean_object* obj = LEAN_POD_ALLOC_CTOR(LEAN_FLECS_RateFilter_LAYOUT);
    LEAN_POD_CTOR_SET(obj, rateFilter.src, LEAN_FLECS_RateFilter_src);
    LEAN_POD_CTOR_SET(obj, lean_pod_Int32_box(rateFilter.rate), LEAN_FLECS_RateFilter_rate);
    LEAN_POD_CTOR_SET(obj, lean_pod_Int32_box(rateFilter.tick_count), LEAN_FLECS_RateFilter_tickCount);
    LEAN_POD_CTOR_SET(obj, lean_flecs_FTime_box(rateFilter.time_elapsed), LEAN_FLECS_RateFilter_timeElapsed);
    return obj;
}

static inline EcsRateFilter lean_flecs_RateFilter_fromRepr(b_lean_obj_arg obj) {
    return (EcsRateFilter){
        .src = LEAN_POD_CTOR_GET(obj, LEAN_FLECS_RateFilter_src),
        .rate = lean_pod_Int32_unbox(LEAN_POD_CTOR_GET(obj, LEAN_FLECS_RateFilter_rate)),
        .tick_count = lean_pod_Int32_unbox(LEAN_POD_CTOR_GET(obj, LEAN_FLECS_RateFilter_tickCount)),
        .time_elapsed = lean_flecs_FTime_unbox(LEAN_POD_CTOR_GET(obj, LEAN_FLECS_RateFilter_timeElapsed))
    };
}

LEAN_POD_RWBYTES_INST(Flecs_RateFilter, EcsRateFilter, lean_object*, lean_flecs_RateFilter_box, lean_flecs_RateFilter_box, lean_flecs_RateFilter_fromRepr)

LEAN_EXPORT lean_obj_res lean_flecs_World_setTimeout(lean_flecs_World world, lean_flecs_Entity tickSource, lean_flecs_FTime timeout, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_Entity_box(ecs_set_timeout(
        lean_flecs_World_fromRepr(world),
        lean_flecs_Entity_fromRepr(tickSource),
        lean_flecs_FTime_fromRepr(timeout)
    )));
}

LEAN_EXPORT lean_obj_res lean_flecs_World_getTimeout(lean_flecs_World world, lean_flecs_Entity tickSource, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_FTime_box(ecs_get_timeout(
        lean_flecs_World_fromRepr(world),
        lean_flecs_Entity_fromRepr(tickSource)
    )));
}

LEAN_EXPORT lean_obj_res lean_flecs_World_setInterval(lean_flecs_World world, lean_flecs_Entity tickSource, lean_flecs_FTime interval, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_Entity_box(ecs_set_interval(
        lean_flecs_World_fromRepr(world),
        lean_flecs_Entity_fromRepr(tickSource),
        lean_flecs_FTime_fromRepr(interval)
    )));
}

LEAN_EXPORT lean_obj_res lean_flecs_World_getInterval(lean_flecs_World world, lean_flecs_Entity tickSource, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_FTime_box(ecs_get_interval(
        lean_flecs_World_fromRepr(world),
        lean_flecs_Entity_fromRepr(tickSource)
    )));
}

LEAN_EXPORT lean_obj_res lean_flecs_World_startTimer(lean_flecs_World world, lean_flecs_Entity tickSource, lean_obj_arg io_) {
    ecs_start_timer(lean_flecs_World_fromRepr(world), lean_flecs_Entity_fromRepr(tickSource));
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_World_stopTimer(lean_flecs_World world, lean_flecs_Entity tickSource, lean_obj_arg io_) {
    ecs_stop_timer(lean_flecs_World_fromRepr(world), lean_flecs_Entity_fromRepr(tickSource));
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_World_resetTimer(lean_flecs_World world, lean_flecs_Entity tickSource, lean_obj_arg io_) {
    ecs_reset_timer(lean_flecs_World_fromRepr(world), lean_flecs_Entity_fromRepr(tickSource));
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_World_randomizeTimers(lean_flecs_World world, lean_obj_arg io_) {
    ecs_randomize_timers(lean_flecs_World_fromRepr(world));
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_World_setRate(
    lean_flecs_World world, lean_flecs_Entity tickSource, lean_pod_Int32 rate,
    lean_flecs_Entity source, lean_obj_arg io_
) {
    return lean_io_result_mk_ok(lean_flecs_Entity_box(ecs_set_rate(
        lean_flecs_World_fromRepr(world),
        lean_flecs_Entity_fromRepr(tickSource),
        lean_pod_Int32_fromRepr(rate),
        lean_flecs_Entity_fromRepr(source)
    )));
}

LEAN_EXPORT lean_obj_res lean_flecs_World_setTickSource(
    lean_flecs_World world, lean_flecs_Entity system, lean_flecs_Entity tickSource, lean_obj_arg io_
) {
    ecs_set_tick_source(lean_flecs_World_fromRepr(world), lean_flecs_Entity_fromRepr(system), lean_flecs_Entity_fromRepr(tickSource));
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_World_timerImport(lean_flecs_World world, lean_obj_arg io_) {
    FlecsTimerImport(lean_flecs_World_fromRepr(world));
    return lean_io_result_mk_ok(lean_box(0));
}
