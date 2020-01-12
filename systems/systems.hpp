#pragma once

#include <memory>
#include <vector>

class ISystem;

using Systems = std::vector<std::unique_ptr<ISystem>>;
