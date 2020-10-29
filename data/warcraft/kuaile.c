// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("幸福[2;37;0m[2;37;0m", ({"yaokuaile"}));        
        set("gender", "男性");                
        set("long", "幸福快乐[2;37;0m
它是高兴的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "kuaile");
        set("owner_name", "高兴");
        set_temp("owner", "kuaile");
        set_temp("owner_name", "高兴");
        ::setup();
}
