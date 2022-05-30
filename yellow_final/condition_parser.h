#pragma once

#include "node.h"

#include <memory>
#include <iostream>

class Node;

std::shared_ptr<Node> ParseCondition(std::istream& is);

void TestParseCondition();