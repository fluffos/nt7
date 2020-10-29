// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m人力三轮[2;37;0m[2;37;0m", ({"doo"}));        
        set("gender", "女性");                
        set("long", "$HIW$人力三轮[2;37;0m
它是认球不得的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "kood");
        set("owner_name", "认球不得");
        set_temp("owner", "kood");
        set_temp("owner_name", "认球不得");
        ::setup();
}
