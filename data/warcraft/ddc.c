// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"ddcc"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是堂吃的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "ddc");
        set("owner_name", "堂吃");
        set_temp("owner", "ddc");
        set_temp("owner_name", "堂吃");
        ::setup();
}
