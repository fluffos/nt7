// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[31m龙兽[2;37;0m[2;37;0m", ({"huo"}));        
        set("gender", "男性");                
        set("long", "远古代时的魔兽[2;37;0m
它是地狱小鬼的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "zskaaa");
        set("owner_name", "地狱小鬼");
        set_temp("owner", "zskaaa");
        set_temp("owner_name", "地狱小鬼");
        ::setup();
}
