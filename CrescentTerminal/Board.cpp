#include "Board.h"
#include "Global.h"

Board::Board(int width, int height, TileType defaultTile)
    : m_width(width)
    , m_height(height)
    , m_tiles(width, std::vector<Tile>(height))
{
    for (int x = 0; x < m_width; ++x) {
        for (int y = 0; y < m_height; ++y) {
            m_tiles[x][y].setType(defaultTile);
        }
    }
}

Tile& Board::getTile(int x, int y)
{
	return m_tiles[x][y];
}

Tile& Board::getTile(sf::Vector2i tilePosition)
{
	return m_tiles[tilePosition.x][tilePosition.y];
}

bool Board::isTileObstacle(int x, int y) const
{
	return m_tiles[x][y].isObstacle();
}

bool Board::isTileInBounds(int x, int y) const
{
	return x >= 0 && x < m_width && y >= 0 && y < m_height;
}

bool Board::isTileOnScreen(int x, int y, sf::RenderWindow& window) const
{
    sf::Vector2f viewCenter = window.getView().getCenter();
    sf::Vector2f viewSize = window.getView().getSize();
    sf::Vector2f position = tileCoordsToPixels({ x, y });
    if (position.x < 0 ||
        position.x < viewCenter.x - viewSize.x / 2 - TILE_SIZE ||
        position.x > viewCenter.x + viewSize.x / 2 ||
        position.y < 0 ||
        position.y < viewCenter.y - viewSize.y / 2 - TILE_SIZE ||
        position.y > viewCenter.y + viewSize.y / 2)
    {
        return false;
    }
    return true;
}

void Board::drawBackground(sf::RenderWindow& window)
{
    for (int x = 0; x < m_width; ++x) {
        for (int y = 0; y < m_height; ++y) {
            if (isTileOnScreen(x, y, window)) {
                m_tiles[x][y].draw(window, { float(x * TILE_SIZE), float(y * TILE_SIZE) });
            }
        }
    }
}

sf::Vector2f Board::getBoardSize() const
{
	return sf::Vector2f(float(m_width * TILE_SIZE), float(m_height * TILE_SIZE));
}

sf::Vector2i Board::pixelsToTileCoords(sf::Vector2f pixelPosition)
{
	return sf::Vector2i(int(pixelPosition.x / TILE_SIZE), int(pixelPosition.y / TILE_SIZE));
}

sf::Vector2f Board::tileCoordsToPixels(sf::Vector2i tilePosition)
{
	return sf::Vector2f(float(tilePosition.x * TILE_SIZE), float(tilePosition.y * TILE_SIZE));
}

