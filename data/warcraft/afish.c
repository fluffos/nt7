// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("七彩祥云[2;37;0m[2;37;0m", ({"beer"}));        
        set("gender", "男性");                
        set("long", "七彩祥云[2;37;0m
它是白鹿的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "afish");
        set("owner_name", "白鹿");
        set_temp("owner", "afish");
        set_temp("owner_name", "白鹿");
        ::setup();
}
