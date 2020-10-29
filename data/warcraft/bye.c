// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("一条龙[2;37;0m[2;37;0m", ({"byebye"}));        
        set("gender", "男性");                
        set("long", "就一条咩...[2;37;0m
它是英雄的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "bye");
        set("owner_name", "英雄");
        set_temp("owner", "bye");
        set_temp("owner_name", "英雄");
        ::setup();
}
