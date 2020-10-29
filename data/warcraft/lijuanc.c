// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m真爱三龙[2;37;0m[2;37;0m", ({"lilongc"}));        
        set("gender", "女性");                
        set("long", "eg[2;37;0m
它是李三娟的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "lijuanc");
        set("owner_name", "李三娟");
        set_temp("owner", "lijuanc");
        set_temp("owner_name", "李三娟");
        ::setup();
}
