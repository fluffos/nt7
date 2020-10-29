// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟兽[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "男性");                
        set("long", "一个兽[2;37;0m
它是舛猪猪的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "wdx");
        set("owner_name", "舛猪猪");
        set_temp("owner", "wdx");
        set_temp("owner_name", "舛猪猪");
        ::setup();
}
