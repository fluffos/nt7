// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("巧[2;37;0m[2;37;0m", ({"qiao"}));        
        set("gender", "女性");                
        set("long", "巧[2;37;0m
它是吖肆的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "ggga");
        set("owner_name", "吖肆");
        set_temp("owner", "ggga");
        set_temp("owner_name", "吖肆");
        ::setup();
}
