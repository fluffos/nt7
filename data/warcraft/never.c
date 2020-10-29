// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m朱珠[2;37;0m[2;37;0m", ({"zhuzhu"}));        
        set("gender", "女性");                
        set("long", "朱[2;37;0m
它是南人锐的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "never");
        set("owner_name", "南人锐");
        set_temp("owner", "never");
        set_temp("owner_name", "南人锐");
        ::setup();
}
