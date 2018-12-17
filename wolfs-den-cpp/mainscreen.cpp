#include "main.hpp"

MainScreen::MainScreen(std::shared_ptr<World> world)
  : Screen("main", world),
    _map(std::unique_ptr<TCODConsole>(new TCODConsole(MAP_MAX_W, MAP_MAX_H))),
    _msgs(std::unique_ptr<TCODConsole>(new TCODConsole(MSG_W, MSG_H))),
    _skls(std::unique_ptr<TCODConsole>(new TCODConsole(SKL_W, SKL_H))),
    _info(std::unique_ptr<TCODConsole>(new TCODConsole(INFO_W, INFO_H))),
    _stats(std::unique_ptr<TCODConsole>(new TCODConsole(STAT_W, STAT_H))),
    _gameStarted(false) {}

void MainScreen::render() {
  border(*_msgs, "Messages");
  border(*_skls, "Skills");
  border(*_info, "Info");
  border(*_stats, "Stats");

  drawMap();
  drawHUD();

  auto c = cam(_world->player);

  TCODConsole::blit(_map.get(), c.x, c.y, MAP_W, MAP_H, TCODConsole::root, 0,
                    0);
  TCODConsole::blit(_msgs.get(), 0, 0, _msgs->getWidth(), _msgs->getHeight(),
                    TCODConsole::root, MSG_X, MSG_Y);
  TCODConsole::blit(_info.get(), 0, 0, _info->getWidth(), _info->getHeight(),
                    TCODConsole::root, INFO_X, INFO_Y);
  TCODConsole::blit(_skls.get(), 0, 0, _skls->getWidth(), _skls->getHeight(),
                    TCODConsole::root, SKL_X, SKL_Y);
  TCODConsole::blit(_stats.get(), 0, 0, _stats->getWidth(), _stats->getHeight(),
                    TCODConsole::root, STAT_X, STAT_Y);
}

void MainScreen::handleKeys(const TCOD_key_t& key, bool shift) {
  int xmax = _world->getCurMap().getWidth() - 1;
  int ymax = _world->getCurMap().getHeight() - 1;
  switch (key.vk) { 
  case TCODK_UP:
    _world->player.y = std::max(0, _world->player.y - 1);
    _world->getCurMap().dirty = true;
    break;
  case TCODK_DOWN:
    _world->player.y = std::min(ymax, _world->player.y + 1);
    _world->getCurMap().dirty = true;
    break;
  case TCODK_LEFT:
    _world->player.x = std::max(0, _world->player.x - 1);
    _world->getCurMap().dirty = true;
    break;
  case TCODK_RIGHT:
    _world->player.x = std::min(xmax, _world->player.x + 1);
    _world->getCurMap().dirty = true;
    break;
  default:
    std::cout << "Key " << key.text << " was pressed";
    if (shift)
      std::cout << " and shift was down." << std::endl;
    else
      std::cout << "." << std::endl;
    break;
  }
}

bool sortByLayer(const Entity& fst, const Entity& snd) {
  return fst.getLayer() < snd.getLayer();
}

void MainScreen::drawMap() {
  _map->clear();
  int w = _world->getCurMap().getWidth();
  int h = _world->getCurMap().getHeight();
  if (_world->getCurMap().dirty) {
    for (int x = 0; x < w; x++) {
      for (int y = 0; y < h; y++) {
        Tile t = _world->getCurMap().getTile(x, y);
        if (t.glyph != 0) {
          TCODColor color = (t.color == nullptr) ? TCODColor::white : *t.color;
          _map->putCharEx(x, y, t.glyph, color, TCODColor::black);
        }
      }
    }
    auto things = _world->curThings();
    std::sort(things.begin(), things.end(), sortByLayer);
    for (auto& thing : things) {
      _map->putCharEx(thing.pos().x, thing.pos().y, thing.glyph, thing.color,
                      TCODColor::black);
    }
    _map->putCharEx(_world->player.x, _world->player.y, 'X', TCODColor::yellow,
                    TCODColor::black);
    _world->getCurMap().dirty = false;
  }
}

void MainScreen::drawHUD() {
  _stats->clear();
  auto c = cam(_world->player);
  _stats->printf(1, 0, TCOD_BKGND_DEFAULT, TCOD_LEFT, "Player at (%d, %d)", _world->player.x, _world->player.y);
  _stats->printf(1, 1, TCOD_BKGND_DEFAULT, TCOD_LEFT, "Cam at (%d, %d)", c.x, c.y);
}

Pos MainScreen::cam(ILocatable& obj) {
  Pos pos = obj.pos();
  int mw = _world->getCurMap().getWidth();
  int mh = _world->getCurMap().getHeight();
  int left = clamp(pos.x - MAP_W/2, 0, std::max(0, mw - MAP_W));
  int top = clamp(pos.y - MAP_H/2, 0, std::max(0, mh - MAP_H));
  return Pos{left, top};
}