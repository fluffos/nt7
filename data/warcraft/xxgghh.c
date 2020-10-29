// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("遁地[2;37;0m[2;37;0m", ({"flytian"}));        
        set("gender", "男性");                
        set("long", "快跑[2;37;0m
它是大胆的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "xxgghh");
        set("owner_name", "大胆");
        set_temp("owner", "xxgghh");
        set_temp("owner_name", "大胆");
        ::setup();
}
