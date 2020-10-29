// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("蓝龙[2;37;0m[2;37;0m", ({"bluedragon"}));        
        set("gender", "男性");                
        set("long", "恶魔坐骑[2;37;0m
它是轩辕无痕的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "chenlei");
        set("owner_name", "轩辕无痕");
        set_temp("owner", "chenlei");
        set_temp("owner_name", "轩辕无痕");
        ::setup();
}
