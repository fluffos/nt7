// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m火烧云[2;37;0m[2;37;0m", ({"yun"}));        
        set("gender", "男性");                
        set("long", "$HIR$火烧云[2;37;0m
它是双鱼的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "yuyu");
        set("owner_name", "双鱼");
        set_temp("owner", "yuyu");
        set_temp("owner_name", "双鱼");
        ::setup();
}
