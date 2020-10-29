// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("碧水晶晶兽[2;37;0m[2;37;0m", ({"super"}));        
        set("gender", "男性");                
        set("long", "两只耳朵竖起来[2;37;0m
它是莫须有的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "upp");
        set("owner_name", "莫须有");
        set_temp("owner", "upp");
        set_temp("owner_name", "莫须有");
        ::setup();
}
