// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("草泥马[2;37;0m[2;37;0m", ({"fuck"}));        
        set("gender", "男性");                
        set("long", "神兽[2;37;0m
它是电网费电的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "wap");
        set("owner_name", "电网费电");
        set_temp("owner", "wap");
        set_temp("owner_name", "电网费电");
        ::setup();
}
