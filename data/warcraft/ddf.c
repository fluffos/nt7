// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"ddff"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是堂发的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "ddf");
        set("owner_name", "堂发");
        set_temp("owner", "ddf");
        set_temp("owner_name", "堂发");
        ::setup();
}
