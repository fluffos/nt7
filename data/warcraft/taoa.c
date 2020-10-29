// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[34m沈[1;33m阳[35m技[36m师[2;37;0m[2;37;0m", ({"qinglong"}));        
        set("gender", "男性");                
        set("long", "哗哗[2;37;0m
它是剑指中都的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "taoa");
        set("owner_name", "剑指中都");
        set_temp("owner", "taoa");
        set_temp("owner_name", "剑指中都");
        ::setup();
}
