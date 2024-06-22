import Pod.Meta
import Flecs.Core.Types

namespace Flecs

/-! # Component id flags -/

/-- Indicates that the id is a pair. -/
define_foreign_constant pair : Id := "lean_flecs_PAIR"

/-- Automatically override component when it is inherited. -/
define_foreign_constant override : Id := "lean_flecs_OVERRIDE"

/-- Adds bitset to storage which allows component to be enabled disabled. -/
define_foreign_constant toggle : Id := "lean_flecs_TOGGLE"

/-- Include all components from entity to which AND is applied. -/
define_foreign_constant and : Id := "lean_flecs_AND"


/-! # Builtin component ids -/

/-- Value used to quickly check if component is builtin. -/
define_foreign_constant lastInternalComponentId : Id := "lean_flecs_LastInternalComponentId"

/-- The first user-defined component starts from this id. -/
define_foreign_constant firstUserComponentId : Id := "lean_flecs_FirstUserComponentId"

/-- The first user-defined entity starts from this id. -/
define_foreign_constant firstUserEntityId : Id := "lean_flecs_FirstUserEntityId"

-- TODO: Builtin component ids
