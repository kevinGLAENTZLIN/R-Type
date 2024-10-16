/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Command_invoker
*/

#include "Command_invoker.hh"

Rtype::Command::Command_invoker::Command_invoker(std::string invoker_type):
    _invokerType(invoker_type), _commandStack()
{
}

Rtype::Command::Command_invoker::~Command_invoker()
{
}

void Rtype::Command::Command_invoker::executeCommand()
{
    while (!_commandStack.empty()) {
        if (_invokerType == "Server") {
            _commandStack.top()->execute_server_side();
            _commandStack.pop();
        } else if (_invokerType == "Client") {
            _commandStack.top()->execute_client_side();
            _commandStack.pop();
        } else
            std::cerr << "Wrong invoker type set. No commands executed." << std::endl;
    }
    
}

void Rtype::Command::Command_invoker::addCommand(std::shared_ptr<ACommand> cmd)
{
    cmd->setOrigins(_invokerType);
    _commandStack.push(cmd);
}
