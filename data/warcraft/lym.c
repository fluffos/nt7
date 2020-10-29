// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("拉克三大纪律[2;37;0m[2;37;0m", ({"cib"}));        
        set("gender", "男性");                
        set("long", "拉克三大纪律[2;37;0m
它是樱桃三号的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lym");
        set("owner_name", "樱桃三号");
        set_temp("owner", "lym");
        set_temp("owner_name", "樱桃三号");
        ::setup();
}
