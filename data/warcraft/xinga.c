// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("星飞[2;37;0m[2;37;0m", ({"xingaa"}));        
        set("gender", "男性");                
        set("long", "星飞[2;37;0m
它是星空的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "xinga");
        set("owner_name", "星空");
        set_temp("owner", "xinga");
        set_temp("owner_name", "星空");
        ::setup();
}
