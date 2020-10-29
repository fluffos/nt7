// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"apppet"}));        
        set("gender", "女性");                
        set("long", "麒麟[2;37;0m
它是金光的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "app");
        set("owner_name", "金光");
        set_temp("owner", "app");
        set_temp("owner_name", "金光");
        ::setup();
}
