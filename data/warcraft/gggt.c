// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("巧[2;37;0m[2;37;0m", ({"qiao"}));        
        set("gender", "女性");                
        set("long", "巧[2;37;0m
它是吖柒的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "gggt");
        set("owner_name", "吖柒");
        set_temp("owner", "gggt");
        set_temp("owner_name", "吖柒");
        ::setup();
}
