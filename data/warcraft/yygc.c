// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("月津梅带子[2;37;0m[2;37;0m", ({"plgt"}));        
        set("gender", "男性");                
        set("long", "@miaoshu[2;37;0m
它是押运三的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "yygc");
        set("owner_name", "押运三");
        set_temp("owner", "yygc");
        set_temp("owner_name", "押运三");
        ::setup();
}
