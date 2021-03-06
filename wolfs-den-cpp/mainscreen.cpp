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

  border(*_skls, "Skills");
  border(*_info, "Info");

  drawMap();
  drawHUD();
  drawMsgs();

  auto c = cam(_world->getPlayer());

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

std::unique_ptr<Command> MainScreen::handleKeys(const TCOD_key_t& key,
                                                bool shift) {
  Command* pCmd;
  switch (key.vk) {
  case TCODK_KP8:
  case TCODK_UP:
    pCmd = new MoveByCommand(0, -1);
    break;
  case TCODK_KP9:
    pCmd = new MoveByCommand(1, -1);
    break;
  case TCODK_KP2:
  case TCODK_DOWN:
    pCmd = new MoveByCommand(0, 1);
    break;
  case TCODK_KP3:
    pCmd = new MoveByCommand(1, 1);
    break;
  case TCODK_KP4:
  case TCODK_LEFT:
    pCmd = new MoveByCommand(-1, 0);
    break;
  case TCODK_KP1:
    pCmd = new MoveByCommand(-1, 1);
    break;
  case TCODK_KP7:
    pCmd = new MoveByCommand(-1, -1);
    break;
  case TCODK_KP6:
  case TCODK_RIGHT:
    pCmd = new MoveByCommand(1, 0);
    break;
  default:
    std::cout << "Key " << key.text << " was pressed";
    if (shift)
      std::cout << " and shift was down." << std::endl;
    else
      std::cout << "." << std::endl;
    pCmd = new WaitCommand();
  }
  return std::unique_ptr<Command>(pCmd);
}

bool sortByLayer(const Entity& fst, const Entity& snd) {
  return fst.getLayer() < snd.getLayer();
}

void MainScreen::drawMap() {
  if (_world->getCurMap().dirty) {
    TCODColor fg, bg, wallBG, floorBG;
    wallBG = _world->getCurMap().wallBG;
    floorBG = _world->getCurMap().floorBG;
    _map->clear();
    int w = _world->getCurMap().getWidth();
    int h = _world->getCurMap().getHeight();
    for (int x = 0; x < w; x++) {
      for (int y = 0; y < h; y++) {
        Tile t = _world->getCurMap().getTile(x, y);
        if (t.glyph != 0) {
          fg = (t.color ? *t.color : TCODColor::white);
          bg = (t.walk ? floorBG : wallBG);
          _map->putCharEx(x, y, t.glyph, fg, bg);
        }
      }
    }
    auto things = _world->curThings();
    std::sort(things.begin(), things.end(), sortByLayer);
    for (auto& thing : things) {
      _map->putCharEx(thing.pos().x, thing.pos().y, thing.glyph, thing.color,
                      floorBG);
    }
    _world->getCurMap().dirty = false;
  }
}

void MainScreen::drawHUD() {
  if (_world->hudDirty) {
    _stats->clear();
    border(*_stats, "Stats");
    auto c = cam(_world->getPlayer());
    Pos playerPos = _world->getPlayer().pos();
    _stats->printf(1, 1, TCOD_BKGND_DEFAULT, TCOD_LEFT, "Player at (%d, %d)",
                   playerPos.x, playerPos.y);
    _stats->printf(1, 2, TCOD_BKGND_DEFAULT, TCOD_LEFT, "Cam at (%d, %d)", c.x,
                   c.y);
    _world->hudDirty = false;
  }
}

void MainScreen::drawMsgs() {
  if (_world->msgDirty) {
    _msgs->clear();
    border(*_msgs, "Messages");
    int counter = 1;
    int w = _msgs->getWidth() - 2;
    for (int i = 0; i < _world->getMessages().size(); i++) {
      if (counter + _world->getMessages()[i].getHeight(*_msgs, counter, w) < 8)
        counter += _world->getMessages()[i].print(*_msgs, counter, w);
      else
        break;
    }
    _world->msgDirty = false;
  }
}

Pos MainScreen::cam(ILocatable& obj) {
  Pos pos = obj.pos();
  int mw = _world->getCurMap().getWidth();
  int mh = _world->getCurMap().getHeight();
  int left = clamp(pos.x - MAP_W / 2, 0, std::max(0, mw - MAP_W));
  int top = clamp(pos.y - MAP_H / 2, 0, std::max(0, mh - MAP_H));
  return Pos{left, top};
}