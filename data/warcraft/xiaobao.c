// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("撒旦[2;37;0m[2;37;0m", ({"asdjij"}));        
        set("gender", "男性");                
        set("long", "uptime[2;37;0m
它是地狱之阎的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "xiaobao");
        set("owner_name", "地狱之阎");
        set_temp("owner", "xiaobao");
        set_temp("owner_name", "地狱之阎");
        ::setup();
}
