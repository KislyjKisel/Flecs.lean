import Flecs.Core.Types

namespace Flecs

variable {α : Type}

/-- Initialization action for modules -/
def ModuleAction (worldCtx) := World worldCtx → BaseIO Unit

/--
Import a module.
This operation will load a modules and store the public module handles in the handles_out out parameter.
The module name will be used to verify if the module was already loaded, in which case it won't be reimported.
The name will be translated from PascalCase to an entity path (pascal.case) before the lookup occurs.

Module contents will be stored as children of the module entity.
This prevents modules from accidentally defining conflicting identifiers.
This is enforced by setting the scope before and after loading the module to the module entity id.
-/
@[extern "lean_flecs_World_import"]
opaque World.import (world : @& World α) (module : ModuleAction α) (moduleName : @& String) : BaseIO Entity

/--
Same as `World.import`, but with name to scope conversion.
PascalCase names are automatically converted to scoped names.
-/
@[extern "lean_flecs_World_importC"]
opaque World.importC (world : @& World α) (module : ModuleAction α) (moduleName : @& String) : BaseIO Entity

/--
Import a module from a library.
Similar to `World.import`, except that this operation will attempt to load the module from a dynamic library.

[...]
-/
@[extern "lean_flecs_World_importFromLibrary"]
opaque World.importFromLibrary
  (world : @& World α) (libraryName : @& String) (moduleName : @& Option String := none) : BaseIO Entity

-- TODO: World.moduleInit
