// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m门堪九雀[2;37;0m[2;37;0m", ({"won"}));        
        set("gender", "男性");                
        set("long", "门堪九雀!!1[2;37;0m
它是夜依伍的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "wonn");
        set("owner_name", "夜依伍");
        set_temp("owner", "wonn");
        set_temp("owner_name", "夜依伍");
        ::setup();
}
