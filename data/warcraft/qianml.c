// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("老马[2;37;0m[2;37;0m", ({"laoma"}));        
        set("gender", "男性");                
        set("long", "老马[2;37;0m
它是南篱旧事的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "qianml");
        set("owner_name", "南篱旧事");
        set_temp("owner", "qianml");
        set_temp("owner_name", "南篱旧事");
        ::setup();
}
