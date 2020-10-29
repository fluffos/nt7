// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m圣火[2;37;0m[2;37;0m", ({"holy"}));        
        set("gender", "男性");                
        set("long", "好看的很[2;37;0m
它是泥巴的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "niba");
        set("owner_name", "泥巴");
        set_temp("owner", "niba");
        set_temp("owner_name", "泥巴");
        ::setup();
}
