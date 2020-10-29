// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("七色白云[2;37;0m[2;37;0m", ({"cyun"}));        
        set("gender", "男性");                
        set("long", "七仙女的白云。[2;37;0m
它是七仙女的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "lxr");
        set("owner_name", "七仙女");
        set_temp("owner", "lxr");
        set_temp("owner_name", "七仙女");
        ::setup();
}
