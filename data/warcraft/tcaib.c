// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("大黄狗[2;37;0m[2;37;0m", ({"tcaibride"}));        
        set("gender", "男性");                
        set("long", "大黄狗[2;37;0m
它是纳尼金的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "tcaib");
        set("owner_name", "纳尼金");
        set_temp("owner", "tcaib");
        set_temp("owner_name", "纳尼金");
        ::setup();
}
