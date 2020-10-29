// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("神仙狗[2;37;0m[2;37;0m", ({"shengou"}));        
        set("gender", "男性");                
        set("long", "神仙狗[2;37;0m
它是凤手腕的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "lfengf");
        set("owner_name", "凤手腕");
        set_temp("owner", "lfengf");
        set_temp("owner_name", "凤手腕");
        ::setup();
}
