import Flecs.Core.Constants
import Flecs.Core.World

namespace Flecs

@[inherit_doc Builtin.isA]
def isA : Entity → Id := makePair Builtin.isA

@[inherit_doc Builtin.childOf]
def childOf : Entity → Id := makePair Builtin.childOf

@[inherit_doc Builtin.dependsOn]
def dependsOn : Entity → Id := makePair Builtin.dependsOn

@[inherit_doc Builtin.with]
def «with» : Entity → Id := makePair Builtin.with
