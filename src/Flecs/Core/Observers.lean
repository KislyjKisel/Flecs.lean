import Flecs.Core.Types

namespace Flecs

variable {α : Type}

/--
Send event.
This sends an event to matching triggers & is the mechanism used by flecs
itself to send `OnAdd`, `OnRemove`, etc events.

Applications can use this function to send custom events, where a custom
event can be any regular entity.

Applications should not send builtin flecs events, as this may violate
assumptions the code makes about the conditions under which those events are sent.

Triggers are invoked synchronously.
-/
@[extern "lean_flecs_World_emit"]
opaque World.emit (world : @& World α) (desc : @& EventDesc α) : BaseIO Unit

/--
Enqueue event.
Same as `World.emit`, but enqueues an event in the command queue instead.
The event will be emitted when `World.deferEnd` is called.

If this operation is called when the provided world is not in deferred mode it behaves just like `World.emit`.
-/
@[extern "lean_flecs_World_enqueue"]
opaque World.enqueue (world : @& World α) (desc : @& EventDesc α) : BaseIO Unit

/--
Create observer.
Observers are like triggers, but can subscribe for multiple terms.
An observer only triggers when the source of the event meets all terms.

See the documentation for `ObserverDesc` for more details.
-/
@[extern "lean_flecs_World_observerInit"]
opaque World.observerInit (world : @& World α) (desc : @& ObserverDesc α) : BaseIO Entity

/--
Get observer object.
Returns the observer object.
Can be used to access various information about the observer, like the query and context.
-/
@[extern "lean_flecs_World_observerGet"]
opaque World.observerGet (world : @& World α) (observer : Entity) : BaseIO Observer
