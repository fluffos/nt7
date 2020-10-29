// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m吡咯[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "男性");                
        set("long", "上古神兽[2;37;0m
它是柳轻风的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "yaomei");
        set("owner_name", "柳轻风");
        set_temp("owner", "yaomei");
        set_temp("owner_name", "柳轻风");
        ::setup();
}
