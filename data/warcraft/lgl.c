// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("老狗历史[2;37;0m[2;37;0m", ({"lgls"}));        
        set("gender", "男性");                
        set("long", "哈哈[2;37;0m
它是老狗来的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lgl");
        set("owner_name", "老狗来");
        set_temp("owner", "lgl");
        set_temp("owner_name", "老狗来");
        ::setup();
}
