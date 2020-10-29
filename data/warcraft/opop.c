// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小大[2;37;0m[2;37;0m", ({"popo"}));        
        set("gender", "女性");                
        set("long", "小大[2;37;0m
它是小小的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "opop");
        set("owner_name", "小小");
        set_temp("owner", "opop");
        set_temp("owner_name", "小小");
        ::setup();
}
