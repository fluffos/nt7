// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小眼[2;37;0m[2;37;0m", ({"myzuoqi"}));        
        set("gender", "女性");                
        set("long", "小眼[2;37;0m
它是前期阿阿的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "nnf");
        set("owner_name", "前期阿阿");
        set_temp("owner", "nnf");
        set_temp("owner_name", "前期阿阿");
        ::setup();
}
