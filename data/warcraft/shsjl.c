// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("龙[2;37;0m[2;37;0m", ({"qlong"}));        
        set("gender", "男性");                
        set("long", "龙[2;37;0m
它是慕容鲤鱼的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "shsjl");
        set("owner_name", "慕容鲤鱼");
        set_temp("owner", "shsjl");
        set_temp("owner_name", "慕容鲤鱼");
        ::setup();
}
