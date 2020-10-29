// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("着骑[2;37;0m[2;37;0m", ({"along"}));        
        set("gender", "男性");                
        set("long", "一八[2;37;0m
它是小宪法的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "xiaoe");
        set("owner_name", "小宪法");
        set_temp("owner", "xiaoe");
        set_temp("owner_name", "小宪法");
        ::setup();
}
