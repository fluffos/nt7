// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("欧欧[2;37;0m[2;37;0m", ({"ouou"}));        
        set("gender", "男性");                
        set("long", "欧欧[2;37;0m
它是吖贰的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "gggw");
        set("owner_name", "吖贰");
        set_temp("owner", "gggw");
        set_temp("owner_name", "吖贰");
        ::setup();
}
