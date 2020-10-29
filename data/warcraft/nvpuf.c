// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m朱雀[2;37;0m[2;37;0m", ({"zhuque"}));        
        set("gender", "男性");                
        set("long", "一种鸟类。[2;37;0m
它是女仆的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "nvpuf");
        set("owner_name", "女仆");
        set_temp("owner", "nvpuf");
        set_temp("owner_name", "女仆");
        ::setup();
}
