// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("银麒麟[2;37;0m[2;37;0m", ({"ttt"}));        
        set("gender", "男性");                
        set("long", "银色的麒麟[2;37;0m
它是天子的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "tian");
        set("owner_name", "天子");
        set_temp("owner", "tian");
        set_temp("owner_name", "天子");
        ::setup();
}
