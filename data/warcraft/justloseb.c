// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("乌龟[2;37;0m[2;37;0m", ({"wugui"}));        
        set("gender", "男性");                
        set("long", "乌龟[2;37;0m
它是丹师的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "justloseb");
        set("owner_name", "丹师");
        set_temp("owner", "justloseb");
        set_temp("owner_name", "丹师");
        ::setup();
}
