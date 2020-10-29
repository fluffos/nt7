// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("火麒麟[2;37;0m[2;37;0m", ({"huoqilin"}));        
        set("gender", "男性");                
        set("long", "完美的一只远古麒麟[2;37;0m
它是诸葛少卿的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "mingdi");
        set("owner_name", "诸葛少卿");
        set_temp("owner", "mingdi");
        set_temp("owner_name", "诸葛少卿");
        ::setup();
}
