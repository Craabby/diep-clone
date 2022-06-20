#include <EntityComponentSystem/Component/Camera.hh>

#include <Coder/Reader.hh>
#include <Coder/Writer.hh>
#include <EntityComponentSystem/Entity.hh>
#include <Simulation.hh>

namespace shared::ecs::component
{
    Camera::Camera(Entity *entity)
        : entity(entity),
          player(-1)
    {
    }

    int32_t Camera::Player()
    {
        return player;
    }

    void Camera::Player(int32_t player)
    {
        this->player = player;
    }

    void Camera::WriteBinary(coder::Writer &writer)
    {
        writer.Vi(player);
    }

    void Camera::FromBinary(coder::Reader &reader)
    {
        player = reader.Vi();
    }
}
