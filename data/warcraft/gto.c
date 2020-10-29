// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("流星雨[2;37;0m[2;37;0m", ({"tsk"}));        
        set("gender", "男性");                
        set("long", "许个愿，或许有天它会实现...。[2;37;0m
它是麻辣教师的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "gto");
        set("owner_name", "麻辣教师");
        set_temp("owner", "gto");
        set_temp("owner_name", "麻辣教师");
        ::setup();
}
