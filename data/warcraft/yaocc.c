// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("踩踩踩[2;37;0m[2;37;0m", ({"yaoccc"}));        
        set("gender", "男性");                
        set("long", "踩踩踩[2;37;0m
它是药串串的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "yaocc");
        set("owner_name", "药串串");
        set_temp("owner", "yaocc");
        set_temp("owner_name", "药串串");
        ::setup();
}
