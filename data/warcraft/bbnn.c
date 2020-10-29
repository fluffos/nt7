// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小龙[2;37;0m[2;37;0m", ({"xiaolong"}));        
        set("gender", "男性");                
        set("long", "小龙飞来了[2;37;0m
它是雾隐牛牛的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "bbnn");
        set("owner_name", "雾隐牛牛");
        set_temp("owner", "bbnn");
        set_temp("owner_name", "雾隐牛牛");
        ::setup();
}
