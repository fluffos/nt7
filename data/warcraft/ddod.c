// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("龙麒麟[2;37;0m[2;37;0m", ({"dragon_d"}));        
        set("gender", "男性");                
        set("long", "龙麒麟[2;37;0m
它是天偷的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "ddod");
        set("owner_name", "天偷");
        set_temp("owner", "ddod");
        set_temp("owner_name", "天偷");
        ::setup();
}
