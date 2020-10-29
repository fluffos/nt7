// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("阿兹猫[2;37;0m[2;37;0m", ({"loy"}));        
        set("gender", "女性");                
        set("long", "阿兹猫[2;37;0m
它是高处胜寒的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "newly");
        set("owner_name", "高处胜寒");
        set_temp("owner", "newly");
        set_temp("owner_name", "高处胜寒");
        ::setup();
}
