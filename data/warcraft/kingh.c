// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("金角五爪龙[2;37;0m[2;37;0m", ({"kingdragon"}));        
        set("gender", "男性");                
        set("long", "这是一条神龙，金色的角，五彩的爪，犀利的眼神！！！[2;37;0m
它是金虎的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "kingh");
        set("owner_name", "金虎");
        set_temp("owner", "kingh");
        set_temp("owner_name", "金虎");
        ::setup();
}
