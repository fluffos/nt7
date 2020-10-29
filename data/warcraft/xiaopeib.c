// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("睡袋[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "男性");                
        set("long", "睡袋[2;37;0m
它是花非花的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "xiaopeib");
        set("owner_name", "花非花");
        set_temp("owner", "xiaopeib");
        set_temp("owner_name", "花非花");
        ::setup();
}
