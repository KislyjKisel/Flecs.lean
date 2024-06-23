import Pod.Meta
import Flecs.Core.Types

namespace Flecs

/-! # Component id flags -/

/-- Indicates that the id is a pair. -/
define_foreign_constant pair : Id := "lean_flecs_pair"

/-- Automatically override component when it is inherited. -/
define_foreign_constant override : Id := "lean_flecs_override"

/-- Adds bitset to storage which allows component to be enabled disabled. -/
define_foreign_constant toggle : Id := "lean_flecs_toggle"

/-- Include all components from entity to which AND is applied. -/
define_foreign_constant and : Id := "lean_flecs_and"


/-! # Builtin component ids -/

/-- Value used to quickly check if component is builtin. -/
define_foreign_constant lastInternalComponentId : Id := "lean_flecs_lastInternalComponentId"

/-- The first user-defined component starts from this id. -/
define_foreign_constant firstUserComponentId : Id := "lean_flecs_firstUserComponentId"

/-- The first user-defined entity starts from this id. -/
define_foreign_constant firstUserEntityId : Id := "lean_flecs_firstUserEntityId"


namespace Builtin

define_foreign_constant component : Entity := "lean_flecs_c_component"

define_foreign_constant identifier : Entity := "lean_flecs_c_identifier"

define_foreign_constant iterable : Entity := "lean_flecs_c_iterable"

define_foreign_constant poly : Entity := "lean_flecs_c_poly"

define_foreign_constant query : Entity := "lean_flecs_c_query"

define_foreign_constant observer : Entity := "lean_flecs_c_observer"

define_foreign_constant system : Entity := "lean_flecs_c_system"

define_foreign_constant tickSource : Entity := "lean_flecs_c_tickSource"

-- TODO: Builtin.pipelineQuery
-- define_foreign_constant pipelineQuery : Entity := "lean_flecs_c_pipelineQuery"

define_foreign_constant timer : Entity := "lean_flecs_c_timer"

define_foreign_constant rateFilter : Entity := "lean_flecs_c_rateFilter"

/-- Root scope for builtin flecs entities. -/
define_foreign_constant flecs : Entity := "lean_flecs_c_flecs"

/-- Core module scope. -/
define_foreign_constant flecsCore : Entity := "lean_flecs_c_flecsCore"

/-- Entity associated with world (used for "attaching" components to world). -/
define_foreign_constant world : Entity := "lean_flecs_c_world"

/-- Wildcard entity ("*"). Matches any id, returns all matches. -/
define_foreign_constant wildcard : Entity := "lean_flecs_c_wildcard"

/-- Any entity ("_"). Matches any id, returns only the first. -/
define_foreign_constant any : Entity := "lean_flecs_c_any"

/-- This entity. Default source for queries. -/
define_foreign_constant this : Entity := "lean_flecs_c_this"

/-- Variable entity ("$"). Used in expressions to prefix variable names. -/
define_foreign_constant «variable» : Entity := "lean_flecs_c_variable"

/-- Marks a relationship as transitive. -/
define_foreign_constant transitive : Entity := "lean_flecs_c_transitive"

/-- Marks a relationship as reflexive. -/
define_foreign_constant reflexive : Entity := "lean_flecs_c_reflexive"

/-- Ensures that entity/component cannot be used as target in IsA relationship. -/
define_foreign_constant final : Entity := "lean_flecs_c_final"

/-- Ensures that component is never inherited from an IsA target. -/
define_foreign_constant dontInherit : Entity := "lean_flecs_c_dontInherit"

/-- Ensures a component is always overridden. -/
define_foreign_constant alwaysOverride : Entity := "lean_flecs_c_alwaysOverride"

/-- Marks relationship as commutative. -/
define_foreign_constant symmetric : Entity := "lean_flecs_c_symmetric"

/-- Can be added to relationship to indicate that the relationship can only occur once on an entity. -/
define_foreign_constant exclusive : Entity := "lean_flecs_c_exclusive"

/-- Marks a relationship as acyclic. -/
define_foreign_constant acyclic : Entity := "lean_flecs_c_acyclic"

/-- Marks a relationship as traversable. -/
define_foreign_constant traversable : Entity := "lean_flecs_c_traversable"

/-- Ensure that a component always is added together with another component. -/
define_foreign_constant «with» : Entity := "lean_flecs_c_with"

/-- Ensure that relationship target is child of specified entity. -/
define_foreign_constant oneOf : Entity := "lean_flecs_c_oneOf"

/-- Can be added to relationship to indicate that it should never hold data, even when it or the relationship target is a component. -/
define_foreign_constant tag : Entity := "lean_flecs_c_tag"

/-- Can be added to components to indicate it is a trait. -/
define_foreign_constant trait : Entity := "lean_flecs_c_trait"

/-- Ensure that an entity is always used in pair as relationship. -/
define_foreign_constant relationship : Entity := "lean_flecs_c_relationship"

/-- Ensure that an entity is always used in pair as target. -/
define_foreign_constant target : Entity := "lean_flecs_c_target"

/-- Tag to indicate that relationship is stored as union. -/
define_foreign_constant union : Entity := "lean_flecs_c_union"

/-- Tag to indicate name identifier. -/
define_foreign_constant name : Entity := "lean_flecs_c_name"

/-- Tag to indicate symbol identifier. -/
define_foreign_constant symbol : Entity := "lean_flecs_c_symbol"

/-- Tag to indicate alias identifier. -/
define_foreign_constant alias : Entity := "lean_flecs_c_alias"

/-- Used to express parent-child relationships. -/
define_foreign_constant childOf : Entity := "lean_flecs_c_childOf"

/-- Used to express inheritance relationships. -/
define_foreign_constant isA : Entity := "lean_flecs_c_isA"

/-- Used to express dependency relationships. -/
define_foreign_constant dependsOn : Entity := "lean_flecs_c_dependsOn"

/-- Used to express a slot (used with prefab inheritance) -/
define_foreign_constant slotOf : Entity := "lean_flecs_c_slotOf"

/-- Tag added to module entities. -/
define_foreign_constant module : Entity := "lean_flecs_c_module"

/-- Tag to indicate an entity/component/system is private to a module. -/
define_foreign_constant «private» : Entity := "lean_flecs_c_private"

/-- Tag added to prefab entities. -/
define_foreign_constant prefab : Entity := "lean_flecs_c_prefab"

/-- When this tag is added to an entity it is skipped by queries, unless EcsDisabled is explicitly queried for. -/
define_foreign_constant disabled : Entity := "lean_flecs_c_disabled"

/-- Event that triggers when an id is added to an entity. -/
define_foreign_constant onAdd : Entity := "lean_flecs_c_onAdd"

/-- Event that triggers when an id is removed from an entity. -/
define_foreign_constant onRemove : Entity := "lean_flecs_c_onRemove"

/-- Event that triggers when a component is set for an entity. -/
define_foreign_constant onSet : Entity := "lean_flecs_c_onSet"

/-- Event that triggers when a component is unset for an entity. -/
define_foreign_constant unSet : Entity := "lean_flecs_c_unSet"

/-- Event that triggers observer when an entity starts/stops matching a query. -/
define_foreign_constant monitor : Entity := "lean_flecs_c_monitor"

/-- Event that triggers when a table is created. -/
define_foreign_constant onTableCreate : Entity := "lean_flecs_c_onTableCreate"

/-- Event that triggers when a table is deleted. -/
define_foreign_constant onTableDelete : Entity := "lean_flecs_c_onTableDelete"

/-- Event that triggers when a table becomes empty (doesn't emit on creation). -/
define_foreign_constant onTableEmpty : Entity := "lean_flecs_c_onTableEmpty"

/-- Event that triggers when a table becomes non-empty. -/
define_foreign_constant onTableFill : Entity := "lean_flecs_c_onTableFill"

/-- Relationship used for specifying cleanup behavior. -/
define_foreign_constant onDelete : Entity := "lean_flecs_c_onDelete"

/-- Relationship used to define what should happen when a target entity (second element of a pair) is deleted. -/
define_foreign_constant onDeleteTarget : Entity := "lean_flecs_c_onDeleteTarget"

/-- Remove cleanup policy. -/
define_foreign_constant remove : Entity := "lean_flecs_c_remove"

/-- Delete cleanup policy. -/
define_foreign_constant delete : Entity := "lean_flecs_c_delete"

/-- Panic cleanup policy. -/
define_foreign_constant panic : Entity := "lean_flecs_c_panic"

/-- Component that stores data for flattened relationships. -/
define_foreign_constant flattenTarget : Entity := "lean_flecs_c_flattenTarget"

/-- Tag added to root entity to indicate its subtree should be flattened. -/
define_foreign_constant flatten : Entity := "lean_flecs_c_flatten"

/-- Used like (EcsDefaultChildComponent, Component). -/
define_foreign_constant defaultChildComponent : Entity := "lean_flecs_c_defaultChildComponent"

define_foreign_constant predEq : Entity := "lean_flecs_c_predEq"

define_foreign_constant predMatch : Entity := "lean_flecs_c_predMatch"

define_foreign_constant predLookup : Entity := "lean_flecs_c_predLookup"

define_foreign_constant scopeOpen : Entity := "lean_flecs_c_scopeOpen"

define_foreign_constant scopeClose : Entity := "lean_flecs_c_scopeClose"

/-- Tag used to indicate query is empty. -/
define_foreign_constant empty : Entity := "lean_flecs_c_empty"

define_foreign_constant pipeline : Entity := "lean_flecs_c_pipeline"

define_foreign_constant onStart : Entity := "lean_flecs_c_onStart"

define_foreign_constant preFrame : Entity := "lean_flecs_c_preFrame"

define_foreign_constant onLoad : Entity := "lean_flecs_c_onLoad"

define_foreign_constant postLoad : Entity := "lean_flecs_c_postLoad"

define_foreign_constant preUpdate : Entity := "lean_flecs_c_preUpdate"

define_foreign_constant onUpdate : Entity := "lean_flecs_c_onUpdate"

define_foreign_constant onValidate : Entity := "lean_flecs_c_onValidate"

define_foreign_constant postUpdate : Entity := "lean_flecs_c_postUpdate"

define_foreign_constant preStore : Entity := "lean_flecs_c_preStore"

define_foreign_constant onStore : Entity := "lean_flecs_c_onStore"

define_foreign_constant postFrame : Entity := "lean_flecs_c_postFrame"

define_foreign_constant phase : Entity := "lean_flecs_c_phase"

end Builtin
