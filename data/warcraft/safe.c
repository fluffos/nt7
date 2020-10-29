// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("穿云[2;37;0m[2;37;0m", ({"tobe"}));        
        set("gender", "男性");                
        set("long", "穿云[2;37;0m
它是云心的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "safe");
        set("owner_name", "云心");
        set_temp("owner", "safe");
        set_temp("owner_name", "云心");
        ::setup();
}
