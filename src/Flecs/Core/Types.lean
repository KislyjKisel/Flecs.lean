import Pod.Meta
import Pod.Fixnum
import Pod.Storable
import Pod.ReadBytes
import Pod.Instances
import Flecs.Core.Defines

open Pod (UFixnum Storable ReadBytes)

namespace Flecs

open scoped Pod

variable {α : Type}

@[extern "lean_flecs_initialize_types"] private
opaque initializeTypes : BaseIO Unit
builtin_initialize initializeTypes


/--
A type with a TypeName instance.
Used to default initialize Dynamic fields since Init doesn't provide TypeName instances for common types.
-/
private inductive Unit' where | mk deriving TypeName

@[export lean_flecs_Dynamic_mk_empty] protected
def mkEmptyDynamic (_ : Unit) : Dynamic := Dynamic.mk Unit'.mk


/-! # Core API Types -/

abbrev Size := Int64
abbrev Flags8 := UInt8
abbrev Flags16 := UInt16
abbrev Flags32 := UInt32
abbrev Flags64 := UInt64

/--
Ids are the things that can be added to an entity.
An id can be an entity or pair, and can have optional id flags.
-/
def Id := UInt64
deriving Repr, Inhabited, AndOp, OrOp, BEq, Ord, ToString, Storable

instance : OfNat Id 0 := inferInstanceAs (OfNat UInt64 0)
instance : ReadBytes Id := inferInstanceAs (ReadBytes UInt64)

abbrev Entity := Id

abbrev «Type» := Array Id

/--
A world is the container for all ECS data and supporting features.
Multiple isolated worlds may exist at the same time.
-/
define_foreign_type World (α : Type)

/-- A table stores entities and components for a specific type. -/
define_foreign_type Table

/-- Range in table. Leave both `offset` and `count` to `0` to cover entire table. -/
structure TableRange where
  table : Table
  offset : Int32
  count : Int32
deriving Nonempty

/-- A query. -/
define_foreign_type Query

/-- An observer is a system that is invoked when an event matches its query. -/
define_foreign_type Observer -- const*

-- Unused
-- /-- An observable produces events that can be listened for by an observer. -/
-- define_foreign_type Observable

/--
Iterator.

Used for iterating queries.

[...]
-/
define_foreign_type Iter (worldCtx : Type)

/-- A ref is a fast way to fetch a component for a specific entity. -/
define_foreign_type Ref (componentType : Type)

-- C only
-- /-- Type hooks are callbacks associated with component lifecycle events. -/
-- define_foreign_type TypeHooks

-- C only
-- /-- Type information. -/
-- define_foreign_type TypeInfo

-- Unused
-- /-- Information about an entity, like its table and row. -/
-- define_foreign_type Record

-- Unused
-- /-- Information about a (component) id, such as type info and tables with the id. -/
-- define_foreign_type IdRecord

-- Unused
-- /-- Information about where in a table a specific (component) id is stored. -/
-- define_foreign_type TableRecord

/--
A poly (short for polymorph) object is an object that has a variable list of capabilities, determined by a mixin table.

This is the current list of types in the flecs API that can be used as an `Poly`:
* `World`
* `Stage`
* `Query`

Functions that accept an `Poly` argument can accept objects of these types.
If the object does not have the requested mixin the API will throw an assert.
-/
define_foreign_type Poly (worldCtx : Type)

private unsafe
def Poly.ofWorldImpl (world : World α) : Poly α := unsafeCast world

@[implemented_by ofWorldImpl]
opaque Poly.ofWorld (world : World α) : Poly α

-- private unsafe
-- def Poly.ofStageImpl (Stage : Stage) : Poly := unsafeCast Stage

-- @[implemented_by ofStageImpl]
-- opaque Poly.ofStage (Stage : Stage) : Poly

private unsafe
def Poly.ofQueryImpl (query : Query) : Poly α := unsafeCast query

@[implemented_by ofQueryImpl]
opaque Poly.ofQuery (query : Query) : Poly α

-- Unused
-- /-- Type that stores poly mixins. -/
-- define_foreign_type Mixins

-- Unused
-- /-- Header for `Poly` objects. -/
-- define_foreign_type Header


/-! # Function Types -/

/-- Action callback on world exit. -/
def FiniAction (α) := World α → BaseIO Unit

/-- Callback used for comparing components. -/
def OrderByAction (α : Type) := Entity → α → Entity → α → BaseIO Int32

/-- Callback used for grouping tables in a query. -/
def GroupByAction (α) := World α → Table → (groupId : Id) → BaseIO UInt64

/-- Callback invoked when a query creates a new group. -/
def GroupCreateAction (worldCtx : Type) := World worldCtx → (groupId : UInt64) → BaseIO Dynamic

def GroupCreateAction.unit : GroupCreateAction α := λ _ _ ↦ pure (Flecs.mkEmptyDynamic ())

/-- Callback invoked when a query deletes an existing group. -/
def GroupDeleteAction (worldCtx : Type) := World worldCtx → (groupId : UInt64) → Dynamic → BaseIO Unit

def GroupDeleteAction.unit : GroupDeleteAction α := λ _ _ _ ↦ pure ()

-- /-- Function type for runnables (systems, observers). -/
-- def RunAction := Iter → BaseIO Unit

-- /-- Function type for iterables. -/
-- def IterAction := Iter → BaseIO Unit

-- /-- Function type for creating an iterator from a poly. -/
-- def IterInitAction := World → Poly → Iter → Term → BaseIO Unit

-- /-- Function type for iterating an iterator  -/
-- def IterNextAction := Iter → BaseIO Bool

-- /-- Function type for freeing an iterator. -/
-- def IterFiniAction := Iter → BaseIO Unit


/-! # Poly mixin types -/


/-! # Query descriptor types -/

/-- Specify read/write access for term. -/
inductive InOutKind where
/-- `inOut` for regular terms, `in` for shared terms. -/
| default
/-- Term is neither read not written. -/
| none
/-- Same as `none` + prevents term from triggering observers -/
| filter
/-- Term is both read and written. -/
| inOut
/-- Term is only read. -/
| in
/-- Term is only written. -/
| out
deriving Repr, Inhabited, DecidableEq

/-- Specify operator for term. -/
inductive OperKind where
/-- The term must match. -/
| and
/-- On of the terms in an or chain must match. (todo: what?) -/
| or
/-- The term must not match. -/
| not
/-- The term may match. -/
| optional
/-- Term must match all components from term id. -/
| andFrom
/-- Term must match at least one component from term id. -/
| orFrom
/-- Term must match none of the components from term id. -/
| notFrom
deriving Repr, Inhabited, DecidableEq

/-- Specify cache policy for query -/
inductive QueryCacheKind where
/-- Behavior determined by query creation context -/
| default
/-- Cache query terms that are cachable -/
| auto
/-- Require that all query terms can be cached -/
| all
/-- No caching -/
| none
deriving Repr, Inhabited, DecidableEq

structure TermFlags where
  val : UInt64
deriving Repr, Inhabited

instance : OfNat TermFlags 0 := ⟨⟨0⟩⟩
instance : OrOp TermFlags where
  or a b := .mk (a.val ||| b.val)


/--
Match on self.
Can be combined with other term flags on the `TermRef.id` field.
-/
def TermFlags.self := TermFlags.mk ((1 : UInt64) <<< 63)

/--
Match by traversing upwards.
Can be combined with other term flags on the `TermRef.id` field.
-/
def TermFlags.up := TermFlags.mk ((1 : UInt64) <<< 62)

/--
Traverse relationship transitively.
Can be combined with other term flags on the `TermRef.id` field.
-/
def TermFlags.trav := TermFlags.mk ((1 : UInt64) <<< 61)

/--
Sort results breadth first.
Can be combined with other term flags on the `TermRef.id` field.
-/
def TermFlags.cascade := TermFlags.mk ((1 : UInt64) <<< 60)

/--
Iterate groups in descending order.
Can be combined with other term flags on the `TermRef.id` field.
-/
def TermFlags.desc := TermFlags.mk ((1 : UInt64) <<< 59)

/--
Term id is a variable.
Can be combined with other term flags on the `TermRef.id` field.
-/
def TermFlags.isVariable := TermFlags.mk ((1 : UInt64) <<< 58)

/--
Term id is an entity.
Can be combined with other term flags on the `TermRef.id` field.
-/
def TermFlags.isEntity := TermFlags.mk ((1 : UInt64) <<< 57)

/--
Term id is a name (don't attempt to lookup as entity).
Can be combined with other term flags on the `TermRef.id` field.
-/
def TermFlags.isName := TermFlags.mk ((1 : UInt64) <<< 56)

/-- All term traversal flags. Can be combined with other term flags on the `TermRef.id` field. -/
def traverseFlags := TermFlags.self ||| TermFlags.up ||| TermFlags.trav ||| TermFlags.cascade ||| TermFlags.desc

/-- All term reference kind flags. Can be combined with other term flags on the `TermRef.id` field. -/
def termRefFlags := traverseFlags ||| TermFlags.isVariable ||| TermFlags.isEntity ||| TermFlags.isName

/-- Type that describes a reference to an entity or variable in a term. -/
structure TermRef where
  /--
  Entity id.
  If left to 0 and flags does not specify whether id is an entity or a variable
  the id will be initialized to `Entity.this`.
  To explicitly set the id to 0, leave the id member to 0 and set `TermFlags.isEntity` in flags.
  -/
  id : Entity := 0
  /--
  Name.
  This can be either the variable name (when `TermFlags.isVariable` flag is set) or an entity name.
  -/
  name : Option String := none
deriving Repr, Inhabited

/-- Type that describes a term (single element in a query). -/
structure Term where
  /--
  Component id to be matched by term.
  Can be set directly, or will be populated from the first/second members, which provide more flexibility.
  -/
  id : Id := 0
  /-- Source of term. -/
  src : Option TermRef := none
  /-- Component or first element of pair. -/
  first : Option TermRef := none
  /-- Second element of pair. -/
  second : Option TermRef := none
  /--
  Relationship to traverse when looking for the component.
  The relationship must have the `Traversable` property.
  Default is `IsA`.
  -/
  trav : Entity := 0
  /-- Access to contents matched by term. -/
  inout : InOutKind := .default
  /-- Operator of term. -/
  oper : OperKind := .and
deriving Inhabited

structure QueryFlags where
  val : UInt32
deriving Repr, Inhabited

instance : OfNat QueryFlags 0 := ⟨⟨0⟩⟩
instance : OrOp QueryFlags where
  or a b := .mk (a.val ||| b.val)

/--
Query must match prefabs.
Can be combined with other query flags on the `QueryDesc.flags` field.
-/
def QueryFlags.matchPrefab := QueryFlags.mk ((1 : UInt32) <<< 1)

/--
Query must match disabled entities.
Can be combined with other query flags on the `QueryDesc.flags` field.
-/
def QueryFlags.matchDisabled := QueryFlags.mk ((1 : UInt32) <<< 2)

/--
Query must match empty tables.
Can be combined with other query flags on the `QueryDesc.flags` field.
-/
def QueryFlags.matchEmptyTables := QueryFlags.mk ((1 : UInt32) <<< 3)

/--
Query won't provide component data.
Can be combined with other query flags on the `QueryDesc.flags` field.
-/
def QueryFlags.noData := QueryFlags.mk ((1 : UInt32) <<< 4)

/--
Query iteration is always instanced.
Can be combined with other query flags on the `QueryDesc.flags` field.
-/
def QueryFlags.isInstanced := QueryFlags.mk ((1 : UInt32) <<< 5)

/--
Query may have unresolved entity identifiers.
Can be combined with other query flags on the `QueryDesc.flags` field.
-/
def QueryFlags.allowUnresolvedByName := QueryFlags.mk ((1 : UInt32) <<< 6)

/--
Query only returns whole tables (ignores toggle/member fields).
Can be combined with other query flags on the `QueryDesc.flags` field.
-/
def QueryFlags.tableOnly := QueryFlags.mk ((1 : UInt32) <<< 7)

inductive OrderBy where
| none
| boxed (entity : Entity) (α : Type) (callback : OrderByAction α)
| unboxed (entity : Entity) (α : Type) (callback : OrderByAction α) [Storable α] [ReadBytes α]

structure GroupBy (worldCtx : Type) where
  component : Id
  callback : Option (GroupByAction worldCtx) := none
  onCreate : GroupCreateAction worldCtx
  onDelete : GroupDeleteAction worldCtx

/-- Used with `Query.init`. -/
structure QueryDesc (worldCtx : Type) where
  /-- Query terms -/
  terms : Array Term := #[]
  terms_size_lt : terms.size < termCountMax := by simp; decide
  /-- Query DSL expression -/
  expr : Option String := none
  /-- Caching policy of query. -/
  cacheKind : QueryCacheKind := .default
  /-- Flags for enabling query features. -/
  flags : QueryFlags := 0
  orderBy : OrderBy := .none
  groupBy : Option (GroupBy worldCtx) := .none
  /-- Entity associated with query (optional). -/
  entity : Entity := 0

inductive EventTarget where
| entity (entity : Entity)
| table (table : Table) (offset count : Int32)

/-- Used with `World.emit` -/
structure EventDesc (worldCtx : Type) where
  /-- The event id. Only observers for the specified event will be notified. -/
  event : Entity
  /--
  Component ids.
  Only observers with a matching component id will be notified.
  Observers are guaranteed to get notified once, even if they match more than one id.
  Leave empty to use defaults (`#[Builtin.Any]`).
  -/
  ids : «Type» := #[]
  /--
  Passed to matched observers' callbacks.
  Bindings use `UFixnum` because it seems to be impossible to free the param, thus requiring an unboxed type.
  -/
  param : UFixnum := 0
  /-- Observable (usually the world) -/
  observable : Option (Poly worldCtx) := none
  /-- Event flags -/
  flags : Flags32 := 0
  target : EventTarget

/-- Used with `World.observerInit` -/
structure ObserverDesc (worldCtx : Type) where
  /-- Existing entity to associate with observer (optional) -/
  entity : Entity := 0
  /-- Query for observer -/
  query : QueryDesc worldCtx
  /-- Events to observe (`OnAdd`, `OnRemove`, `OnSet`) -/
  events : Array Entity
  /-- Observer must have at least one event -/
  events_lt_size : 0 < events.size
  events_size_lt : events.size < eventDescMax
  /--
  When observer is created, generate events from existing data.
  For example, `OnAdd` `Position` would match all existing instances of `Position`.
  -/
  yieldExisting : Bool := false
  /-- Callback to invoke on an event, invoked when the observer matches. -/
  callback : Iter worldCtx → (param : UFixnum) → BaseIO Unit
  /-- Observable with which to register the observer -/
  observable : Option (Poly worldCtx) := none


/-! # Miscellaneous types -/

-- TODO: Dependently typed `Value` (if its types aren't extensible, or class fromValue : Option α ?)
-- define_foreign_type Value

-- @[extern "lean_flecs_Value_type"]
-- opaque Value.type (value : @& Value) : Entity

structure EntityDesc where
  /-- Set to modify existing entity (optional) -/
  id : Entity := 0
  /-- Parent entity. -/
  parent : Entity := 0
  /--
  Name of the entity.
  If no entity is provided, an entity with this name will be looked up first.
  When an entity is provided, the name will be verified with the existing entity.
  -/
  name : Option String := none
  /--
  Optional custom separator for hierarchical names.
  Leave to `none` for default (`"."`) separator.
  Set to an empty string to prevent tokenization of name.
  -/
  sep : Option String := none
  /-- Optional, used for identifiers relative to root -/
  rootSep : Option String := none
  /--
  Optional entity symbol.
  A symbol is an unscoped identifier that can be used to lookup an entity.
  The primary use case for this is to associate the entity with a
  language identifier, such as a type or function name, where these
  identifiers differ from the name they are registered with in flecs.
  For example, C type "EcsPosition" might be registered as
  "flecs.components.transform.Position", with the symbol set to "EcsPosition".
  -/
  symbol : Option String := none
  /--
  When set to true, a low id (typically reserved for components)
  will be used to create the entity, if no id is specified.
  -/
  useLowId : Bool := false
  /-- Array of ids to add to the entity. -/
  add : Array Id := #[]
  -- TODO: Support "values" in `World.entityInit`
  /-- String expression with components to add -/
  addExpr : Option String := none

/-- Type with information about the current Flecs build. -/
define_foreign_type BuildInfo

/-- Compiler used to compile flecs. -/
@[extern "lean_flecs_BuildInfo_compiler"]
opaque BuildInfo.compiler (bi : @& BuildInfo) : BaseIO String

/-- Addons included in build. -/
@[extern "lean_flecs_BuildInfo_addons"]
opaque BuildInfo.addons (bi : @& BuildInfo) : BaseIO (Array String)

/-- Stringified version. -/
@[extern "lean_flecs_BuildInfo_version"]
opaque BuildInfo.version (bi : @& BuildInfo) : BaseIO String

/-- Major flecs version. -/
@[extern "lean_flecs_BuildInfo_versionMajor"]
opaque BuildInfo.versionMajor (bi : @& BuildInfo) : BaseIO Int16

/-- Minor flecs version. -/
@[extern "lean_flecs_BuildInfo_versionMinor"]
opaque BuildInfo.versionMinor (bi : @& BuildInfo) : BaseIO Int16

/-- Patch flecs version. -/
@[extern "lean_flecs_BuildInfo_versionPatch"]
opaque BuildInfo.versionPatch (bi : @& BuildInfo) : BaseIO Int16

/-- Is this a debug build. -/
@[extern "lean_flecs_BuildInfo_debug"]
opaque BuildInfo.debug (bi : @& BuildInfo) : BaseIO Bool

/-- Is this a sanitize build. -/
@[extern "lean_flecs_BuildInfo_sanitize"]
opaque BuildInfo.sanitize (bi : @& BuildInfo) : BaseIO Bool

/-- Is this a perf tracing build. -/
@[extern "lean_flecs_BuildInfo_perfTrace"]
opaque BuildInfo.perfTrace (bi : @& BuildInfo) : BaseIO Bool


/-- Type that contains information about the world. -/
define_foreign_type WorldInfo

/-- Last issued component entity id. -/
@[extern "lean_flecs_WorldInfo_lastComponentId"]
opaque WorldInfo.lastComponentId (wi : @& WorldInfo) : BaseIO Entity

/-- First allowed entity id. -/
@[extern "lean_flecs_WorldInfo_minId"]
opaque WorldInfo.minId (wi : @& WorldInfo) : BaseIO Entity

/-- Last allowed entity id. -/
@[extern "lean_flecs_WorldInfo_maxId"]
opaque WorldInfo.maxId (wi : @& WorldInfo) : BaseIO Entity

/-- Raw delta time (no time scaling). -/
@[extern "lean_flecs_WorldInfo_deltaTimeRaw"]
opaque WorldInfo.deltaTimeRaw (wi : @& WorldInfo) : BaseIO FTime

/-- Time passed to or computed by `progress`. -/
@[extern "lean_flecs_WorldInfo_deltaTime"]
opaque WorldInfo.deltaTime (wi : @& WorldInfo) : BaseIO FTime

/-- Time scaled applied to `deltaTime`. -/
@[extern "lean_flecs_WorldInfo_timeScale"]
opaque WorldInfo.timeScale (wi : @& WorldInfo) : BaseIO FTime

/-- Target FPS. -/
@[extern "lean_flecs_WorldInfo_targetFps"]
opaque WorldInfo.targetFps (wi : @& WorldInfo) : BaseIO FTime

/-- Total time spent processing a frame. -/
@[extern "lean_flecs_WorldInfo_frameTimeTotal"]
opaque WorldInfo.frameTimeTotal (wi : @& WorldInfo) : BaseIO FTime

/-- Total time spent in systems. -/
@[extern "lean_flecs_WorldInfo_systemTimeTotal"]
opaque WorldInfo.systemTimeTotal (wi : @& WorldInfo) : BaseIO FTime

/-- Total time spent notifying observers. -/
@[extern "lean_flecs_WorldInfo_emitTimeTotal"]
opaque WorldInfo.emitTimeTotal (wi : @& WorldInfo) : BaseIO FTime

/-- Total time spent in merges. -/
@[extern "lean_flecs_WorldInfo_mergeTimeTotal"]
opaque WorldInfo.mergeTimeTotal (wi : @& WorldInfo) : BaseIO FTime

/-- Time elapsed in simulation. -/
@[extern "lean_flecs_WorldInfo_worldTimeTotal"]
opaque WorldInfo.worldTimeTotal (wi : @& WorldInfo) : BaseIO FTime

/-- Time elapsed in simulation (no scaling). -/
@[extern "lean_flecs_WorldInfo_worldTimeTotalRaw"]
opaque WorldInfo.worldTimeTotalRaw (wi : @& WorldInfo) : BaseIO FTime

/-- Time spent on query rematching. -/
@[extern "lean_flecs_WorldInfo_rematchTimeTotal"]
opaque WorldInfo.rematchTimeTotal (wi : @& WorldInfo) : BaseIO FTime

/-- Total number of frames. -/
@[extern "lean_flecs_WorldInfo_frameCountTotal"]
opaque WorldInfo.frameCountTotal (wi : @& WorldInfo) : BaseIO Int64

/-- Total number of merges. -/
@[extern "lean_flecs_WorldInfo_mergeCountTotal"]
opaque WorldInfo.mergeCountTotal (wi : @& WorldInfo) : BaseIO Int64

/-- Total time of rematches. -/
@[extern "lean_flecs_WorldInfo_rematchCountTotal"]
opaque WorldInfo.rematchCountTotal (wi : @& WorldInfo) : BaseIO Int64

/-- Total number of times an id was created. -/
@[extern "lean_flecs_WorldInfo_idCreateTotal"]
opaque WorldInfo.idCreateTotal (wi : @& WorldInfo) : BaseIO Int64

/-- Total number of times an id was deleted. -/
@[extern "lean_flecs_WorldInfo_idDeleteTotal"]
opaque WorldInfo.idDeleteTotal (wi : @& WorldInfo) : BaseIO Int64

/-- Total number of times a table was created. -/
@[extern "lean_flecs_WorldInfo_tableCreateTotal"]
opaque WorldInfo.tableCreateTotal (wi : @& WorldInfo) : BaseIO Int64

/-- Total number of times a table was deleted. -/
@[extern "lean_flecs_WorldInfo_tableDeleteTotal"]
opaque WorldInfo.tableDeleteTotal (wi : @& WorldInfo) : BaseIO Int64

/-- Total number of pipeline builds. -/
@[extern "lean_flecs_WorldInfo_pipelineBuildCountTotal"]
opaque WorldInfo.pipelineBuildCountTotal (wi : @& WorldInfo) : BaseIO Int64

/-- Total number of systems ran in last frame. -/
@[extern "lean_flecs_WorldInfo_systemsRanFrame"]
opaque WorldInfo.systemsRanFrame (wi : @& WorldInfo) : BaseIO Int64

/-- Total number of times observer was invoked. -/
@[extern "lean_flecs_WorldInfo_observersRanFrame"]
opaque WorldInfo.observersRanFrame (wi : @& WorldInfo) : BaseIO Int64

/-- Number of tag (no data) ids in the world. -/
@[extern "lean_flecs_WorldInfo_tagIdCount"]
opaque WorldInfo.tagIdCount (wi : @& WorldInfo) : BaseIO Int32

/-- Number of component (data) ids in the world. -/
@[extern "lean_flecs_WorldInfo_componentIdCount"]
opaque WorldInfo.componentIdCount (wi : @& WorldInfo) : BaseIO Int32

/-- Number of pair ids in the world. -/
@[extern "lean_flecs_WorldInfo_pairIdCount"]
opaque WorldInfo.pairIdCount (wi : @& WorldInfo) : BaseIO Int32

/-- Number of tables. -/
@[extern "lean_flecs_WorldInfo_tableCount"]
opaque WorldInfo.tableCount (wi : @& WorldInfo) : BaseIO Int32


/-- Type that contains information about a query group. -/
define_foreign_type QueryGroupInfo

/-- How often tables have been matched/unmatched. -/
@[extern "lean_flecs_QueryGroupInfo_matchCount"]
opaque QueryGroupInfo.matchCount (qgi : @& QueryGroupInfo) : BaseIO Int32

/-- Number of tables in group. -/
@[extern "lean_flecs_QueryGroupInfo_tableCount"]
opaque QueryGroupInfo.tableCount (qgi : @& QueryGroupInfo) : BaseIO Int32

/-- Group context, returned by the group creation callback. -/
@[extern "lean_flecs_QueryGroupInfo_ctx"]
opaque QueryGroupInfo.ctx (qgi : @& QueryGroupInfo) : BaseIO Dynamic


/-- Used with `World.deleteEmptyTables` -/
structure DeleteEmptyTablesDesc where
  /-- Optional component filter for the tables to evaluate. -/
  id : Id := 0
  /-- Free table data when generation > clearGeneration. -/
  clearGeneration : UInt16 := 0
  /-- Delete table when generation > deleteGeneration. -/
  deleteGeneration : UInt16 := 0
  /-- Minimum number of component ids the table should have. -/
  minIdCount : UInt32 := 0
  /-- Amount of time operation is allowed to spend. -/
  timeBudgetSeconds : Float := 0.0
deriving Inhabited


/-! # Builtin component types -/


/-! # Other types -/
/-! # Other types -/


/-! # Wrapper types -/

/-- Aperiodic action flags (used by `World.runAperiodic`) -/
structure AperiodicActionFlags where
  val : UInt32
deriving Repr, Inhabited

instance : OfNat AperiodicActionFlags 0 := ⟨⟨0⟩⟩
instance : OrOp AperiodicActionFlags where
  or a b := .mk (a.val ||| b.val)

private
define_foreign_constant AperiodicActionFlags.emptyQueries' : Flags32 := "lean_flecs_AperiodicActionFlags_emptyQueries"

private
define_foreign_constant AperiodicActionFlags.componentMonitors' : Flags32 := "lean_flecs_AperiodicActionFlags_componentMonitors"

/--
Process empty queries.
-/
def AperiodicActionFlags.emptyQueries :=
  AperiodicActionFlags.mk AperiodicActionFlags.emptyQueries'

/--
Process component monitors.
-/
def AperiodicActionFlags.componentMonitors :=
  AperiodicActionFlags.mk AperiodicActionFlags.componentMonitors'
