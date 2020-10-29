// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;33m好声音[1;31m座椅[2;37;0m[2;37;0m", ({"baima"}));        
        set("gender", "男性");                
        set("long", "这个是从英国空运来的好声音豪华转椅，犀牛皮做成，价值80多万。[2;37;0m
它是庾澄庆的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "chengqing");
        set("owner_name", "庾澄庆");
        set_temp("owner", "chengqing");
        set_temp("owner_name", "庾澄庆");
        ::setup();
}
