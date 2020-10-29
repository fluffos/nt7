// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"ddxsss"}));        
        set("gender", "女性");                
        set("long", "搜索[2;37;0m
它是破华的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "pohua");
        set("owner_name", "破华");
        set_temp("owner", "pohua");
        set_temp("owner_name", "破华");
        ::setup();
}
