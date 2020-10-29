// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("神兽玄武[2;37;0m[2;37;0m", ({"xuanwu"}));        
        set("gender", "男性");                
        set("long", "一只神兽玄武。[2;37;0m
它是清水的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "mooktx");
        set("owner_name", "清水");
        set_temp("owner", "mooktx");
        set_temp("owner_name", "清水");
        ::setup();
}
