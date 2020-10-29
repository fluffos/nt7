// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("玄武[2;37;0m[2;37;0m", ({"dsy"}));        
        set("gender", "女性");                
        set("long", "这是一只玄武[2;37;0m
它是数支的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "dsydxlb");
        set("owner_name", "数支");
        set_temp("owner", "dsydxlb");
        set_temp("owner_name", "数支");
        ::setup();
}
