// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("罹天火[2;37;0m[2;37;0m", ({"que"}));        
        set("gender", "男性");                
        set("long", "拈花渡影摄太虚，傲世无双罹乾坤[2;37;0m
它是剑无尘的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "longjian");
        set("owner_name", "剑无尘");
        set_temp("owner", "longjian");
        set_temp("owner_name", "剑无尘");
        ::setup();
}
