// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白虎[2;37;0m[2;37;0m", ({"olk"}));        
        set("gender", "男性");                
        set("long", "白虎[2;37;0m
它是独白打铁的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "klkgm");
        set("owner_name", "独白打铁");
        set_temp("owner", "klkgm");
        set_temp("owner_name", "独白打铁");
        ::setup();
}
