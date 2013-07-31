#include "network/network_world.hpp"

#include "network/protocol_manager.hpp"
#include "network/protocols/synchronization_protocol.hpp"
#include "network/protocols/controller_events_protocol.hpp"
#include "modes/world.hpp"

#include "karts/controller/controller.hpp"

NetworkWorld::NetworkWorld()
{
    m_running = false;
}

NetworkWorld::~NetworkWorld()
{
}

void NetworkWorld::update(float dt)
{
    SynchronizationProtocol* protocol = static_cast<SynchronizationProtocol*>(
            ProtocolManager::getInstance()->getProtocol(PROTOCOL_SYNCHRONIZATION));
    if (protocol) // if this protocol exists, that's that we play online
    {
        Log::debug("NetworkWorld", "Coutdown value is %f", protocol->getCountdown());
        if (protocol->getCountdown() > 0.0)
        {
            return;
        }
    }
    World::getWorld()->updateWorld(dt);
}

void NetworkWorld::controllerAction(Controller* controller, PlayerAction action, int value)
{
    ControllerEventsProtocol* protocol = static_cast<ControllerEventsProtocol*>(
        ProtocolManager::getInstance()->getProtocol(PROTOCOL_CONTROLLER_EVENTS));
    if (protocol)
        protocol->controllerAction(controller, action, value);
}
