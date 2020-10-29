// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m输出文字中[2;37;0m[2;37;0m", ({"bmw"}));        
        set("gender", "男性");                
        set("long", "bmw[2;37;0m
它是鞋弓袜小的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "xboots");
        set("owner_name", "鞋弓袜小");
        set_temp("owner", "xboots");
        set_temp("owner_name", "鞋弓袜小");
        ::setup();
}
