// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m古琦[2;37;0m[2;37;0m", ({"gucoi"}));        
        set("gender", "女性");                
        set("long", "古琦[2;37;0m
它是猪八的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "gucci");
        set("owner_name", "猪八");
        set_temp("owner", "gucci");
        set_temp("owner_name", "猪八");
        ::setup();
}
