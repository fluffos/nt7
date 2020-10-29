// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[33m小柜子[2;37;0m[2;37;0m", ({"guier"}));        
        set("gender", "男性");                
        set("long", "一只干瘪瘪的小乌龟[2;37;0m
它是月儿眉的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "yjpffox");
        set("owner_name", "月儿眉");
        set_temp("owner", "yjpffox");
        set_temp("owner_name", "月儿眉");
        ::setup();
}
