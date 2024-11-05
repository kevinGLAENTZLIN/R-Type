/*                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
** EPITECH PROJECT, 2024                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
** R-Type                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
** File description:                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
** Command_invoker                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
*/

#include "Command_invoker.hh"

Rtype::Command::Command_invoker::Command_invoker(std::string invoker_type):
    _invokerType(invoker_type), _commandQueue()
{
}

Rtype::Command::Command_invoker::~Command_invoker()
{
}

// void Rtype::Command::Command_invoker::executeCommand()                                                                                                                                                                                                                                                                                                                                                                                                                                  
// {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
//     while (!_commandQueue.empty()) {                                                                                                                                                                                                                                                                                                                                                                                                                                                    
//         if (_invokerType == "Server") {                                                                                                                                                                                                                                                                                                                                                                                                                                                 
//             _commandQueue.front()->execute_server_side();                                                                                                                                                                                                                                                                                                                                                                                                                               
//             _commandQueue.pop();                                                                                                                                                                                                                                                                                                                                                                                                                                                        
//         } else if (_invokerType == "Client") {                                                                                                                                                                                                                                                                                                                                                                                                                                          
//             _commandQueue.front()->execute_client_side();                                                                                                                                                                                                                                                                                                                                                                                                                               
//             _commandQueue.pop();                                                                                                                                                                                                                                                                                                                                                                                                                                                        
//         } else                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
//             std::cerr << "Wrong invoker type set. No commands executed." << std::endl;                                                                                                                                                                                                                                                                                                                                                                                                  
//     }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   

// }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       

// void Rtype::Command::Command_invoker::addCommand(std::unique_ptr<Rtype::Command::ACommand> cmd)                                                                                                                                                                                                                                                                                                                                                                                         
// {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
//     cmd->setOrigins(_invokerType);                                                                                                                                                                                                                                                                                                                                                                                                                                                      
//     _commandQueue.push(std::move(cmd));                                                                                                                                                                                                                                                                                                                                                                                                                                                 
// }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       

void Rtype::Command::Command_invoker::executeCommand()
{
    std::lock_guard<std::mutex> lock(_queueMutex);  // Lock for the duration of command execution                                                                                                                                                                                                                                                                                                                                                                                          

    while (!_commandQueue.empty()) {
        auto &command = _commandQueue.front();
        if (!command) {
            std::cerr << "Error: Null command in queue." << std::endl;
            _commandQueue.pop();
            continue;
        }

        if (_invokerType == "Server") {
            command->execute_server_side();
        } else if (_invokerType == "Client") {
            command->execute_client_side();
        } else {
            std::cerr << "Wrong invoker type set. No commands executed." << std::endl;
        }

        _commandQueue.pop();
    }
}

void Rtype::Command::Command_invoker::addCommand(std::unique_ptr<Rtype::Command::ACommand> cmd)
{
    std::lock_guard<std::mutex> lock(_queueMutex);  // Lock for queue modification                                                                                                                                                                                                                                                                                                                                                                                                         
    if (!cmd) {
        std::cerr << "Error: Null command cannot be added." << std::endl;
        return;
    }
    cmd->setOrigins(_invokerType);
    _commandQueue.push(std::move(cmd));
}
