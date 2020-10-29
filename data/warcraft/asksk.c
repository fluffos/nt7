// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m小绿马[2;37;0m[2;37;0m", ({"jinju"}));        
        set("gender", "男性");                
        set("long", "一披矫健的千里马[2;37;0m
它是没影子的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "asksk");
        set("owner_name", "没影子");
        set_temp("owner", "asksk");
        set_temp("owner_name", "没影子");
        ::setup();
}
