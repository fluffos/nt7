// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("巧[2;37;0m[2;37;0m", ({"qiao"}));        
        set("gender", "女性");                
        set("long", "巧[2;37;0m
它是吖酒的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "gggx");
        set("owner_name", "吖酒");
        set_temp("owner", "gggx");
        set_temp("owner_name", "吖酒");
        ::setup();
}
