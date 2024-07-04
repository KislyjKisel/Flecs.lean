import Pod.Int
import Flecs.Core.Types

open Pod (Int32)

namespace Flecs

variable {α : Type}

/-! # Creating & Deleting -/

/--
Create new entity id.

This operation returns an unused entity id.
This operation is guaranteed to return an empty entity as it does not use values set by `setScope` or `setWith`.
-/
@[extern "lean_flecs_new"]
opaque World.new (world : @& World α) : BaseIO Entity

/--
Create new low id.

This operation returns a new low id.
Entity ids start after the FLECS_HI_COMPONENT_ID constant.
This reserves a range of low ids for things like components,
and allows parts of the code to optimize operations.

Note that FLECS_HI_COMPONENT_ID does not represent the maximum number of components that
can be created, only the maximum number of components that can take advantage of these optimizations.

This operation is guaranteed to return an empty entity as
it does not use values set by `setScope` or `setWith`.

This operation does not recycle ids.
-/
@[extern "lean_flecs_newLowId"]
opaque World.newLowId (world : @& World α) : BaseIO Entity

/--
Create new entity with (component) id.

This operation creates a new entity with an optional (component) id.
When 0 is passed to the id parameter, no component is added to the new entity.
-/
@[extern "lean_flecs_newWithId"]
opaque World.newWithId (world : @& World α) (id : Id) : BaseIO Entity

/--
Find or create entity.

[...]
-/
@[extern "lean_flecs_World_entityInit"]
opaque World.entityInit (world : @& World α) (desc : @& EntityDesc) : BaseIO Entity

/--
This operation clones the components of one entity into another entity.

If no destination entity is provided, a new entity will be created.
Component values are not copied unless `copyValue` is true.

If the source entity has a name, it will not be copied to the destination entity.
This is to prevent having two entities with the same name under the same parent, which is not allowed.

Returns the destination entity.
-/
@[extern "lean_flecs_clone"]
opaque World.clone (world : @& World α) (dst src : Entity) (copyValue : Bool) : BaseIO Entity

/--
Delete an entity.

This operation will delete an entity and all of its components.
The entity id will be made available for recycling.
If the entity passed to `delete` is not alive, the operation will have no side effects.
-/
@[extern "lean_flecs_delete"]
opaque World.delete (world : @& World α) (entity : Entity) : BaseIO Unit

/--
Delete all entities with the specified id.

This will delete all entities (tables) that have the specified id.
The id may be a wildcard and/or a pair.
-/
@[extern "lean_flecs_deleteWith"]
opaque World.deleteWith (world : @& World α) (id : Id) : BaseIO Unit

-- TODO: ecs_new_w_table ecs_bulk_new_w_id ecs_bulk_init


/-! # Adding & Removing -/

/--
Add a (component) id to an entity.

This operation adds a single (component) id to an entity.
If the entity already has the id, this operation will have no side effects.
-/
@[extern "lean_flecs_addId"]
opaque World.addId (world : @& World α) (entity : Entity) (id : Id) : BaseIO Unit

/--
Remove a (component) id from an entity.

This operation removes a single (component) id to an entity.
If the entity does not have the id, this operation will have no side effects.
-/
@[extern "lean_flecs_removeId"]
opaque World.removeId (world : @& World α) (entity : Entity) (id : Id) : BaseIO Unit

/--
Add auto override for (component) id.
An auto override is a component that is automatically added to an entity when it is instantiated from a prefab.
Auto overrides are added to the entity that is inherited from (usually a prefab).
An auto override is equivalent to a manual override.
This operation is equivalent to manually adding the id with the `autoOverride` bit applied.

When a component is overridden and inherited from a prefab, the value from
the prefab component is copied to the instance. When the component is not
inherited from a prefab, it is added to the instance as if using ecs_add_id.

Overriding is the default behavior on prefab instantiation. Auto overriding
is only useful for components with the (OnInstantiate, Inherit) trait.
When a component has the (OnInstantiate, DontInherit) trait and is overridden
the component is added, but the value from the prefab will not be copied.
-/
@[extern "lean_flecs_autoOverrideId"]
opaque World.autoOverrideId (world : @& World α) (entity : Entity) (id : Id) : BaseIO Unit

/--
Clear all components.

This operation will remove all components from an entity.
-/
@[extern "lean_flecs_clear"]
opaque World.clear (world : @& World α) (entity : Entity) : BaseIO Unit

/--
Remove all instances of the specified (component) id.

This will remove the specified id from all entities (tables). The id may be a wildcard and/or a pair.
-/
@[extern "lean_flecs_removeAll"]
opaque World.removeAll (world : @& World α) (id : Id) : BaseIO Unit

/--
Set current with id.

New entities are automatically created with the specified id.
-/
@[extern "lean_flecs_setWith"]
opaque World.setWith (world : @& World α) (id : Id) : BaseIO Entity

/-- Get the id set with `setWith`. -/
@[extern "lean_flecs_getWith"]
opaque World.getWith (world : @& World α) : BaseIO Id


/-! # Enabling & Disabling -/

/--
Enable or disable entity.

This operation enables or disables an entity by adding or removing the `disabled` tag.
A disabled entity will not be matched with any systems,
unless the system explicitly specifies the `disabled` tag.
-/
@[extern "lean_flecs_enable"]
opaque World.enable (world : @& World α) (entity : Entity) (enabled : Bool) : BaseIO Unit

/--
Enable or disable component.

Enabling or disabling a component does not add or remove a component from an entity,
but prevents it from being matched with queries.
This operation can be useful when a component must be temporarily disabled without destroying its value.
It is also a more performant operation for when an application needs to
add/remove components at high frequency, as enabling/disabling is cheaper than a regular add or remove.
-/
@[extern "lean_flecs_enableId"]
opaque World.enableId (world : @& World α) (entity : Entity) (id : Id) (enable : Bool) : BaseIO Unit

/--
Test if component is enabled.

Test whether a component is currently enabled or disabled.
This operation will return true when the entity has the component and
if it has not been disabled by `enableId`.
-/
@[extern "lean_flecs_isEnabledId"]
opaque World.isEnabledId (world : @& World α) (entity : Entity) (id : Id) : BaseIO Bool


/-! # Getting and setting -/

-- TODO


/-! # Liveliness -/

/--
Test whether an entity is valid.
Entities that are valid can be used with API functions.
Using invalid entities with API operations will cause the function to panic.

An entity is valid if it is not `0` and if it is alive.

`World.isValid` will return `true` for ids that don't exist (alive or not alive).
This allows for using ids that have never been created by `World.newWithId` or similar.
In this the function differs from `World.isAlive`, which will return `false` for entities that do not yet exist.
-/
@[extern "lean_flecs_World_isValid"]
opaque World.isValid (world : @& World α) (entity : Entity) : BaseIO Bool

/--
Test whether an entity is alive.
Entities are alive after they are created, and become not alive when they are deleted.
Operations that return alive ids are (amongst others) `World.new`, `World.newLowId` and `World.entityInit`.
Ids can be made alive with the `World.makeAlive` function.

After an id is deleted it can be recycled.
Recycled ids are different from the original id in that they have a different generation count.
This makes it possible for the API to distinguish between the two.
An example:

```lean4
let e1 ← world.new
world.isAlive e1 -- true
world.delete e1
world.isAlive e1 -- false
let e2 ← world.new -- recycles e1
world.isAlive e2 -- true
world.isAlive e1 -- false
```
-/
@[extern "lean_flecs_World_isAlive"]
opaque World.isAlive (world : @& World α) (entity : Entity) : BaseIO Bool

/-- Remove generation from entity id. -/
@[extern "lean_flecs_World_stripGeneration"]
opaque World.stripGeneration (entity : Entity) : Id

/--
Get alive identifier.
In some cases an application may need to work with identifiers from which the generation has been stripped.
A typical scenario in which this happens is when iterating relationships in an entity type.

For example, when obtaining the parent id from a ChildOf relationship, the parent
(second element of the pair) will have been stored in a 32 bit value, which
cannot store the entity generation.
This function can retrieve the identifier with the current generation for that id.

If the provided identifier is not alive, the function will return `0`.
-/
@[extern "lean_flecs_World_getAlive"]
opaque World.getAlive (world : @& World α) (entity : Entity) : BaseIO Entity

/--
Ensure id is alive.
This operation ensures that the provided id is alive.
This is useful in scenarios where an application has an existing id that has not been created with
`World.newWithId` (such as a global constant or an id from a remote application).

When this operation is successful it guarantees that the provided id exists, is valid and is alive.

Before this operation the id must either not be alive or have a generation that
is equal to the passed in entity.

If the provided id has a non-zero generation count and the id does not exist in the world,
the id will be created with the specified generation.

If the provided id is alive and has a generation count that does not match the provided id,
the operation will fail.
-/
@[extern "lean_flecs_World_makeAlive"]
opaque World.makeAlive (world : @& World α) (entity : Entity) : BaseIO Unit

/--
Same as `World.makeAlive`, but for (component) ids.
An id can be an entity or pair, and can contain id flags.
This operation ensures that the entity (or entities, for a pair) are alive.

When this operation is successful it guarantees that the provided id can be
used in operations that accept an id.

Since entities in a pair do not encode their generation ids, this operation
will not fail when an entity with non-zero generation count already exists in
the world.

This is different from `World.makeAlive`, which will fail if attempted with an id
that has generation `0` and an entity with a non-zero generation is currently alive.
-/
@[extern "lean_flecs_World_makeAliveId"]
opaque World.makeAliveId (world : @& World α) (id : Id) : BaseIO Unit

/--
Test whether an entity exists.
Similar as `World.isAlive`, but ignores entity generation count.
-/
@[extern "lean_flecs_World_exists"]
opaque World.exists (world : @& World α) (entity : Entity) : BaseIO Bool

/--
Override the generation of an entity.
The generation count of an entity is increased each time an entity is deleted
and is used to test whether an entity id is alive.

This operation overrides the current generation of an entity with the
specified generation, which can be useful if an entity is externally managed,
like for external pools, savefiles or netcode.

This operation is similar to `World.makeAlive`, except that it will also
override the generation of an alive entity.
-/
@[extern "lean_flecs_World_setGeneration"]
opaque World.setGeneration (world : @& World α) (entity : Entity) : BaseIO Unit


/-! # Information -/

/-- Get the type of an entity (array with ids). -/
@[extern "lean_flecs_World_getType"]
opaque World.getType (world : @& World α) (entity : Entity) : BaseIO «Type»

/-- Get the table of an entity. -/
@[extern "lean_flecs_World_getTable"]
opaque World.getTable (world : @& World α) (entity : Entity) : BaseIO Table

/--
Convert table to string.
Same as `world.typeStr (← table.getType)`.
-/
@[extern "lean_flecs_Table_str"]
opaque Table.str (world : @& World α) (table : @& Table) : BaseIO String

/--
Convert entity to string.

[...]
-/
@[extern "lean_flecs_World_entityStr"]
opaque World.entityStr (world : @& World α) (entity : Entity) : BaseIO String

/--
Test if an entity has an id.
This operation returns `true` if the entity has or inherits the specified id.
-/
@[extern "lean_flecs_World_hasId"]
opaque World.hasId (world : @& World α) (entity : Entity) (id : Id) : BaseIO Bool

/--
Test if an entity owns an id.
This operation returns `true` if the entity has the specified id.
The operation behaves the same as `World.hasId`, except that it will return `false` for
components that are inherited through an `IsA` relationship.
-/
@[extern "lean_flecs_World_ownsId"]
opaque World.ownsId (world : @& World α) (entity : Entity) (id : Id) : BaseIO Bool

/--
Get the target of a relationship.
This will return a target (second element of a pair) of the entity for the specified relationship.
The index allows for iterating through the targets,
if a single entity has multiple targets for the same relationship.

If the index is larger than the total number of instances the entity has for the relationship,
the operation will return `0`.
-/
@[extern "lean_flecs_World_getTarget"]
opaque World.getTarget (world : @& World α) (entity rel : Entity) (index : Int32) : BaseIO Entity

/--
Get parent (target of `ChildOf` relationship) for entity.
This operation is the same as calling:
```lean4
world.getTarget entity Entity.childOf 0
```
-/
@[extern "lean_flecs_World_getParent"]
opaque World.getParent (world : @& World α) (entity : Entity) : BaseIO Entity

/--
Get the target of a relationship for a given id.
This operation returns the first entity that has the provided id by following the specified relationship.
If the entity itself has the id then entity will be returned.
If the id cannot be found on the entity or by following the relationship, the operation will return `0`.

This operation can be used to lookup, for example,
which prefab is providing a component by specifying the `IsA` relationship:
```lean4
world.getTargetForId entity Entity.isA Position.id
```
-/
@[extern "lean_flecs_World_getTargetForId"]
opaque World.getTargetForId (world : @& World α) (entity rel : Entity) (id : Id) : BaseIO Entity

/--
Return depth for entity in tree for the specified relationship.
Depth is determined by counting the number of targets encountered while
traversing up the relationship tree for `rel`.
Only acyclic relationships are supported.
-/
@[extern "lean_flecs_World_getDepth"]
opaque World.getDepth (world : @& World α) (entity rel : Entity) : BaseIO Int32

/-- Count entities that have the specified id. -/
@[extern "lean_flecs_World_countId"]
opaque World.countId (world : @& World α) (entity : Id) : BaseIO Int32


/-! # Names -/

-- TODO
