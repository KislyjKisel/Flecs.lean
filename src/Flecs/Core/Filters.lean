import Pod.Int
import Flecs.Core.Types

open Pod (Int32)

namespace Flecs

variable {α : Type}

/--
Iterator for a parent's children.

This operation is equivalent to a term iterator for (ChildOf, parent).
Iterate the result with ecs_children_next().
-/
@[extern "lean_flecs_children"]
opaque World.children (world : @& World α) (parent : Entity) : BaseIO Iter

/--
Progress a children iterator.

Equivalent to `termNext`.
-/
@[extern "lean_flecs_Iter_childrenNext"]
opaque Iter.childrenNext (it : @& Iter) : BaseIO Bool

/--
A filter is a lightweight object that can be used to query for entities in a world.

[docs](https://www.flecs.dev/flecs/group__filters.html#ga39dda9984bff90cba46d2182280e23c5)
-/
@[extern "lean_flecs_filterInit"]
opaque World.filterInit (world : @& World α) (desc : @& FilterDesc) : BaseIO Filter

/-- Free resources associated with filter. -/
@[extern "lean_flecs_Filter_fini"]
opaque Filter.fini (filter : @& Filter) : BaseIO Unit

/--
Return a filter iterator.

A filter iterator lets an application iterate over entities that match the specified filter.
-/
@[extern "lean_flecs_Filter_iter"]
opaque Filter.iter (world : @& World α) (filter : @& Filter) : BaseIO Iter

/--
Return a chained filter iterator.

A chained iterator applies a filter to the results of the input iterator.
The resulting iterator must be iterated with `Iter.filterNext`.
-/
@[extern "lean_flecs_Filter_chainIter"]
opaque Filter.chainIter (it : @& Iter) (filter : @& Filter) : BaseIO Iter

/--
Convert filter terms to a string expression.
The resulting expression can be parsed to create the same filter.
-/
@[extern "lean_flecs_Filter_str"]
opaque Filter.str (world : @& World α) (filter : @& Filter) : BaseIO String

/--
Iterate tables matched by filter.

This operation progresses the filter iterator to the next table.
The iterator must have been initialized with `Filter.iter`.
This operation must be invoked at least once before interpreting the contents of the iterator.
-/
@[extern "lean_flecs_Iter_filterNext"]
opaque Iter.filterNext (it : @& Iter) : BaseIO Bool

/--
This operation checks whether a term is matched on a 0 source.
A 0 source is a term that isn't matched against anything,
and can be used just to pass (component) ids to a query iterator.

[docs](https://www.flecs.dev/flecs/group__filters.html#gaf4b52e0b71cdbef2639ddcb3b64363f3)
-/
@[extern "lean_flecs_Term_match0"]
opaque Term.match0 (term : @& Term) : BaseIO Bool

/--
This operation checks whether a term is matched on the $this variable, which is the default source for queries.

[docs](https://www.flecs.dev/flecs/group__filters.html#gaaf035f257b9e5af9dac67026021c5333)
-/
@[extern "lean_flecs_Term_matchThis"]
opaque Term.matchThis (term : @& Term) : BaseIO Bool

/--
A term iterator returns all entities (tables) that match a single (component) id.
The search for the matching set of entities (tables) is performed in constant time.
-/
@[extern "lean_flecs_Term_iter"]
opaque Term.iter (world : @& World α) (term : @& Term) : BaseIO Iter

/--
Return a chained term iterator.

A chained iterator applies a filter to the results of the input iterator.
The resulting iterator must be iterated with `Iter.termNext`.
-/
@[extern "lean_flecs_Term_chainIter"]
opaque Term.chainIter (world : @& World α) (it : @& Iter) (term : @& Term) : BaseIO Iter

/--
Progress a term iterator.

This operation progresses the term iterator to the next table.
The iterator must have been initialized with `termIter`.
This operation must be invoked at least once before interpreting the contents of the iterator.
-/
@[extern "lean_flecs_Iter_termNext"]
opaque Iter.termNext (it : @& Iter) : BaseIO Iter

/--
Convert term to a string expression.
The resulting expression is equivalent to the same term, with the exception of And & Or operators.
-/
@[extern "lean_flecs_Term_str"]
opaque Term.str (world : @& World α) (term : @& Term) : BaseIO String

-- TODO: ecs_filter_pivot_term ecs_filter_next_instanced ecs_filter_find_this_var
