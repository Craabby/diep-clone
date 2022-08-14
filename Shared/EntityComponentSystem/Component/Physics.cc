#include <Shared/EntityComponentSystem/Component/Physics.hh>

#include <Shared/Coder/Reader.hh>
#include <Shared/Coder/Writer.hh>
#include <Shared/EntityComponentSystem/Component/Types.hh>

namespace shared::ecs::component
{
    Physics::Physics(uint32_t ownerId)
        : ownerId(ownerId),
          updated(true)
    {
    }

    void Physics::Tick()
    {
        xVelocity *= 0.9;
        yVelocity *= 0.9;
        // float rounding issues
        if (xPosition + xVelocity == xPosition)
            xVelocity = 0;
        if (yPosition + xVelocity == yPosition)
            yVelocity = 0;
        xPosition += xVelocity;
        yPosition += yVelocity;
    }

    DEFINE_COMPONENT_FIELD(float, Physics, xPosition)
    DEFINE_COMPONENT_FIELD(float, Physics, yPosition)
    DEFINE_COMPONENT_FIELD(float, Physics, xVelocity)
    DEFINE_COMPONENT_FIELD(float, Physics, yVelocity)
    DEFINE_COMPONENT_FIELD(float, Physics, size)

    void Physics::WriteBinary(Writer &writer)
    {
        writer.Float(xPosition);
        writer.Float(yPosition);
        writer.Float(xVelocity);
        writer.Float(yVelocity);
        writer.Float(size);
    }

    void Physics::ReadBinary(Reader &reader)
    {
        xPosition = reader.Float();
        yPosition = reader.Float();
        xVelocity = reader.Float();
        yVelocity = reader.Float();
        size = reader.Float();
    }
}
