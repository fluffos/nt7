// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小飞[2;37;0m[2;37;0m", ({"dick"}));        
        set("gender", "男性");                
        set("long", "超帅的！[2;37;0m
它是姬太昊的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "zephyrzh");
        set("owner_name", "姬太昊");
        set_temp("owner", "zephyrzh");
        set_temp("owner_name", "姬太昊");
        ::setup();
}
