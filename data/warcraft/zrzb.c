// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m小泽玛利亚[1;37m[2;37;0m[2;37;0m", ({"maria"}));        
        set("gender", "女性");                
        set("long", "AV女优[2;37;0m
它是粽二的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "zrzb");
        set("owner_name", "粽二");
        set_temp("owner", "zrzb");
        set_temp("owner_name", "粽二");
        ::setup();
}
