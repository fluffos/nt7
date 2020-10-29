// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("众生回避[2;37;0m[2;37;0m", ({"zqlowekk"}));        
        set("gender", "男性");                
        set("long", "众生回避[2;37;0m
它是夜魔出行的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "zqlowek");
        set("owner_name", "夜魔出行");
        set_temp("owner", "zqlowek");
        set_temp("owner_name", "夜魔出行");
        ::setup();
}
