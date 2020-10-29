// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m[30m怕鬼[2;37;0m[2;37;0m", ({"paa"}));        
        set("gender", "男性");                
        set("long", "一直爬的贼慢的老乌龟[2;37;0m
它是避邪的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "bixie");
        set("owner_name", "避邪");
        set_temp("owner", "bixie");
        set_temp("owner_name", "避邪");
        ::setup();
}
