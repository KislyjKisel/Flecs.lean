namespace Flecs

def versionMajor := 3
def versionMinor := 2
def versionPatch := 12
def version := s!"{versionMajor}.{versionMinor}.{versionPatch}"

/-- Customizable precision for floating point operations. -/
abbrev FloatX := Float

/-- Customizable precision for scalar time values -/
abbrev FTime := FloatX

-- TODO: Parse flecs cflags option, provide configuration info
