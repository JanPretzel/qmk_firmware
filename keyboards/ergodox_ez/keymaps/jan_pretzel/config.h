#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

#define ONESHOT_TAP_TOGGLE 2
#define ONESHOT_TIMEOUT 1000

#undef LEADER_TIMEOUT
#define LEADER_TIMEOUT 500

#define IGNORE_MOD_TAP_INTERRUPT
#undef PERMISSIVE_HOLD

#define FORCE_NKRO

// defining it per key, since TAPPING_FORCE_HOLD will break anything
// that uses tapping toggles (Such as the TT layer keycode, and the
// One Shot Tapping Toggle).
#define TAPPING_FORCE_HOLD_PER_KEY

#endif
