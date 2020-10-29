// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[36m青玉龙[2;37;0m[2;37;0m", ({"gdragon"}));        
        set("gender", "男性");                
        set("long", "这是一条通体发出宝玉光芒的神龙。[2;37;0m
它是花千树的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "light");
        set("owner_name", "花千树");
        set_temp("owner", "light");
        set_temp("owner_name", "花千树");
        ::setup();
}
