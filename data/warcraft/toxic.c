// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m无毒[2;37;0m[2;37;0m", ({"notoxic"}));        
        set("gender", "女性");                
        set("long", "阿[2;37;0m
它是唔够毒的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "toxic");
        set("owner_name", "唔够毒");
        set_temp("owner", "toxic");
        set_temp("owner_name", "唔够毒");
        ::setup();
}
