// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("老马[2;37;0m[2;37;0m", ({"laoma"}));        
        set("gender", "男性");                
        set("long", "老马[2;37;0m
它是倾国倾城的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "fadpoo");
        set("owner_name", "倾国倾城");
        set_temp("owner", "fadpoo");
        set_temp("owner_name", "倾国倾城");
        ::setup();
}
