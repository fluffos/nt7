// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("考拉[2;37;0m[2;37;0m", ({"myfy"}));        
        set("gender", "女性");                
        set("long", "考拉[2;37;0m
它是菜比五的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "fye");
        set("owner_name", "菜比五");
        set_temp("owner", "fye");
        set_temp("owner_name", "菜比五");
        ::setup();
}
