// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[37m门堪罗雀[2;37;0m[2;37;0m", ({"wod"}));        
        set("gender", "女性");                
        set("long", "门堪罗雀!!![2;37;0m
它是夜乏的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "wodd");
        set("owner_name", "夜乏");
        set_temp("owner", "wodd");
        set_temp("owner_name", "夜乏");
        ::setup();
}
