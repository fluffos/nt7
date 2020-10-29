// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("考拉[2;37;0m[2;37;0m", ({"myfy"}));        
        set("gender", "女性");                
        set("long", "考拉[2;37;0m
它是嘎嘎耐肥的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "nnc");
        set("owner_name", "嘎嘎耐肥");
        set_temp("owner", "nnc");
        set_temp("owner_name", "嘎嘎耐肥");
        ::setup();
}
