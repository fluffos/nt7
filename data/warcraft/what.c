// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小飞虎[2;37;0m[2;37;0m", ({"tttiger"}));        
        set("gender", "男性");                
        set("long", "小飞虎[2;37;0m
它是瓦特力的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "what");
        set("owner_name", "瓦特力");
        set_temp("owner", "what");
        set_temp("owner_name", "瓦特力");
        ::setup();
}
