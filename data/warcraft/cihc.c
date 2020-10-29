// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("驴[2;37;0m[2;37;0m", ({"gyill"}));        
        set("gender", "男性");                
        set("long", "无[2;37;0m
它是眼三三的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "cihc");
        set("owner_name", "眼三三");
        set_temp("owner", "cihc");
        set_temp("owner_name", "眼三三");
        ::setup();
}
