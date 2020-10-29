// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小蛇[2;37;0m[2;37;0m", ({"xiaosheq"}));        
        set("gender", "男性");                
        set("long", "小蛇[2;37;0m
它是康梓一的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "kcm");
        set("owner_name", "康梓一");
        set_temp("owner", "kcm");
        set_temp("owner_name", "康梓一");
        ::setup();
}
