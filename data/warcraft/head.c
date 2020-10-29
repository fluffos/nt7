// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m头魔[2;37;0m[2;37;0m", ({"headhead"}));        
        set("gender", "男性");                
        set("long", "$HIR$头魔[2;37;0m
它是魔头的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "head");
        set("owner_name", "魔头");
        set_temp("owner", "head");
        set_temp("owner_name", "魔头");
        ::setup();
}
