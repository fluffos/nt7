// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m江铁牛[2;37;0m[2;37;0m", ({"dukeo"}));        
        set("gender", "女性");                
        set("long", "江铁牛[2;37;0m
它是猪七的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "duke");
        set("owner_name", "猪七");
        set_temp("owner", "duke");
        set_temp("owner_name", "猪七");
        ::setup();
}
