// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("皮冻[2;37;0m[2;37;0m", ({"axx"}));        
        set("gender", "男性");                
        set("long", "sada[2;37;0m
它是爆炸的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "plutonium");
        set("owner_name", "爆炸");
        set_temp("owner", "plutonium");
        set_temp("owner_name", "爆炸");
        ::setup();
}
