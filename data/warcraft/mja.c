// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[36m浅[1;31m斟[33m低[1;37m唱[2;37;0m[2;37;0m", ({"shenggui"}));        
        set("gender", "男性");                
        set("long", "天子[2;37;0m
它是明教弟子的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "mja");
        set("owner_name", "明教弟子");
        set_temp("owner", "mja");
        set_temp("owner_name", "明教弟子");
        ::setup();
}
