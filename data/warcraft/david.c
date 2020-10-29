// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"zizi"}));        
        set("gender", "男性");                
        set("long", "一条青龙[2;37;0m
它是风中叶子的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "david");
        set("owner_name", "风中叶子");
        set_temp("owner", "david");
        set_temp("owner_name", "风中叶子");
        ::setup();
}
