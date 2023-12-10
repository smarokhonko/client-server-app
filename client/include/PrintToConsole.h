#include "IPrintMessage.h"

class PrintToConsole : public IPrintMessage
{
public:
    ~PrintToConsole(){}

    void print(const std::string&) override;
};