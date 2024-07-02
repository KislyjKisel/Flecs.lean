import Flecs.Core.Types

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

-- TODO: ecs_new_w_table ecs_delete_with ecs_bulk_new_w_id ecs_bulk_init


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

-- TODO


/-! # Information -/

-- TODO


/-! # Names -/

-- TODO
