// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("摩卡[2;37;0m[2;37;0m", ({"mooka"}));        
        set("gender", "男性");                
        set("long", "坐骑而已[2;37;0m
它是麦克的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "mac");
        set("owner_name", "麦克");
        set_temp("owner", "mac");
        set_temp("owner_name", "麦克");
        ::setup();
}
