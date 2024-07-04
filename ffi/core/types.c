#include <lean/lean.h>
#include <flecs.h>
#include <flecs.lean/types.h>

LEAN_POD_DEFINE_EXTERNAL_CLASS(flecs_Iter)
LEAN_POD_DEFINE_EXTERNAL_CLASS(flecs_Ref)

LEAN_EXPORT lean_obj_res lean_flecs_initialize_types(lean_obj_arg io_) {
    LEAN_POD_INITIALIZE_EXTERNAL_CLASS(flecs_Iter, lean_pod_free, lean_pod_default_foreach);
    LEAN_POD_INITIALIZE_EXTERNAL_CLASS(flecs_Ref, lean_pod_free, lean_pod_default_foreach);
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_BuildInfo_compiler(lean_flecs_BuildInfo bi, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_mk_string(lean_flecs_BuildInfo_fromRepr(bi)->compiler));
}

LEAN_EXPORT lean_obj_res lean_flecs_BuildInfo_addons(lean_flecs_BuildInfo bi, lean_obj_arg io_) {
    size_t count = 0;
    const ecs_build_info_t* bic = lean_flecs_BuildInfo_fromRepr(bi);
    const char** ptrs = bic->addons;
    while(ptrs) {
        count += 1;
        ptrs += 1;
    }
    lean_object* arr = lean_alloc_array(count, count);
    for (size_t i = 0; i < count; ++i) {
        lean_array_set_core(arr, i, lean_mk_string(bic->addons[i]));
    }
    return lean_io_result_mk_ok(arr);
}

LEAN_EXPORT lean_obj_res lean_flecs_BuildInfo_version(lean_flecs_BuildInfo bi, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_mk_string(lean_flecs_BuildInfo_fromRepr(bi)->version));
}

LEAN_EXPORT lean_obj_res lean_flecs_BuildInfo_versionMajor(lean_flecs_BuildInfo bi, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box((uint16_t)lean_flecs_BuildInfo_fromRepr(bi)->version_major));
}

LEAN_EXPORT lean_obj_res lean_flecs_BuildInfo_versionMinor(lean_flecs_BuildInfo bi, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box((uint16_t)lean_flecs_BuildInfo_fromRepr(bi)->version_minor));
}

LEAN_EXPORT lean_obj_res lean_flecs_BuildInfo_versionPatch(lean_flecs_BuildInfo bi, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box((uint16_t)lean_flecs_BuildInfo_fromRepr(bi)->version_patch));
}

LEAN_EXPORT lean_obj_res lean_flecs_BuildInfo_debug(lean_flecs_BuildInfo bi, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box(lean_flecs_BuildInfo_fromRepr(bi)->debug));
}

LEAN_EXPORT lean_obj_res lean_flecs_BuildInfo_sanitize(lean_flecs_BuildInfo bi, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box(lean_flecs_BuildInfo_fromRepr(bi)->sanitize));
}

LEAN_EXPORT lean_obj_res lean_flecs_BuildInfo_perfTrace(lean_flecs_BuildInfo bi, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box(lean_flecs_BuildInfo_fromRepr(bi)->perf_trace));
}

LEAN_EXPORT lean_obj_res lean_flecs_WorldInfo_lastComponentId(lean_flecs_WorldInfo wi, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_Entity_box(lean_flecs_WorldInfo_fromRepr(wi)->last_component_id));
}

LEAN_EXPORT lean_obj_res lean_flecs_WorldInfo_minId(lean_flecs_WorldInfo wi, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_Entity_box(lean_flecs_WorldInfo_fromRepr(wi)->min_id));
}

LEAN_EXPORT lean_obj_res lean_flecs_WorldInfo_maxId(lean_flecs_WorldInfo wi, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_Entity_box(lean_flecs_WorldInfo_fromRepr(wi)->max_id));
}

LEAN_EXPORT lean_obj_res lean_flecs_WorldInfo_deltaTimeRaw(lean_flecs_WorldInfo wi, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_FTime_box(lean_flecs_WorldInfo_fromRepr(wi)->delta_time_raw));
}

LEAN_EXPORT lean_obj_res lean_flecs_WorldInfo_deltaTime(lean_flecs_WorldInfo wi, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_FTime_box(lean_flecs_WorldInfo_fromRepr(wi)->delta_time));
}

LEAN_EXPORT lean_obj_res lean_flecs_WorldInfo_timeScale(lean_flecs_WorldInfo wi, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_FTime_box(lean_flecs_WorldInfo_fromRepr(wi)->time_scale));
}

LEAN_EXPORT lean_obj_res lean_flecs_WorldInfo_targetFps(lean_flecs_WorldInfo wi, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_FTime_box(lean_flecs_WorldInfo_fromRepr(wi)->target_fps));
}

LEAN_EXPORT lean_obj_res lean_flecs_WorldInfo_frameTimeTotal(lean_flecs_WorldInfo wi, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_FTime_box(lean_flecs_WorldInfo_fromRepr(wi)->frame_time_total));
}

LEAN_EXPORT lean_obj_res lean_flecs_WorldInfo_systemTimeTotal(lean_flecs_WorldInfo wi, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_FTime_box(lean_flecs_WorldInfo_fromRepr(wi)->system_time_total));
}

LEAN_EXPORT lean_obj_res lean_flecs_WorldInfo_emitTimeTotal(lean_flecs_WorldInfo wi, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_FTime_box(lean_flecs_WorldInfo_fromRepr(wi)->emit_time_total));
}

LEAN_EXPORT lean_obj_res lean_flecs_WorldInfo_mergeTimeTotal(lean_flecs_WorldInfo wi, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_FTime_box(lean_flecs_WorldInfo_fromRepr(wi)->merge_time_total));
}

LEAN_EXPORT lean_obj_res lean_flecs_WorldInfo_worldTimeTotal(lean_flecs_WorldInfo wi, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_FTime_box(lean_flecs_WorldInfo_fromRepr(wi)->world_time_total));
}

LEAN_EXPORT lean_obj_res lean_flecs_WorldInfo_worldTimeTotalRaw(lean_flecs_WorldInfo wi, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_FTime_box(lean_flecs_WorldInfo_fromRepr(wi)->world_time_total_raw));
}

LEAN_EXPORT lean_obj_res lean_flecs_WorldInfo_rematchTimeTotal(lean_flecs_WorldInfo wi, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_FTime_box(lean_flecs_WorldInfo_fromRepr(wi)->rematch_time_total));
}

LEAN_EXPORT lean_obj_res lean_flecs_WorldInfo_frameCountTotal(lean_flecs_WorldInfo wi, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box_uint64((uint64_t)lean_flecs_WorldInfo_fromRepr(wi)->frame_count_total));
}

LEAN_EXPORT lean_obj_res lean_flecs_WorldInfo_mergeCountTotal(lean_flecs_WorldInfo wi, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box_uint64((uint64_t)lean_flecs_WorldInfo_fromRepr(wi)->merge_count_total));
}

LEAN_EXPORT lean_obj_res lean_flecs_WorldInfo_rematchCountTotal(lean_flecs_WorldInfo wi, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box_uint64((uint64_t)lean_flecs_WorldInfo_fromRepr(wi)->rematch_count_total));
}

LEAN_EXPORT lean_obj_res lean_flecs_WorldInfo_idCreateTotal(lean_flecs_WorldInfo wi, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box_uint64((uint64_t)lean_flecs_WorldInfo_fromRepr(wi)->id_create_total));
}

LEAN_EXPORT lean_obj_res lean_flecs_WorldInfo_idDeleteTotal(lean_flecs_WorldInfo wi, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box_uint64((uint64_t)lean_flecs_WorldInfo_fromRepr(wi)->id_delete_total));
}

LEAN_EXPORT lean_obj_res lean_flecs_WorldInfo_tableCreateTotal(lean_flecs_WorldInfo wi, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box_uint64((uint64_t)lean_flecs_WorldInfo_fromRepr(wi)->table_create_total));
}

LEAN_EXPORT lean_obj_res lean_flecs_WorldInfo_tableDeleteTotal(lean_flecs_WorldInfo wi, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box_uint64((uint64_t)lean_flecs_WorldInfo_fromRepr(wi)->table_delete_total));
}

LEAN_EXPORT lean_obj_res lean_flecs_WorldInfo_pipelineBuildCountTotal(lean_flecs_WorldInfo wi, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box_uint64((uint64_t)lean_flecs_WorldInfo_fromRepr(wi)->pipeline_build_count_total));
}

LEAN_EXPORT lean_obj_res lean_flecs_WorldInfo_systemsRanFrame(lean_flecs_WorldInfo wi, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box_uint64((uint64_t)lean_flecs_WorldInfo_fromRepr(wi)->systems_ran_frame));
}

LEAN_EXPORT lean_obj_res lean_flecs_WorldInfo_observersRanFrame(lean_flecs_WorldInfo wi, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box_uint64((uint64_t)lean_flecs_WorldInfo_fromRepr(wi)->observers_ran_frame));
}

LEAN_EXPORT lean_obj_res lean_flecs_WorldInfo_tagIdCount(lean_flecs_WorldInfo wi, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box_uint32((uint32_t)lean_flecs_WorldInfo_fromRepr(wi)->tag_id_count));
}

LEAN_EXPORT lean_obj_res lean_flecs_WorldInfo_componentIdCount(lean_flecs_WorldInfo wi, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box_uint32((uint32_t)lean_flecs_WorldInfo_fromRepr(wi)->component_id_count));
}

LEAN_EXPORT lean_obj_res lean_flecs_WorldInfo_pairIdCount(lean_flecs_WorldInfo wi, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box_uint32((uint32_t)lean_flecs_WorldInfo_fromRepr(wi)->pair_id_count));
}

LEAN_EXPORT lean_obj_res lean_flecs_WorldInfo_tableCount(lean_flecs_WorldInfo wi, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box_uint32((uint32_t)lean_flecs_WorldInfo_fromRepr(wi)->table_count));
}

LEAN_EXPORT lean_obj_res lean_flecs_WorldInfo_emptyTableCount(lean_flecs_WorldInfo wi, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box_uint32((uint32_t)lean_flecs_WorldInfo_fromRepr(wi)->empty_table_count));
}

LEAN_EXPORT lean_obj_res lean_flecs_QueryGroupInfo_matchCount(lean_flecs_QueryGroupInfo qgi, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box_uint32((uint32_t)lean_flecs_QueryGroupInfo_fromRepr(qgi)->match_count));
}

LEAN_EXPORT lean_obj_res lean_flecs_QueryGroupInfo_tableCount(lean_flecs_QueryGroupInfo qgi, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box_uint32((uint32_t)lean_flecs_QueryGroupInfo_fromRepr(qgi)->table_count));
}

LEAN_EXPORT lean_obj_res lean_flecs_QueryGroupInfo_ctx(lean_flecs_QueryGroupInfo qgi, lean_obj_arg io_) {
    return lean_io_result_mk_ok((lean_object*)lean_flecs_QueryGroupInfo_fromRepr(qgi)->ctx);
}
