import Flecs

def main : IO Unit := do
  let world ← Flecs.init 42
  world.atFini λ w ↦ do EIO.toBaseIO (IO.println s!"Hello! {← w.isFini}") *> pure ()
  world.fini
