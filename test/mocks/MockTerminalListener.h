#include "gmock/gmock.h"

#include "Terminal/TerminalListener.h"

class MockTerminalListener : public TerminalListener {
public:
    MOCK_METHOD1(handle_input, void(const std::string&));
};
