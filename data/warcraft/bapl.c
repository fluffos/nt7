// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m七七[2;37;0m[2;37;0m", ({"qise"}));        
        set("gender", "女性");                
        set("long", "$HIC$这是一天七色彩龙，精致小巧，威严。[2;37;0m
它是色不亦空的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "bapl");
        set("owner_name", "色不亦空");
        set_temp("owner", "bapl");
        set_temp("owner_name", "色不亦空");
        ::setup();
}
