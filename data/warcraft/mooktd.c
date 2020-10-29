// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("神兽玄武[2;37;0m[2;37;0m", ({"xuanwu"}));        
        set("gender", "男性");                
        set("long", "一只神兽玄武[2;37;0m
它是清三的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "mooktd");
        set("owner_name", "清三");
        set_temp("owner", "mooktd");
        set_temp("owner_name", "清三");
        ::setup();
}
