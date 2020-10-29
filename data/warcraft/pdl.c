// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("顶戴[2;37;0m[2;37;0m", ({"ldp"}));        
        set("gender", "女性");                
        set("long", "顶戴[2;37;0m
它是潘多拉的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "pdl");
        set("owner_name", "潘多拉");
        set_temp("owner", "pdl");
        set_temp("owner_name", "潘多拉");
        ::setup();
}
