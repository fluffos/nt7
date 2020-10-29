// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("潜水艇[2;37;0m[2;37;0m", ({"ioi"}));        
        set("gender", "男性");                
        set("long", "good[2;37;0m
它是独孤求拜的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "feier");
        set("owner_name", "独孤求拜");
        set_temp("owner", "feier");
        set_temp("owner_name", "独孤求拜");
        ::setup();
}
