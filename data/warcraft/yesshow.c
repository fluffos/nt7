// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("奈法利安[2;37;0m[2;37;0m", ({"nba"}));        
        set("gender", "男性");                
        set("long", "奈法利安是神龙[2;37;0m
它是前天出狱的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "yesshow");
        set("owner_name", "前天出狱");
        set_temp("owner", "yesshow");
        set_temp("owner_name", "前天出狱");
        ::setup();
}
