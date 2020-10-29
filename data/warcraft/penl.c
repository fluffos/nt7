// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m赤焰驹[2;37;0m[2;37;0m", ({"baima"}));        
        set("gender", "女性");                
        set("long", "$HIW$赤焰驹[2;37;0m
它是柳公权的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "penl");
        set("owner_name", "柳公权");
        set_temp("owner", "penl");
        set_temp("owner_name", "柳公权");
        ::setup();
}
