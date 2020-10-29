// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("聂小倩[2;37;0m[2;37;0m", ({"zzyangxu"}));        
        set("gender", "男性");                
        set("long", "聂小倩[2;37;0m
它是杨旭的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "yangxuzz");
        set("owner_name", "杨旭");
        set_temp("owner", "yangxuzz");
        set_temp("owner_name", "杨旭");
        ::setup();
}
