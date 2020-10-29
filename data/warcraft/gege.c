// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("你死定了[2;37;0m[2;37;0m", ({"kou"}));        
        set("gender", "男性");                
        set("long", "床豢梢皇?[2;37;0m
它是胡千刀的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "gege");
        set("owner_name", "胡千刀");
        set_temp("owner", "gege");
        set_temp("owner_name", "胡千刀");
        ::setup();
}
