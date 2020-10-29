// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m千里马[2;37;0m[2;37;0m", ({"baima"}));        
        set("gender", "男性");                
        set("long", "一匹千里马[2;37;0m
它是没影儿的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "mangmang");
        set("owner_name", "没影儿");
        set_temp("owner", "mangmang");
        set_temp("owner_name", "没影儿");
        ::setup();
}
