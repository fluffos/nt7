// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("大火鸡[2;37;0m[2;37;0m", ({"dahuoji"}));        
        set("gender", "男性");                
        set("long", "一只不知道什么种类的大火鸡[2;37;0m
它是龙影的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "zhaoxinng");
        set("owner_name", "龙影");
        set_temp("owner", "zhaoxinng");
        set_temp("owner_name", "龙影");
        ::setup();
}
