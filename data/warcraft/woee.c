// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[35m门堪五雀[2;37;0m[2;37;0m", ({"wee"}));        
        set("gender", "男性");                
        set("long", "门堪五雀!!![2;37;0m
它是夜伍的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "woee");
        set("owner_name", "夜伍");
        set_temp("owner", "woee");
        set_temp("owner_name", "夜伍");
        ::setup();
}
