import Flecs

structure Position where
  x : Float
  y : Float
  z : Float
deriving Repr, Inhabited

def main : IO Unit := do
  let world ← Flecs.init 42
  let positionId ← world.component Position
  let entity ← world.newWithId positionId
  IO.println positionId
  IO.println entity
  world.atFini λ w ↦ do EIO.toBaseIO (IO.println s!"Hello! {← w.isFini}") *> pure ()
  world.fini
