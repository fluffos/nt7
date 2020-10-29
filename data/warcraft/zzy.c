// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m风[1;34m雷[5m[2;37;0m[2;37;0m", ({"zyy"}));        
        set("gender", "女性");                
        set("long", "一声惊雷从天降，风火烧成万骨灰[2;37;0m
它是残天的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "zzy");
        set("owner_name", "残天");
        set_temp("owner", "zzy");
        set_temp("owner_name", "残天");
        ::setup();
}
