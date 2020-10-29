// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("考拉[2;37;0m[2;37;0m", ({"myfya"}));        
        set("gender", "男性");                
        set("long", "考拉[2;37;0m
它是菜比一的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "fya");
        set("owner_name", "菜比一");
        set_temp("owner", "fya");
        set_temp("owner_name", "菜比一");
        ::setup();
}
