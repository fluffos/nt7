// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m乌云踏雪[2;37;0m[2;37;0m", ({"fggg"}));        
        set("gender", "男性");                
        set("long", "战国名驹[2;37;0m
它是欧阳风儿的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "kiki");
        set("owner_name", "欧阳风儿");
        set_temp("owner", "kiki");
        set_temp("owner_name", "欧阳风儿");
        ::setup();
}
