// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m侠游[2;37;0m[2;37;0m", ({"matzpet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是游侠的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "matz");
        set("owner_name", "游侠");
        set_temp("owner", "matz");
        set_temp("owner_name", "游侠");
        ::setup();
}
