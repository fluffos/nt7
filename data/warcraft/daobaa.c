// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m大鹏鸟[2;37;0m[2;37;0m", ({"peng"}));        
        set("gender", "男性");                
        set("long", "好大的鸟[2;37;0m
它是郭大路的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "daobaa");
        set("owner_name", "郭大路");
        set_temp("owner", "daobaa");
        set_temp("owner_name", "郭大路");
        ::setup();
}
