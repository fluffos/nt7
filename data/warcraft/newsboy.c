// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m叼毛兽[2;37;0m[2;37;0m", ({"dms"}));        
        set("gender", "女性");                
        set("long", "这只与时代格格不入的二次元神兽正以一副猥琐的表情痴痴地望着你[2;37;0m
它是赵日天的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "newsboy");
        set("owner_name", "赵日天");
        set_temp("owner", "newsboy");
        set_temp("owner_name", "赵日天");
        ::setup();
}
