import Pod.Int
import Flecs.Core.Types

open Pod (Int32)

namespace Flecs

variable {α : Type}

/-- Callback type for init action -/
def AppInitAction (worldCtx) := World worldCtx → BaseIO Unit

/-- Callback type for run action -/
def AppRunAction (worldCtx) := World worldCtx → BaseIO Int32

/-- Callback type for frame action -/
def AppFrameAction (worldCtx) := World worldCtx → BaseIO Int32

/-- Used with `World.appRunFrame` -/
structure AppDesc where
  /-- Target FPS -/
  targetFps : FTime := 0
  /-- Frame time increment (0 for measured values) -/
  deltaTime : FTime := 0
  /-- Number of threads -/
  threads : Int32 := 0
  /-- Number of frames to run (0 for infinite) -/
  frames : Int32 := 0
  /-- Enables ECS access over HTTP, necessary for explorer -/
  enableRest : Bool := false
  /-- Periodically collect statistics -/
  enableStats : Bool := false
  /-- HTTP port used by REST API -/
  port : UInt16 := 0

/-- Used with `World.appRun` -/
structure AppDesc' (worldCtx : Type) extends AppDesc where
  /-- If `some`, function is ran before the run action -/
  init : Option (AppInitAction worldCtx) := none
  /-- If `none`, `frame` or default frame action gets called until returns non-zero result. -/
  run : Option (AppRunAction worldCtx) := none
  /-- If `run` is none, gets called by default run action every frame. Non-zero result stops execution. -/
  frame : Option (AppFrameAction worldCtx) := none

/--
Run application.
This will run the application with the parameters specified in `desc`.
After the application quits (`quit` is called) the world will be cleaned up.

If a custom run action is set, it will be invoked by this operation.
The default run action calls the frame action in a loop until it returns a non-zero value.
-/
@[extern "lean_flecs_World_appRun"]
opaque World.appRun (world : @& World α) (desc : AppDesc' α) : BaseIO Int32

/--
Default frame callback.
This operation will run a single frame.
By default this operation will invoke `progress` directly, unless a custom frame action is set.

Returns value returned by `progress`.
-/
@[extern "lean_flecs_World_appRunFrame"]
opaque World.appRunFrame (world : @& World α) (desc : @& AppDesc) : BaseIO Int32
