// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("垃圾[2;37;0m[2;37;0m", ({"abcde"}));        
        set("gender", "男性");                
        set("long", "垃圾[2;37;0m
它是庭庭的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "tingting");
        set("owner_name", "庭庭");
        set_temp("owner", "tingting");
        set_temp("owner_name", "庭庭");
        ::setup();
}
