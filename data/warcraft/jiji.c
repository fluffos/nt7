// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;31m囚牛[2;37;0m[2;37;0m", ({"xiaoq"}));        
        set("gender", "女性");                
        set("long", "龙老大[2;37;0m
它是做了就爱的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "jiji");
        set("owner_name", "做了就爱");
        set_temp("owner", "jiji");
        set_temp("owner_name", "做了就爱");
        ::setup();
}
