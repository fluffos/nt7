// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[35m紫骝马[2;37;0m[2;37;0m", ({"myma"}));        
        set("gender", "男性");                
        set("long", "一只紫骝马[2;37;0m
它是紫旗的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "ziqi");
        set("owner_name", "紫旗");
        set_temp("owner", "ziqi");
        set_temp("owner_name", "紫旗");
        ::setup();
}
