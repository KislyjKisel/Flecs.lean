#include <lean/lean.h>
#include <flecs.h>
#include <flecs.lean/types.h>

#define LEAN_FLECS_DEFINE_TYPE(name)\
lean_external_class* lean_flecs_##name##_class;

#define LEAN_FLECS_INITIALIZE_TYPE(name, finalize, foreach)\
lean_flecs_##name##_class = lean_register_external_class(finalize, foreach);

static void lean_flecs_default_finalize(void* obj) {}
static void lean_flecs_default_foreach(void* obj, b_lean_obj_arg f) {}

LEAN_FLECS_DEFINE_TYPE(World);

LEAN_EXPORT lean_obj_res lean_flecs_initialize_types(lean_obj_arg world) {
    LEAN_FLECS_INITIALIZE_TYPE(World, lean_flecs_default_finalize, lean_flecs_default_foreach)
    return lean_io_result_mk_ok(lean_box(0));
}
