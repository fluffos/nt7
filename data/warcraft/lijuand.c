// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m真爱四龙[2;37;0m[2;37;0m", ({"lilongd"}));        
        set("gender", "女性");                
        set("long", "天下有情人终成眷属[2;37;0m
它是李四娟的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "lijuand");
        set("owner_name", "李四娟");
        set_temp("owner", "lijuand");
        set_temp("owner_name", "李四娟");
        ::setup();
}
