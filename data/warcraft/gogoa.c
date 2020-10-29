// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小青龙[2;37;0m[2;37;0m", ({"qinglong"}));        
        set("gender", "男性");                
        set("long", "一条小青龙[2;37;0m
它是无涯的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "gogoa");
        set("owner_name", "无涯");
        set_temp("owner", "gogoa");
        set_temp("owner_name", "无涯");
        ::setup();
}
