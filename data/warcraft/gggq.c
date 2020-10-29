// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("欧欧[2;37;0m[2;37;0m", ({"ouou"}));        
        set("gender", "男性");                
        set("long", "欧欧[2;37;0m
它是吖壹的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "gggq");
        set("owner_name", "吖壹");
        set_temp("owner", "gggq");
        set_temp("owner_name", "吖壹");
        ::setup();
}
