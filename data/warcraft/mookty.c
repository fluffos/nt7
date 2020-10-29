// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("神兽玄武[2;37;0m[2;37;0m", ({"xuanwu"}));        
        set("gender", "男性");                
        set("long", "神兽玄武[2;37;0m
它是清山的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "mookty");
        set("owner_name", "清山");
        set_temp("owner", "mookty");
        set_temp("owner_name", "清山");
        ::setup();
}
