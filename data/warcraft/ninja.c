// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("鸟[2;37;0m[2;37;0m", ({"axe"}));        
        set("gender", "男性");                
        set("long", "撒大声地大飒飒的[2;37;0m
它是纯纯的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "ninja");
        set("owner_name", "纯纯");
        set_temp("owner", "ninja");
        set_temp("owner_name", "纯纯");
        ::setup();
}
