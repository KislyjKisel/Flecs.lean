import Pod.Meta
import Pod.Int

open Pod (Int32)

namespace Flecs

@[extern "lean_flecs_initialize_types"] private
opaque initializeTypes : BaseIO Unit
builtin_initialize initializeTypes


/-! # Core API Types -/

/--
Ids are the things that can be added to an entity.
An id can be an entity or pair, and can have optional id flags.
-/
def Id := UInt64

instance : Nonempty Id := inferInstanceAs (Nonempty UInt64)
instance : AndOp Id := inferInstanceAs (AndOp UInt64)
instance : OrOp Id := inferInstanceAs (OrOp UInt64)
instance : BEq Id := inferInstanceAs (BEq UInt64)
instance : Ord Id := inferInstanceAs (Ord UInt64)
instance : OfNat Id 0 := inferInstanceAs (OfNat UInt64 0)

abbrev Entity := Id

/--
A world is the container for all ECS data and supporting features.
Multiple isolated worlds may exist at the same time.
-/
define_foreign_type World

/-- A table stores entities and components for a specific type. -/
define_foreign_type Table

/-- A term is a single element in a query. -/
define_foreign_type Term

/-- A filter is an iterable data structure that describes a query. -/
define_foreign_type Filter

/-- A query that caches its results. -/
define_foreign_type Query

/-- A rule is a query with advanced graph traversal features. -/
define_foreign_type Rule

/-- An observer is a system that is invoked when an event matches its query. -/
define_foreign_type Observer

/-- An observable produces events that can be listened for by an observer. -/
define_foreign_type Observable

define_foreign_type Iter

/-- A ref is a fast way to fetch a component for a specific entity. -/
define_foreign_type Ref

/-- Type hooks are callbacks associated with component lifecycle events. -/
define_foreign_type TypeHooks

/-- Type information. -/
define_foreign_type TypeInfo

/-- Information about an entity, like its table and row. -/
define_foreign_type Record

/-- Information about a (component) id, such as type info and tables with the id. -/
define_foreign_type IdRecord

/-- Information about where in a table a specific (component) id is stored. -/
define_foreign_type TableRecord

/--
A poly (short for polymorph) object is an object that has a variable list of capabilities, determined by a mixin table.

This is the current list of types in the flecs API that can be used as an `Poly`:
* `World`
* `Stage`
* `Query`
* `Filter`
* `Rule`

Functions that accept an `Poly` argument can accept objects of these types.
If the object does not have the requested mixin the API will throw an assert.
-/
define_foreign_type Poly

private unsafe
def Poly.ofWorldImpl (world : World) : Poly := unsafeCast world

@[implemented_by ofWorldImpl]
opaque Poly.ofWorld (world : World) : Poly

-- private unsafe
-- def Poly.ofStageImpl (Stage : Stage) : Poly := unsafeCast Stage

-- @[implemented_by ofStageImpl]
-- opaque Poly.ofStage (Stage : Stage) : Poly

private unsafe
def Poly.ofQueryImpl (Query : Query) : Poly := unsafeCast Query

@[implemented_by ofQueryImpl]
opaque Poly.ofQuery (Query : Query) : Poly

private unsafe
def Poly.ofFilterImpl (Filter : Filter) : Poly := unsafeCast Filter

@[implemented_by ofFilterImpl]
opaque Poly.ofFilter (Filter : Filter) : Poly

private unsafe
def Poly.ofRuleImpl (Rule : Rule) : Poly := unsafeCast Rule

@[implemented_by ofRuleImpl]
opaque Poly.ofRule (Rule : Rule) : Poly

/-- Type that stores poly mixins. -/
define_foreign_type Mixins

/-- Header for `Poly` objects. -/
define_foreign_type Header


/-! # Function Types -/

/-- Action callback on world exit. -/
def FiniAction := World → BaseIO Unit



/-- Function type for runnables (systems, observers). -/
def RunAction := Iter → BaseIO Unit

/-- Function type for iterables. -/
def IterAction := Iter → BaseIO Unit

/-- Function type for creating an iterator from a poly. -/
def IterInitAction := World → Poly → Iter → Term → BaseIO Unit

/-- Function type for iterating an iterator  -/
def IterNextAction := Iter → BaseIO Bool

/-- Function type for freeing an iterator. -/
def IterFiniAction := Iter → BaseIO Unit

/-- Callback used for comparing components. -/
def OrderByAction (α : Type) := Entity → α → Entity → α → BaseIO Int32

-- /-- Callback used for sorting the entire table of components. -/
-- def SortTableAction

-- TODO: Complete function types (opaque or not? depends on usage)
