#include "gmock/gmock.h"

#include "../../src/TerminalListener.h"

class MockTerminalListener : public TerminalListener {
public:
    MOCK_METHOD1(handle_input, void(const std::string&));
};
