// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("灵鹫一一一[2;37;0m[2;37;0m", ({"lingjiuaaa"}));        
        set("gender", "男性");                
        set("long", "灵鹫一一一[2;37;0m
它是灵鹫一号的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "lingjiuid");
        set("owner_name", "灵鹫一号");
        set_temp("owner", "lingjiuid");
        set_temp("owner_name", "灵鹫一号");
        ::setup();
}
