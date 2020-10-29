// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小依[2;37;0m[2;37;0m", ({"feeling"}));        
        set("gender", "女性");                
        set("long", "无[2;37;0m
它是谢七的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "toko");
        set("owner_name", "谢七");
        set_temp("owner", "toko");
        set_temp("owner_name", "谢七");
        ::setup();
}
