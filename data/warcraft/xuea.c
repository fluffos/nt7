// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[35m绝[1;36m灭[36m小[1;31m师[33m太[2;37;0m[2;37;0m", ({"shen"}));        
        set("gender", "男性");                
        set("long", "四项基本原则[2;37;0m
它是一锤定音的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "xuea");
        set("owner_name", "一锤定音");
        set_temp("owner", "xuea");
        set_temp("owner_name", "一锤定音");
        ::setup();
}
