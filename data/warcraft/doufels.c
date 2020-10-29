// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("蠢笨猪[2;37;0m[2;37;0m", ({"kelvin"}));        
        set("gender", "女性");                
        set("long", "蠢笨猪[2;37;0m
它是太空沐浴的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "doufels");
        set("owner_name", "太空沐浴");
        set_temp("owner", "doufels");
        set_temp("owner_name", "太空沐浴");
        ::setup();
}
