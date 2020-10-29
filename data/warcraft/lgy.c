// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m输出文字中[2;37;0m[2;37;0m", ({"bmw"}));        
        set("gender", "男性");                
        set("long", "bmw[2;37;0m
它是栏杆效率的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "lgy");
        set("owner_name", "栏杆效率");
        set_temp("owner", "lgy");
        set_temp("owner_name", "栏杆效率");
        ::setup();
}
