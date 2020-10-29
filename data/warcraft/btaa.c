// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[35m虎[1;36m虎[36m虎[2;37;0m[2;37;0m", ({"tigger"}));        
        set("gender", "男性");                
        set("long", "天天[2;37;0m
它是欧阳阳欧的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "btaa");
        set("owner_name", "欧阳阳欧");
        set_temp("owner", "btaa");
        set_temp("owner_name", "欧阳阳欧");
        ::setup();
}
