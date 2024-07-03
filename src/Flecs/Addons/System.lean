import Pod.Meta
import Pod.Int
import Pod.Instances
import Flecs.Core.Types
import Flecs.Core.Constants

open Pod (Int32 Int64 Storable ReadBytes WriteBytes)

namespace Flecs

open scoped Pod

variable {α β : Type}

/-- Component used to provide a tick source to systems -/
structure TickSource where
  /-- `true` if providing tick -/
  tick : Bool
  /-- Time elapsed since last tick -/
  timeElapsed : FTime
deriving Repr, Inhabited

@[inherit_doc Entity.tickSource]
abbrev TickSource.id : Entity := Entity.tickSource

instance : Storable TickSource where
  byteSize := 8
  alignment := 4
  alignment_dvd_byteSize := by exists 2

#pod_c_rwbytes_instance Flecs.TickSource

/-- Use with `World.systemInit` to create or update a system. -/
structure SystemDesc (worldCtx groupCtx : Type) where
    /-- Existing entity to associate with system (optional) -/
    entity : Entity := 0
    /-- System query parameters -/
    query : QueryDesc worldCtx groupCtx
    /--
    Callback that is ran for each result returned by the system's query.
    This means that this callback can be invoked multiple times per system per frame,
    typically once for each matching table.

    Recieved iterator is (probably) valid only during callback execution and shouldn't escape it.
    -/
    callback : Iter worldCtx → (param : Dynamic) → BaseIO Unit
    /-- Interval in seconds at which the system should run -/
    interval : FTime := 0
    /-- Rate at which the system should run -/
    rate : Int32 := 0
    /-- External tick source that determines when system ticks -/
    tickSource : Entity := 0
    /-- If true, system will be ran on multiple threads -/
    multiThreaded : Bool := false
    /--
    If true, system will have access to the actual world.
    Cannot be true at the same time as `multiThreaded`.
    -/
    immediate : Bool := false

/-- Create or update a system -/
@[extern "lean_flecs_World_systemInit"]
opaque World.systemInit (world : @& World α) (desc : @& SystemDesc α β) : BaseIO Entity

define_foreign_type System (worldCtx : Type)  -- const*

/-- Entity associated with query -/
@[extern "lean_flecs_System_queryEntity"]
opaque System.queryEntity (system : @& System α) : BaseIO Entity

/-- Tick source associated with system -/
@[extern "lean_flecs_System_tickSource"]
opaque System.tickSource (system : @& System α) : BaseIO Entity

/-- Is system multithreaded -/
@[extern "lean_flecs_System_multiThreaded"]
opaque System.multiThreaded (system : @& System α) : BaseIO Bool

/-- Is system ran in immediate mode -/
@[extern "lean_flecs_System_immediate"]
opaque System.immediate (system : @& System α) : BaseIO Bool

/-- Time spent on running system -/
@[extern "lean_flecs_System_timeSpent"]
opaque System.timeSpent (system : @& System α) : BaseIO FTime

/-- Time passed since last invocation -/
@[extern "lean_flecs_System_timePassed"]
opaque System.timePassed (system : @& System α) : BaseIO FTime

/-- Last frame for which the system was considered -/
@[extern "lean_flecs_System_lastFrame"]
opaque System.lastFrame (system : @& System α) : BaseIO Int64

@[extern "lean_flecs_System_world"]
opaque System.world (system : @& System α) : BaseIO (@& World α)

@[extern "lean_flecs_System_entity"]
opaque System.entity (system : @& System α) : BaseIO Entity

/--
Returns the system object.
Can be used to access various information about the system, like the query and context.
-/
@[extern "lean_flecs_World_systemGet"]
opaque World.systemGet (world : @& World α) (system : Entity) : BaseIO (Option (System α))

/--
Run a specific system manually.
This operation runs a single system manually. It is an efficient way to
invoke logic on a set of entities, as manual systems are only matched to
tables at creation time or after creation time, when a new table is created.

Manual systems are useful to evaluate lists of pre-matched entities at
application defined times. Because none of the matching logic is evaluated
before the system is invoked, manual systems are much more efficient than
manually obtaining a list of entities and retrieving their components.

An application may pass custom data to a system through the param parameter.
This data can be accessed by the system through the param member in the
`Iter` value that is passed to the system callback.

Any system may interrupt execution by using `Iter.setInterruptedBy`.
This is particularly useful for manual systems, where the value provided is returned by this operation.
This, in combination with the param argument lets applications use manual systems to lookup entities:
once the entity has been found its handle is passed to `Iter.setInterruptedBy`,
which is then subsequently returned.
-/
@[extern "lean_flecs_World_run"]
opaque World.run (world : @& World α) (system : Entity) (deltaTime : FTime) (param : @& Dynamic) : BaseIO Entity

/--
Same as `World.run`, but subdivides entities across number of provided stages.
-/
@[extern "lean_flecs_World_runWorker"]
opaque World.runWorker
  (world : @& World α) (system : Entity) (stageCurrent stageCount : Int32)
  (deltaTime : FTime) (param : @& Dynamic) : BaseIO Entity

/-- System module import function. -/
@[extern "lean_flecs_World_systemImport"]
opaque World.systemImport (world : @& World α) : BaseIO Unit
