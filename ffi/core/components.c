#include <lean/lean.h>
#include <lean_pod.h>
#include <flecs.h>
#include <flecs.lean/types.h>

LEAN_EXPORT lean_obj_res lean_flecs_componentS(b_lean_obj_arg world, b_lean_obj_arg storable, lean_obj_arg io_) {
    ecs_component_desc_t desc = {
        .type.size = lean_usize_of_nat(lean_pod_Storable_byteSize(storable)),
        .type.alignment = lean_usize_of_nat(lean_pod_Storable_alignment(storable)),
    };
    ecs_entity_t entity = ecs_component_init(lean_flecs_World_fromRepr(world), &desc);
    return lean_io_result_mk_ok(lean_flecs_Entity_box(entity));
}

static void lean_flecs_component_hooks_bindings_ctx_free(void* ctx) {
    lean_dec((lean_object*)ctx);
}

static void lean_flecs_component_ctor(void *ptr, int32_t count, const ecs_type_info_t *type_info) {
    for (int32_t i = 0; i < count; ++i) {
        lean_inc(type_info->hooks.binding_ctx);
        *((lean_object**)ptr + i) = type_info->hooks.binding_ctx;
    }
}

static void lean_flecs_component_dtor(void *ptr, int32_t count, const ecs_type_info_t *type_info) {
    for (int32_t i = 0; i < count; ++i) {
        lean_dec(*((lean_object**)ptr + i));
    }
}

static void lean_flecs_component_copy(void *dst_ptr, const void *src_ptr, int32_t count, const ecs_type_info_t *type_info) {
    for (int32_t i = 0; i < count; ++i) {
        lean_object* src = *((lean_object**)src_ptr + i);
        lean_inc(src);
        *((lean_object**)dst_ptr + i) = src;
    }
}

static void lean_flecs_component_move(void *dst_ptr, void *src_ptr, int32_t count, const ecs_type_info_t *type_info) {
    for (int32_t i = 0; i < count; ++i) {
        lean_object** src_ptr_i = ((lean_object**)src_ptr + i);
        *((lean_object**)dst_ptr + i) = *src_ptr_i;
        *src_ptr_i = lean_box(0);
    }
}

LEAN_EXPORT lean_obj_res lean_flecs_component(b_lean_obj_arg world, lean_obj_arg inhabited, lean_obj_arg io_) {
    ecs_component_desc_t desc = {
        .type.size = sizeof(lean_object*),
        .type.alignment = ECS_ALIGNOF(lean_object*),
        .type.hooks.binding_ctx = inhabited,
        .type.hooks.binding_ctx_free = lean_flecs_component_hooks_bindings_ctx_free,
        .type.hooks.ctor = lean_flecs_component_ctor,
        .type.hooks.dtor = lean_flecs_component_dtor,
        .type.hooks.copy = lean_flecs_component_copy,
        .type.hooks.move = lean_flecs_component_move,
    };
    ecs_entity_t entity = ecs_component_init(lean_flecs_World_fromRepr(world), &desc);
    return lean_io_result_mk_ok(lean_flecs_Entity_box(entity));
}
