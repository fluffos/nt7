// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"ddddd"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是啊迷的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "dddz");
        set("owner_name", "啊迷");
        set_temp("owner", "dddz");
        set_temp("owner_name", "啊迷");
        ::setup();
}
