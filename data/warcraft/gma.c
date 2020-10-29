// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("走了[2;37;0m[2;37;0m", ({"gmalong"}));        
        set("gender", "男性");                
        set("long", "不起床[2;37;0m
它是令改的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "gma");
        set("owner_name", "令改");
        set_temp("owner", "gma");
        set_temp("owner_name", "令改");
        ::setup();
}
