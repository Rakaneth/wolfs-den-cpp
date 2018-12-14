#include "main.hpp"



Equipment::Equipment(const std::shared_ptr<World>& world,
                     const EquipTemplate& eqTemp, const Material* mat)
  : Item(world, IT_EQUIP),
    _atp(eqTemp.atp),
    _dfp(eqTemp.dfp),
    _dmg(eqTemp.dmg),
    _res(eqTemp.res),
    _tou(eqTemp.tou),
    _wil(eqTemp.wil),
    _pwr(eqTemp.pwr),
    _vision(eqTemp.vision) {
  if (eqTemp.slot == "weapon")
    _slot = ES_WEAPON;
  else if (eqTemp.slot == "armor")
    _slot = ES_ARMOR;
  else if (eqTemp.slot == "trinket")
    _slot = ES_TRINKET;
  else {
    std::cout << "Bad slot for " << eqTemp.name << "; check data files."
              << std::endl;
    exit(1);
  }
  glyph = eqTemp.glyph;
  if (eqTemp.damageType == "slash")
    _damageType = DT_SLASH;
  else if (eqTemp.damageType == "pierce")
    _damageType = DT_PIERCE;
  else if (eqTemp.damageType == "blunt")
    _damageType = DT_BLUNT;
  else
    _damageType = DT_SLASH;

  if (eqTemp.equipType == "axe")
    _eqType = ET_AXE;
  else if (eqTemp.equipType == "sword")
    _eqType = ET_SWORD;
  else if (eqTemp.equipType == "staff")
    _eqType = ET_STAFF;
  else if (eqTemp.equipType == "hammer")
    _eqType = ET_HAMMER;
  else if (eqTemp.equipType == "rapier")
    _eqType = ET_RAPIER;
  else if (eqTemp.equipType == "armor")
    _eqType = ET_ARMOR;
  else
    _eqType = ET_NONE;

  if (eqTemp.material) {
    if (mat == nullptr) {
      std::cout << eqTemp.name << " must be made of a material." << std::endl;
      exit(1);
    } else {
      std::string lookFor("<material>");
      std::string matName(mat->name);
      std::string eqDesc(eqTemp.desc);

      desc = eqDesc.replace(eqDesc.find(lookFor), lookFor.size(), matName);
      name = matName + " " + eqTemp.name;
      if (eqTemp.equipType == "axe")
        applyMaterial(mat->axe);
      else if (eqTemp.equipType == "sword")
        applyMaterial(mat->sword);
      else if (eqTemp.equipType == "staff")
        applyMaterial(mat->staff);
      else if (eqTemp.equipType == "hammer")
        applyMaterial(mat->hammer);
      else if (eqTemp.equipType == "rapier")
        applyMaterial(mat->rapier);
      else if (eqTemp.equipType == "armor")
        applyMaterial(mat->armor);
      else {
        std::cout << "Invalid equipment type: " << eqTemp.equipType
                  << std::endl;
        exit(1);
      }
      color = mat->color;
      _hardness = mat->hardness;
    }
  } else {
    color = eqTemp.color;
    name = eqTemp.name;
    desc = eqTemp.desc;
    _hardness = 5;
  }
}

bool Equipment::use(Creature& user, const Creature* target) { return false; }

void Equipment::debugPrint() {
  std::cout << "---Equipment: " << name << "(" << _id << ")---" << std::endl;
  std::cout << "Desc: " << desc << std::endl;
  std::cout << "Stats:" << std::endl;
  std::cout << "Atp " << _atp;
  std::cout << " Dfp " << _dfp;
  std::cout << " Dmg " << _dmg;
  std::cout << " Tou " << _tou;
  std::cout << " Res " << _res;
  std::cout << " Wil " << _wil;
  std::cout << " Pwr " << _pwr;
  std::cout << " Vision " << _vision << std::endl;
}

void Equipment::applyMaterial(const MatStatSet& set) {
  _atp += set.atp;
  _dfp += set.dfp;
  _dmg += set.dmg;
  _tou += set.tou;
  _res += set.res;
  _wil += set.wil;
  _pwr += set.pwr;
  _vision += set.vision;
}
