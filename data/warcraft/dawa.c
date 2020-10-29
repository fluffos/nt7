// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m不动明王[2;37;0m[2;37;0m", ({"mingwang"}));        
        set("gender", "女性");                
        set("long", "不动明王为佛教密宗八大明王首座。[2;37;0m
它是达瓦扎西的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "dawa");
        set("owner_name", "达瓦扎西");
        set_temp("owner", "dawa");
        set_temp("owner_name", "达瓦扎西");
        ::setup();
}
