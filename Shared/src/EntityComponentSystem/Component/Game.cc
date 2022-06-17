#include <EntityComponentSystem/Component/Game.hh>

#include <Coder/Writer.hh>
#include <EntityComponentSystem/Entity.hh>

namespace shared::ecs::component
{
    Game::Game(Entity *entity)
        : entity(entity)
    {
    }

    void Game::WriteBinary(coder::Writer &writer)
    {
        writer.Vu(xAxisSize);
        writer.Vu(yAxisSize);
    }
}
