// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("巧[2;37;0m[2;37;0m", ({"qiao"}));        
        set("gender", "女性");                
        set("long", "qiao[2;37;0m
它是吖霸的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "gggz");
        set("owner_name", "吖霸");
        set_temp("owner", "gggz");
        set_temp("owner_name", "吖霸");
        ::setup();
}
