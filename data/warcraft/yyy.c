// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("睡袋[2;37;0m[2;37;0m", ({"sleep"}));        
        set("gender", "男性");                
        set("long", "屌屌屌[2;37;0m
它是李叔叔的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "yyy");
        set("owner_name", "李叔叔");
        set_temp("owner", "yyy");
        set_temp("owner_name", "李叔叔");
        ::setup();
}
