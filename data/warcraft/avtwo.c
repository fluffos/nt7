// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("空空[2;37;0m[2;37;0m", ({"avdragon"}));        
        set("gender", "男性");                
        set("long", "空空[2;37;0m
它是波多老师的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "avtwo");
        set("owner_name", "波多老师");
        set_temp("owner", "avtwo");
        set_temp("owner_name", "波多老师");
        ::setup();
}
