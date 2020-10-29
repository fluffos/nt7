// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("西米露露[2;37;0m[2;37;0m", ({"omo"}));        
        set("gender", "女性");                
        set("long", "老大是经济晚来风事发后[2;37;0m
它是周仓贰的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "btg");
        set("owner_name", "周仓贰");
        set_temp("owner", "btg");
        set_temp("owner_name", "周仓贰");
        ::setup();
}
