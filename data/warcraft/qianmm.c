// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("老马[2;37;0m[2;37;0m", ({"laoma"}));        
        set("gender", "男性");                
        set("long", "老马[2;37;0m
它是何必再忆的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "qianmm");
        set("owner_name", "何必再忆");
        set_temp("owner", "qianmm");
        set_temp("owner_name", "何必再忆");
        ::setup();
}
