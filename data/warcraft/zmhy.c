// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("煌儿[2;37;0m[2;37;0m", ({"huanger"}));        
        set("gender", "女性");                
        set("long", "煌儿[2;37;0m
它是苍婧空的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "zmhy");
        set("owner_name", "苍婧空");
        set_temp("owner", "zmhy");
        set_temp("owner_name", "苍婧空");
        ::setup();
}
