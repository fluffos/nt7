// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("我党[2;37;0m[2;37;0m", ({"along"}));        
        set("gender", "男性");                
        set("long", "无法[2;37;0m
它是大华山的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "wristsb");
        set("owner_name", "大华山");
        set_temp("owner", "wristsb");
        set_temp("owner_name", "大华山");
        ::setup();
}
