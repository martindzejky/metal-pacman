#include "LevelLoader.hpp"

#include <fstream>
#include <random>

#include "Error.hpp"
#include "EntityFactory.hpp"


void LevelLoader::Load(std::string filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        THROW_ERROR(std::string("Cannot open level file ") + filename);
    }

    std::default_random_engine re;
    std::uniform_int_distribution<int> dist;

    std::string line;
    int x = 0;
    int z = 0;
    bool floor = true;
    while (std::getline(file, line)) {
        for (auto c : line) {
            switch (c) {
                case 'W':
                    EntityFactory::CreateWall(dist(re) % 3 + 1, x, 0, z);
                    floor = false;
                    break;

                case 'L':
                    EntityFactory::CreateLight(x, 2, z, 1, 1, .9f, 7);
                    break;

                case 'R':
                    EntityFactory::CreateLight(x, 2, z, 1, .1f, .1f, 4);
                    break;

                case 'G':
                    EntityFactory::CreateLight(x, 2, z, .1f, 1, .1f, 4);
                    break;

                case 'B':
                    EntityFactory::CreateLight(x, 2, z, .1f, .1f, 1, 4);
                    break;

                case 'P':
                    EntityFactory::CreatePlayer(x, 0, z);
                    break;

                case 'M':
                    EntityFactory::CreateMonster(x, 0, z);
                    break;

                case 'S':
                    EntityFactory::CreateSpikes(x, 0, z);
                    floor = false;
                    break;

                case ',':
                    if (floor) {
                        EntityFactory::CreateFloor(x, 0, z);
                    }
                    ++x;
                    floor = true;
                    break;

                default:
                    break;
            }
        }

        x = 0;
        ++z;
        floor = true;
    }
}
