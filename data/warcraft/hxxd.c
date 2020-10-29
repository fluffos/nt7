// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小马[2;37;0m[2;37;0m", ({"xiaoma"}));        
        set("gender", "男性");                
        set("long", "小马[2;37;0m
它是华多多的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "hxxd");
        set("owner_name", "华多多");
        set_temp("owner", "hxxd");
        set_temp("owner_name", "华多多");
        ::setup();
}
