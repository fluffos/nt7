// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("菜麒麟[2;37;0m[2;37;0m", ({"cql"}));        
        set("gender", "男性");                
        set("long", "菜麒麟[2;37;0m
它是菜小邪的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "caiyao");
        set("owner_name", "菜小邪");
        set_temp("owner", "caiyao");
        set_temp("owner_name", "菜小邪");
        ::setup();
}
