// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m腰魔[2;37;0m[2;37;0m", ({"moyao"}));        
        set("gender", "男性");                
        set("long", "$HIR$腰魔[2;37;0m
它是魔腰的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "waist");
        set("owner_name", "魔腰");
        set_temp("owner", "waist");
        set_temp("owner_name", "魔腰");
        ::setup();
}
