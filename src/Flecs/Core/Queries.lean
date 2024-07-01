import Pod.Int
import Flecs.Core.Types

open Pod (Int32)

namespace Flecs

variable {α : Type}

/-- Create a query. -/
@[extern "lean_flecs_Query_init"]
opaque Query.init (world : @& World α) (desc : QueryDesc α) : BaseIO Query

/--
This operation destroys a query and its resources.
If the query is used as the parent of subqueries, those subqueries will be orphaned and must be deinitialized as well.
-/
@[extern "lean_flecs_Query_fini"]
opaque Query.fini (query : @& Query) : BaseIO Unit



-- /--
-- A query iterator lets an application iterate over entities that match the specified query.
-- If a sorting function is specified, the query will check whether a resort is required upon creating the iterator.

-- [docs](https://www.flecs.dev/flecs/group__queries.html#gab597483f9cec7f66c63f036fd418fcca)
-- -/
-- @[extern "lean_flecs_Query_iter"]
-- opaque Query.iter (world : @& World α) (query : @& Query) : BaseIO Iter

-- /--
-- Progress the query iterator.

-- This operation progresses the query iterator to the next table.
-- The iterator must have been initialized with `Query.iter`.
-- This operation must be invoked at least once before interpreting the contents of the iterator.
-- -/
-- @[extern "lean_flecs_Iter_queryNext"]
-- opaque Iter.queryNext (it : @& Iter) : BaseIO Bool

-- /-- Convert query to string. -/
-- @[extern "lean_flecs_Query_str"]
-- opaque Query.str (query : @& Query) : BaseIO String

-- /--
-- Returns whether query is orphaned.

-- When the parent query of a subquery is deleted, it is left in an orphaned state.
-- The only valid operation on an orphaned query is deleting it.
-- Only subqueries can be orphaned.
-- -/
-- @[extern "lean_flecs_Query_orphaned"]
-- opaque Query.orphaned (query : @& Query) : BaseIO Bool

-- /--
-- Returns whether the query data changed since the last iteration.
-- The operation will return true after:
-- * new entities have been matched with
-- * new tables have been matched/unmatched with
-- * matched entities were deleted
-- * matched components were changed

-- Parameters
-- * `query`: the query (optional if 'it' is provided).
-- * `it`:	the iterator result to test (optional if 'query' is provided).

-- [docs](https://www.flecs.dev/flecs/group__queries.html#gaeef4c3d6f9135c8bd771a940bb140a43)
-- -/
-- @[extern "lean_flecs_Query_changed"]
-- opaque Query.changed (query : @& Option Query) (it : @& Option Iter) : IO Bool

-- /--
-- Returns number of entities query matched with.

-- This operation iterates all non-empty tables in the query cache to find the total number of entities.
-- -/
-- @[extern "lean_flecs_Query_entityCount"]
-- opaque Query.entityCount (query : @& Query) : BaseIO Int32

-- /-- Returns number of tables query matched with. -/
-- @[extern "lean_flecs_Query_tableCount"]
-- opaque Query.tableCount (query : @& Query) : BaseIO Int32

-- /-- Returns number of empty tables query matched with. -/
-- @[extern "lean_flecs_Query_emptyTableCount"]
-- opaque Query.emptyTableCount (query : @& Query) : BaseIO Int32

-- -- TODO:
-- -- ecs_query_get_filter ecs_query_get_group_ctx ecs_query_get_group_info
-- -- ecs_query_next_instanced ecs_query_next_table ecs_query_populate ecs_query_set_group ecs_query_skip
