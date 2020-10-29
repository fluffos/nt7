// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m白虎[2;37;0m[2;37;0m", ({"bhu"}));        
        set("gender", "女性");                
        set("long", "白虎[2;37;0m
它是甜甜的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "ttian");
        set("owner_name", "甜甜");
        set_temp("owner", "ttian");
        set_temp("owner_name", "甜甜");
        ::setup();
}
