// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("齐齐[2;37;0m[2;37;0m", ({"qiqiqi"}));        
        set("gender", "女性");                
        set("long", "齐齐[2;37;0m
它是天副的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "sysan");
        set("owner_name", "天副");
        set_temp("owner", "sysan");
        set_temp("owner_name", "天副");
        ::setup();
}
