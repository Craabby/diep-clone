#include <EntityComponentSystem/Component/Game.hh>

#include <EntityComponentSystem/Entity.hh>

#include <Coder/Reader.hh>
#include <Coder/Writer.hh>

namespace shared::ecs::component
{
    Game::Game(Entity *entity)
        : entity(entity)
    {
    }

    void Game::WriteBinary(coder::Writer &writer)
    {
        writer.Vu(Width());
        writer.Vu(Height());
    }

    void Game::FromBinary(coder::Reader &reader)
    {
        m_Width = reader.Vu();
        m_Height = reader.Vu();
    }

    uint32_t Game::Width()
    {
        return m_Width;
    }

    uint32_t Game::Height()
    {
        return m_Height;
    }

    void Game::Width(uint32_t value)
    {
        if (Width() == value) 
            return;
        updated = true;

        m_Width = value;
    }

    void Game::Height(uint32_t value)
    {
        if (Height() == value) 
            return;
        updated = true;

        m_Height = value;
    }

}
