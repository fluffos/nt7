// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m避水金睛兽[2;37;0m[2;37;0m", ({"fhh"}));        
        set("gender", "男性");                
        set("long", "超现实魔幻主义。[2;37;0m
它是紫薯蛋挞的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "xmotoboy");
        set("owner_name", "紫薯蛋挞");
        set_temp("owner", "xmotoboy");
        set_temp("owner_name", "紫薯蛋挞");
        ::setup();
}
