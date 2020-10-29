// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("哦死得很[2;37;0m[2;37;0m", ({"cib"}));        
        set("gender", "男性");                
        set("long", "哦死得很[2;37;0m
它是樱桃一号的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lyk");
        set("owner_name", "樱桃一号");
        set_temp("owner", "lyk");
        set_temp("owner_name", "樱桃一号");
        ::setup();
}
