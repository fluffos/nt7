// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m齐玲[2;37;0m[2;37;0m", ({"moneyaa"}));        
        set("gender", "男性");                
        set("long", "齐玲[2;37;0m
它是钱大通的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "moneyp");
        set("owner_name", "钱大通");
        set_temp("owner", "moneyp");
        set_temp("owner_name", "钱大通");
        ::setup();
}
