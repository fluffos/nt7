// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m麒麟兽[2;37;0m[2;37;0m", ({"yuql"}));        
        set("gender", "男性");                
        set("long", "卢俊义的坐骑[2;37;0m
它是卢俊义的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lujunyi");
        set("owner_name", "卢俊义");
        set_temp("owner", "lujunyi");
        set_temp("owner_name", "卢俊义");
        ::setup();
}
