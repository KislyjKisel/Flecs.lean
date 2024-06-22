#include <lean/lean.h>
#include <flecs.h>

LEAN_EXPORT uint64_t lean_flecs_PAIR(lean_object* unit) {
    return ECS_PAIR;
}

LEAN_EXPORT uint64_t lean_flecs_OVERRIDE(lean_object* unit) {
    return ECS_OVERRIDE;
}

LEAN_EXPORT uint64_t lean_flecs_TOGGLE(lean_object* unit) {
    return ECS_TOGGLE;
}

LEAN_EXPORT uint64_t lean_flecs_AND(lean_object* unit) {
    return ECS_AND;
}

LEAN_EXPORT uint64_t lean_flecs_LastInternalComponentId(lean_object* unit) {
    return EcsLastInternalComponentId;
}

LEAN_EXPORT uint64_t lean_flecs_FirstUserComponentId(lean_object* unit) {
    return EcsFirstUserComponentId;
}

LEAN_EXPORT uint64_t lean_flecs_FirstUserEntityId(lean_object* unit) {
    return EcsFirstUserEntityId;
}
