// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m登[5m[1;32m龙[2;37;0m[1;37m剑[2;37;0m[2;37;0m", ({"drago"}));        
        set("gender", "女性");                
        set("long", "飞云[2;37;0m
它是金刚的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "unchibb");
        set("owner_name", "金刚");
        set_temp("owner", "unchibb");
        set_temp("owner_name", "金刚");
        ::setup();
}
