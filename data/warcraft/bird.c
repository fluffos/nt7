// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;35m小[1;31m鸟[2;37;0m[2;37;0m", ({"niao"}));        
        set("gender", "男性");                
        set("long", "一只小小鸟[2;37;0m
它是鸟人的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "bird");
        set("owner_name", "鸟人");
        set_temp("owner", "bird");
        set_temp("owner_name", "鸟人");
        ::setup();
}
