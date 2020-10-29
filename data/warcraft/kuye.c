// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("酷酷[2;37;0m[2;37;0m", ({"kuku"}));        
        set("gender", "女性");                
        set("long", "酷酷的酷酷[2;37;0m
它是枯叶的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "kuye");
        set("owner_name", "枯叶");
        set_temp("owner", "kuye");
        set_temp("owner_name", "枯叶");
        ::setup();
}
