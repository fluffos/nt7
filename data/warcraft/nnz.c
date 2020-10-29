// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小眼[2;37;0m[2;37;0m", ({"myzuoqi"}));        
        set("gender", "女性");                
        set("long", "小眼[2;37;0m
它是海龟很高的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "nnz");
        set("owner_name", "海龟很高");
        set_temp("owner", "nnz");
        set_temp("owner_name", "海龟很高");
        ::setup();
}
