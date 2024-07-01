import Pod.Meta
import Pod.Int
import Pod.Storable
import Flecs.Core.Defines

open Pod (Int16 Int32 Int64 Storable)

namespace Flecs

open scoped Pod

variable {α : Type}

@[extern "lean_flecs_initialize_types"] private
opaque initializeTypes : BaseIO Unit
builtin_initialize initializeTypes


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

instance : Inhabited Id := inferInstanceAs (Inhabited UInt64)
instance : AndOp Id := inferInstanceAs (AndOp UInt64)
instance : OrOp Id := inferInstanceAs (OrOp UInt64)
instance : BEq Id := inferInstanceAs (BEq UInt64)
instance : Ord Id := inferInstanceAs (Ord UInt64)
instance : OfNat Id 0 := inferInstanceAs (OfNat UInt64 0)
instance : Repr Id := inferInstanceAs (Repr UInt64)
instance : ToString Id := inferInstanceAs (ToString UInt64)
instance : Storable Id := inferInstanceAs (Storable UInt64)

abbrev Entity := Id

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

-- Unused
-- /-- An observer is a system that is invoked when an event matches its query. -/
-- define_foreign_type Observer

-- Unused
-- /-- An observable produces events that can be listened for by an observer. -/
-- define_foreign_type Observable

define_foreign_type Iter

-- Unused
-- /-- A ref is a fast way to fetch a component for a specific entity. -/
-- define_foreign_type Ref

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
define_foreign_type Poly (α : Type)

private unsafe
def Poly.ofWorldImpl (world : World α) : Poly α := unsafeCast world

@[implemented_by ofWorldImpl]
opaque Poly.ofWorld (world : World α) : Poly α

-- private unsafe
-- def Poly.ofStageImpl (Stage : Stage) : Poly := unsafeCast Stage

-- @[implemented_by ofStageImpl]
-- opaque Poly.ofStage (Stage : Stage) : Poly

private unsafe
def Poly.ofQueryImpl (Query : Query) : Poly α := unsafeCast Query
@[implemented_by ofQueryImpl]
opaque Poly.ofQuery (Query : Query) : Poly α

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
def GroupByAction (α) := World α → Table → Id → BaseIO UInt64

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

structure TermIdFlags where
  val : UInt64
deriving Repr, Inhabited

instance : OfNat TermIdFlags 0 := ⟨⟨0⟩⟩
instance : OrOp TermIdFlags where
  or a b := .mk (a.val ||| b.val)


/--
Match on self.
Can be combined with other term flags on the `TermRef.id` field.
-/
def TermIdFlags.self := TermIdFlags.mk ((1 : UInt64) <<< 63)

/--
Match by traversing upwards.
Can be combined with other term flags on the `TermRef.id` field.
-/
def TermIdFlags.up := TermIdFlags.mk ((1 : UInt64) <<< 62)

/--
Traverse relationship transitively.
Can be combined with other term flags on the `TermRef.id` field.
-/
def TermIdFlags.trav := TermIdFlags.mk ((1 : UInt64) <<< 61)

/--
Sort results breadth first.
Can be combined with other term flags on the `TermRef.id` field.
-/
def TermIdFlags.cascade := TermIdFlags.mk ((1 : UInt64) <<< 60)

/--
Iterate groups in descending order.
Can be combined with other term flags on the `TermRef.id` field.
-/
def TermIdFlags.desc := TermIdFlags.mk ((1 : UInt64) <<< 59)

/--
Term id is a variable.
Can be combined with other term flags on the `TermRef.id` field.
-/
def TermIdFlags.isVariable := TermIdFlags.mk ((1 : UInt64) <<< 58)

/--
Term id is an entity.
Can be combined with other term flags on the `TermRef.id` field.
-/
def TermIdFlags.isEntity := TermIdFlags.mk ((1 : UInt64) <<< 57)

/--
Term id is a name (don't attempt to lookup as entity).
Can be combined with other term flags on the `TermRef.id` field.
-/
def TermIdFlags.isName := TermIdFlags.mk ((1 : UInt64) <<< 56)

/-- All term traversal flags. Can be combined with other term flags on the `TermRef.id` field. -/
def traverseFlags := TermIdFlags.self ||| TermIdFlags.up ||| TermIdFlags.trav ||| TermIdFlags.cascade ||| TermIdFlags.desc

/-- All term reference kind flags. Can be combined with other term flags on the `TermRef.id` field. -/
def termRefFlags := traverseFlags ||| TermIdFlags.isVariable ||| TermIdFlags.isEntity ||| TermIdFlags.isName

/-- Type that describes a reference to an entity or variable in a term. -/
structure TermRef where
  /--
  Entity id.
  If left to 0 and flags does not specify whether id is an entity or a variable
  the id will be initialized to `Entity.this`.
  To explicitly set the id to 0, leave the id member to 0 and set `TermIdFlags.isEntity` in flags.
  -/
  id : Entity
  /--
  Name.
  This can be either the variable name (when `TermIdFlags.isVariable` flag is set) or an entity name.
  -/
  name : String
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
  /-- Access to contents matched by term. -/
  inout : InOutKind := .default
  /-- Operator of term. -/
  oper : OperKind := .and
  /-- Index of field for term in iterator. -/
  fieldIndex : Int16
deriving Repr, Inhabited


/-! # Miscellaneous types -/

-- TODO: Dependently typed `Value` (if its types aren't extensible, or class fromValue : Option α ?)
-- define_foreign_type Value

-- @[extern "lean_flecs_Value_type"]
-- opaque Value.type (value : @& Value) : Entity


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

/-- Number of tables without entities. -/
@[extern "lean_flecs_WorldInfo_emptyTableCount"]
opaque WorldInfo.emptyTableCount (wi : @& WorldInfo) : BaseIO Int32


/-- Type that contains information about a query group. -/
define_foreign_type QueryGroupInfo (α : Type)

/-- How often tables have been matched/unmatched. -/
@[extern "lean_flecs_QueryGroupInfo_matchCount"]
opaque QueryGroupInfo.matchCount (qgi : @& QueryGroupInfo α) : BaseIO Int32

/-- Number of tables in group. -/
@[extern "lean_flecs_QueryGroupInfo_tableCount"]
opaque QueryGroupInfo.tableCount (qgi : @& QueryGroupInfo α) : BaseIO Int32

/-- Group context, returned by the group creation callback. -/
@[extern "lean_flecs_QueryGroupInfo_ctx"]
opaque QueryGroupInfo.ctx [Nonempty α] (qgi : @& QueryGroupInfo α) : BaseIO α


/-! # Builtin component types -/


/-! # Other types -/

structure FilterDesc where
  terms : Array Term
  instanced : Bool := false
  flags : Flags32 := 0
  entity : Entity := 0
deriving Repr, Inhabited

/--
* `α` is used by `orderBy` as the `orderByComponent`'s component type
-/
structure QueryDesc (α : Type) where
  /--
  If set, the query will be created as a subquery.

  A subquery matches at most a subset of its parent query.
  Subqueries do not directly receive (table) notifications from the world.
  Instead parent queries forward results to subqueries.
  This can improve matching performance, as fewer queries need to be matched with new tables.
  Subqueries can be nested.
  -/
  parent : Option Query
  filter : FilterDesc
  /-- Component to be used by `orderBy`. -/
  orderByComponent : Entity
  orderBy : Option (OrderByAction α)
  -- todo: sort_table, group by
deriving Inhabited
