#include <lean/lean.h>
#include <lean_pod.h>
#include <flecs.h>
#include <flecs.lean/types.h>

LEAN_EXPORT lean_obj_res lean_flecs_Iter_next(lean_flecs_Iter it, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box(
        ecs_iter_next(lean_flecs_Iter_fromRepr(it))
    ));
}

LEAN_EXPORT lean_obj_res lean_flecs_Iter_fini(lean_flecs_Iter it, lean_obj_arg io_) {
    ecs_iter_fini(lean_flecs_Iter_fromRepr(it));
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_Iter_count(lean_flecs_Iter it, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box_uint32(
        ecs_iter_count(lean_flecs_Iter_fromRepr(it))
    ));
}

LEAN_EXPORT lean_obj_res lean_flecs_Iter_isTrue(lean_flecs_Iter it, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box(
        ecs_iter_is_true(lean_flecs_Iter_fromRepr(it))
    ));
}

LEAN_EXPORT lean_obj_res lean_flecs_Iter_first(lean_flecs_Iter it, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_Entity_box(
        ecs_iter_first(lean_flecs_Iter_fromRepr(it))
    ));
}

LEAN_EXPORT lean_obj_res lean_flecs_Iter_setVar(lean_flecs_Iter it, uint32_t varId, lean_flecs_Entity entity, lean_obj_arg io_) {
    ecs_iter_set_var(lean_flecs_Iter_fromRepr(it), (int32_t)varId, lean_flecs_Entity_fromRepr(entity));
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_Iter_setVarAsTable(lean_flecs_Iter it, uint32_t varId, lean_flecs_Table table, lean_obj_arg io_) {
    ecs_iter_set_var_as_table(lean_flecs_Iter_fromRepr(it), (int32_t)varId, lean_flecs_Table_fromRepr(table));
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_Iter_setVarAsRange(lean_flecs_Iter it, uint32_t varId, b_lean_obj_arg range, lean_obj_arg io_) {
    ecs_table_range_t range_c;
    range_c.table = lean_flecs_Table_unbox(LEAN_POD_CTOR_GET(range, LEAN_FLECS_TableRange_table));
    range_c.offset = lean_pod_Int32_unbox(LEAN_POD_CTOR_GET(range, LEAN_FLECS_TableRange_offset));
    range_c.count = lean_pod_Int32_unbox(LEAN_POD_CTOR_GET(range, LEAN_FLECS_TableRange_count));
    ecs_iter_set_var_as_range(lean_flecs_Iter_fromRepr(it), (int32_t)varId, &range_c);
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_Iter_getVar(lean_flecs_Iter it, uint32_t varId, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_Entity_box(
        ecs_iter_get_var(lean_flecs_Iter_fromRepr(it), (int32_t)varId)
    ));
}

LEAN_EXPORT lean_obj_res lean_flecs_Iter_getVarAsTable(lean_flecs_Iter it, uint32_t varId, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_Table_box(
        ecs_iter_get_var_as_table(lean_flecs_Iter_fromRepr(it), (int32_t)varId)
    ));
}

LEAN_EXPORT lean_obj_res lean_flecs_Iter_getVarAsRange(lean_flecs_Iter it, uint32_t varId, lean_obj_arg io_) {
    ecs_table_range_t range = ecs_iter_get_var_as_range(lean_flecs_Iter_fromRepr(it), (int32_t)varId);
    return lean_io_result_mk_ok(lean_flecs_TableRange_box(&range));
}

LEAN_EXPORT lean_obj_res lean_flecs_Iter_varIsConstrained(lean_flecs_Iter it, uint32_t varId, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box(
        ecs_iter_var_is_constrained(lean_flecs_Iter_fromRepr(it), (int32_t)varId)
    ));
}

LEAN_EXPORT lean_obj_res lean_flecs_Iter_changed(lean_flecs_Iter it, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box(
        ecs_iter_changed(lean_flecs_Iter_fromRepr(it))
    ));
}

LEAN_EXPORT lean_obj_res lean_flecs_Iter_str(lean_flecs_Iter it, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_mk_string(
        ecs_iter_str(lean_flecs_Iter_fromRepr(it))
    ));
}

LEAN_EXPORT lean_obj_res lean_flecs_Iter_fieldWithSize(lean_flecs_Iter it, b_lean_obj_arg storable, uint32_t index, lean_obj_arg io_) {
    size_t size = lean_usize_of_nat(lean_pod_Storable_byteSize(storable));
    return lean_io_result_mk_ok(lean_pod_BytesRef_box(
        ecs_field_w_size(lean_flecs_Iter_fromRepr(it), size, (int32_t)index)
    ));
}

LEAN_EXPORT lean_obj_res lean_flecs_Iter_field(lean_flecs_Iter it, uint32_t index, lean_obj_arg io_) {
    lean_object* value = *ecs_field(lean_flecs_Iter_fromRepr(it), lean_object*, (int32_t)index);
    lean_inc(value);
    return lean_io_result_mk_ok(value);
}

LEAN_EXPORT lean_obj_res lean_flecs_Iter_setField(lean_flecs_Iter it, uint32_t index, lean_obj_arg value, lean_obj_arg io_) {
    *ecs_field(lean_flecs_Iter_fromRepr(it), lean_object*, (int32_t)index) = value;
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_Iter_fieldIsReadonly(lean_flecs_Iter it, uint32_t index, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box(
        ecs_field_is_readonly(lean_flecs_Iter_fromRepr(it), (int32_t)index)
    ));
}

LEAN_EXPORT lean_obj_res lean_flecs_Iter_fieldIsWriteonly(lean_flecs_Iter it, uint32_t index, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box(
        ecs_field_is_writeonly(lean_flecs_Iter_fromRepr(it), (int32_t)index)
    ));
}

LEAN_EXPORT lean_obj_res lean_flecs_Iter_fieldIsSet(lean_flecs_Iter it, uint32_t index, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box(
        ecs_field_is_set(lean_flecs_Iter_fromRepr(it), (int32_t)index)
    ));
}

LEAN_EXPORT lean_obj_res lean_flecs_Iter_fieldId(lean_flecs_Iter it, uint32_t index, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_Id_box(
        ecs_field_id(lean_flecs_Iter_fromRepr(it), (int32_t)index)
    ));
}

LEAN_EXPORT lean_obj_res lean_flecs_Iter_fieldColumn(lean_flecs_Iter it, uint32_t index, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box_uint32((uint32_t)
        ecs_field_column(lean_flecs_Iter_fromRepr(it), (int32_t)index)
    ));
}

LEAN_EXPORT lean_obj_res lean_flecs_Iter_fieldSrc(lean_flecs_Iter it, uint32_t index, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_Entity_box(
        ecs_field_src(lean_flecs_Iter_fromRepr(it), (int32_t)index)
    ));
}

LEAN_EXPORT lean_obj_res lean_flecs_Iter_fieldSize(lean_flecs_Iter it, uint32_t index, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box_usize(
        ecs_field_size(lean_flecs_Iter_fromRepr(it), (int32_t)index)
    ));
}

LEAN_EXPORT lean_obj_res lean_flecs_Iter_fieldIsSelf(lean_flecs_Iter it, uint32_t index, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box(
        ecs_field_is_self(lean_flecs_Iter_fromRepr(it), (int32_t)index)
    ));
}
