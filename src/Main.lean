import Flecs

def main : IO Unit := do
  let world ← Flecs.init
  world.atFini λ w ↦ do EIO.toBaseIO (IO.println s!"Hello! {← w.isFini}") *> pure ()
  world.fini
