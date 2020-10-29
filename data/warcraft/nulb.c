// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"qinglong"}));        
        set("gender", "男性");                
        set("long", "幻兽呀！请你以最深的灵性，聆听我的倾诉[2;37;0m
它是乌龙鱼的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "nulb");
        set("owner_name", "乌龙鱼");
        set_temp("owner", "nulb");
        set_temp("owner_name", "乌龙鱼");
        ::setup();
}
