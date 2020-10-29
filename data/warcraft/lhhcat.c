// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("睡袋[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "女性");                
        set("long", "hahahahahah[2;37;0m
它是亮晶晶的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "lhhcat");
        set("owner_name", "亮晶晶");
        set_temp("owner", "lhhcat");
        set_temp("owner_name", "亮晶晶");
        ::setup();
}
