// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m神仙狗[2;37;0m[2;37;0m", ({"shengou"}));        
        set("gender", "男性");                
        set("long", "神仙狗[2;37;0m
它是珑风的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "lfd");
        set("owner_name", "珑风");
        set_temp("owner", "lfd");
        set_temp("owner_name", "珑风");
        ::setup();
}
