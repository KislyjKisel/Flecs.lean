import Lake
open Lake DSL

package flecs where
  srcDir := "src"
  leanOptions := #[⟨`autoImplicit, false⟩]

lean_lib Flecs where

@[default_target]
lean_exe «flecs-test» where
  root := `Main
