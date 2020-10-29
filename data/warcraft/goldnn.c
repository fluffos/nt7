// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("难难难[2;37;0m[2;37;0m", ({"goldnnn"}));        
        set("gender", "男性");                
        set("long", "难难难[2;37;0m
它是金男的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "goldnn");
        set("owner_name", "金男");
        set_temp("owner", "goldnn");
        set_temp("owner_name", "金男");
        ::setup();
}
