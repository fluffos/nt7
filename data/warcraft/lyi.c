// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("哦岁的河南[2;37;0m[2;37;0m", ({"cib"}));        
        set("gender", "男性");                
        set("long", "哦岁的河南[2;37;0m
它是葡萄酒号的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lyi");
        set("owner_name", "葡萄酒号");
        set_temp("owner", "lyi");
        set_temp("owner_name", "葡萄酒号");
        ::setup();
}
