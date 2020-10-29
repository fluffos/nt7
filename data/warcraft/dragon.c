// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m九头黄金圣龙[2;37;0m[2;37;0m", ({"golden"}));        
        set("gender", "男性");                
        set("long", "九头黄金圣龙[2;37;0m
它是龙神的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "dragon");
        set("owner_name", "龙神");
        set_temp("owner", "dragon");
        set_temp("owner_name", "龙神");
        ::setup();
}
