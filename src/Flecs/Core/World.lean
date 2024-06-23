import Pod.Int
import Flecs.Core.Defines
import Flecs.Core.Types

open Pod (Int32)

namespace Flecs

/-! # Creation and deletion -/

/--
Create a new world.
Automatically imports modules from addons Flecs has been built with,
except when the module specifies otherwise.
-/
@[extern "lean_flecs_init"]
opaque init {α} (ctx : α) : BaseIO (World α)

/-- Create a new world with just the core module. -/
@[extern "lean_flecs_mini"]
opaque mini {α} (ctx : α) : BaseIO (World α)

/--
Create a new world with arguments.
Arguments are used to:
* automatically derive the name of the application from `args[0]`.
-/
@[extern "lean_flecs_init_w_args"]
opaque initWithArgs {α} (ctx : α) (args : @& Array String) : BaseIO (World α)

/-- This operation deletes a world, and everything it contains. -/
@[extern "lean_flecs_fini"]
opaque World.fini {α} (world : @& World α) : BaseIO Unit

/-- Returns whether the world is being deleted. -/
@[extern "lean_flecs_is_fini"]
opaque World.isFini {α} (world : @& World α) : BaseIO Bool

/-- Register an action to be executed when the world is destroyed. -/
@[extern "lean_flecs_at_fini"]
opaque World.atFini {α} (world : @& World α) (action : FiniAction α) : BaseIO Unit
