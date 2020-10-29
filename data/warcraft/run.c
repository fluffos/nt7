// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("太古青龙[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "女性");                
        set("long", "万物源头[2;37;0m
它是糙汉的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "run");
        set("owner_name", "糙汉");
        set_temp("owner", "run");
        set_temp("owner_name", "糙汉");
        ::setup();
}
