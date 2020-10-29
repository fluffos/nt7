// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("靓仔[2;37;0m[2;37;0m", ({"ioi"}));        
        set("gender", "男性");                
        set("long", "靓[2;37;0m
它是蟾蜍的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "lha");
        set("owner_name", "蟾蜍");
        set_temp("owner", "lha");
        set_temp("owner_name", "蟾蜍");
        ::setup();
}
