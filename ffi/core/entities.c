#include <lean/lean.h>
#include <lean_pod.h>
#include <flecs.h>
#include <flecs.lean/types.h>


// Creating & Deleting

LEAN_EXPORT lean_obj_res lean_flecs_World_new(b_lean_obj_arg world, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_Entity_box(
        ecs_new(lean_flecs_World_fromRepr(world))
    ));
}

LEAN_EXPORT lean_obj_res lean_flecs_World_newLowId(b_lean_obj_arg world, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_Entity_box(
        ecs_new_low_id(lean_flecs_World_fromRepr(world))
    ));
}

LEAN_EXPORT lean_obj_res lean_flecs_World_newWithId(b_lean_obj_arg world, uint64_t id, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_Entity_box(
        ecs_new_w_id(lean_flecs_World_fromRepr(world), lean_flecs_Id_fromRepr(id))
    ));
}

LEAN_EXPORT lean_obj_res lean_flecs_World_entityInit(lean_flecs_World world, b_lean_obj_arg desc, lean_obj_arg io_) {
    ecs_entity_desc_t desc_c = lean_flecs_EntityDesc_fromRepr(desc);
    ecs_entity_t entity = ecs_entity_init(lean_flecs_World_fromRepr(world), &desc_c);
    if (desc_c.add) {
        free((void*)desc_c.add);
    }
    if (entity == 0 && desc_c.name) {
        ecs_os_free((void*)desc_c.name);
    }
    return lean_io_result_mk_ok(lean_flecs_Entity_box(entity));
}

LEAN_EXPORT lean_obj_res lean_flecs_Entity_clone(b_lean_obj_arg world, uint64_t src, uint64_t dst, uint8_t copyValue, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_Entity_box(ecs_clone(
        lean_flecs_World_fromRepr(world),
        lean_flecs_Entity_fromRepr(dst),
        lean_flecs_Entity_fromRepr(src),
        copyValue
    )));
}

LEAN_EXPORT lean_obj_res lean_flecs_Entity_delete(b_lean_obj_arg world, lean_flecs_Entity entity, lean_obj_arg io_) {
    ecs_delete(lean_flecs_World_fromRepr(world), lean_flecs_Entity_fromRepr(entity));
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_World_deleteWith(b_lean_obj_arg world, lean_flecs_Id id, lean_obj_arg io_) {
    ecs_delete_with(lean_flecs_World_fromRepr(world), lean_flecs_Id_fromRepr(id));
    return lean_io_result_mk_ok(lean_box(0));
}


// Adding & Removing

LEAN_EXPORT lean_obj_res lean_flecs_Entity_addId(lean_flecs_World world, lean_flecs_Entity entity, lean_flecs_Id id, lean_obj_arg io_) {
    ecs_add_id(
        lean_flecs_World_fromRepr(world),
        lean_flecs_Entity_fromRepr(entity),
        lean_flecs_Id_fromRepr(id)
    );
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_Entity_removeId(lean_flecs_World world, lean_flecs_Entity entity, lean_flecs_Id id, lean_obj_arg io_) {
    ecs_remove_id(
        lean_flecs_World_fromRepr(world),
        lean_flecs_Entity_fromRepr(entity),
        lean_flecs_Id_fromRepr(id)
    );
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_Entity_autoOverrideId(lean_flecs_World world, lean_flecs_Entity entity, lean_flecs_Id id, lean_obj_arg io_) {
    ecs_auto_override_id(
        lean_flecs_World_fromRepr(world),
        lean_flecs_Entity_fromRepr(entity),
        lean_flecs_Id_fromRepr(id)
    );
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_Entity_clear(lean_flecs_World world, lean_flecs_Entity entity, lean_obj_arg io_) {
    ecs_clear(
        lean_flecs_World_fromRepr(world),
        lean_flecs_Entity_fromRepr(entity)
    );
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_World_removeAll(lean_flecs_World world, lean_flecs_Id id, lean_obj_arg io_) {
    ecs_remove_all(
        lean_flecs_World_fromRepr(world),
        lean_flecs_Id_fromRepr(id)
    );
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_World_setWith(lean_flecs_World world, lean_flecs_Id id, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_Entity_box(
        ecs_set_with(lean_flecs_World_fromRepr(world), lean_flecs_Id_fromRepr(id))
    ));
}

LEAN_EXPORT lean_obj_res lean_flecs_World_getWith(lean_flecs_World world, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_Id_box(
        ecs_get_with(lean_flecs_World_fromRepr(world))
    ));
}


// Enabling & Disabling

LEAN_EXPORT lean_obj_res lean_flecs_Entity_enable(lean_flecs_World world, lean_flecs_Entity entity, uint8_t enabled, lean_obj_arg io_) {
    ecs_enable(
        lean_flecs_World_fromRepr(world),
        lean_flecs_Entity_fromRepr(entity),
        enabled
    );
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_Entity_enableId(lean_flecs_World world, lean_flecs_Entity entity, lean_flecs_Id id, uint8_t enable, lean_obj_arg io_) {
    ecs_enable_id(
        lean_flecs_World_fromRepr(world),
        lean_flecs_Entity_fromRepr(entity),
        lean_flecs_Id_fromRepr(id),
        enable
    );
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_Entity_isEnabledId(lean_flecs_World world, lean_flecs_Entity entity, lean_flecs_Id id, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box(ecs_is_enabled_id(
        lean_flecs_World_fromRepr(world),
        lean_flecs_Entity_fromRepr(entity),
        lean_flecs_Id_fromRepr(entity)
    )));
}


// Getting and setting

LEAN_EXPORT lean_obj_res lean_flecs_Entity_get(
    lean_flecs_World world, lean_flecs_Entity entity, lean_flecs_Id id, lean_obj_arg io_
) {
    const void* p = ecs_get_id(
        lean_flecs_World_fromRepr(world),
        lean_flecs_Entity_fromRepr(entity),
        lean_flecs_Id_fromRepr(id)
    );
    if (p == NULL) {
        return lean_io_result_mk_ok(lean_mk_option_none());
    }
    lean_object* x = *(lean_object**)p;
    lean_inc(x);
    return lean_io_result_mk_ok(lean_mk_option_some(x));
}

LEAN_EXPORT lean_obj_res lean_flecs_Entity_getUnboxed(
    lean_flecs_World world, lean_flecs_Entity entity, b_lean_obj_arg storable,
    b_lean_obj_arg readBytes, lean_flecs_Id id, lean_obj_arg io_
) {
    const void* p = ecs_get_id(
        lean_flecs_World_fromRepr(world),
        lean_flecs_Entity_fromRepr(entity),
        lean_flecs_Id_fromRepr(id)
    );
    if (p == NULL) {
        return lean_io_result_mk_ok(lean_mk_option_none());
    }
    lean_object* readBytesRef = LEAN_POD_CTOR_GET(readBytes, LEAN_POD_ReadBytes_readBytesRef);
    lean_inc_ref(readBytesRef);
    lean_object* res_box = lean_apply_3(readBytesRef, lean_box(0), lean_pod_BytesRef_box((void*)p), lean_box(0));
    lean_object* res = lean_ctor_get(res_box, 0);
    lean_inc(res);
    lean_dec_ref(res_box);
    return lean_io_result_mk_ok(lean_mk_option_some(res));
}

LEAN_EXPORT lean_obj_res lean_flecs_Entity_set(
    lean_flecs_World world, lean_flecs_Entity entity, lean_flecs_Id id, lean_obj_arg value, lean_obj_arg io_
) {
    void* p = ecs_get_mut_id(
        lean_flecs_World_fromRepr(world),
        lean_flecs_Entity_fromRepr(entity),
        lean_flecs_Id_fromRepr(id)
    );
    if (LEAN_LIKELY(p != NULL)) {
        lean_object* x = *(lean_object**)p;
        lean_dec(x);
        *(lean_object**)p = value;
    }
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_Entity_setUnboxed(
    lean_flecs_World world, lean_flecs_Entity entity, lean_flecs_Id id,
    b_lean_obj_arg storable, b_lean_obj_arg writeBytes, lean_obj_arg value, lean_obj_arg io_
) {
    void* p = ecs_get_mut_id(
        lean_flecs_World_fromRepr(world),
        lean_flecs_Entity_fromRepr(entity),
        lean_flecs_Id_fromRepr(id)
    );
    if (LEAN_LIKELY(p != NULL)) {
        lean_object* writeBytesRef = LEAN_POD_CTOR_GET(writeBytes, LEAN_POD_WriteBytes_writeBytesRef);
        lean_inc_ref(writeBytesRef);
        lean_dec_ref(lean_apply_4(writeBytesRef, lean_box(0), lean_pod_BytesRef_box(p), value, lean_box(0)));
    }
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_Entity_set_2(
    lean_flecs_World world, lean_flecs_Entity entity, lean_flecs_Id id,
    lean_obj_arg value, uint8_t modified, lean_obj_arg io_
) {
    void* p;
    if (LEAN_UNLIKELY(modified)) {
        p = ecs_ensure_modified_id(
            lean_flecs_World_fromRepr(world),
            lean_flecs_Entity_fromRepr(entity),
            lean_flecs_Id_fromRepr(id)
        );
    } else {
        p = ecs_ensure_id(
            lean_flecs_World_fromRepr(world),
            lean_flecs_Entity_fromRepr(entity),
            lean_flecs_Id_fromRepr(id)
        );
    }
    if (LEAN_LIKELY(p != NULL)) {
        lean_object* x = *(lean_object**)p;
        lean_dec(x);
        *(lean_object**)p = value;
    }
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_Entity_setUnboxed_2(
    lean_flecs_World world, lean_flecs_Entity entity, lean_flecs_Id id, b_lean_obj_arg storable,
    b_lean_obj_arg writeBytes, lean_obj_arg value, uint8_t modified, lean_obj_arg io_
) {
    void* p;
    if (LEAN_UNLIKELY(modified)) {
        p = ecs_ensure_modified_id(
            lean_flecs_World_fromRepr(world),
            lean_flecs_Entity_fromRepr(entity),
            lean_flecs_Id_fromRepr(id)
        );
    } else {
        p = ecs_ensure_id(
            lean_flecs_World_fromRepr(world),
            lean_flecs_Entity_fromRepr(entity),
            lean_flecs_Id_fromRepr(id)
        );
    }
    if (LEAN_LIKELY(p != NULL)) {
        lean_object* writeBytesRef = LEAN_POD_CTOR_GET(writeBytes, LEAN_POD_WriteBytes_writeBytesRef);
        lean_inc_ref(writeBytesRef);
        lean_dec_ref(lean_apply_4(writeBytesRef, lean_box(0), lean_pod_BytesRef_box(p), value, lean_box(0)));
    }
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_Entity_ref(
    lean_flecs_World world, lean_flecs_Entity entity, lean_flecs_Id id, lean_obj_arg io_
) {
    return lean_io_result_mk_ok(lean_flecs_Ref_box(ecs_ref_init_id(
        lean_flecs_World_fromRepr(world),
        lean_flecs_Entity_fromRepr(entity),
        lean_flecs_Id_fromRepr(id)
    )));
}

LEAN_EXPORT lean_obj_res lean_flecs_Ref_update(lean_flecs_World world, lean_flecs_Ref ref, lean_obj_arg io_) {
    ecs_ref_update(lean_flecs_World_fromRepr(world), lean_flecs_Ref_fromRepr(ref));
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_Ref_get(lean_flecs_World world, lean_flecs_Ref ref, lean_obj_arg io_) {
    ecs_ref_t* ref_c = lean_flecs_Ref_fromRepr(ref);
    void* p = ecs_ref_get_id(lean_flecs_World_fromRepr(world), ref_c, ref_c->id);
    if (p == NULL) {
        return lean_io_result_mk_ok(lean_mk_option_none());
    }
    lean_object* x = *(lean_object**)p;
    lean_inc(x);
    return lean_io_result_mk_ok(lean_mk_option_some(x));
}

LEAN_EXPORT lean_obj_res lean_flecs_Ref_getUnboxed(lean_flecs_World world, lean_flecs_Ref ref, b_lean_obj_arg storable, b_lean_obj_arg readBytes, lean_obj_arg io_) {
    ecs_ref_t* ref_c = lean_flecs_Ref_fromRepr(ref);
    void* p = ecs_ref_get_id(lean_flecs_World_fromRepr(world), ref_c, ref_c->id);
    if (p == NULL) {
        return lean_io_result_mk_ok(lean_mk_option_none());
    }
    lean_object* readBytesRef = LEAN_POD_CTOR_GET(readBytes, LEAN_POD_ReadBytes_readBytesRef);
    lean_inc_ref(readBytesRef);
    lean_object* res_box = lean_apply_3(readBytesRef, lean_box(0), lean_pod_BytesRef_box((void*)p), lean_box(0));
    lean_object* res = lean_ctor_get(res_box, 0);
    lean_inc(res);
    lean_dec_ref(res_box);
    return lean_io_result_mk_ok(lean_mk_option_some(res));
}

LEAN_EXPORT lean_obj_res lean_flecs_Ref_set(lean_flecs_World world, lean_flecs_Ref ref, lean_obj_arg value, lean_obj_arg io_) {
    ecs_ref_t* ref_c = lean_flecs_Ref_fromRepr(ref);
    void* p = ecs_ref_get_id(lean_flecs_World_fromRepr(world), ref_c, ref_c->id);
    if (LEAN_LIKELY(p != NULL)) {
        lean_object* x = *(lean_object**)p;
        lean_dec(x);
        *(lean_object**)p = value;
    }
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_Ref_setUnboxed(
    lean_flecs_World world, lean_flecs_Ref ref, b_lean_obj_arg storable,
    b_lean_obj_arg writeBytes, lean_obj_arg value, lean_obj_arg io_
) {
    ecs_ref_t* ref_c = lean_flecs_Ref_fromRepr(ref);
    void* p = ecs_ref_get_id(lean_flecs_World_fromRepr(world), ref_c, ref_c->id);
    if (LEAN_LIKELY(p != NULL)) {
        lean_object* writeBytesRef = LEAN_POD_CTOR_GET(writeBytes, LEAN_POD_WriteBytes_writeBytesRef);
        lean_inc_ref(writeBytesRef);
        lean_dec_ref(lean_apply_4(writeBytesRef, lean_box(0), lean_pod_BytesRef_box(p), value, lean_box(0)));
    }
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_Entity_modified(
    lean_flecs_World world, lean_flecs_Entity entity, lean_flecs_Id id, lean_obj_arg io_
) {
    ecs_modified_id(
        lean_flecs_World_fromRepr(world),
        lean_flecs_Entity_fromRepr(entity),
        lean_flecs_Id_fromRepr(id)
    );
    return lean_io_result_mk_ok(lean_box(0));
}


// Liveliness

LEAN_EXPORT lean_obj_res lean_flecs_Entity_isValid(lean_flecs_World world, lean_flecs_Entity entity, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box(
        ecs_is_valid(lean_flecs_World_fromRepr(world), lean_flecs_Entity_fromRepr(entity))
    ));
}

LEAN_EXPORT lean_obj_res lean_flecs_Entity_isAlive(lean_flecs_World world, lean_flecs_Entity entity, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box(
        ecs_is_alive(lean_flecs_World_fromRepr(world), lean_flecs_Entity_fromRepr(entity))
    ));
}

LEAN_EXPORT lean_flecs_Id lean_flecs_Entity_stripGeneration(lean_flecs_Entity entity) {
    return lean_flecs_Id_toRepr(ecs_strip_generation(lean_flecs_Entity_fromRepr(entity)));
}

LEAN_EXPORT lean_obj_res lean_flecs_Entity_getAlive(lean_flecs_World world, lean_flecs_Entity entity, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_Entity_box(
        ecs_get_alive(lean_flecs_World_fromRepr(world), lean_flecs_Entity_fromRepr(entity))
    ));
}

LEAN_EXPORT lean_obj_res lean_flecs_Entity_makeAlive(lean_flecs_World world, lean_flecs_Entity entity, lean_obj_arg io_) {
    ecs_make_alive(lean_flecs_World_fromRepr(world), lean_flecs_Entity_fromRepr(entity));
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_World_makeAliveId(lean_flecs_World world, lean_flecs_Id id, lean_obj_arg io_) {
    ecs_make_alive_id(lean_flecs_World_fromRepr(world), lean_flecs_Id_fromRepr(id));
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_Entity_exists(lean_flecs_World world, lean_flecs_Entity entity, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box(
        ecs_exists(lean_flecs_World_fromRepr(world), lean_flecs_Entity_fromRepr(entity))
    ));
}

LEAN_EXPORT lean_obj_res lean_flecs_Entity_setVersion(lean_flecs_World world, lean_flecs_Entity entity, lean_obj_arg io_) {
    ecs_set_version(lean_flecs_World_fromRepr(world), lean_flecs_Entity_fromRepr(entity));
    return lean_io_result_mk_ok(lean_box(0));
}


// Information

LEAN_EXPORT lean_obj_res lean_flecs_Entity_getType(lean_flecs_World world, lean_flecs_Entity entity, lean_obj_arg io_) {
    const ecs_type_t* type = ecs_get_type(lean_flecs_World_fromRepr(world), lean_flecs_Entity_fromRepr(entity));
    if (type == NULL) {
        return lean_io_result_mk_ok(lean_mk_empty_array());
    }
    lean_object* arr = lean_alloc_array(type->count, type->count);
    for (size_t i = 0; i < type->count; ++i) {
        lean_array_set_core(arr, i, lean_flecs_Id_box(type->array[i]));
    }
    return lean_io_result_mk_ok(arr);
}

LEAN_EXPORT lean_obj_res lean_flecs_Entity_getTable(lean_flecs_World world, lean_flecs_Entity entity, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_Table_box(
        ecs_get_table(lean_flecs_World_fromRepr(world), lean_flecs_Entity_fromRepr(entity))
    ));
}

LEAN_EXPORT lean_obj_res lean_flecs_Table_str(lean_flecs_World world, lean_flecs_Table table, lean_obj_arg io_) {
    char* s_c = ecs_table_str(lean_flecs_World_fromRepr(world), lean_flecs_Table_fromRepr(table));
    lean_object* s = lean_mk_string(s_c);
    ecs_os_free(s_c);
    return lean_io_result_mk_ok(s);
}

LEAN_EXPORT lean_obj_res lean_flecs_Entity_str(lean_flecs_World world, lean_flecs_Entity entity, lean_obj_arg io_) {
    char* s_c = ecs_entity_str(lean_flecs_World_fromRepr(world), lean_flecs_Entity_fromRepr(entity));
    lean_object* s = lean_mk_string(s_c);
    ecs_os_free(s_c);
    return lean_io_result_mk_ok(s);
}

LEAN_EXPORT lean_obj_res lean_flecs_Entity_hasId(lean_flecs_World world, lean_flecs_Entity entity, lean_flecs_Id id, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box(ecs_has_id(
        lean_flecs_World_fromRepr(world),
        lean_flecs_Entity_fromRepr(entity),
        lean_flecs_Id_fromRepr(id)
    )));
}

LEAN_EXPORT lean_obj_res lean_flecs_Entity_ownsId(lean_flecs_World world, lean_flecs_Entity entity, lean_flecs_Id id, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box(ecs_owns_id(
        lean_flecs_World_fromRepr(world),
        lean_flecs_Entity_fromRepr(entity),
        lean_flecs_Id_fromRepr(id)
    )));
}

LEAN_EXPORT lean_obj_res lean_flecs_Entity_getTarget(
    lean_flecs_World world, lean_flecs_Entity entity, lean_flecs_Entity rel, lean_pod_Int32 index,
    lean_obj_arg io_
) {
    return lean_io_result_mk_ok(lean_flecs_Entity_box(ecs_get_target(
        lean_flecs_World_fromRepr(world),
        lean_flecs_Entity_fromRepr(entity),
        lean_flecs_Entity_fromRepr(rel),
        lean_pod_Int32_fromRepr(index)
    )));
}

LEAN_EXPORT lean_obj_res lean_flecs_Entity_getParent(lean_flecs_World world, lean_flecs_Entity entity, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_Entity_box(
        ecs_get_parent(lean_flecs_World_fromRepr(world), lean_flecs_Entity_fromRepr(entity))
    ));
}

LEAN_EXPORT lean_obj_res lean_flecs_Entity_getTargetForId(
    lean_flecs_World world, lean_flecs_Entity entity, lean_flecs_Entity rel, lean_flecs_Id id,
    lean_obj_arg io_
) {
    return lean_io_result_mk_ok(lean_flecs_Entity_box(ecs_get_target_for_id(
        lean_flecs_World_fromRepr(world),
        lean_flecs_Entity_fromRepr(entity),
        lean_flecs_Entity_fromRepr(rel),
        lean_flecs_Id_fromRepr(id)
    )));
}

LEAN_EXPORT lean_obj_res lean_flecs_Entity_getDepth(
    lean_flecs_World world, lean_flecs_Entity entity, lean_flecs_Entity rel, lean_obj_arg io_
) {
    return lean_io_result_mk_ok(lean_pod_Int32_box(ecs_get_depth(
        lean_flecs_World_fromRepr(world),
        lean_flecs_Entity_fromRepr(entity),
        lean_flecs_Entity_fromRepr(rel)
    )));
}

LEAN_EXPORT lean_obj_res lean_flecs_World_countId(lean_flecs_World world, lean_flecs_Id entity, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_pod_Int32_box(ecs_count_id(
        lean_flecs_World_fromRepr(world),
        lean_flecs_Id_fromRepr(entity)
    )));
}


// Names

// TODO
