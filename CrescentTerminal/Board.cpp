#include <iostream>

#include "Board.h"
#include "Global.h"
#include "Building.h"

Board::Board(int width, int height, BoardType type, TileType defaultTile)
    : m_width(width)
    , m_height(height)
    , m_type(type)
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

bool Board::isTileBuildEligible(int x, int y) const
{
    return m_tiles[x][y].isBuildEligible();
}

void Board::highlightTiles(sf::Vector2i footprint, sf::Vector2f mousePos, bool canBuild)
{
    // Reset all tiles
    for (int x = 0; x < m_width; ++x) {
        for (int y = 0; y < m_height; ++y) {
			m_tiles[x][y].setHighlight(sf::Color::Transparent);
		}
	}

    // Highlight new tiles
	sf::Vector2i tileCoords = pixelsToTileCoords(mousePos);
    for (int x = 0; x < footprint.x; ++x) {
        for (int y = 0; y < footprint.y; ++y) {
            if (isTileInBounds(tileCoords.x + x, tileCoords.y + y)) {
                if (canBuild) {
                    m_tiles[tileCoords.x + x][tileCoords.y + y].setHighlight(sf::Color::Green);
                }
                else {
                    m_tiles[tileCoords.x + x][tileCoords.y + y].setHighlight(sf::Color::Red);
                }
            }
		}
	}
}

void Board::clearHighlights()
{
    for (int x = 0; x < m_width; ++x) {
        for (int y = 0; y < m_height; ++y) {
			m_tiles[x][y].setHighlight(sf::Color::Transparent);
		}
	}
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

void Board::buildBuilding(BuildingType type, sf::Vector2f position) {
	m_buildings.push_back(std::make_shared<Building>(type, true));
    // Update tiles to reflect new building
    sf::Vector2i tileCoords = pixelsToTileCoords(position);
    m_buildings.back()->setBoardPosition(tileCoords);
    for (int x = 0; x < m_buildings.back()->getFootprintSize().x; ++x) {
        for (int y = 0; y < m_buildings.back()->getFootprintSize().y; ++y) {
			m_tiles[tileCoords.x + x][tileCoords.y + y].setType(m_buildings.back()->getTileType(sf::Vector2i(x, y)));
		}
	}
}

bool Board::canBuildHere(sf::Vector2i footprint, sf::Vector2f mousepos) const {
    sf::Vector2i tileCoords = pixelsToTileCoords(mousepos);
    for (int x = 0; x < footprint.x; ++x) {
        for (int y = 0; y < footprint.y; ++y) {
            if (!isTileInBounds(tileCoords.x + x, tileCoords.y + y)) {
				return false;
			}
            if (isTileObstacle(tileCoords.x + x, tileCoords.y + y)) {
				return false;
			}
            if (!isTileBuildEligible(tileCoords.x + x, tileCoords.y + y)) {
				return false;
            }
		}
	}
	return true;
}

std::shared_ptr<Board> Board::getDoorDestination(sf::Vector2i position) const
{
    for (auto& building : m_buildings) {
        if (building->hasDoorAt(position)) {
			return building->getInterior();
	    }
	}
	return nullptr;
}

sf::Vector2f Board::getBoardSize() const
{
	return sf::Vector2f(float(m_width * TILE_SIZE), float(m_height * TILE_SIZE));
}

sf::Vector2i Board::pixelsToTileCoords(sf::Vector2f pixelPosition)
{
    // Because e.g. int(-5 / 32) = 0, but we want it to resolve to -1
    if (pixelPosition.x < 0) {
		pixelPosition.x -= TILE_SIZE;
	}
    if (pixelPosition.y < 0) {
        pixelPosition.y -= TILE_SIZE;
    }

    sf::Vector2i tileCoords;
    tileCoords.x = int(pixelPosition.x / TILE_SIZE);
    tileCoords.y = int(pixelPosition.y / TILE_SIZE);

    return tileCoords;
}

sf::Vector2f Board::tileCoordsToPixels(sf::Vector2i tilePosition)
{
	return sf::Vector2f(float(tilePosition.x * TILE_SIZE), float(tilePosition.y * TILE_SIZE));
}

