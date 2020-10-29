// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m品当武[2;37;0m[2;37;0m", ({"wdtestcc"}));        
        set("gender", "男性");                
        set("long", "阿[2;37;0m
它是武当品的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "wdtestc");
        set("owner_name", "武当品");
        set_temp("owner", "wdtestc");
        set_temp("owner_name", "武当品");
        ::setup();
}
