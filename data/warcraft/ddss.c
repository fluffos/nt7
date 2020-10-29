// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"ddtt"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是堂说的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "ddss");
        set("owner_name", "堂说");
        set_temp("owner", "ddss");
        set_temp("owner_name", "堂说");
        ::setup();
}
