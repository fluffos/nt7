// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟兽[2;37;0m[2;37;0m", ({"qilinshou"}));        
        set("gender", "男性");                
        set("long", "攻击神兽[2;37;0m
它是胡家刀的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "hujiadao");
        set("owner_name", "胡家刀");
        set_temp("owner", "hujiadao");
        set_temp("owner_name", "胡家刀");
        ::setup();
}
