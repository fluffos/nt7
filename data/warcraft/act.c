// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白马[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "男性");                
        set("long", "白马[2;37;0m
它是动作游戏的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "act");
        set("owner_name", "动作游戏");
        set_temp("owner", "act");
        set_temp("owner_name", "动作游戏");
        ::setup();
}
