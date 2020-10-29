// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m生命[2;37;0m[2;37;0m", ({"rizz"}));        
        set("gender", "女性");                
        set("long", "$HIR$生命[2;37;0m
它是西若的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "rica");
        set("owner_name", "西若");
        set_temp("owner", "rica");
        set_temp("owner_name", "西若");
        ::setup();
}
