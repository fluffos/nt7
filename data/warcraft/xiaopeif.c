// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"flower"}));        
        set("gender", "男性");                
        set("long", "青龙[2;37;0m
它是花无痕的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "xiaopeif");
        set("owner_name", "花无痕");
        set_temp("owner", "xiaopeif");
        set_temp("owner_name", "花无痕");
        ::setup();
}
