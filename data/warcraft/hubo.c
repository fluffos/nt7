// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("桎梏[2;37;0m[2;37;0m", ({"zhigu"}));        
        set("gender", "男性");                
        set("long", "桎梏[2;37;0m
它是扈擘的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "hubo");
        set("owner_name", "扈擘");
        set_temp("owner", "hubo");
        set_temp("owner_name", "扈擘");
        ::setup();
}
