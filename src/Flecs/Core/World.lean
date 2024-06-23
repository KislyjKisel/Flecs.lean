import Pod.Int
import Flecs.Core.Defines
import Flecs.Core.Types

open Pod (Int32)

namespace Flecs

variable {α : Type}

/-! # Creation and deletion -/

/--
Create a new world.
Automatically imports modules from addons Flecs has been built with,
except when the module specifies otherwise.
-/
@[extern "lean_flecs_init"]
opaque init (ctx : α) : BaseIO (World α)

/-- Create a new world with just the core module. -/
@[extern "lean_flecs_mini"]
opaque mini (ctx : α) : BaseIO (World α)

/--
Create a new world with arguments.
Arguments are used to:
* automatically derive the name of the application from `args[0]`.
-/
@[extern "lean_flecs_initWithArgs"]
opaque initWithArgs (ctx : α) (args : @& Array String) : BaseIO (World α)

/-- This operation deletes a world, and everything it contains. -/
@[extern "lean_flecs_fini"]
opaque World.fini (world : @& World α) : BaseIO Unit

/-- Returns whether the world is being deleted. -/
@[extern "lean_flecs_isFini"]
opaque World.isFini (world : @& World α) : BaseIO Bool

/-- Register an action to be executed when the world is destroyed. -/
@[extern "lean_flecs_atFini"]
opaque World.atFini (world : @& World α) (action : FiniAction α) : BaseIO Unit


/-! # Frame -/

/--
When an application does not use `progress` to control the main loop,
it can still use Flecs features such as

Calls to `frameBegin` must always be followed by `frameEnd`.

`deltaTime` is passed to systems and used to to compute the amount of time
the function needs to sleep to ensure it does not exceed target fps, when it is set.
If `deltaTime` is zero, the time will be measured.

This function should only be ran from the main thread.
-/
@[extern "lean_flecs_frameBegin"]
opaque World.frameBegin (world : @& World α) (deltaTime : FTime) : BaseIO Unit

/-- This operation must be called at the end of the frame, and always after `frameBegin`. -/
@[extern "lean_flecs_frameEnd"]
opaque World.frameEnd (world : @& World α) : BaseIO Unit

/--
Frame time measurements measure total time passed in a single frame,
and how much of that time was spent on systems and on merging.

Frame time measurements add a small constant-time overhead to an application.
When an application sets a target FPS, frame time measurements are enabled by default.
-/
@[extern "lean_flecs_measureFrameTime"]
opaque World.measureFrameTime (world : @& World α) (enable : Bool) : BaseIO Unit

/--
System time measurements measure the time spent in each system.

System time measurements add overhead to every system invokation and
therefore have a small but measurable impact on application performance.
System time measurements must be enabled before obtaining system statistics.
-/
@[extern "lean_flecs_measureSystemTime"]
opaque World.measureSystemTime (world : @& World α) (enable : Bool) : BaseIO Unit

/--
This operation signals that the application should quit.

It will cause `progress` to return false.
-/
@[extern "lean_flecs_quit"]
opaque World.quit (world : @& World α) : BaseIO Unit

/--
Register action to be executed once after frame.

Post frame actions are typically used for calling operations that cannot be invoked during iteration, such as changing the number of threads.
-/
@[extern "lean_flecs_runPostFrame"]
opaque World.runPostFrame (world : @& World α) (action : FiniAction α) : BaseIO Unit

/--
Set a default value for the `ecs_filter_desc_t::flags` field.
Default flags are applied in addition to the flags provided in the descriptor.
For a list of available flags, see `include/flecs/private/api_flags.h`.
Typical flags to use are:

* `EcsFilterMatchInstanced`
* `EcsFilterMatchEmptyTables`
* `EcsFilterMatchDisabled`
* `EcsFilterMatchPrefab`

Only use flags that start with `EcsFilter`.
Do not use `EcsQuery*` flags.
This function may only be called when no queries are created.
-/
@[extern "lean_flecs_setDefaultQueryFlags"]
opaque World.setDefaultQueryFlags (world : @& World α) (flags : Flags32) : BaseIO Unit

/--
Set target frames per second (FPS) for application.

Setting the target FPS ensures that `progress` is not invoked faster than the specified FPS.
When enabled, `progress` tracks the time passed since the last invocation,
and sleeps the remaining time of the frame (if any).

This feature ensures systems are ran at a consistent interval,
as well as conserving CPU time by not running systems more often than required.

Note that `progress` only sleeps if there is time left in the frame.
Both time spent in flecs as time spent outside of flecs are taken into account.
-/
@[extern "lean_flecs_setTargetFps"]
opaque World.setTargetFps (world : @& World α) (fps : FTime) : BaseIO Unit

/-- Return whether a quit has been signaled. -/
@[extern "lean_flecs_shouldQuit"]
opaque World.shouldQuit (world : @& World α) : BaseIO Bool


/-! # Commands -/

/--
Begin readonly mode.

[docs](https://www.flecs.dev/flecs/group__commands.html#ga409ffe8d65b84e8b629e7c373ba6fffb)
-/
@[extern "lean_flecs_readonlyBegin"]
opaque World.readonlyBegin (world : @& World α) (mutliThreaded : Bool) : BaseIO Bool

/--
End readonly mode.

This operation ends readonly mode, and must be called after `readonlyBegin`.
Operations that were deferred while the world was in readonly mode will be flushed.
-/
@[extern "lean_flecs_readonlyEnd"]
opaque World.readonlyEnd (world : @& World α) : BaseIO Unit

/--
Merge world or stage.

When automatic merging is disabled, an application can call this operation on either
an individual stage, or on the world which will merge all stages.
This operation may only be called when staging is not enabled
(either after `progress` or after `readonlyEnd`).

This operation may be called on an already merged stage or world.
-/
@[extern "lean_flecs_merge"]
opaque World.merge (world : @& World α) : BaseIO Unit

/--
Defer operations until end of frame.

When this operation is invoked while iterating,
operations inbetween the `deferBegin` and `deferEnd` operations are executed at the end of the frame.

This operation is thread safe.
-/
@[extern "lean_flecs_deferBegin"]
opaque World.deferBegin (world : @& World α) : BaseIO Bool

/-- Test if deferring is enabled for current stage. -/
@[extern "lean_flecs_isDeferred"]
opaque World.isDeferred (world : @& World α) : BaseIO Bool

/--
End block of operations to defer.

See `deferBegin`.

This operation is thread safe.
-/
@[extern "lean_flecs_deferEnd"]
opaque World.deferEnd (world : @& World α) : BaseIO Bool

/--
Suspend deferring but do not flush queue.

This operation can be used to do an undeferred operation while not flushing the operations in the queue.

An application should invoke `deferResume` before `deferEnd` is called.
The operation may only be called when deferring is enabled.
-/
@[extern "lean_flecs_deferSuspend"]
opaque World.deferSuspend (world : @& World α) : BaseIO Unit

/-- Resume deferring. -/
@[extern "lean_flecs_deferResume"]
opaque World.deferResume (world : @& World α) : BaseIO Unit

/--
Enable/disable auto-merging for world or stage.

When auto-merging is enabled, staged data will automatically be merged with the world when staging ends.
This happens at the end of `progress`, at a sync point or when `readonlyEnd` is called.

Applications can exercise more control over when data from a stage is merged by disabling auto-merging.
This requires an application to explicitly call `merge` on the stage.

When this function is invoked on the world, it sets all current stages to
the provided value and sets the default for new stages.
When this function is invoked on a stage, auto-merging is only set for that specific stage.
-/
@[extern "lean_flecs_setAutomerge"]
opaque World.setAutomerge (world : @& World α) (automerge : Bool) : BaseIO Unit

/--
Configure world to have N stages.

This initializes N stages, which allows applications to defer operations to multiple isolated defer queues.
This is typically used for applications with multiple threads,
where each thread gets its own queue, and commands are merged when threads are synchronized.

Note that the `setThreads` function already creates the appropriate number of stages.
The `setStageCount` operation is useful for applications that want to manage their own stages and/or threads.
-/
@[extern "lean_flecs_setStageCount"]
opaque World.setStageCount (world : @& World α) (stages : Int32) : BaseIO Unit

/--
Get number of configured stages.

Return number of stages set by `setStageCount`.
-/
@[extern "lean_flecs_getStageCount"]
opaque World.getStageCount (world : @& World α) : BaseIO Int32

/--
Get current stage id.

The stage id can be used by an application to learn about which stage it is using,
which typically corresponds with the worker thread id.
-/
@[extern "lean_flecs_getStageId"]
opaque World.getStageId (world : @& World α) : BaseIO Int32

/--
Get stage-specific world pointer.

Flecs threads can safely invoke the API as long as they have a private context
to write to, also referred to as the stage.
This function returns a pointer to a stage, disguised as a world pointer.

Note that this function does not(!) create a new world.
It simply wraps the existing world in a thread-specific context, which the API knows how to unwrap.
The reason the stage is returned as an `World` is so that it can be passed transparently to
the existing API functions, vs. having to create a dedicated API for threading.
-/
@[extern "lean_flecs_getStage"]
opaque World.getStage (world : @& World α) (stageId : Int32) : BaseIO (World α)

/--
Test whether the current world is readonly.

This function allows the code to test whether the currently used world
is readonly or whether it allows for writing.
-/
@[extern "lean_flecs_stageIsReadonly"]
opaque World.stageIsReadonly (world : @& World α) : BaseIO Bool

/--
Create asynchronous stage.

An asynchronous stage can be used to asynchronously queue operations for later merging with the world.
An asynchronous stage is similar to a regular stage, except that it does not allow reading from the world.

Asynchronous stages are never merged automatically,
and must therefore be manually merged with the `merge` function.
It is not necessary to call `deferBegin` or `deferEnd` before and after enqueuing commands,
as an asynchronous stage unconditionally defers operations.

The application must ensure that no commands are added to the stage while the stage is being merged.

An asynchronous stage must be cleaned up by `asyncStageFree`.
-/
@[extern "lean_flecs_asyncStageNew"]
opaque World.asyncStageNew (world : @& World α) : BaseIO (World α)

/--
Free asynchronous stage.

The provided stage must be an asynchronous stage.
If a non-asynchronous stage is provided, the operation will fail.
-/
@[extern "lean_flecs_asyncStageFree"]
opaque World.asyncStageFree (stage : @& World α) : BaseIO Unit

/-- Test whether provided stage is asynchronous.  -/
@[extern "lean_flecs_stageIsAsync"]
opaque World.stageIsAsync (stage : @& World α) : BaseIO Bool


/-! # Misc -/

/--
Set a world context.

This operation allows an application to register custom data with a world that
can be accessed anywhere where the application has the world.
-/
@[extern "lean_flecs_setCtx"]
opaque World.setCtx (world : @& World α) (value : α) : BaseIO Unit

/--
Get the world context.

This operation retrieves a previously set world context.
-/
@[extern "lean_flecs_getCtx"]
opaque World.getCtx [Nonempty α] (world : @& World α) : BaseIO α

/-- Get build info. -/
@[extern "lean_flecs_getBuildInfo"]
opaque getBuildInfo : BaseIO BuildInfo

/-- Get world info. -/
@[extern "lean_flecs_getWorldInfo"]
opaque World.getWorldInfo (world : @& World α) : BaseIO WorldInfo

/-- Dimension the world for a specified number of entities. -/
@[extern "lean_flecs_dim"]
opaque World.dim (world : @& World α) (entityCount : Int32) : BaseIO Unit

/-- Set a range for issuing new entity ids. -/
@[extern "lean_flecs_setEntityRange"]
opaque World.setEntityRange (world : @& World α) (idStart idEnd : Entity) : BaseIO Unit

/-- Enable/disable range limits. -/
@[extern "lean_flecs_enableRangeCheck"]
opaque World.enableRangeCheck (world : @& World α) (enable : Bool) : BaseIO Bool

/-- Get the largest issued entity id (not counting generation). -/
@[extern "lean_flecs_getMaxId"]
opaque World.getMaxId (world : @& World α) : BaseIO Entity

/-- Force aperiodic actions. -/
@[extern "lean_flecs_runAperiodic"]
opaque World.runAperiodic (world : @& World α) (flags : Flags32) : BaseIO Unit

-- TODO: getWorld (const pointer)
-- /-- Get world from poly. -/
-- @[extern "lean_flecs_getWorld"]
-- opaque getWorld (poly : @& Poly α) : BaseIO (World α)

/-- Get entity from poly. -/
@[extern "lean_flecs_getEntity"]
opaque Poly.getEntity (poly : @& Poly α) : BaseIO Entity

/-- Make a pair id. -/
@[extern "lean_flecs_makePair"]
opaque makePair (first second : Entity) : Id

@[extern "lean_flecs_Poly_asWorld"]
opaque Poly.asWorld (poly : @& Poly α) : BaseIO (Option (World α))

@[extern "lean_flecs_Poly_asQuery"]
opaque Poly.asQuery (poly : @& Poly α) : BaseIO (Option Query)

@[extern "lean_flecs_Poly_asFilter"]
opaque Poly.asFilter (poly : @& Poly α) : BaseIO (Option Filter)

@[extern "lean_flecs_Poly_asRule"]
opaque Poly.asRule (poly : @& Poly α) : BaseIO (Option Rule)
