// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("阿贡[2;37;0m[2;37;0m", ({"aka"}));        
        set("gender", "女性");                
        set("long", "来自娜美克星的无敌宝宝[2;37;0m
它是薛雨的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "jasdin");
        set("owner_name", "薛雨");
        set_temp("owner", "jasdin");
        set_temp("owner_name", "薛雨");
        ::setup();
}
