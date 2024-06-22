#include <lean/lean.h>
#include <flecs.h>
#include <flecs.lean/types.h>

LEAN_EXPORT lean_obj_res lean_flecs_init(lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_World_box(ecs_init()));
}

LEAN_EXPORT lean_obj_res lean_flecs_mini(lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_flecs_World_box(ecs_mini()));
}

LEAN_EXPORT lean_obj_res lean_flecs_init_w_args(b_lean_obj_arg args, lean_obj_arg io_) {
    size_t size = lean_array_size(args);
    char** argv = malloc(size * sizeof(char*));
    for (size_t i = 0; i < size; ++i) {
        argv[i] = (char*)lean_string_cstr(lean_array_get_core(args, i));
    }
    ecs_world_t* world = ecs_init_w_args(size, argv);
    free(argv);
    return lean_io_result_mk_ok(lean_flecs_World_box(world));
}

LEAN_EXPORT lean_obj_res lean_flecs_fini(b_lean_obj_arg world, lean_obj_arg io_) {
    ecs_fini(lean_flecs_World_fromRepr(world));
    return lean_io_result_mk_ok(lean_box(0));
}

LEAN_EXPORT lean_obj_res lean_flecs_is_fini(b_lean_obj_arg world, lean_obj_arg io_) {
    return lean_io_result_mk_ok(lean_box(
        ecs_is_fini(lean_flecs_World_fromRepr(world))
    ));
}

static void lean_flecs_at_fini_wrapper(ecs_world_t* world, void* ctx) {
    lean_object* action = (lean_object*)ctx;
    lean_apply_2(action, lean_flecs_World_box(world), lean_box(0));
    lean_dec_ref(action); // called only once before the world is destroyed
}

LEAN_EXPORT lean_obj_res lean_flecs_at_fini(b_lean_obj_arg world, lean_obj_arg action, lean_obj_arg io_) {
    ecs_atfini(lean_flecs_World_fromRepr(world), lean_flecs_at_fini_wrapper, (void*)action);
    return lean_io_result_mk_ok(lean_box(0));
}
