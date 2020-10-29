// self.h

#ifndef __SELF_LOAD_WEAPON__
#define __SELF_LOAD_WEAPON__

#define SELF_DIR        "/inherit/self/"

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

#define SELF_A_HEAD     SELF_DIR"armor/head"
#define SELF_A_ARMOR    SELF_DIR"armor/armor"
#define SELF_A_CLOTH    SELF_DIR"armor/cloth"
#define SELF_A_HANDS    SELF_DIR"armor/hands"
#define SELF_A_BOOTS    SELF_DIR"armor/boots"
#define SELF_A_WAIST    SELF_DIR"armor/waist"
#define SELF_A_WRISTS   SELF_DIR"armor/wrists"

#endif

void init_armor(int armor) { set("armor_prop/armor", armor); }
void init_damage(int damage) { set("weapon_prop/damage", damage); }

void killer_reward(object me, object victim)
{
        ITEM_D->killer_reward(me, victim, this_object());
}

string long() { return short() + query("long") + (query("makeinfo")?query("makeinfo"):""); }