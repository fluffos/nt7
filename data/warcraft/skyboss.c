// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小蛇[2;37;0m[2;37;0m", ({"qinglong"}));        
        set("gender", "男性");                
        set("long", "小蛇[2;37;0m
它是龙套的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "skyboss");
        set("owner_name", "龙套");
        set_temp("owner", "skyboss");
        set_temp("owner_name", "龙套");
        ::setup();
}
