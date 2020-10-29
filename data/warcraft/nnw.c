// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小眼[2;37;0m[2;37;0m", ({"myzuoqi"}));        
        set("gender", "女性");                
        set("long", "小眼[2;37;0m
它是爱过后的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "nnw");
        set("owner_name", "爱过后");
        set_temp("owner", "nnw");
        set_temp("owner_name", "爱过后");
        ::setup();
}
