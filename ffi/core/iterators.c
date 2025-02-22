#include <lean/lean.h>
#include <lean_pod.h>
#include <flecs.h>
#include <flecs.lean/types.h>

LEAN_EXPORT lean_obj_res lean_flecs_Iter_world(lean_flecs_Iter it, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_World_box(lean_flecs_Iter_fromRepr(it)->world));
}

LEAN_EXPORT lean_obj_res lean_flecs_Iter_realWorld(lean_flecs_Iter it, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_World_box(lean_flecs_Iter_fromRepr(it)->real_world));
}

LEAN_EXPORT lean_obj_res lean_flecs_Iter_system(lean_flecs_Iter it, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_Entity_box(lean_flecs_Iter_fromRepr(it)->system));
}

LEAN_EXPORT lean_obj_res lean_flecs_Iter_event(lean_flecs_Iter it, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_Entity_box(lean_flecs_Iter_fromRepr(it)->event));
}

LEAN_EXPORT lean_obj_res lean_flecs_Iter_eventId(lean_flecs_Iter it, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_Id_box(lean_flecs_Iter_fromRepr(it)->event_id));
}

LEAN_EXPORT lean_obj_res lean_flecs_Iter_eventCur(lean_flecs_Iter it, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_pod_Int32_box(lean_flecs_Iter_fromRepr(it)->event_cur));
}

LEAN_EXPORT lean_obj_res lean_flecs_Iter_variableCount(lean_flecs_Iter it, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box_uint32(lean_flecs_Iter_fromRepr(it)->variable_count));
}

LEAN_EXPORT lean_obj_res lean_flecs_Iter_deltaTime(lean_flecs_Iter it, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_FTime_box(lean_flecs_Iter_fromRepr(it)->delta_time));
}

LEAN_EXPORT lean_obj_res lean_flecs_Iter_deltaSystemTime(lean_flecs_Iter it, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_FTime_box(lean_flecs_Iter_fromRepr(it)->delta_system_time));
}

LEAN_EXPORT lean_obj_res lean_flecs_Iter_frameOffset(lean_flecs_Iter it, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_pod_Int32_box(lean_flecs_Iter_fromRepr(it)->frame_offset));
}

LEAN_EXPORT lean_obj_res lean_flecs_Iter_offset(lean_flecs_Iter it, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_pod_Int32_box(lean_flecs_Iter_fromRepr(it)->offset));
}

LEAN_EXPORT lean_obj_res lean_flecs_Iter_count(lean_flecs_Iter it, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box_uint32(lean_flecs_Iter_fromRepr(it)->count));
}

LEAN_EXPORT lean_obj_res lean_flecs_Iter_flags(lean_flecs_Iter it, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box_uint32(lean_flecs_Iter_fromRepr(it)->flags));
}

LEAN_EXPORT lean_obj_res lean_flecs_Iter_setFlags(lean_flecs_Iter it, uint32_t flags, lean_obj_arg io_) {
    lean_flecs_Iter_fromRepr(it)->flags = flags;
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_Iter_setInterruptedBy(lean_flecs_Iter it, lean_flecs_Entity entity, lean_obj_arg io_) {
    lean_flecs_Iter_fromRepr(it)->interrupted_by = lean_flecs_Entity_fromRepr(entity);
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_Iter_next(lean_flecs_Iter it, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box(
        ecs_iter_next(lean_flecs_Iter_fromRepr(it))
    ));
}

LEAN_EXPORT lean_obj_res lean_flecs_Iter_fini(lean_flecs_Iter it, lean_obj_arg io_) {
    ecs_iter_fini(lean_flecs_Iter_fromRepr(it));
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_Iter_count_f(lean_flecs_Iter it, lean_obj_arg io_) {
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
    ecs_table_range_t range_c = lean_flecs_TableRange_fromRepr(range);
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
    char* expr_c = ecs_iter_str(lean_flecs_Iter_fromRepr(it));
    lean_object* expr = lean_mk_string(expr_c);
    ecs_os_free(expr_c);
    return lean_io_result_mk_ok(expr);
}

LEAN_EXPORT lean_obj_res lean_flecs_Iter_fieldUnboxed(lean_flecs_Iter it, b_lean_obj_arg storable, b_lean_obj_arg readBytes, uint32_t fieldIndex, uint32_t entityIndex, lean_obj_arg io_) {
    ecs_iter_t* it_c = lean_flecs_Iter_fromRepr(it);
    if (LEAN_UNLIKELY(entityIndex >= it_c->count)) {
        return lean_mk_io_user_error(lean_mk_string("entityIndex >= it.count"));
    }
    size_t component_size = lean_usize_of_nat(lean_pod_Storable_byteSize(storable));
    lean_object* readBytesRefOffEl = LEAN_POD_CTOR_GET(readBytes, LEAN_POD_ReadBytes_readBytesRefOffEl);
    lean_inc_ref(readBytesRefOffEl);
    lean_object* res_box = lean_apply_6(
        readBytesRefOffEl,
        lean_box(0),
        lean_usize_to_nat(it_c->count * component_size),
        lean_pod_BytesRef_box(ecs_field_w_size(it_c, component_size, (int32_t)fieldIndex)),
        lean_uint32_to_nat(entityIndex),
        lean_box(0),
        lean_box(0)
    );
    lean_object* res = lean_ctor_get(res_box, 0);
    lean_inc(res);
    lean_dec_ref(res_box);
    return lean_io_result_mk_ok(res);
}

LEAN_EXPORT lean_obj_res lean_flecs_Iter_setFieldUnboxed(lean_flecs_Iter it, b_lean_obj_arg storable, b_lean_obj_arg writeBytes, uint32_t fieldIndex, uint32_t entityIndex, lean_obj_arg value, lean_obj_arg io_) {
    ecs_iter_t* it_c = lean_flecs_Iter_fromRepr(it);
    if (LEAN_LIKELY(entityIndex < it_c->count)) {
        size_t component_size = lean_usize_of_nat(lean_pod_Storable_byteSize(storable));
        lean_object* writeBytesRefOffEl = LEAN_POD_CTOR_GET(writeBytes, LEAN_POD_WriteBytes_writeBytesRefOffEl);
        lean_inc_ref(writeBytesRefOffEl);
        lean_dec_ref(lean_apply_7(
            writeBytesRefOffEl,
            lean_box(0),
            lean_usize_to_nat(it_c->count * component_size),
            lean_pod_BytesRef_box(ecs_field_w_size(it_c, component_size, (int32_t)fieldIndex)),
            lean_uint32_to_nat(entityIndex),
            value,
            lean_box(0),
            lean_box(0)
        ));
    }
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_Iter_field(lean_flecs_Iter it, uint32_t fieldIndex, uint32_t entityIndex, lean_obj_arg io_) {
    ecs_iter_t* it_c = lean_flecs_Iter_fromRepr(it);
    if (LEAN_UNLIKELY(entityIndex >= it_c->count)) {
        return lean_mk_io_user_error(lean_mk_string("entityIndex >= it.count"));
    }
    lean_object** values = ecs_field(it_c, lean_object*, (int32_t)fieldIndex);
    lean_inc(values[entityIndex]);
    return lean_io_result_mk_ok(values[entityIndex]);
}

LEAN_EXPORT lean_obj_res lean_flecs_Iter_fieldAt(lean_flecs_Iter it, uint32_t fieldIndex, uint32_t entityIndex, lean_obj_arg io_) {
    ecs_iter_t* it_c = lean_flecs_Iter_fromRepr(it);
    lean_object** value = ecs_field_at(it_c, lean_object*, (int32_t)fieldIndex, (int32_t)entityIndex);
    if (LEAN_UNLIKELY(value == NULL)) {
        return lean_mk_io_user_error(lean_mk_string("ecs_field_at returned NULL"));
    }
    lean_inc(*value);
    return lean_io_result_mk_ok(*value);
}

LEAN_EXPORT lean_obj_res lean_flecs_Iter_setField(lean_flecs_Iter it, uint32_t fieldIndex, uint32_t entityIndex, lean_obj_arg value, lean_obj_arg io_) {
    ecs_iter_t* it_c = lean_flecs_Iter_fromRepr(it);
    if (LEAN_LIKELY(entityIndex < it_c->count)) {
        ecs_field(lean_flecs_Iter_fromRepr(it), lean_object*, (int32_t)fieldIndex)[entityIndex] = value;
    }
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
