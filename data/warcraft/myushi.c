// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("秋天不回来[2;37;0m[2;37;0m", ({"dingdong"}));        
        set("gender", "男性");                
        set("long", "对方身份[2;37;0m
它是沐石的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "myushi");
        set("owner_name", "沐石");
        set_temp("owner", "myushi");
        set_temp("owner_name", "沐石");
        ::setup();
}
