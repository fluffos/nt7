// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("哈哈[2;37;0m[2;37;0m", ({"hahaha"}));        
        set("gender", "男性");                
        set("long", "好[2;37;0m
它是特务的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "cyjeff");
        set("owner_name", "特务");
        set_temp("owner", "cyjeff");
        set_temp("owner_name", "特务");
        ::setup();
}
