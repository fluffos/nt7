// self.h
// Find.

#ifndef __SELF_LOAD_WEAPON__
#define __SELF_LOAD_WEAPON__

#define SELF_DIR        "/obj/self/"

#define SELF_W_AXE        SELF_DIR"weapon/axe"
#define SELF_W_BLADE        SELF_DIR"weapon/blade"
#define SELF_W_DAGGER        SELF_DIR"weapon/dagger"
#define SELF_W_DHAMMER        SELF_DIR"weapon/dhammer"
#define SELF_W_HAMMER        SELF_DIR"weapon/hammer"
#define SELF_W_SPEAR        SELF_DIR"weapon/spear"
#define SELF_W_STICK        SELF_DIR"weapon/stick"
#define SELF_W_SWORD        SELF_DIR"weapon/sword"
#define SELF_W_WHIP        SELF_DIR"weapon/whip"
#define SELF_W_STAFF    SELF_DIR"weapon/staff"
#define SELF_W_FAN      SELF_DIR"weapon/fan"
#define SELF_W_BRUSH    SELF_DIR"weapon/brush"
#define SELF_W_HOOK     SELF_DIR"weapon/hook"
#define SELF_W_FORK     SELF_DIR"weapon/fork"
#define SELF_W_BOW      SELF_DIR"weapon/bow"


class weapon_args
{
        string fname;
        string name;
        string id;
        string desc;
        string wield_msg;
        string unwield_msg;
        string material;
        int damage;
        int mangle;
        int weapon_flag;
        string weapon_effect;
}
#endif
