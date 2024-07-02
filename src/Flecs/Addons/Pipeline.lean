import Pod.Int
import Flecs.Core.Types

open Pod (Int32)

namespace Flecs

variable {α β : Type}

structure PipelineDesc (α β : Type) where
  /-- Existing entity to associate with pipeline (optional). -/
  entity : Entity := 0
  /--
  The pipeline query.
  Pipelines are queries that are matched with system entities. Pipeline
  queries are the same as regular queries, which means the same query rules
  apply. A common mistake is to try a pipeline that matches systems in a
  list of phases by specifying all the phases, like: `OnUpdate, OnPhysics, OnRender`.

  That however creates a query that matches entities with OnUpdate _and_
  OnPhysics _and_ OnRender tags, which is likely undesired. Instead, a
  query could use the or operator match a system that has one of the
  specified phases: `OnUpdate || OnPhysics || OnRender`.

  This will return the correct set of systems, but they likely won't be in
  the correct order. To make sure systems are returned in the correct order
  two query ordering features can be used:
  - `groupBy`
  - `orderBy`

  Take a look at the system manual for a more detailed explanation of
  how query features can be applied to pipelines, and how the builtin
  pipeline query works.
  -/
  query : QueryDesc α β

/-- Create a custom pipeline. -/
@[extern "lean_flecs_World_pipelineInit"]
opaque World.pipelineInit (world : @& World α) (desc : @& PipelineDesc α β) : BaseIO Entity

/--
Set a custom pipeline.
This operation sets the pipeline to run when `World.progress` is invoked.
-/
@[extern "lean_flecs_World_setPipeline"]
opaque World.setPipeline (world : @& World α) (pipeline : Entity) : BaseIO Unit

/-- Get the current pipeline. -/
@[extern "lean_flecs_World_getPipeline"]
opaque World.getPipeline (world : @& World α) : BaseIO Entity

/--
Progress a world.
This operation progresses the world by running all systems that are both
enabled and periodic on their matching entities.

An application can pass a delta_time into the function, which is the time passed since the last frame.
This value is passed to systems so they can update entity values
proportional to the elapsed time since their last invocation.

When an application passes `0` to `deltaTime`,
`World.progress` will automatically measure the time passed since the last frame.
If an application does not uses time management,
it should pass a non-zero value for delta_time (1.0 is recommended).
That way, no time will be wasted measuring the time.

Returns `false` if `World.quit` has been called, `true` otherwise.
-/
@[extern "lean_flecs_World_progress"]
opaque World.progress (world : @& World α) (deltaTime : FTime := 0) : BaseIO Bool

/--
Set time scale.
Increase or decrease simulation speed by the provided multiplier.
-/
@[extern "lean_flecs_World_setTimeScale"]
opaque World.setTimeScale (world : @& World α) (scale : FTime := 1.0) : BaseIO Unit

/-- Reset the clock that keeps track of the total time passed in the simulation. -/
@[extern "lean_flecs_World_resetClock"]
opaque World.resetClock (world : @& World α) : BaseIO Unit

/--
Run pipeline.
This will run all systems in the provided pipeline.
This operation may be invoked from multiple threads, and only when staging is disabled,
as the pipeline manages staging and, if necessary, synchronization between threads.

If 0 is provided for the pipeline id, the default pipeline will be ran
(this is either the builtin pipeline or the pipeline set with `World.setPipeline`).

When using `World.progress` this operation will be invoked automatically for the
default pipeline (either the builtin pipeline or the pipeline set with `World.setPipeline`).
An application may run additional pipelines.
-/
@[extern "lean_flecs_World_runPipeline"]
opaque World.runPipeline (world : @& World α) (pipeline : Entity) (deltaTime : FTime) : BaseIO Unit

/--
Set number of worker threads.
Setting this value to a value higher than 1 will start as many threads and
will cause systems to evenly distribute matched entities across threads.
The operation may be called multiple times to reconfigure the number of threads used,
but never while running a system / pipeline.
Calling `World.setThreads` will also end the use of task threads setup with `World.setTaskThreads` and vice-versa.
-/
@[extern "lean_flecs_World_setThreads"]
opaque World.setThreads (world : @& World α) (threads : Int32) : BaseIO Unit

/--
Set number of worker task threads.
`World.setTaskThreads` is similar to `World.setThreads`, except threads are treated
as short-lived tasks and will be created and joined around each update of the world.
Creation and joining of these tasks will use the `os_api_t` tasks APIs rather than the
the standard thread API functions, although they may be the same if desired.
This function is useful for multithreading world updates using an external
asynchronous job system rather than long running threads by providing the APIs
to create tasks for your job system and then wait on their conclusion.
The operation may be called multiple times to reconfigure the number of task threads used,
but never while running a system / pipeline.
Calling `World.setTaskThreads` will also end the use of threads setup with `World.setThreads` and vice-versa.
-/
@[extern "lean_flecs_World_setTaskThreads"]
opaque World.setTaskThreads (world : @& World α) (taskThreads : Int32) : BaseIO Unit

/-- Returns true if task thread use have been requested. -/
@[extern "lean_flecs_World_usingTaskThreads"]
opaque World.usingTaskThreads (world : @& World α) : BaseIO Bool
