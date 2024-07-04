import Pod.Int
import Flecs.Core.Types

open Pod (Int32)

namespace Flecs

variable {α : Type}

/--
Returns whether specified id a tag.
This operation returns whether the specified type is a tag (a component without data/size).

An id is a tag when:
- it is an entity without the `Component` component
- it has an `Component` with size member set to `0`
- it is a pair where both elements are a tag
- it is a pair where the first element has the `PairIsTag` tag
-/
@[extern "lean_flecs_Id_isTag"]
opaque Id.isTag (world : @& World α) (id : Id) : BaseIO Bool

/--
This operation returns whether an id is in use in the world.
An id is in use if it has been added to one or more tables.
-/
@[extern "lean_flecs_Id_inUse"]
opaque Id.inUse (world : @& World α) (id : Id) : BaseIO Bool

/--
This operation returns the component id for an id, if the id is associated with a type.
For a regular component with a non-zero size (an entity with the
`Component` component) the operation will return the entity itself.

For an entity that does not have the EcsComponent component, or with an
`Component` value with size `0`, the operation will return `0`.

For a pair id the operation will return the type associated with the pair, by
applying the following querys in order:
- The first pair element is returned if it is a component
- `0` is returned if the relationship entity has the `Tag` property
- The second pair element is returned if it is a component
- `0` is returned.
-/
@[extern "lean_flecs_Id_getTypeId"]
opaque Id.getTypeId (world : @& World α) (id : Id) : BaseIO Entity

/--
Utility to match an id with a pattern.
This operation returns true if the provided pattern matches the provided id.
The pattern may contain a wildcard (or wildcards, when a pair).
-/
@[extern "lean_flecs_Id_match"]
opaque Id.match (id pattern : Id) : Bool

/-- Utility to check if id is a pair. -/
@[extern "lean_flecs_Id_isPair"]
opaque Id.isPair (id : Id) : Bool

/-- Utility to check if id is a wildcard. -/
@[extern "lean_flecs_Id_isWildcard"]
opaque Id.isWildcard (id : Id) : Bool

/--
Utility to check if id is valid.
A valid id is an id that can be added to an entity.
Invalid ids are:
- ids that contain wildcards
- ids that contain invalid entities
- ids that are `0` or contain `0` entities

Note that the same rules apply to removing from an entity, with the exception of wildcards.
-/
@[extern "lean_flecs_Id_isValid"]
opaque Id.isValid (world : @& World α) (id : Id) : BaseIO Bool

/-- Get intenal flags associated with id. [...] -/
@[extern "lean_flecs_Id_flags"]
opaque Id.flags (world : @& World α) (id : Id) : BaseIO Flags32

/-- Convert id flag to string. -/
@[extern "lean_flecs_Id_flagStr"]
opaque Id.flagStr (id : Id) : String

/-- This operation interprets the structure of an id and converts it to a string. -/
@[extern "lean_flecs_Id_str"]
opaque Id.str (world : @& World α) (id : Id) : BaseIO String
