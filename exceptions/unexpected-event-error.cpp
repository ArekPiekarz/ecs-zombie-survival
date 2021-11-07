#include "exceptions/unexpected-event-error.hpp"
#include <fmt/format.h>

using fmt::format;


UnexpectedEventError::UnexpectedEventError(ExpectedEventType expected, ReceivedEventType received)
  : std::invalid_argument(format("Expected event: {}, received: {}", expected.value, received.value))
{}
