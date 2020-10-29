// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱雀[2;37;0m[2;37;0m", ({"cris"}));        
        set("gender", "女性");                
        set("long", "asf  [2;37;0m
它是孙瑟的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "sirc");
        set("owner_name", "孙瑟");
        set_temp("owner", "sirc");
        set_temp("owner_name", "孙瑟");
        ::setup();
}
