// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m小绿茶[2;37;0m[2;37;0m", ({"spceial"}));        
        set("gender", "女性");                
        set("long", "小绿茶[2;37;0m
它是猪大的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "special");
        set("owner_name", "猪大");
        set_temp("owner", "special");
        set_temp("owner_name", "猪大");
        ::setup();
}
