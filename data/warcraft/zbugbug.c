// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m泰麒[2;37;0m[2;37;0m", ({"kilin"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是令狐虫的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "zbugbug");
        set("owner_name", "令狐虫");
        set_temp("owner", "zbugbug");
        set_temp("owner_name", "令狐虫");
        ::setup();
}
