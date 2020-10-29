// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;36m阿[1;32m里[1;31m狼[2;37;0m[2;37;0m", ({"alang"}));        
        set("gender", "女性");                
        set("long", "阿里狼[2;37;0m
它是浪子的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "lang");
        set("owner_name", "浪子");
        set_temp("owner", "lang");
        set_temp("owner_name", "浪子");
        ::setup();
}
