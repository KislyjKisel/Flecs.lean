#include <lean/lean.h>
#include <lean_pod.h>
#include <flecs.h>
#include <flecs.lean/types.h>


// Creating & Deleting

LEAN_EXPORT lean_obj_res lean_flecs_newId(b_lean_obj_arg world, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_Entity_box(
        ecs_new_id(lean_flecs_World_fromRepr(world))
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

LEAN_EXPORT lean_obj_res lean_flecs_delete(b_lean_obj_arg world, uint64_t entity, lean_obj_arg io_) {
    ecs_delete(lean_flecs_World_fromRepr(world), lean_flecs_Entity_fromRepr(entity));
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_clone(b_lean_obj_arg world, uint64_t dst, uint64_t src, uint8_t copyValue, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_Entity_box(ecs_clone(
        lean_flecs_World_fromRepr(world),
        lean_flecs_Entity_fromRepr(dst),
        lean_flecs_Entity_fromRepr(src),
        copyValue
    )));
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

LEAN_EXPORT lean_obj_res lean_flecs_overrideId(lean_flecs_World world, lean_flecs_Entity entity, lean_flecs_Id id, lean_obj_arg io_) {
    ecs_override_id(
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
