import Pod.Int
import Pod.Storable
import Pod.BytesRef
import Flecs.Core.Types

open Pod (Int32 Storable BytesRefMut)

namespace Flecs

variable {α}

/--
Progress any iterator.

This operation is useful in combination with iterators for which it is not known what created them.
Example use cases are functions that should accept any kind of iterator (such as serializers)
or iterators created from poly objects.

This operation is slightly slower than using a type-specific iterator (e.g. `Iter.filterNext`,
`Iter.queryNext`) as it has to call a function pointer which introduces a level of indirection.

Returns true if iterator has more results, false if not.
-/
@[extern "lean_flecs_Iter_next"]
opaque Iter.next (it : @& Iter) : BaseIO Bool

/--
This operation cleans up any resources associated with the iterator.

This operation should only be used when an iterator is not iterated until completion
(next has not yet returned false).
When an iterator is iterated until completion, resources are automatically freed.
-/
@[extern "lean_flecs_Iter_fini"]
opaque Iter.fini (it : @& Iter) : BaseIO Unit

/--
Count number of matched entities in query.

This operation returns the number of matched entities.
If a query contains no matched entities but still yields results
(e.g. it has no terms with This sources) the operation will return 0.

To determine the number of matched entities,
the operation iterates the iterator until it yields no more results.
-/
@[extern "lean_flecs_Iter_count"]
opaque Iter.count (it : @& Iter) : BaseIO Int32

/--
Test if iterator is true.

This operation will return true if the iterator returns at least one result.
This is especially useful in combination with fact-checking rules (see the rules addon).

The operation requires a valid iterator.
After the operation is invoked, the application should no longer invoke next on the iterator
and should treat it as if the iterator is iterated until completion.
-/
@[extern "lean_flecs_Iter_isTrue"]
opaque Iter.isTrue (it : @& Iter) : BaseIO Bool

/--
Get first matching entity from iterator.

After this operation the application should treat the iterator as if it has been iterated until completion.

Returns 0 if no entities were matched.
-/
@[extern "lean_flecs_Iter_first"]
opaque Iter.first (it : @& Iter) : BaseIO Entity

/--
Set value for iterator variable.
This constrains the iterator to return only results for which the variable equals the specified value.
The default value for all variables is `.wildcard`,
which means the variable can assume any value.
-/
@[extern "lean_flecs_Iter_setVar"]
opaque Iter.setVar (it : @& Iter) (varId : Int32) (entity : Entity) : BaseIO Unit

/--
Same as `Iter.setVar`, but for a table.
This constrains the variable to all entities in a table.
-/
@[extern "lean_flecs_Iter_setVarAsTable"]
opaque Iter.setVarAsTable (it : @& Iter) (varId : Int32) (table : @& Table) : BaseIO Unit

/--
Same as `Iter.setVar`, but for a range of entities
This constrains the variable to a range of entities in a table.
-/
@[extern "lean_flecs_Iter_setVarAsRange"]
opaque Iter.setVarAsRange (it : @& Iter) (varId : Int32) (range : @& TableRange) : BaseIO Unit

/--
Get value of iterator variable as entity.
A variable can be interpreted as entity if it is set to an entity, or if it
is set to a table range with count 1.

This operation can only be invoked on valid iterators.
The variable index must be smaller than the total number of variables provided by the iterator.
(`Iter.variableCount`).
-/
@[extern "lean_flecs_Iter_getVar"]
opaque Iter.getVar (it : @& Iter) (varId : Int32) : BaseIO Entity

/--
Get value of iterator variable as table.
A variable can be interpreted as table if it is set as table range with
both offset and count set to 0, or if offset is 0 and count matches the
number of elements in the table.

This operation can only be invoked on valid iterators.
The variable index must be smaller than the total number of variables provided by the iterator
(`Iter.variableCount`).
-/
@[extern "lean_flecs_Iter_getVarAsTable"]
opaque Iter.getVarAsTable (it : @& Iter) (varId : Int32) : BaseIO Table

/--
Get value of iterator variable as table range.
A value can be interpreted as table range if it is set as table range, or if
it is set to an entity with a non-empty type (the entity must have at least
one component, tag or relationship in its type).

This operation can only be invoked on valid iterators.
The variable index must be smaller than the total number of variables provided by the iterator
(`Iter.variableCount`).
-/
@[extern "lean_flecs_Iter_getVarAsRange"]
opaque Iter.getVarAsRange (it : @& Iter) (varId : Int32) : BaseIO TableRange

/--
Returns whether variable is constrained.
This operation returns true for variables set by one of the `Iter.setVar*` operations.

A constrained variable is guaranteed not to change values while results are being iterated.
-/
@[extern "lean_flecs_Iter_varIsConstrained"]
opaque Iter.varIsConstrained (it : @& Iter) (varId : Int32) : BaseIO Bool

/--
Returns whether current iterator result has changed.
This operation must be used in combination with a query that supports change detection (e.g. is cached).
The operation returns whether the currently iterated result
has changed since the last time it was iterated by the query.

Change detection works on a per-table basis.
Changes to individual entities cannot be detected this way.
-/
@[extern "lean_flecs_Iter_changed"]
opaque Iter.changed (it : @& Iter) : BaseIO Bool

/--
Convert iterator to string.

Prints the contents of an iterator to a string.
Useful for debugging and/or testing the output of an iterator.

The function only converts the currently iterated data to a string.
To convert all data, the application has to manually call the next function and call `Iter.str` on each result.
-/
@[extern "lean_flecs_Iter_str"]
opaque Iter.str (it : @& Iter) : BaseIO String

-- TODO:
-- ecs_page_iter ecs_page_next
-- ecs_worker_iter ecs_worker_next

/--
This operation retrieves a pointer to an array of data that belongs to the term in the query.
The index refers to the location of the term in the query, and starts counting from one.

[docs](https://www.flecs.dev/flecs/group__iterator.html#ga2ac48f96b44d1ed4e69bc28d96029b7a)
-/
@[extern "lean_flecs_Iter_fieldWithSize"]
opaque Iter.fieldWithSize (it : @& Iter) (α : Type) [S : @& Storable α] (index : Int32) : BaseIO (BytesRefMut IO.RealWorld S.byteSize S.alignment)

/-- `Iter.fieldWithSize` alternative for boxed components. -/
@[extern "lean_flecs_Iter_field"]
opaque Iter.field (it : @& Iter) (α : Type) [Nonempty α] (index : Int32) : BaseIO α

/-- `Iter.fieldWithSize` alternative for boxed components. -/
@[extern "lean_flecs_Iter_setField"]
opaque Iter.setField (it : @& Iter) (index : Int32) (value : α) : BaseIO Unit

/-- Test whether the field is readonly. -/
@[extern "lean_flecs_Iter_fieldIsReadonly"]
opaque Iter.fieldIsReadonly (it : @& Iter) (index : Int32) : BaseIO Bool

/-- Test whether the field is writeonly. -/
@[extern "lean_flecs_Iter_fieldIsWriteonly"]
opaque Iter.fieldIsWriteonly (it : @& Iter) (index : Int32) : BaseIO Bool

/-- Test whether field is set. -/
@[extern "lean_flecs_Iter_fieldIsSet"]
opaque Iter.fieldIsSet (it : @& Iter) (index : Int32) : BaseIO Bool

/-- Return id matched for field. -/
@[extern "lean_flecs_Iter_fieldId"]
opaque Iter.fieldId (it : @& Iter) (index : Int32) : BaseIO Id

/--
Return index of matched table column.

This function only returns column indices for fields that have been matched on the $this variable.
Fields matched on other tables will return -1.
-/
@[extern "lean_flecs_Iter_fieldColumn"]
opaque Iter.fieldColumn (it : @& Iter) (index : Int32) : BaseIO Int32

/-- The field source is the entity on which the field was matched. -/
@[extern "lean_flecs_Iter_fieldSrc"]
opaque Iter.fieldSrc (it : @& Iter) (index : Int32) : BaseIO Entity

/-- Return type size of the field. Returns 0 if the field has no data. -/
@[extern "lean_flecs_Iter_fieldSize"]
opaque Iter.fieldSize (it : @& Iter) (index : Int32) : BaseIO USize

/--
Test whether the field is matched on self.

This operation returns whether the field is matched on the currently iterated entity.
This function will return false when the field is owned by another entity, such as a parent or a prefab.

When this operation returns false, the field must be accessed as a single value instead of an array.
Fields for which this operation returns true return arrays with it->count values.
-/
@[extern "lean_flecs_Iter_fieldIsSelf"]
opaque Iter.fieldIsSelf (it : @& Iter) (index : Int32) : BaseIO Bool
