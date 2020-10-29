// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("桃杰[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "男性");                
        set("long", "陶杰[2;37;0m
它是桃花盛开的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "thddumy");
        set("owner_name", "桃花盛开");
        set_temp("owner", "thddumy");
        set_temp("owner_name", "桃花盛开");
        ::setup();
}
