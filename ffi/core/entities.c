#include <lean/lean.h>
#include <lean_pod.h>
#include <flecs.h>
#include <flecs.lean/types.h>


// Creating & Deleting

LEAN_EXPORT lean_obj_res lean_flecs_new(b_lean_obj_arg world, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_Entity_box(
        ecs_new(lean_flecs_World_fromRepr(world))
    ));
}

LEAN_EXPORT lean_obj_res lean_flecs_newLowId(b_lean_obj_arg world, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_Entity_box(
        ecs_new_low_id(lean_flecs_World_fromRepr(world))
    ));
}

LEAN_EXPORT lean_obj_res lean_flecs_newWithId(b_lean_obj_arg world, uint64_t id, lean_obj_arg io_) {
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

LEAN_EXPORT lean_obj_res lean_flecs_clone(b_lean_obj_arg world, uint64_t dst, uint64_t src, uint8_t copyValue, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_Entity_box(ecs_clone(
        lean_flecs_World_fromRepr(world),
        lean_flecs_Entity_fromRepr(dst),
        lean_flecs_Entity_fromRepr(src),
        copyValue
    )));
}

LEAN_EXPORT lean_obj_res lean_flecs_delete(b_lean_obj_arg world, lean_flecs_Entity entity, lean_obj_arg io_) {
    ecs_delete(lean_flecs_World_fromRepr(world), lean_flecs_Entity_fromRepr(entity));
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_deleteWith(b_lean_obj_arg world, lean_flecs_Id id, lean_obj_arg io_) {
    ecs_delete_with(lean_flecs_World_fromRepr(world), lean_flecs_Id_fromRepr(id));
    return lean_io_result_mk_ok(lean_box(0));
}


// Adding & Removing

LEAN_EXPORT lean_obj_res lean_flecs_addId(lean_flecs_World world, lean_flecs_Entity entity, lean_flecs_Id id, lean_obj_arg io_) {
    ecs_add_id(
        lean_flecs_World_fromRepr(world),
        lean_flecs_Entity_fromRepr(entity),
        lean_flecs_Id_fromRepr(id)
    );
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_removeId(lean_flecs_World world, lean_flecs_Entity entity, lean_flecs_Id id, lean_obj_arg io_) {
    ecs_remove_id(
        lean_flecs_World_fromRepr(world),
        lean_flecs_Entity_fromRepr(entity),
        lean_flecs_Id_fromRepr(id)
    );
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_autoOverrideId(lean_flecs_World world, lean_flecs_Entity entity, lean_flecs_Id id, lean_obj_arg io_) {
    ecs_auto_override_id(
        lean_flecs_World_fromRepr(world),
        lean_flecs_Entity_fromRepr(entity),
        lean_flecs_Id_fromRepr(id)
    );
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_clear(lean_flecs_World world, lean_flecs_Entity entity, lean_obj_arg io_) {
    ecs_clear(
        lean_flecs_World_fromRepr(world),
        lean_flecs_Entity_fromRepr(entity)
    );
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_removeAll(lean_flecs_World world, lean_flecs_Id id, lean_obj_arg io_) {
    ecs_remove_all(
        lean_flecs_World_fromRepr(world),
        lean_flecs_Id_fromRepr(id)
    );
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_setWith(lean_flecs_World world, lean_flecs_Id id, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_Entity_box(
        ecs_set_with(lean_flecs_World_fromRepr(world), lean_flecs_Id_fromRepr(id))
    ));
}

LEAN_EXPORT lean_obj_res lean_flecs_getWith(lean_flecs_World world, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_Id_box(
        ecs_get_with(lean_flecs_World_fromRepr(world))
    ));
}


// Enabling & Disabling

LEAN_EXPORT lean_obj_res lean_flecs_enable(lean_flecs_World world, lean_flecs_Entity entity, uint8_t enabled, lean_obj_arg io_) {
    ecs_enable(
        lean_flecs_World_fromRepr(world),
        lean_flecs_Entity_fromRepr(entity),
        enabled
    );
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_enableId(lean_flecs_World world, lean_flecs_Entity entity, lean_flecs_Id id, uint8_t enable, lean_obj_arg io_) {
    ecs_enable_id(
        lean_flecs_World_fromRepr(world),
        lean_flecs_Entity_fromRepr(entity),
        lean_flecs_Id_fromRepr(id),
        enable
    );
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_isEnabledId(lean_flecs_World world, lean_flecs_Entity entity, lean_flecs_Id id, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box(ecs_is_enabled_id(
        lean_flecs_World_fromRepr(world),
        lean_flecs_Entity_fromRepr(entity),
        lean_flecs_Id_fromRepr(entity)
    )));
}


// Getting and setting

// TODO


// Liveliness

LEAN_EXPORT lean_obj_res lean_flecs_World_isValid(lean_flecs_World world, lean_flecs_Entity entity, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box(
        ecs_is_valid(lean_flecs_World_fromRepr(world), lean_flecs_Entity_fromRepr(entity))
    ));
}

LEAN_EXPORT lean_obj_res lean_flecs_World_isAlive(lean_flecs_World world, lean_flecs_Entity entity, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box(
        ecs_is_alive(lean_flecs_World_fromRepr(world), lean_flecs_Entity_fromRepr(entity))
    ));
}

LEAN_EXPORT lean_flecs_Id lean_flecs_World_stripGeneration(lean_flecs_Entity entity) {
    return lean_flecs_Id_toRepr(ecs_strip_generation(lean_flecs_Entity_fromRepr(entity)));
}

LEAN_EXPORT lean_obj_res lean_flecs_World_getAlive(lean_flecs_World world, lean_flecs_Entity entity, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_Entity_box(
        ecs_get_alive(lean_flecs_World_fromRepr(world), lean_flecs_Entity_fromRepr(entity))
    ));
}

LEAN_EXPORT lean_obj_res lean_flecs_World_makeAlive(lean_flecs_World world, lean_flecs_Entity entity, lean_obj_arg io_) {
    ecs_make_alive(lean_flecs_World_fromRepr(world), lean_flecs_Entity_fromRepr(entity));
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_World_makeAliveId(lean_flecs_World world, lean_flecs_Id id, lean_obj_arg io_) {
    ecs_make_alive_id(lean_flecs_World_fromRepr(world), lean_flecs_Id_fromRepr(id));
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_World_exists(lean_flecs_World world, lean_flecs_Entity entity, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box(
        ecs_exists(lean_flecs_World_fromRepr(world), lean_flecs_Entity_fromRepr(entity))
    ));
}

LEAN_EXPORT lean_obj_res lean_flecs_World_setGeneration(lean_flecs_World world, lean_flecs_Entity entity, lean_obj_arg io_) {
    ecs_set_generation(lean_flecs_World_fromRepr(world), lean_flecs_Entity_fromRepr(entity));
    return lean_io_result_mk_ok(lean_box(0));
}


// Information

LEAN_EXPORT lean_obj_res lean_flecs_World_getType(lean_flecs_World world, lean_flecs_Entity entity, lean_obj_arg io_) {
    const ecs_type_t* type = ecs_get_type(lean_flecs_World_fromRepr(world), lean_flecs_Entity_fromRepr(entity));
    lean_object* arr = lean_alloc_array(type->count, type->count);
    for (size_t i = 0; i < type->count; ++i) {
        lean_array_set_core(arr, i, lean_flecs_Id_box(type->array[i]));
    }
    return lean_io_result_mk_ok(arr);
}

LEAN_EXPORT lean_obj_res lean_flecs_World_getTable(lean_flecs_World world, lean_flecs_Entity entity, lean_obj_arg io_) {
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

LEAN_EXPORT lean_obj_res lean_flecs_World_entityStr(lean_flecs_World world, lean_flecs_Entity entity, lean_obj_arg io_) {
    char* s_c = ecs_entity_str(lean_flecs_World_fromRepr(world), lean_flecs_Entity_fromRepr(entity));
    lean_object* s = lean_mk_string(s_c);
    ecs_os_free(s_c);
    return lean_io_result_mk_ok(s);
}

LEAN_EXPORT lean_obj_res lean_flecs_World_hasId(lean_flecs_World world, lean_flecs_Entity entity, lean_flecs_Id id, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box(ecs_has_id(
        lean_flecs_World_fromRepr(world),
        lean_flecs_Entity_fromRepr(entity),
        lean_flecs_Id_fromRepr(id)
    )));
}

LEAN_EXPORT lean_obj_res lean_flecs_World_ownsId(lean_flecs_World world, lean_flecs_Entity entity, lean_flecs_Id id, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box(ecs_owns_id(
        lean_flecs_World_fromRepr(world),
        lean_flecs_Entity_fromRepr(entity),
        lean_flecs_Id_fromRepr(id)
    )));
}

LEAN_EXPORT lean_obj_res lean_flecs_World_getTarget(
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

LEAN_EXPORT lean_obj_res lean_flecs_World_getParent(lean_flecs_World world, lean_flecs_Entity entity, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_Entity_box(
        ecs_get_parent(lean_flecs_World_fromRepr(world), lean_flecs_Entity_fromRepr(entity))
    ));
}

LEAN_EXPORT lean_obj_res lean_flecs_World_getTargetForId(
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

LEAN_EXPORT lean_obj_res lean_flecs_World_getDepth(
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
