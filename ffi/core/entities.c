#include <lean/lean.h>
#include <lean_pod.h>
#include <flecs.h>
#include <flecs.lean/types.h>

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
