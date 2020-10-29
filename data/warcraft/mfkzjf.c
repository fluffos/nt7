// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;36m火[1;35m麒[1;33m麟[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "男性");                
        set("long", "麒麟王者[2;37;0m
它是苦楝树的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "mfkzjf");
        set("owner_name", "苦楝树");
        set_temp("owner", "mfkzjf");
        set_temp("owner_name", "苦楝树");
        ::setup();
}
