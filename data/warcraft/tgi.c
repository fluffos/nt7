// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("陆地乌龟[2;37;0m[2;37;0m", ({"tgid"}));        
        set("gender", "男性");                
        set("long", "陆地乌龟1号[2;37;0m
它是硫磺二代的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "tgi");
        set("owner_name", "硫磺二代");
        set_temp("owner", "tgi");
        set_temp("owner_name", "硫磺二代");
        ::setup();
}
