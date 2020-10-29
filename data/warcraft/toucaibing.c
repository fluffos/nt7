// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"niu"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是菜农丙的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "toucaibing");
        set("owner_name", "菜农丙");
        set_temp("owner", "toucaibing");
        set_temp("owner_name", "菜农丙");
        ::setup();
}
