#include "logging.hh"

int main() {
    log_init();
    debugf("foo bar baz: %d", 42);
}
