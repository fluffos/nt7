// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m九头鸟[2;37;0m[2;37;0m", ({"birdjiu"}));        
        set("gender", "男性");                
        set("long", "九头鸟[2;37;0m
它是九重天的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "dangjiu");
        set("owner_name", "九重天");
        set_temp("owner", "dangjiu");
        set_temp("owner_name", "九重天");
        ::setup();
}
