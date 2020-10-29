// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[35m浩瀚星空[2;37;0m[2;37;0m", ({"space"}));        
        set("gender", "男性");                
        set("long", "浩瀚星空[2;37;0m
它是星河大帝的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lyrone");
        set("owner_name", "星河大帝");
        set_temp("owner", "lyrone");
        set_temp("owner_name", "星河大帝");
        ::setup();
}
