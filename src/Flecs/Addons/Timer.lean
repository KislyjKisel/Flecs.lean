import Pod.Int
import Pod.Instances
import Flecs.Core.Types
import Flecs.Core.Constants

open Pod (Int32 Storable)

namespace Flecs

variable {α : Type}

/-- Component used for one shot/interval timer functionality -/
structure Timer where
  /-- Timer timeout period -/
  timeout : FTime
  /-- Incrementing time value -/
  time : FTime
  /-- Used to correct returned interval time -/
  overshoot : FTime
  /-- Number of times ticked -/
  firedCount : Int32
  /-- Is the timer active or not -/
  active : Bool
  /-- Is this a single shot timer -/
  singleShot : Bool
deriving Repr, Inhabited

@[inherit_doc Entity.timer]
abbrev Timer.id : Entity := Entity.timer

instance : Storable Timer where
  byteSize := 20
  alignment := 4
  alignment_dvd_byteSize := by exists 5

#pod_c_rwbytes_instance Flecs.Timer

/-- Apply a rate filter to a tick source -/
structure RateFilter where
  /-- Source of the rate filter -/
  src : Entity
  /-- Rate of the rate filter -/
  rate : Int32
  /-- Number of times the rate filter ticked -/
  tickCount : Int32
  /-- Time elapsed since last tick -/
  timeElapsed : FTime
deriving Repr, Inhabited

@[inherit_doc Entity.rateFilter]
abbrev RateFilter.id : Entity := Entity.rateFilter

instance : Storable RateFilter where
  byteSize := 24
  alignment := 8
  alignment_dvd_byteSize := by exists 3

#pod_c_rwbytes_instance Flecs.RateFilter

/--
Set timer timeout.
This operation executes any systems associated with the timer after the specified timeout value.
If the entity contains an existing timer, the timeout value will be reset.
The timer can be started and stopped with `World.startTimer` and `World.stopTimer`.

The timer is synchronous, and is incremented each frame by `deltaTime`.

The `tickSource` entity will be a tick source after this operation.
Tick sources can be read by getting the `TickSource` component.
If the tick source ticked this frame, the `tick` member will be true.
When the tick source is a system, the system will tick when the timer ticks.
-/
@[extern "lean_flecs_World_setTimeout"]
opaque World.setTimeout (world : @& World α) (tickSource : Entity) (timeout : FTime) : BaseIO Entity

/--
Get current timeout value for the specified timer.
This operation returns the value set by `World.setTimeout`.
If no timer is active for this entity, the operation returns `0`.

After the timeout expires the `Timer` component is removed from the entity.
This means that if `World.getTimeout` is invoked after the timer is expired, the operation will return `0`.

The timer is synchronous, and is incremented each frame by `deltaTime`.

The `tickSource` entity will be a tick source after this operation.
Tick sources can be read by getting the `TickSource` component.
If the tick source ticked this frame, the `tick` member will be true.
When the tick source is a system, the system will tick when the timer ticks.
-/
@[extern "lean_flecs_World_getTimeout"]
opaque World.getTimeout (world : @& World α) (tickSource : Entity) : BaseIO FTime

/--
Set timer interval.
This operation will continuously invoke systems associated with the timer after the interval period expires.
If the entity contains an existing timer, the interval value will be reset.

The timer is synchronous, and is incremented each frame by `deltaTime`.

The `tickSource` entity will be a tick source after this operation.
Tick sources can be read by getting the `TickSource` component.
If the tick source ticked this frame, the `tick` member will be true.
When the tick source is a system, the system will tick when the timer ticks.
-/
@[extern "lean_flecs_World_setInterval"]
opaque World.setInterval (world : @& World α) (tickSource : Entity) (interval : FTime) : BaseIO Entity

/--
Get current interval value for the specified timer.
This operation returns the value set by `World.setInterval`.
If the entity is not a timer, the operation will return `0`.
-/
@[extern "lean_flecs_World_getInterval"]
opaque World.getInterval (world : @& World α) (tickSource : Entity) : BaseIO FTime

/--
Start timer.
This operation resets the timer and starts it with the specified timeout.
-/
@[extern "lean_flecs_World_startTimer"]
opaque World.startTimer (world : @& World α) (tickSource : Entity) : BaseIO Unit

/--
Stop timer.
This operation stops a timer from triggering.
-/
@[extern "lean_flecs_World_stopTimer"]
opaque World.stopTimer (world : @& World α) (tickSource : Entity) : BaseIO Unit

/--
Reset time value of timer to `0`.
This operation resets the timer value to `0`.
-/
@[extern "lean_flecs_World_resetTimer"]
opaque World.resetTimer (world : @& World α) (tickSource : Entity) : BaseIO Unit

/--
Enable randomizing initial time value of timers.
Initializes timers with a random time value, which can improve scheduling as
systems/timers for the same interval don't all happen on the same tick.
-/
@[extern "lean_flecs_World_randomizeTimers"]
opaque World.randomizeTimers (world : @& World α) : BaseIO Unit

/--
Set rate filter.
This operation initializes a rate filter. Rate filters sample tick sources
and tick at a configurable multiple. A rate filter is a tick source itself,
which means that rate filters can be chained.

Rate filters enable deterministic system execution which cannot be achieved
with interval timers alone. For example, if timer A has interval `2.0` and
timer B has interval `4.0`, it is not guaranteed that B will tick at exactly
twice the multiple of A. This is partly due to the indeterministic nature of
timers, and partly due to floating point rounding errors.

Rate filters can be combined with timers (or other rate filters) to ensure
that a system ticks at an exact multiple of a tick source (which can be
another system). If a rate filter is created with a rate of `1` it will tick
at the exact same time as its source.

If no tick source is provided, the rate filter will use the frame tick as
source, which corresponds with the number of times `World.progress` is called.

The tick_source entity will be a tick source after this operation. Tick
sources can be read by getting the `TickSource` component. If the tick
source ticked this frame, the `tick` member will be true. When the tick
source is a system, the system will tick when the timer ticks.

Parameters:
* `tickSource` The rate filter entity (0 to create one).
* `rate` The rate to apply.
* `source` The tick source (0 to use frames)

Returns the filter entity.
-/
@[extern "lean_flecs_World_setRate"]
opaque World.setRate (world : @& World α) (tickSource : Entity) (rate : Int32) (source : Entity) : BaseIO Entity

/--
Assign tick source to system.
Systems can be their own tick source, which can be any of the tick sources
(one shot timers, interval times and rate filters). However, in some cases it
is must be guaranteed that different systems tick on the exact same frame.

This cannot be guaranteed by giving two systems the same interval/rate filter
as it is possible that one system is (for example) disabled, which would
cause the systems to go out of sync. To provide these guarantees, systems
must use the same tick source, which is what this operation enables.

When two systems share the same tick source, it is guaranteed that they tick
in the same frame. The provided tick source can be any entity that is a tick
source, including another system. If the provided entity is not a tick source
the system will not be ran.

To disassociate a tick source from a system, use `0` for the `tickSource`
parameter.
-/
@[extern "lean_flecs_World_setTickSource"]
opaque World.setTickSource (world : @& World α) (system tickSource : Entity) : BaseIO Unit

/-- Timer module import function. -/
@[extern "lean_flecs_World_timerImport"]
opaque World.timerImport (world : @& World α) : BaseIO Unit
