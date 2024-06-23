import Flecs.Core.Types

namespace Flecs

variable {α : Type}

/--
Create new entity id.

This operation returns an unused entity id.
This operation is guaranteed to return an empty entity as it does not use values set by `setScope` or `setWith`.
-/
@[extern "lean_flecs_newId"]
opaque World.newId (world : @& World α) : BaseIO Entity

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

-- TODO: ecs_new_w_table ecs_entity_init ecs_delete_with ecs_bulk_new_w_id ecs_bulk_init
