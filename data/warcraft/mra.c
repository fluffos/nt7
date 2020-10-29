// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("龙马[2;37;0m[2;37;0m", ({"mralong"}));        
        set("gender", "男性");                
        set("long", "骨地[2;37;0m
它是迅雷哥的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "mra");
        set("owner_name", "迅雷哥");
        set_temp("owner", "mra");
        set_temp("owner_name", "迅雷哥");
        ::setup();
}
