// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m时而[2;37;0m[2;37;0m", ({"shier"}));        
        set("gender", "男性");                
        set("long", "时而[2;37;0m
它是食饵不化的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "dangser");
        set("owner_name", "食饵不化");
        set_temp("owner", "dangser");
        set_temp("owner_name", "食饵不化");
        ::setup();
}
