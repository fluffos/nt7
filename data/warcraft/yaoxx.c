// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"yaoxxx"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是药学校的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "yaoxx");
        set("owner_name", "药学校");
        set_temp("owner", "yaoxx");
        set_temp("owner_name", "药学校");
        ::setup();
}
