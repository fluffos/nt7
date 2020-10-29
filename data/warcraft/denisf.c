// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("宝马[2;37;0m[2;37;0m", ({"ziqiang"}));        
        set("gender", "男性");                
        set("long", "宝马[2;37;0m
它是自强不息的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "denisf");
        set("owner_name", "自强不息");
        set_temp("owner", "denisf");
        set_temp("owner_name", "自强不息");
        ::setup();
}
