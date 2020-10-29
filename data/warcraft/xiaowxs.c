// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m玄武[2;37;0m[2;37;0m", ({"xuanw"}));        
        set("gender", "男性");                
        set("long", "玄武[2;37;0m
它是风花雪月的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "xiaowxs");
        set("owner_name", "风花雪月");
        set_temp("owner", "xiaowxs");
        set_temp("owner_name", "风花雪月");
        ::setup();
}
