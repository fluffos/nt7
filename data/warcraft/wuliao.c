// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m丘[1;35m比[1;31m龙[2;37;0m[2;37;0m", ({"xlong"}));        
        set("gender", "男性");                
        set("long", "龙龙[2;37;0m
它是无聊的鱼的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "wuliao");
        set("owner_name", "无聊的鱼");
        set_temp("owner", "wuliao");
        set_temp("owner_name", "无聊的鱼");
        ::setup();
}
