import Flecs.Core.Types

namespace Flecs

/--
Create a new world.
Automatically imports modules from addons Flecs has been built with,
except when the module specifies otherwise.
-/
@[extern "lean_flecs_init"]
opaque init : BaseIO World

/-- Create a new world with just the core module. -/
@[extern "lean_flecs_mini"]
opaque mini : BaseIO World

/--
Create a new world with arguments.
Arguments are used to:
* automatically derive the name of the application from `args[0]`.
-/
@[extern "lean_flecs_init_w_args"]
opaque initWithArgs (args : @& Array String) : BaseIO World

/-- This operation deletes a world, and everything it contains. -/
@[extern "lean_flecs_fini"]
opaque World.fini (world : @& World) : BaseIO Unit

/-- Returns whether the world is being deleted. -/
@[extern "lean_flecs_is_fini"]
opaque World.isFini (world : @& World) : BaseIO Bool

/-- Register an action to be executed when the world is destroyed. -/
@[extern "lean_flecs_at_fini"]
opaque World.atFini (world : @& World) (action : FiniAction) : BaseIO Unit
