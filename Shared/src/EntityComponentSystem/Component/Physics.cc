#include <EntityComponentSystem/Component/Physics.hh>

#include <Coder/Reader.hh>
#include <Coder/Writer.hh>
#include <EntityComponentSystem/Entity.hh>

namespace shared::ecs::component
{
    Physics::PhysicsVector::PhysicsVector(Physics *entity, float x, float y)
        : physicsComponent(entity),
          physics::Vector(x, y)
    {
    }

    float Physics::PhysicsVector::X()
    {
        return m_X;
    }

    float Physics::PhysicsVector::Y()
    {
        return m_Y;
    }

    void Physics::PhysicsVector::X(float x)
    {
        physicsComponent->updated = true;
        m_X = x;
    }

    void Physics::PhysicsVector::Y(float y)
    {
        physicsComponent->updated = true;
        m_Y = y;
    }

    Physics::Physics(Entity *entity)
        : entity(entity)
    {
    }

    void Physics::WriteBinary(coder::Writer &writer)
    {
        writer.Vu(position.X());
        writer.Vu(position.Y());
    }

    void Physics::FromBinary(coder::Reader &reader)
    {
        position.X(reader.Vu());
        position.Y(reader.Vu());
    }
}
