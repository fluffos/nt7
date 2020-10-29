// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("城长[2;37;0m[2;37;0m", ({"wallgreat"}));        
        set("gender", "女性");                
        set("long", "城长[2;37;0m
它是长城的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "greatwall");
        set("owner_name", "长城");
        set_temp("owner", "greatwall");
        set_temp("owner_name", "长城");
        ::setup();
}
