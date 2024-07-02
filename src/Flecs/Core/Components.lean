import Pod.Storable
import Flecs.Core.Types

open Pod (Storable)

namespace Flecs

variable {α : Type}

/--
This operation creates a new component, or finds an existing one.
The find or create behavior is the same as `entityInit`.
When an existing component is found, the size and alignment are verified with the provided values.
If the values do not match, the operation will fail.

This variant is for POD components, uses `Storable` to specify size and alignment.

Returns a handle to the new or existing component, or 0 if failed.
-/
@[extern "lean_flecs_componentUnboxed"]
opaque World.componentUnboxed (world : @& World α) (τ : Type) [@& Storable τ] (name : @& Option String := none) : BaseIO Entity

/--
This operation creates a new component, or finds an existing one.
The find or create behavior is the same as `entityInit`.
When an existing component is found, the size and alignment are verified with the provided values.
If the values do not match, the operation will fail.

This variant works for any component type.
Values are stored boxed.

Returns a handle to the new or existing component, or 0 if failed.
-/
@[extern "lean_flecs_component"]
opaque World.component (world : @& World α) (τ : Type) [Inhabited τ] (name : @& Option String := none) : BaseIO Entity
