namespace Flecs

def versionMajor := 3
def versionMinor := 2
def versionPatch := 12
def version := s!"{versionMajor}.{versionMinor}.{versionPatch}"

/-- Customizable precision for floating point operations. -/
abbrev FloatX := Float32

/-- Customizable precision for scalar time values -/
abbrev FTime := FloatX

-- TODO: Parse flecs cflags option, provide configuration info

/-- Maximum number of ids to add `EntityDesc` / `BulkDesc`. -/
def idDescMax := 32

/-- Maximum number of events in `ObserverDesc`. -/
def eventDescMax := 8

/-- Maximum number of query variables per query. -/
def variableCountMax := 64

/-- Maximum number of terms in queries. Should not be set higher than 64. -/
def termCountMax := 32

/-- Maximum number of arguments for a term. -/
def termArgCountMax := 16
