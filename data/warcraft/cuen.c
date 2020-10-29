// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"pet"}));        
        set("gender", "女性");                
        set("long", "青龙[2;37;0m
它是灵寸的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "cuen");
        set("owner_name", "灵寸");
        set_temp("owner", "cuen");
        set_temp("owner_name", "灵寸");
        ::setup();
}
