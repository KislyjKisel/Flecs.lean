#include <lean/lean.h>
#include <flecs.h>
#include <flecs.lean/types.h>

static lean_object* lean_flecs_ModuleAction_current = NULL;

static void lean_flecs_ModuleAction_wrapper(ecs_world_t* world) {
    lean_dec_ref(lean_apply_2(lean_flecs_ModuleAction_current, lean_flecs_World_box(world), lean_box(0)));
    lean_flecs_ModuleAction_current = NULL;
}

LEAN_EXPORT lean_obj_res lean_flecs_World_import(lean_flecs_World world, lean_obj_arg module, b_lean_obj_arg modName, lean_obj_arg io_) {
    lean_flecs_ModuleAction_current = module;
    return lean_io_result_mk_ok(lean_flecs_Entity_box(ecs_import(
        lean_flecs_World_fromRepr(world),
        lean_flecs_ModuleAction_wrapper,
        lean_string_cstr(modName)
    )));
}

LEAN_EXPORT lean_obj_res lean_flecs_World_importC(lean_flecs_World world, lean_obj_arg module, b_lean_obj_arg modName, lean_obj_arg io_) {
    lean_flecs_ModuleAction_current = module;
    return lean_io_result_mk_ok(lean_flecs_Entity_box(ecs_import_c(
        lean_flecs_World_fromRepr(world),
        lean_flecs_ModuleAction_wrapper,
        lean_string_cstr(modName)
    )));
}

LEAN_EXPORT lean_obj_res lean_flecs_World_importFromLibrary(lean_flecs_World world, b_lean_obj_arg libName, b_lean_obj_arg modName, lean_obj_arg io_) {
    const char* modName_c = NULL;
    if (lean_option_is_some(modName)) {
        modName_c = lean_string_cstr(lean_ctor_get(modName, 0));
    }
    return lean_io_result_mk_ok(lean_flecs_Entity_box(ecs_import_from_library(
        lean_flecs_World_fromRepr(world),
        lean_string_cstr(libName),
        modName_c
    )));
}
