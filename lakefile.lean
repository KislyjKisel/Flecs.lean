import Lake
open Lake DSL

def splitArgStr (s : String) : Array String :=
  Array.mk $ s.splitOn.filter $ not ∘ String.isEmpty

def optionCompilerFlecs := (get_config? flecs_cc).getD "cc"
def optionCompilerBindings := (get_config? bindings_cc).getD "cc"
def optionFlagsCompileFlecs := splitArgStr $ (get_config? flecs_cflags).getD ""
def optionFlagsCompileBindings := splitArgStr $ (get_config? bindings_cflags).getD ""

require pod from git "https://github.com/KislyjKisel/lean-pod" @ "b363d7c"

package flecs where
  srcDir := "src"
  leanOptions := #[⟨`autoImplicit, false⟩]

lean_lib Flecs where

@[default_target]
lean_exe «flecs-test» where
  root := `Main


section Flecs

def flecsFlags := #[
  "-DFLECS_CUSTOM_BUILD",
  "-DFLECS_OS_API_IMPL",
  "-DFLECS_MODULE",
  "-DFLECS_STATS",
  "-DFLECS_SYSTEM",
  "-DFLECS_PIPELINE",
  "-DFLECS_TIMER",
  "-DFLECS_APP"
]

target flecs.o pkg : FilePath := do
  let oFile := pkg.buildDir / "c" / "flecs.o"
  let srcJob ← inputTextFile <| pkg.dir / "flecs" / "flecs.c"
  buildO oFile srcJob #[]
    (optionFlagsCompileFlecs.push "-fPIC" |>.append flecsFlags)
    optionCompilerFlecs

-- extern_lib «flecs» pkg := do
--   let flecsO ← flecs.o.fetch
--   buildStaticLib (pkg.nativeLibDir / nameToStaticLib "flecs") #[flecsO]

end Flecs


section Bindings

def bindingsSources := #[
  "core/constants",
  "core/types",
  "core/world",
  "core/entities",
  "core/components",
  "core/ids",
  "core/queries",
  "core/observers",
  "core/iterators",
  "core/tables",
  "addons/module",
  "addons/stats",
  "addons/system",
  "addons/pipeline",
  "addons/timer",
  "addons/app"
]

def bindingsExtras : Array String := #[
  "ffi/include/flecs.lean/types.h",
  "ffi/util.h"
]

def bindingsCFlags (pkg : NPackage _package.name) : FetchM (Array String × Array String) := do
  let mut weakArgs := #["-I", (← getLeanIncludeDir).toString]
  let mut traceArgs := optionFlagsCompileBindings.append #[
    "-fPIC",
    "-I", (pkg.dir / "flecs").toString,
    "-I", (pkg.dir / "ffi" / "include").toString
  ] |>.append flecsFlags

  match pkg.deps.find? λ dep ↦ dep.name == `pod with
    | none => error "Missing dependency 'Pod'"
    | some pod => weakArgs := weakArgs ++ #["-I", (pod.dir / "src" / "native" / "include").toString]

  pure (weakArgs, traceArgs)

extern_lib «flecs-lean» pkg := do
  let name := nameToStaticLib "flecs-lean"
  let (weakArgs, traceArgs) ← bindingsCFlags pkg
  let nativeSrcDir := pkg.dir / "ffi"
  let objectFileDir := pkg.irDir / "ffi"
  let extraTrace ← mixTraceArray <$> (bindingsExtras.mapM $ λ h ↦ computeTrace (pkg.dir / ⟨h⟩))
  buildStaticLib (pkg.nativeLibDir / name)
    (#[(← flecs.o.fetch)].append
      (← bindingsSources.mapM λ suffix ↦ do
        buildO
          (objectFileDir / (suffix ++ ".o"))
          (← inputTextFile $ nativeSrcDir / (suffix ++ ".c"))
          weakArgs traceArgs
          optionCompilerBindings
          (pure extraTrace)
      ))

end Bindings
