// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("泪水[2;37;0m[2;37;0m", ({"kou"}));        
        set("gender", "女性");                
        set("long", "一滴晶莹的泪珠从脸颊滑□过[2;37;0m
它是孤星泪的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "xinglei");
        set("owner_name", "孤星泪");
        set_temp("owner", "xinglei");
        set_temp("owner_name", "孤星泪");
        ::setup();
}
