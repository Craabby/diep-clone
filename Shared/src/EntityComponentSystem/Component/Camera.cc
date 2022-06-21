#include <EntityComponentSystem/Component/Camera.hh>

#include <algorithm>

#include <Coder/Reader.hh>
#include <Coder/Writer.hh>
#include <EntityComponentSystem/Component/Physics.hh>
#include <EntityComponentSystem/Entity.hh>
#include <Simulation.hh>

namespace shared::ecs::component
{
    Camera::Camera(Entity *entity)
        : entity(entity),
          playerId(-1),
          inputs({{0, 0}, false, false, true, true})
    {
    }

    void Camera::Tick()
    {
        if (PlayerId() == -1)
            return;
        physics::Vector force(0, 0);
        if (inputs.up) force.Y(force.Y() + 1);
        if (inputs.left) force.X(force.X() - 1);
        if (inputs.down) force.Y(force.Y() - 1);
        if (inputs.right) force.X(force.X() + 1);

        force.Distance(1);

        std::vector<Entity *> *entities = &entity->simulation->entities;
        Entity *player = *std::find(entities->begin(), entities->end(), entity);
        player->Get<Physics>().velocity += force;
    }

    int32_t Camera::PlayerId()
    {
        return playerId;
    }

    void Camera::PlayerId(int32_t playerId)
    {
        this->playerId = playerId;
    }

    void Camera::WriteBinary(coder::Writer &writer)
    {
        writer.Vi(playerId);
    }

    void Camera::FromBinary(coder::Reader &reader)
    {
        playerId = reader.Vi();
    }
}
