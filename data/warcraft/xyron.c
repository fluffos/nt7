// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m玄君[1;34m[2;37;0m[2;37;0m", ({"blacklord"}));        
        set("gender", "男性");                
        set("long", "北方之主[2;37;0m
它是薛朗的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "xyron");
        set("owner_name", "薛朗");
        set_temp("owner", "xyron");
        set_temp("owner_name", "薛朗");
        ::setup();
}
