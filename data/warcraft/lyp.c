// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("扣篮对决[2;37;0m[2;37;0m", ({"cib"}));        
        set("gender", "男性");                
        set("long", "扣篮对决[2;37;0m
它是樱桃六号的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lyp");
        set("owner_name", "樱桃六号");
        set_temp("owner", "lyp");
        set_temp("owner_name", "樱桃六号");
        ::setup();
}
