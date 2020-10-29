// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"ddaa"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是堂啊的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "dda");
        set("owner_name", "堂啊");
        set_temp("owner", "dda");
        set_temp("owner_name", "堂啊");
        ::setup();
}
