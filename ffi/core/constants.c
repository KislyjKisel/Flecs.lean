#include <lean/lean.h>
#include <flecs.h>
#include <flecs.lean/types.h>

LEAN_EXPORT lean_flecs_Id lean_flecs_pair(lean_object* unit) {
    return lean_flecs_Id_toRepr(ECS_PAIR);
}

LEAN_EXPORT lean_flecs_Id lean_flecs_autoOverride(lean_object* unit) {
    return lean_flecs_Id_toRepr(ECS_AUTO_OVERRIDE);
}

LEAN_EXPORT lean_flecs_Id lean_flecs_toggle(lean_object* unit) {
    return lean_flecs_Id_toRepr(ECS_TOGGLE);
}


LEAN_EXPORT lean_flecs_Id lean_flecs_lastInternalComponentId(lean_object* unit) {
    return lean_flecs_Id_toRepr(EcsLastInternalComponentId);
}

LEAN_EXPORT lean_flecs_Id lean_flecs_firstUserComponentId(lean_object* unit) {
    return lean_flecs_Id_toRepr(EcsFirstUserComponentId);
}

LEAN_EXPORT lean_flecs_Id lean_flecs_firstUserEntityId(lean_object* unit) {
    return lean_flecs_Id_toRepr(EcsFirstUserEntityId);
}


// Builtin component ids

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_component(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(ecs_id(EcsComponent));
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_identifier(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(ecs_id(EcsIdentifier));
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_poly(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(ecs_id(EcsPoly));
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_defaultChildComponent(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(ecs_id(EcsDefaultChildComponent));
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_query(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsQuery);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_observer(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsObserver);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_system(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsSystem);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_tickSource(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(ecs_id(EcsTickSource));
}

// TODO: pipelineQuery constant (linker error, requires building with pipelines enabled, cfg from lake?)
// LEAN_EXPORT lean_flecs_Entity lean_flecs_c_pipelineQuery(lean_obj_arg unit) {
//   return lean_flecs_Entity_toRepr(ecs_id(EcsPipelineQuery));
// }

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_timer(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(ecs_id(EcsTimer));
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_rateFilter(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(ecs_id(EcsRateFilter));
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_flecs(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsFlecs);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_flecsCore(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsFlecsCore);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_world(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsWorld);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_wildcard(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsWildcard);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_any(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsAny);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_this(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsThis);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_variable(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsVariable);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_transitive(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsTransitive);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_reflexive(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsReflexive);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_final(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsFinal);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_onInstantiate(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsOnInstantiate);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_override(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsOverride);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_inherit(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsInherit);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_dontInherit(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsDontInherit);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_symmetric(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsSymmetric);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_exclusive(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsExclusive);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_acyclic(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsAcyclic);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_traversable(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsTraversable);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_with(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsWith);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_oneOf(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsOneOf);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_canToggle(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsCanToggle);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_trait(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsTrait);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_relationship(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsRelationship);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_target(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsTarget);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_pairIsTag(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsPairIsTag);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_name(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsName);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_symbol(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsSymbol);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_alias(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsAlias);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_childOf(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsChildOf);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_isA(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsIsA);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_dependsOn(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsDependsOn);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_slotOf(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsSlotOf);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_module(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsModule);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_private(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsPrivate);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_prefab(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsPrefab);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_disabled(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsDisabled);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_onAdd(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsOnAdd);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_onRemove(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsOnRemove);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_onSet(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsOnSet);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_unSet(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsUnSet);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_monitor(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsMonitor);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_onTableCreate(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsOnTableCreate);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_onTableDelete(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsOnTableDelete);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_onTableEmpty(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsOnTableEmpty);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_onTableFill(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsOnTableFill);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_onDelete(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsOnDelete);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_onDeleteTarget(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsOnDeleteTarget);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_remove(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsRemove);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_delete(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsDelete);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_panic(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsPanic);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_sparse(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsSparse);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_union(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsUnion);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_predEq(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsPredEq);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_predMatch(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsPredMatch);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_predLookup(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsPredLookup);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_scopeOpen(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsScopeOpen);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_scopeClose(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsScopeClose);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_empty(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsEmpty);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_pipeline(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(ecs_id(EcsPipeline));
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_onStart(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsOnStart);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_preFrame(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsPreFrame);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_onLoad(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsOnLoad);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_postLoad(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsPostLoad);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_preUpdate(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsPreUpdate);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_onUpdate(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsOnUpdate);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_onValidate(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsOnValidate);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_postUpdate(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsPostUpdate);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_preStore(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsPreStore);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_onStore(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsOnStore);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_postFrame(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsPostFrame);
}

LEAN_EXPORT lean_flecs_Entity lean_flecs_c_phase(lean_obj_arg unit) {
  return lean_flecs_Entity_toRepr(EcsPhase);
}
