// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m坑蒙拐骗[2;37;0m[2;37;0m", ({"fyy"}));        
        set("gender", "女性");                
        set("long", "                 [2;37;0m
它是淡泊的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "fxy");
        set("owner_name", "淡泊");
        set_temp("owner", "fxy");
        set_temp("owner_name", "淡泊");
        ::setup();
}
