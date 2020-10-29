// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("五毒一一一[2;37;0m[2;37;0m", ({"wuduidaaa"}));        
        set("gender", "男性");                
        set("long", "五毒一一一[2;37;0m
它是五毒一号的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "wuduid");
        set("owner_name", "五毒一号");
        set_temp("owner", "wuduid");
        set_temp("owner_name", "五毒一号");
        ::setup();
}
