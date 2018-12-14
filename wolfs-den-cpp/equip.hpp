#pragma once

class Equipment : public Item {
public:
  Equipment(const std::shared_ptr<World>& world, const EquipTemplate& eqTemp,
            const Material* mat = nullptr);
  Equipment() = delete;
  bool use(Creature& user, const Creature* target = nullptr) override;
  int getAtp() const { return _atp; }
  int getDfp() const { return _dfp; }
  int getDmg() const { return _dmg; }
  int getTou() const { return _tou; }
  int getRes() const { return _res; }
  int getWil() const { return _wil; }
  int getPwr() const { return _pwr; }
  int getVision() const { return _vision; }
  void debugPrint();

private:
  void applyMaterial(const MatStatSet& set);
  EquipSlot _slot;
  int _atp, _dfp, _dmg, _tou, _res, _wil, _pwr, _vision, _hardness;
};
