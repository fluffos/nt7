// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m真爱一龙[2;37;0m[2;37;0m", ({"lilonga"}));        
        set("gender", "女性");                
        set("long", "天下有情人终成眷属[2;37;0m
它是李一娟的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "lijuana");
        set("owner_name", "李一娟");
        set_temp("owner", "lijuana");
        set_temp("owner_name", "李一娟");
        ::setup();
}
