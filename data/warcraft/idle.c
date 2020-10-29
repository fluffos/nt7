// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m张蠢龙[2;37;0m[2;37;0m", ({"lcnely"}));        
        set("gender", "男性");                
        set("long", "张椿龙大王的宠物，也不要瞎骑，小心你的JJ被它的菊给夹掉。[2;37;0m
它是张椿龙的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "idle");
        set("owner_name", "张椿龙");
        set_temp("owner", "idle");
        set_temp("owner_name", "张椿龙");
        ::setup();
}
