// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m墨鱼[2;37;0m[2;37;0m", ({"mql"}));        
        set("gender", "男性");                
        set("long", "墨鱼噢[2;37;0m
它是熊二的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "uliane");
        set("owner_name", "熊二");
        set_temp("owner", "uliane");
        set_temp("owner_name", "熊二");
        ::setup();
}
