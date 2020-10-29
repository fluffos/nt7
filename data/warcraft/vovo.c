// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("飞[2;37;0m[2;37;0m", ({"gogoto"}));        
        set("gender", "女性");                
        set("long", "无[2;37;0m
它是云一心的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "vovo");
        set("owner_name", "云一心");
        set_temp("owner", "vovo");
        set_temp("owner_name", "云一心");
        ::setup();
}
