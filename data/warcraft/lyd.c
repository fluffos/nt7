// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("贷款金额哦[2;37;0m[2;37;0m", ({"cib"}));        
        set("gender", "男性");                
        set("long", "贷款金额哦[2;37;0m
它是葡萄四号的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lyd");
        set("owner_name", "葡萄四号");
        set_temp("owner", "lyd");
        set_temp("owner_name", "葡萄四号");
        ::setup();
}
