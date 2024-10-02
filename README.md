# log.h

Header-only library for simple `printf` logging in C/C++ (not thread safe).

## Usage

```c
#include "log.h"

int main() {
  set_log_level(LOG_LEVEL_DEBUG);

  trace("This is a trace message and will not be shown.");
  debug("Debugging value: %d", 42);
  info("Application started.");
  warning("Low disk space.");
  error("Failed to open file: %s", "config.txt");
}
```
