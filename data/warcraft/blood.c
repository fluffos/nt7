// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;31m噬血狂[2;37;0m[2;37;0m", ({"blod"}));        
        set("gender", "男性");                
        set("long", "噬血狂来了，别跑啊，让我吸你的血[2;37;0m
它是血舞狂刀的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "blood");
        set("owner_name", "血舞狂刀");
        set_temp("owner", "blood");
        set_temp("owner_name", "血舞狂刀");
        ::setup();
}
