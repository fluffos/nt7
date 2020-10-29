// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("天之虎[2;37;0m[2;37;0m", ({"skyt"}));        
        set("gender", "女性");                
        set("long", "苍天之神兽，全身发出白色的神光···[2;37;0m
它是风小飞的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "jesse");
        set("owner_name", "风小飞");
        set_temp("owner", "jesse");
        set_temp("owner_name", "风小飞");
        ::setup();
}
