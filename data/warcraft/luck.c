// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("玛莎拉蒂[2;37;0m[2;37;0m", ({"mashaladi"}));        
        set("gender", "男性");                
        set("long", "玛莎拉蒂[2;37;0m
它是埃辛摩卡的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "luck");
        set("owner_name", "埃辛摩卡");
        set_temp("owner", "luck");
        set_temp("owner_name", "埃辛摩卡");
        ::setup();
}
