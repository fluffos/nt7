// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小马[2;37;0m[2;37;0m", ({"xiaoma"}));        
        set("gender", "女性");                
        set("long", "日行千里[2;37;0m
它是华小侠的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "hxx");
        set("owner_name", "华小侠");
        set_temp("owner", "hxx");
        set_temp("owner_name", "华小侠");
        ::setup();
}
