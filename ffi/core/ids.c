#include <lean/lean.h>
#include <lean_pod.h>
#include <flecs.h>
#include <flecs.lean/types.h>

LEAN_EXPORT lean_obj_res lean_flecs_Id_isTag(lean_flecs_World world, lean_flecs_Id id, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box(
        ecs_id_is_tag(lean_flecs_World_fromRepr(world), lean_flecs_Id_fromRepr(id))
    ));
}

LEAN_EXPORT lean_obj_res lean_flecs_Id_inUse(lean_flecs_World world, lean_flecs_Id id, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box(
        ecs_id_in_use(lean_flecs_World_fromRepr(world), lean_flecs_Id_fromRepr(id))
    ));
}

LEAN_EXPORT lean_obj_res lean_flecs_Id_getTypeId(lean_flecs_World world, lean_flecs_Id id, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_Entity_box(
        ecs_get_typeid(lean_flecs_World_fromRepr(world), lean_flecs_Id_fromRepr(id))
    ));
}

LEAN_EXPORT uint8_t lean_flecs_Id_match(lean_flecs_Id id, lean_flecs_Id pattern) {
    return ecs_id_match(lean_flecs_Id_fromRepr(id), lean_flecs_Id_fromRepr(pattern));
}

LEAN_EXPORT uint8_t lean_flecs_Id_isPair(lean_flecs_Id id) {
    return ecs_id_is_pair(lean_flecs_Id_fromRepr(id));
}

LEAN_EXPORT uint8_t lean_flecs_Id_isWildcard(lean_flecs_Id id) {
    return ecs_id_is_wildcard(lean_flecs_Id_fromRepr(id));
}

LEAN_EXPORT lean_obj_res lean_flecs_Id_isValid(lean_flecs_World world, lean_flecs_Id id, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box(
        ecs_id_is_valid(lean_flecs_World_fromRepr(world), lean_flecs_Id_fromRepr(id))
    ));
}

LEAN_EXPORT lean_obj_res lean_flecs_Id_flags(lean_flecs_World world, lean_flecs_Id id, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box_uint32(
        ecs_id_get_flags(lean_flecs_World_fromRepr(world), lean_flecs_Id_fromRepr(id))
    ));
}

LEAN_EXPORT lean_obj_res lean_flecs_Id_flagStr(lean_flecs_Id id) {
    return lean_mk_string(
        ecs_id_flag_str(lean_flecs_Id_fromRepr(id))
    );
}

LEAN_EXPORT lean_obj_res lean_flecs_Id_str(lean_flecs_World world, lean_flecs_Id id, lean_obj_arg io_) {
    char* s_c = ecs_id_str(lean_flecs_World_fromRepr(world), lean_flecs_Id_fromRepr(id));
    lean_object* s = lean_mk_string(s_c);
    ecs_os_free(s_c);
    return lean_io_result_mk_ok(s);
}
