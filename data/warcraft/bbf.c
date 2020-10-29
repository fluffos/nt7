// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m火云兽[2;37;0m[2;37;0m", ({"wwjr"}));        
        set("gender", "男性");                
        set("long", "$HIM$火云兽[2;37;0m
它是边不负的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "bbf");
        set("owner_name", "边不负");
        set_temp("owner", "bbf");
        set_temp("owner_name", "边不负");
        ::setup();
}
