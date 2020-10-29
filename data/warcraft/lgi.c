// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("老狗诶丝[2;37;0m[2;37;0m", ({"lgis"}));        
        set("gender", "男性");                
        set("long", "哈哈[2;37;0m
它是老狗玖的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lgi");
        set("owner_name", "老狗玖");
        set_temp("owner", "lgi");
        set_temp("owner_name", "老狗玖");
        ::setup();
}
