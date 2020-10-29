// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("乌龟王八[2;37;0m[2;37;0m", ({"pdkinga"}));        
        set("gender", "男性");                
        set("long", "乌龟王八[2;37;0m
它是邋遢小王的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "pdking");
        set("owner_name", "邋遢小王");
        set_temp("owner", "pdking");
        set_temp("owner_name", "邋遢小王");
        ::setup();
}
