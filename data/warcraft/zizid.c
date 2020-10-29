// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("对依依[2;37;0m[2;37;0m", ({"ziziddd"}));        
        set("gender", "女性");                
        set("long", "自由的飞翔[2;37;0m
它是姿对的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "zizid");
        set("owner_name", "姿对");
        set_temp("owner", "zizid");
        set_temp("owner_name", "姿对");
        ::setup();
}
