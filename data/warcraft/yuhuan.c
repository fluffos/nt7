// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m乌云[1;37m盖雪[2;37;0m[2;37;0m", ({"baima"}));        
        set("gender", "男性");                
        set("long", "这匹西域神驹通体雪白，只是马背黑色如云，神骏非常。[2;37;0m
它是杨玉环的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "yuhuan");
        set("owner_name", "杨玉环");
        set_temp("owner", "yuhuan");
        set_temp("owner_name", "杨玉环");
        ::setup();
}
