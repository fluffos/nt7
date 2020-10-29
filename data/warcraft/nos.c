// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m陈水扁[2;37;0m[2;37;0m", ({"noos"}));        
        set("gender", "男性");                
        set("long", "台北市议员、立法院立法委员、台北市市长。[2;37;0m
它是马英九的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "nos");
        set("owner_name", "马英九");
        set_temp("owner", "nos");
        set_temp("owner_name", "马英九");
        ::setup();
}
