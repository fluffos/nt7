// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m抹布[2;37;0m[2;37;0m", ({"poss"}));        
        set("gender", "男性");                
        set("long", "$HIR$抹布[2;37;0m
它是破四的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "pos");
        set("owner_name", "破四");
        set_temp("owner", "pos");
        set_temp("owner_name", "破四");
        ::setup();
}
