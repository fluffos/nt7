// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("神兽玄武[2;37;0m[2;37;0m", ({"xuanwu"}));        
        set("gender", "男性");                
        set("long", "一只神兽玄武。[2;37;0m
它是清五的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "mooktf");
        set("owner_name", "清五");
        set_temp("owner", "mooktf");
        set_temp("owner_name", "清五");
        ::setup();
}
