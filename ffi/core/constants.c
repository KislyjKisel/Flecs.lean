#include <lean/lean.h>
#include <flecs.h>

LEAN_EXPORT uint64_t lean_flecs_pair(lean_object* unit) {
    return ECS_PAIR;
}

LEAN_EXPORT uint64_t lean_flecs_override(lean_object* unit) {
    return ECS_OVERRIDE;
}

LEAN_EXPORT uint64_t lean_flecs_toggle(lean_object* unit) {
    return ECS_TOGGLE;
}

LEAN_EXPORT uint64_t lean_flecs_and(lean_object* unit) {
    return ECS_AND;
}

LEAN_EXPORT uint64_t lean_flecs_lastInternalComponentId(lean_object* unit) {
    return EcsLastInternalComponentId;
}

LEAN_EXPORT uint64_t lean_flecs_firstUserComponentId(lean_object* unit) {
    return EcsFirstUserComponentId;
}

LEAN_EXPORT uint64_t lean_flecs_firstUserEntityId(lean_object* unit) {
    return EcsFirstUserEntityId;
}
