// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("互动[2;37;0m[2;37;0m", ({"oko"}));        
        set("gender", "男性");                
        set("long", "人[2;37;0m
它是合得来的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "lntv");
        set("owner_name", "合得来");
        set_temp("owner", "lntv");
        set_temp("owner_name", "合得来");
        ::setup();
}
