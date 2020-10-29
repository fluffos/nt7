// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m踏雪[1;34m乌锥[2;37;0m[2;37;0m", ({"baima"}));        
        set("gender", "男性");                
        set("long", "这匹神驹通体如黑缎子一般，只四蹄白色，神骏非凡、如天龙下凡。[2;37;0m
它是王昭君的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "zhaojun");
        set("owner_name", "王昭君");
        set_temp("owner", "zhaojun");
        set_temp("owner_name", "王昭君");
        ::setup();
}
