// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("神兽玄武[2;37;0m[2;37;0m", ({"xuanwu"}));        
        set("gender", "男性");                
        set("long", "hi[2;37;0m
它是清二的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "mooktc");
        set("owner_name", "清二");
        set_temp("owner", "mooktc");
        set_temp("owner_name", "清二");
        ::setup();
}
