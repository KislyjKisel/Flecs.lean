#include <lean/lean.h>
#include <lean_pod.h>
#include <flecs.h>
#include <flecs.lean/types.h>

LEAN_EXPORT lean_obj_res lean_flecs_Iter_field(lean_flecs_Iter it, uint32_t index, lean_obj_arg io_) {
    lean_object* value = *ecs_field(lean_flecs_Iter_fromRepr(it), lean_object*, (int32_t)index);
    lean_inc(value);
    return lean_io_result_mk_ok(value);
}

LEAN_EXPORT lean_obj_res lean_flecs_Iter_setField(lean_flecs_Iter it, uint32_t index, lean_obj_arg value, lean_obj_arg io_) {
    *ecs_field(lean_flecs_Iter_fromRepr(it), lean_object*, (int32_t)index) = value;
    return lean_io_result_mk_ok(lean_box(0));
}
