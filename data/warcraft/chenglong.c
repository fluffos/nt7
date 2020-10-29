// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("玄武[2;37;0m[2;37;0m", ({"aasw"}));        
        set("gender", "男性");                
        set("long", "玄武[2;37;0m
它是成隆的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "chenglong");
        set("owner_name", "成隆");
        set_temp("owner", "chenglong");
        set_temp("owner_name", "成隆");
        ::setup();
}
