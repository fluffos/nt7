// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[30m屠龙刀[2;37;0m[2;37;0m", ({"tulong"}));        
        set("gender", "男性");                
        set("long", "$BLK$屠龙刀[2;37;0m
它是一指禅功的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "wuji");
        set("owner_name", "一指禅功");
        set_temp("owner", "wuji");
        set_temp("owner_name", "一指禅功");
        ::setup();
}
