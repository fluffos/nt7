// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("瘦成闪电[2;37;0m[2;37;0m", ({"bigwave"}));        
        set("gender", "男性");                
        set("long", "一头速度很快的东东[2;37;0m
它是胖大头的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "pangdatou");
        set("owner_name", "胖大头");
        set_temp("owner", "pangdatou");
        set_temp("owner_name", "胖大头");
        ::setup();
}
