// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("金铃[2;37;0m[2;37;0m", ({"wdan"}));        
        set("gender", "女性");                
        set("long", "金铃[2;37;0m
它是铃铛的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "ldang");
        set("owner_name", "铃铛");
        set_temp("owner", "ldang");
        set_temp("owner_name", "铃铛");
        ::setup();
}
