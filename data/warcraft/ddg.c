// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"ddgg"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是堂改的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "ddg");
        set("owner_name", "堂改");
        set_temp("owner", "ddg");
        set_temp("owner_name", "堂改");
        ::setup();
}
