// dagger.c

#include <weapon.h>

#ifdef AS_FEATURE
#include <dbase.h>
#else
inherit EQUIP;
#endif

int is_weapon() { return 1; }
varargs void init_ring(int damage, int flag)
{
        //if( clonep(this_object()) ) return;
        set("weapon_prop/damage", damage);
        set("flag", (int)flag | EDGED);
        set("skill_type", "unarmed");
        if( !query("actions") ) {
                set("actions", (: call_other,WEAPON_D, "query_action" :) );
                set("verbs", ({ "slash", "slice", "hack" }) );
        }
}
