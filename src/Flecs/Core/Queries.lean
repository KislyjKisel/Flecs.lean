import Flecs.Core.Types

namespace Flecs

variable {α : Type}

/--
Convert query to a string expression.
The resulting expression can be parsed to create the same query.
-/
@[extern "lean_flecs_Query_str"]
opaque Query.str (query : @& Query) : BaseIO String

/-- Create a query. -/
@[extern "lean_flecs_World_queryInit"]
opaque World.queryInit (world : @& World α) (desc : QueryDesc α) : BaseIO Query

/--
This operation destroys a query and its resources.
If the query is used as the parent of subqueries, those subqueries will be orphaned and must be deinitialized as well.
-/
@[extern "lean_flecs_Query_fini"]
opaque Query.fini (query : @& Query) : BaseIO Unit

/--
Find variable index.
This operation looks up the index of a variable in the query.
This index can be used in operations like `Iter.setVar` and `Iter.getVar`.

Returns `-1` if the variable wasn't found.
-/
@[extern "lean_flecs_Query_findVar"]
opaque Query.findVar (query : @& Query) (name : @& String) : BaseIO Int32

/--
Get variable name.

Returns `none` if `varId` is invalid.
-/
@[extern "lean_flecs_Query_varName"]
opaque Query.varName (query : @& Query) (varId : Int32) : BaseIO (Option String)

/--
Test if variable is an entity.
Internally the query engine has entity variables and table variables. When
iterating through query variables (by using ecs_query_variable_count) only
the values for entity variables are accessible. This operation enables an
application to check if a variable is an entity variable.

Returns `false` if `varId` is invalid.
-/
@[extern "lean_flecs_Query_varIsEntity"]
opaque Query.varIsEntity (query : @& Query) (varId : Int32) : BaseIO Bool

/--
Create a query iterator.
* Use an iterator to iterate through the entities that match an entity. Queries
* can return multiple results, and have to be iterated by repeatedly calling
* `Iter.queryNext` until the operation returns false.
*
* Depending on the query, a single result can contain an entire table, a range
* of entities in a table, or a single entity. Iteration code has an inner and
* an outer loop. The outer loop loops through the query results, and typically
* corresponds with a table. The inner loop loops entities in the result.

```lean4
let it ← q.iter world
while ← it.queryNext do
  for i in [: ← it.count] do
    let p ← it.field Position 0 i
    let v ← it.field Velocity 1 i
    it.setField 0 i (p + v)
```

If query iteration is stopped without the last call to `Iter.queryNext` returning `false`,
iterator resources need to be cleaned up explicitly.

[...]
-/
@[extern "lean_flecs_Query_iter"]
opaque Query.iter (world : @& World α) (query : @& Query) : BaseIO (Iter α)

/-- Progress query iterator. Returns `true` if the iterator has more results, `false` if not. -/
@[extern "lean_flecs_Iter_queryNext"]
opaque Iter.queryNext (it : @& Iter α) : BaseIO Bool

/--
Match entity with query.
This operation matches an entity with a query and returns the result of the match.
-/
@[extern "lean_flecs_Query_has"]
opaque Query.has (query : @& Query) (entity : Entity) : BaseIO (Option (Iter α))

/--
Match table with query.
This operation matches a table with a query and returns the result of the match.
-/
@[extern "lean_flecs_Query_hasTable"]
opaque Query.hasTable (query : @& Query) (table : @& Table) : BaseIO (Option (Iter α))

/--
Match range with query.
This operation matches a range with a query and returns the result of the match.

The entire range must match the query for the operation to return `some`.
-/
@[extern "lean_flecs_Query_hasRange"]
opaque Query.hasRange (query : @& Query) (range : @& TableRange) : BaseIO (Option (Iter α))

/--
Returns how often a match event happened for a cached query.
This operation can be used to determine whether the query cache has been updated with new tables.
-/
@[extern "lean_flecs_Query_matchCount"]
opaque Query.matchCount (query : @& Query) : BaseIO Int32

/--
Convert query to a string.
This will convert the query program to a string which can aid in debugging the behavior of a query.
-/
@[extern "lean_flecs_Query_plan"]
opaque Query.plan (query : @& Query) : BaseIO String

/--
Convert query to string with profile.
To use this you must set the `IterFlags.profile` flag on an iterator before starting iteration:
```lean4
it.setFlags ((← it.flags) ||| IterFlags.profile)
```
-/
@[extern "lean_flecs_Query_planWithProfile"]
opaque Query.planWithProfile (query : @& Query) (it : @& Iter α) : BaseIO String

-- TODO: Query.argsParse
-- /--
-- Populate variables from key-value string.
-- Convenience function to set query variables from a key-value string separated by comma's.
-- The string must have the following format: `var_a: value, var_b: value`.

-- The key-value list may optionally be enclosed in parenthesis.

-- This function uses the script addon.

-- Returns offset from the start of `expr` of the next character after the last parsed one.
-- -/
-- @[extern "lean_flecs_Query_argsParse"]
-- opaque Query.argsParse (query : @& Query) (it : @& Iter α) (expr : @& String) : BaseIO Nat

/--
Returns whether the query data changed since the last iteration.
The operation will return `true` after:
- new entities have been matched with
- new tables have been matched/unmatched with
- matched entities were deleted
- matched components were changed

[...]
-/
@[extern "lean_flecs_Query_changed"]
opaque Query.changed (query : @& Query) : BaseIO Bool

/--
Skip a table while iterating.
This operation lets the query iterator know that a table was skipped while iterating.
A skipped table will not reset its changed state,
and the query will not update the dirty flags of the table for its out columns.

Only valid iterators must be provided (next has to be called at least once & return `true`)
and the iterator must be a query iterator.
-/
@[extern "lean_flecs_Iter_skip"]
opaque Iter.skip (it : @& Iter α) : BaseIO Unit

/--
Set group to iterate for query iterator.
This operation limits the results returned by the query to only the selected
group id. The query must have a group_by function, and the iterator must be a query iterator.

[...]
-/
@[extern "lean_flecs_Iter_setGroup"]
opaque Iter.setGroup (it : @& Iter α) (groupId : UInt64) : BaseIO Unit

/--
Get context of query group.
This operation returns the context of a query group as returned by the `GroupBy` `onCreate` callback.
-/
@[extern "lean_flecs_Query_getGroupCtx"]
opaque Query.getGroupCtx (query : @& Query) (groupId : UInt64) : BaseIO (Option Dynamic)

/--
Get information about query group.
This operation returns information about a query group, including the group
context returned by the `GroupBy` `onCreate` callback.
-/
@[extern "lean_flecs_Query_getGroupInfo"]
opaque Query.getGroupInfo (query : @& Query) (groupId : UInt64) : BaseIO (Option QueryGroupInfo)

/-- Structure returned by `Query.count`. -/
structure QueryCount where
  /-- Number of results returned by query. -/
  results : Int32
  /-- Number of entities returned by query. -/
  entities : Int32
  /-- Number of tables returned by query. -/
  tables : Int32
  /-- Number of empty tables returned by query. -/
  emptyTables : Int32
deriving Inhabited

/--
Returns number of entities and results the query matches with.
Only entities matching the `$this` variable as source are counted.
-/
@[extern "lean_flecs_Query_count"]
opaque Query.count (query : @& Query) : BaseIO QueryCount

/-- Does query return one or more results.  -/
@[extern "lean_flecs_Query_isTrue"]
opaque Query.isTrue (query : @& Query) : BaseIO Bool
