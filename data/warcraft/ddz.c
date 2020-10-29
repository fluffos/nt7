// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"ddzz"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是堂杂的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "ddz");
        set("owner_name", "堂杂");
        set_temp("owner", "ddz");
        set_temp("owner_name", "堂杂");
        ::setup();
}
