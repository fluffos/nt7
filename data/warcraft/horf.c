// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("玄武[2;37;0m[2;37;0m", ({"xuanwu"}));        
        set("gender", "男性");                
        set("long", "玄武[2;37;0m
它是左丘明的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "horf");
        set("owner_name", "左丘明");
        set_temp("owner", "horf");
        set_temp("owner_name", "左丘明");
        ::setup();
}
